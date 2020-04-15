

#include "FlyWindow.h"
#include <stdio.h>

FlyWindow::FlyWindow(const char *title, int x, int y, int width, int height)
{
    this->title = title;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;

    this->event = (Event*)calloc(0, sizeof(Event));
    this->event_n = 0;
}


FlyWindow::~FlyWindow()
{
    SDL_DestroyWindow(this->window);//销毁SDL窗口
    SDL_DestroyRenderer(this->renderer->r);//销毁SDL窗口SDL渲染器
    free(this->renderer);//释放窗口渲染器
    free(this);//释放窗口
}


void FlyWindow::Create(Uint32 flags)//创建窗口
{
    this->window = SDL_CreateWindow(this->title, this->x, this->y, this->width, this->height, flags);
    this->renderer = RendererInit(this, -1, RENDERER_ACCELERATED);//初始化窗口渲染器
}

void FlyWindow::SetRenderer(FlyRenderer *renderer)//设置渲染器
{
    this->renderer = renderer;
}

/*设置渲染事件*/
void FlyWindow::SetRenderEvent(RenderEvent event)
{
    this->render_event = event;
}

/*设置鼠标移动事件*/
void FlyWindow::SetMouseMotionEvent(MouseMotionEvent event)
{
    this->mouse_motion_event = event;
}

/*设置鼠标按下事件*/
void FlyWindow::SetMouseButtonDownEvent(MouseButtonEvent event)
{
    this->mouse_button_down_event = event;
}

/*设置鼠标按键弹起事件*/
void FlyWindow::SetMouseButtonUpEvent(MouseButtonEvent event)
{
    this->mouse_button_up_event = event;
}

/*设置鼠标wheel事件*/
void FlyWindow::SetMouseWheelEvent(MouseWheelEvent event)
{
    this->mouse_wheel_event = event;
}


/*添加普通事件*/
void FlyWindow::AddEvent(Event event)
{
    this->event = (Event*)realloc(this->event, sizeof(this->event) + sizeof(event));
    this->event[this->event_n] = event;
    this->event_n++;
}




/*窗口循环*/
void FlyWindow::MainLoop()
{
    int quit = 0;//退出为假

    while (!quit)//假则循环
        quit = WebMainLoop(this);//循环

    Quit();//退出
}

/*多窗口循环*/
void WindowsMainLoop(const int window_n, ...) //window_n为窗口数量  窗口类型为 Window*
{
    int i;
    int quit = 0;                                       //退出真假
    int *destroy = (int*)calloc(window_n, sizeof(int));  //window销毁记录
    int destroy_n = 0;                                  //windows销毁数量

    FlyWindow **window = (FlyWindow**)calloc(window_n,sizeof(FlyWindow*));//各个窗口
    //SDL_Thread *window_thread[window_n];//各个窗口事件线程

    va_list window_list;//窗口列表
    va_start(window_list, window_n);

    for (i = 0; i < window_n; i++)
    {
        window[i] = va_arg(window_list, FlyWindow*);//将各个窗口取出
    }

    va_end(window_list);

    while (!quit)//未退出
    {
        for (i = 0; i < window_n; i++)
        {
            if (!destroy[i])//窗口未销毁
            {
                //window_thread[i] = SDL_CreateThread(WebMainLoop,NULL,window[i]);//创建事件窗口线程

                destroy[i] = WebMainLoop(window[i]);//执行程序循环，并取得窗口销毁与否
                if (destroy[i])//窗口被销毁
                {
                    destroy_n++;//销毁窗口数++
                }
            }
        }
        if (destroy_n == window_n)//销毁窗口数等于总窗口数
            quit = 1;//退出为真
    }

    free(destroy);//释放销毁信息

    delete[] window;//释放窗口

    Quit();//退出
}


int WebMainLoop(FlyWindow *window)
{
    int quit = 0;//退出
    SDL_Event event;//事件

    static int window_id_cache_count = 0;//要销毁的窗口的数量
    static Uint32 *window_id_cache = (Uint32*)calloc(0,sizeof(Uint32));//要销毁的窗口记录

    //printf("%d\n",window_id_cache_count);

    /*窗口销毁*/
    if (window_id_cache_count > 0)
    {
        int old_count = window_id_cache_count;
        for (int i = 0; i < window_id_cache_count; i++)
        {
            if (window_id_cache[i] == window->GetRenderer()->window_id)
            {
                window->~FlyWindow();
                for (int j = 0; j < window_id_cache_count - i; j++)
                {
                    window_id_cache[i + j] = window_id_cache[i + j + 1];
                    window_id_cache[window_id_cache_count - 1] = NULL;
                }
                window_id_cache_count--;
            }
        }
        if (old_count > window_id_cache_count)
        {
            quit = 1;//退出
            return quit;//返回窗口已销毁，函数结束
        }
    }


    if (SDL_PollEvent(&event))//获取事件
    {
        switch (event.type)//判断事件类型
        {
        case SDL_QUIT://退出事件
            SDL_Log("Program quit after %i ticks", event.quit.timestamp);
            quit = 1;//退出为真
            break;
        case SDL_USEREVENT:
            break;
        case SDL_WINDOWEVENT://窗口事件
            if (event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window->GetWindow()))//窗口关闭，且id等于执行事件的窗口
            {
                window->~FlyWindow();//销毁窗口
                quit = 1;//退出
                return quit;//返回窗口已销毁，函数结束
            }
            else if (event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID != SDL_GetWindowID(window->GetWindow()))
            {
                bool hava = false;//是否已有销毁记录
                for (int i = 0; i < window_id_cache_count; i++)
                {
                    if (window_id_cache[i] == event.window.windowID)
                        hava = true;
                }
                if (!hava)
                {
                    window_id_cache_count++;
                    window_id_cache = (Uint32*)realloc(window_id_cache,sizeof(Uint32) * window_id_cache_count);
                    window_id_cache[window_id_cache_count - 1] = event.window.windowID;
                }
                
            }
            break;
            /*鼠标事件*/
        case SDL_MOUSEMOTION:
            if (window->GetMouseMotionEvent() != NULL)
                window->GetMouseMotionEvent()(event.motion);
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (window->GetMouseButtonDownEvent() != NULL)
                window->GetMouseButtonDownEvent()(event.motion);
            break;
        case SDL_MOUSEBUTTONUP:
            if (window->GetMouseButtonUpEvent() != NULL)
                window->GetMouseButtonUpEvent()(event.motion);
            break;
        case SDL_MOUSEWHEEL:
            if (window->GetMouseWheelEvent() != NULL)
                window->GetMouseWheelEvent()(event.motion);
            break;
        }
    }

    /*获取执行事件的窗口的坐标与大小*/
    SDL_GetWindowPosition(window->GetWindow(), window->GetX(), window->GetY());
    SDL_GetWindowSize(window->GetWindow(), window->GetWidth(), window->GetWidth());


    for (int i = 0; i < window->GetEventCount(); i++)
        window->GetEvent(i)();//执行窗口所有普通事件


    RenderClear(window->GetRenderer());

    
    if (window->GetRenderEvent() != NULL)//渲染事件不为空
        window->GetRenderEvent()(window->GetRenderer());//执行窗口渲染事件
    RenderPresent(window->GetRenderer());//交换
    

    return quit;//返回程序是否结束，函数结束
}



/*退出*/
void Quit()
{
    SDL_Quit();
}



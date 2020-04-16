


#ifdef _WIN32
#include <SDL.h>
#endif // _WIN32


#ifdef __linux
#include <SDL2/SDL.h>
#endif // __linux

#include "FlyRenderer.h"

#ifndef FLYWINDOW
#define FLYWINDOW

#define WINDOWPOS_CENTERED  SDL_WINDOWPOS_CENTERED
#define WINDOWPOS_UNDEFINED SDL_WINDOWPOS_UNDEFINED

#define WINDOW_FULLSCREEN           0x00000001      /**< fullscreen window */
#define WINDOW_OPENGL               0x00000002      /**< window usable with OpenGL context */
#define WINDOW_SHOWN                0x00000004      /**< window is visible */
#define WINDOW_HIDDEN               0x00000008      /**< window is not visible */
#define WINDOW_BORDERLESS           0x00000010      /**< no window decoration */
#define WINDOW_RESIZABLE            0x00000020      /**< window can be resized */
#define WINDOW_MINIMIZED            0x00000040      /**< window is minimized */
#define WINDOW_MAXIMIZED            0x00000080      /**< window is maximized */
#define WINDOW_INPUT_GRABBED        0x00000100      /**< window has grabbed input focus */
#define WINDOW_INPUT_FOCUS          0x00000200      /**< window has input focus */
#define WINDOW_MOUSE_FOCUS          0x00000400      /**< window has mouse focus */
#define WINDOW_FULLSCREEN_DESKTOP   ( SDL_WINDOW_FULLSCREEN | 0x00001000 )
#define WINDOW_FOREIGN              0x00000800      /**< window not created by SDL */

#define WINDOW_ALLOW_HIGHDPI        0x00002000      /**< window should be created in high-DPI mode if supported. */
                                                    /**  On macOS NSHighResolutionCapable must be set true in the */
                                                    /**  application's Info.plist for this to have any effect. */

#define WINDOW_MOUSE_CAPTURE        0x00004000      /**< window has mouse captured (unrelated to INPUT_GRABBED) */
#define WINDOW_ALWAYS_ON_TOP        0x00008000      /**< window should always be above others */
#define WINDOW_SKIP_TASKBAR         0x00010000      /**< window should not be added to the taskbar */
#define WINDOW_UTILITY              0x00020000      /**< window should be treated as a utility window */
#define WINDOW_TOOLTIP              0x00040000      /**< window should be treated as a tooltip */
#define WINDOW_POPUP_MENU           0x00080000      /**< window should be treated as a popup menu */
#define WINDOW_VULKAN               0x10000000      /**< window usable for Vulkan surface */


#define MouseMotion SDL_MouseMotionEvent

typedef void(*RenderEvent)(FlyRenderer*);//渲染事件
typedef void(*Event)(void);//普通事件

typedef void(*MouseMotionEvent)(MouseMotion);//
typedef void(*MouseButtonEvent)(MouseMotion);//鼠标按钮事件
typedef void(*MouseWheelEvent)(MouseMotion);//

class FlyWindow
{
private:
    const char *title;

    int x, y;
    int width, height;

    SDL_Window *window;
    FlyRenderer *renderer;

    int event_n = 0;
    Event *event = NULL;

    RenderEvent render_event = NULL;

    MouseMotionEvent mouse_motion_event = NULL;
    MouseButtonEvent mouse_button_down_event = NULL;
    MouseButtonEvent mouse_button_up_event = NULL;
    MouseWheelEvent mouse_wheel_event = NULL;

public:
    FlyWindow(const char *title, int x = WINDOWPOS_CENTERED, int y = WINDOWPOS_CENTERED, int width = 800, int height = 600);
    ~FlyWindow();

    void Create(Uint32 flags);//创建窗口

    const char* GetTitle() { return this->title; }
    int *GetX() { return &this->x; }
    int *GetY() { return &this->y; }
    int *GetWidth() { return &this->width; }
    int *GetHeight() { return &this->height; }

    Uint32 GetWindowID() { return SDL_GetWindowID(this->window); }

    SDL_Window *GetWindow() { return this->window; }
    FlyRenderer *GetRenderer() { return this->renderer; }

    int GetEventCount() { return this->event_n; }
    Event GetEvent(int index) { return this->event[index]; }

    RenderEvent GetRenderEvent() { return this->render_event; }

    MouseMotionEvent GetMouseMotionEvent() { return this->mouse_motion_event; }
    MouseButtonEvent GetMouseButtonDownEvent() { return this->mouse_button_down_event; }
    MouseButtonEvent GetMouseButtonUpEvent() { return this->mouse_button_up_event; }
    MouseWheelEvent GetMouseWheelEvent() { return this->mouse_wheel_event; }

    void SetRenderer(FlyRenderer*);//设置窗口渲染器
    void SetBackGroundColor(Uint8, Uint8, Uint8, Uint8);//设置窗口背景颜色

    /*设置窗口各种事件*/
    void SetRenderEvent(RenderEvent);//设置窗口渲染事件

    void SetMouseMotionEvent(MouseMotionEvent);//
    void SetMouseButtonDownEvent(MouseButtonEvent);
    void SetMouseButtonUpEvent(MouseButtonEvent);
    void SetMouseWheelEvent(MouseWheelEvent);

    /*添加普通事件*/
    void AddEvent(Event);

    /*窗口循环*/
    void MainLoop();
};






/*多窗口循环*/
void WindowsMainLoop(const int window_n, ...);


int WebMainLoop(FlyWindow *window);

/*退出*/
void Quit();



#endif






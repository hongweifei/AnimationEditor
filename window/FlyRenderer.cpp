

#include "FlyRenderer.h"
#include "FlyWindow.h"

#include <stdio.h>
#include <string.h>

/*
#ifdef _cplusplus
extern "C" {
#endif // _cplusplus


    FlyRenderer* RendererInit(FlyWindow* window, int index, Uint32 flags)//渲染器初始化
    {
        FlyRenderer* renderer = (FlyRenderer*)calloc(1, sizeof(FlyRenderer));
        renderer->r = SDL_CreateRenderer(window->GetWindow(), index, flags);//创建SDL渲染器
        renderer->window_id = SDL_GetWindowID(window->GetWindow());//获取窗口id
        return renderer;
    }

    //设置渲染颜色
    int SetRenderDrawColor(FlyRenderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a) { return SDL_SetRenderDrawColor(renderer->r, r, g, b, a); }

    //用渲染颜色清空
    int RenderClear(FlyRenderer* renderer) { return SDL_RenderClear(renderer->r); }
    //交换
    void RenderPresent(FlyRenderer* renderer) { SDL_RenderPresent(renderer->r); }

    int RenderCopy(FlyRenderer* renderer, SDL_Texture* texture, SDL_Rect* src_rect, SDL_Rect* dest_rect)
    {
        return SDL_RenderCopy(renderer->r, texture, src_rect, dest_rect);
    }




#ifdef _cplusplus
}
#endif // _cplusplus


*/



FlyRenderer::FlyRenderer(FlyWindow *window, Uint32 flags)
{
    //static int index = 0;

    this->renderer = SDL_CreateRenderer(window->GetWindow(), -1, flags);//创建SDL渲染器
    this->window_id = SDL_GetWindowID(window->GetWindow());//获取窗口id

    //index++;
}

FlyRenderer::~FlyRenderer()
{
    SDL_DestroyRenderer(this->renderer);//销毁SDL渲染器
    free(this);
}

/*设置渲染颜色*/
int FlyRenderer::SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    return SDL_SetRenderDrawColor(this->renderer, r, g, b, a);
}

/*清空*/
int FlyRenderer::Clear()
{
    return SDL_RenderClear(this->renderer);
}



int FlyRenderer::Flush()
{
    return SDL_RenderFlush(this->renderer);
}


/*交换*/
void FlyRenderer::Present()
{
    SDL_RenderPresent(this->renderer);
}


/*绘制一条线*/
int FlyRenderer::DrawLine(int x1,int y1,int x2,int y2)
{
    return SDL_RenderDrawLine(this->renderer,x1,y1,x2,y2);
}

/*绘制n条线*/
int FlyRenderer::DrawLines(const SDL_Point *points,int count)
{
    return SDL_RenderDrawLines(this->renderer, points,count);
}







/*绘制一条线*/
int FlyRenderer::DrawLineF(float x1, float y1, float x2, float y2)
{
    return SDL_RenderDrawLineF(this->renderer,x1,y1,x2,y2);
}

/*绘制n条线*/
int FlyRenderer::DrawLinesF(const SDL_FPoint *points, int count)
{
    return SDL_RenderDrawLinesF(this->renderer, points, count);
}


/*绘制点*/
int FlyRenderer::DrawPoint(int x,int y)
{
    return SDL_RenderDrawPoint(this->renderer,x,y);
}


/*绘制点*/
int FlyRenderer::DrawPoints(const SDL_Point *points, int count)
{
    return SDL_RenderDrawPoints(this->renderer, points, count);
}






/*绘制点*/
int FlyRenderer::DrawPointF(float x, float y)
{
    return SDL_RenderDrawPointF(this->renderer, x, y);
}

/*绘制点*/
int FlyRenderer::DrawPointsF(const SDL_FPoint *points, int count)
{
    return SDL_RenderDrawPointsF(this->renderer, points, count);
}


/*
/*绘制矩形
int FlyRenderer::DrawRect(const SDL_Rect rect)
{
    return SDL_RenderDrawRect(this->renderer, &rect);
}
*/

/*绘制矩形*/
int FlyRenderer::DrawRect(const SDL_Rect *rect)
{
    return SDL_RenderDrawRect(this->renderer, rect);
}

/*绘制矩形*/
int FlyRenderer::DrawRects(const SDL_Rect *rects,int count)
{
    return SDL_RenderDrawRects(this->renderer, rects, count);
}





/*
/*绘制矩形
int FlyRenderer::DrawRectF(const SDL_FRect rect)
{
    return SDL_RenderDrawRectF(this->renderer, &rect);
}
*/

/*绘制矩形*/
int FlyRenderer::DrawRectF(const SDL_FRect *rect)
{
    return SDL_RenderDrawRectF(this->renderer, rect);
}

/*绘制矩形*/
int FlyRenderer::DrawRectsF(const SDL_FRect *rects,int count)
{
    return SDL_RenderDrawRectsF(this->renderer, rects, count);
}

/*
/*绘制矩形
int FlyRenderer::DrawFillRect(const SDL_Rect rect)
{
    return SDL_RenderFillRect(this->renderer, &rect);
}
*/

/*绘制矩形*/
int FlyRenderer::DrawFillRect(const SDL_Rect *rect)
{
    return SDL_RenderFillRect(this->renderer, rect);
}

/*绘制矩形*/
int FlyRenderer::DrawFillRects(const SDL_Rect *rects, int count)
{
    return SDL_RenderFillRects(this->renderer, rects, count);
}





/*
/*绘制矩形
int FlyRenderer::DrawFillRectF(const SDL_FRect rect)
{
    return SDL_RenderFillRectF(this->renderer, &rect);
}
*/

/*绘制矩形*/
int FlyRenderer::DrawFillRectF(const SDL_FRect *rect)
{
    return SDL_RenderFillRectF(this->renderer, rect);
}

/*绘制矩形*/
int FlyRenderer::DrawFillRectsF(const SDL_FRect *rects, int count)
{
    return SDL_RenderFillRectsF(this->renderer, rects, count);
}

/*
/*绘制BMP图像
int FlyRenderer::DrawImageBMP(const char *path, const SDL_Rect rect)
{
    return this->DrawImageBMP(path, &rect);
}
*/

/*绘制BMP图像*/
int FlyRenderer::DrawImageBMP(const char *path, const SDL_Rect *rect)
{
    static int count = 0;
    static char** cache_path = (char**)calloc(0, sizeof(char*));
    static SDL_Surface* surface = NULL;
    static SDL_Texture** texture = (SDL_Texture**)calloc(count, sizeof(SDL_Texture*));

    static int draw_index = count;


    for (int i = 0; i < count; i++)
    {
        if (cache_path[i] == path)
        {
            draw_index = i;
            goto draw;
        }
    }

    cache_path = (char**)realloc(cache_path, sizeof(char*) * (count + 1));
    cache_path[count] = (char*)path;

    surface = SDL_LoadBMP(cache_path[count]);
    if (surface == NULL)
    {
        fprintf(stderr, "CreateSurface failed: %s\n", SDL_GetError());
        return -1;
    }

    texture = (SDL_Texture**)calloc(count + 1, sizeof(SDL_Texture*));
    texture[count] = SDL_CreateTextureFromSurface(this->renderer, surface);
    if (texture[count] == NULL)
    {
        fprintf(stderr, "CreateTextureFromSurface failed: %s\n", SDL_GetError());
        return -1;
    }

    SDL_FreeSurface(surface);
    surface = NULL;

    count++;
    draw_index = count - 1;

draw:
    return this->DrawTexture(texture[draw_index],rect);

}

/*绘制BMP图像*/
int FlyRenderer::DrawImageBMP(const char* path, int x, int y, int width, int height)
{
    
    static int count = 0;
    static SDL_Rect *rect = (SDL_Rect*)calloc(0,sizeof(SDL_Rect));
    static const char** cache_path = (const char**)calloc(0, sizeof(char*));

    static int draw_index = count;

    for (int i = 0; i < count; i++)
    {
        if (cache_path[i] == path)
        {
            draw_index = i;
            goto draw;
        }
    }

    cache_path = (const char**)realloc(cache_path, (count + 1) * sizeof(char*));
    cache_path[count] = path;

    rect = (SDL_Rect*)realloc(rect, sizeof(SDL_Rect) * (count + 1));
    rect[count] = { x,y,width,height };

    count++;
    draw_index = count - 1;

draw:
    return this->DrawImageBMP(path, &rect[draw_index]);
    

    //SDL_Rect rect = {x,y,width,height};
    //return this->DrawImageBMP(path, &rect);
}




/*
/*绘制BMP图像
int FlyRenderer::DrawImageBMP(const char* path, const SDL_FRect rect)
{
    return this->DrawImageBMP(path, &rect);
}
*/

/*绘制BMP图像*/
int FlyRenderer::DrawImageBMP(const char* path, const SDL_FRect* rect)
{
    static int count = 0;
    static const char** cache_path = (const char**)calloc(0, sizeof(char*));
    static SDL_Surface* surface = NULL;
    static SDL_Texture** texture = (SDL_Texture**)calloc(count, sizeof(SDL_Texture*));

    static int draw_index = count;


    for (int i = 0; i < count; i++)
    {
        if (strcmp(cache_path[i], path) == 0)
        {
            draw_index = i;
            goto draw;
        }
    }

    cache_path = (const char**)realloc(cache_path, sizeof(char*) * (count + 1));
    cache_path[count] = path;

    surface = SDL_LoadBMP(cache_path[count]);
    if (surface == NULL)
    {
        fprintf(stderr, "CreateSurface failed: %s\n", SDL_GetError());
        return -1;
    }

    texture = (SDL_Texture**)calloc(count + 1, sizeof(SDL_Texture*));
    texture[count] = SDL_CreateTextureFromSurface(this->renderer, surface);
    if (texture[count] == NULL)
    {
        fprintf(stderr, "CreateTextureFromSurface failed: %s\n", SDL_GetError());
        return -1;
    }

    SDL_FreeSurface(surface);
    surface = NULL;

    count++;
    draw_index = count - 1;

draw:
    return this->DrawTextureF(texture[draw_index], rect);

}

/*绘制BMP图像*/
int FlyRenderer::DrawImageBMP(const char* path, float x, float y, float width, float height)
{
    SDL_FRect rect = { x,y,width,height };
    return this->DrawImageBMP(path, &rect);
}








/*绘制纹理，不可翻转*/
int FlyRenderer::DrawTexture(SDL_Texture* texture)
{
    return SDL_RenderCopy(this->renderer, texture, NULL, NULL);
}


/*绘制纹理，可翻转*/
int FlyRenderer::DrawTexture(SDL_Texture* texture,const RendererFlip flip)
{
    return SDL_RenderCopyEx(this->renderer, texture, NULL, NULL,0,NULL,(SDL_RendererFlip)flip);
}









/*
/*绘制纹理，不可翻转
int FlyRenderer::DrawTexture(SDL_Texture* texture, const SDL_Rect dest_rect)
{
    return SDL_RenderCopy(this->renderer, texture, NULL, &dest_rect);
}
*/


/*绘制纹理，不可翻转*/
int FlyRenderer::DrawTexture(SDL_Texture* texture, const SDL_Rect *dest_rect)
{
    return SDL_RenderCopy(this->renderer, texture, NULL, dest_rect);
}





/*
/*绘制纹理，不可翻转
int FlyRenderer::DrawTextureF(SDL_Texture* texture, const SDL_FRect dest_rect)
{
    return SDL_RenderCopyF(this->renderer, texture, NULL, &dest_rect);
}
*/

/*绘制纹理，不可翻转*/
int FlyRenderer::DrawTextureF(SDL_Texture* texture, const SDL_FRect *dest_rect)
{
    return SDL_RenderCopyF(this->renderer, texture, NULL, dest_rect);
}







/*
/*绘制纹理,可翻转
int FlyRenderer::DrawTexture(SDL_Texture* texture, const SDL_Rect dest_rect, const RendererFlip flip)
{
    return SDL_RenderCopyEx(this->renderer, texture,NULL, &dest_rect, 0, NULL, (SDL_RendererFlip)flip);
}
*/

/*绘制纹理,可翻转*/
int FlyRenderer::DrawTexture(SDL_Texture* texture, const SDL_Rect* dest_rect, const RendererFlip flip)
{
    return SDL_RenderCopyEx(this->renderer, texture, NULL, dest_rect, 0, NULL, (SDL_RendererFlip)flip);
}





/*
/*绘制纹理,可翻转
int FlyRenderer::DrawTextureF(SDL_Texture* texture, const SDL_FRect dest_rect, const RendererFlip flip)
{
    return SDL_RenderCopyExF(this->renderer, texture, NULL, &dest_rect, 0, NULL, (SDL_RendererFlip)flip);
}
*/

/*绘制纹理,可翻转*/
int FlyRenderer::DrawTextureF(SDL_Texture* texture, const SDL_FRect* dest_rect, const RendererFlip flip)
{
    return SDL_RenderCopyExF(this->renderer, texture, NULL, dest_rect, 0, NULL, (SDL_RendererFlip)flip);
}









/*
/*绘制纹理,可翻转
int FlyRenderer::DrawTexture(SDL_Texture* texture, const SDL_Rect dest_rect, double angle, const RendererFlip flip)
{
    return SDL_RenderCopyEx(this->renderer, texture, NULL, &dest_rect, angle, NULL, (SDL_RendererFlip)flip);
}
*/

/*绘制纹理,可翻转*/
int FlyRenderer::DrawTexture(SDL_Texture* texture, const SDL_Rect* dest_rect, double angle, const RendererFlip flip)
{
    return SDL_RenderCopyEx(this->renderer, texture, NULL, dest_rect, angle, NULL, (SDL_RendererFlip)flip);
}





/*
/*绘制纹理,可翻转
int FlyRenderer::DrawTextureF(SDL_Texture* texture, const SDL_FRect dest_rect, double angle, const RendererFlip flip)
{
    return SDL_RenderCopyExF(this->renderer, texture, NULL, &dest_rect, angle, NULL, (SDL_RendererFlip)flip);
}
*/

/*绘制纹理,可翻转*/
int FlyRenderer::DrawTextureF(SDL_Texture* texture, const SDL_FRect* dest_rect, double angle, const RendererFlip flip)
{
    return SDL_RenderCopyExF(this->renderer, texture, NULL, dest_rect, angle, NULL, (SDL_RendererFlip)flip);
}











/*
/*绘制纹理，不可翻转
int FlyRenderer::DrawTexture(SDL_Texture *texture, const SDL_Rect src_rect, const SDL_Rect dest_rect)
{
    return SDL_RenderCopy(this->renderer, texture, &src_rect, &dest_rect);
}
*/

/*绘制纹理，不可翻转*/
int FlyRenderer::DrawTexture(SDL_Texture *texture, const SDL_Rect *src_rect, const SDL_Rect *dest_rect)
{
    return SDL_RenderCopy(this->renderer, texture, src_rect, dest_rect);
}




/*
/*绘制纹理，不可翻转
int FlyRenderer::DrawTextureF(SDL_Texture *texture, const SDL_Rect src_rect, const SDL_FRect dest_rect)
{
    return SDL_RenderCopyF(this->renderer, texture, &src_rect, &dest_rect);
}
*/

/*绘制纹理，不可翻转*/
int FlyRenderer::DrawTextureF(SDL_Texture *texture, const SDL_Rect *src_rect, const SDL_FRect *dest_rect)
{
    return SDL_RenderCopyF(this->renderer, texture, src_rect, dest_rect);
}










/*
/*绘制纹理,可翻转
int FlyRenderer::DrawTexture(SDL_Texture* texture, const SDL_Rect src_rect, const SDL_Rect dest_rect, const RendererFlip flip)
{
    return SDL_RenderCopyEx(this->renderer, texture, &src_rect, &dest_rect,0,NULL,(SDL_RendererFlip)flip);
}
*/

/*绘制纹理,可翻转*/
int FlyRenderer::DrawTexture(SDL_Texture* texture, const SDL_Rect* src_rect, const SDL_Rect* dest_rect, const RendererFlip flip)
{
    return SDL_RenderCopyEx(this->renderer, texture, src_rect, dest_rect,0,NULL,(SDL_RendererFlip)flip);
}


/*
/*绘制纹理,可翻转
int FlyRenderer::DrawTextureF(SDL_Texture* texture, const SDL_Rect src_rect, const SDL_FRect dest_rect, const RendererFlip flip)
{
    return SDL_RenderCopyExF(this->renderer, texture, &src_rect, &dest_rect, 0, NULL, (SDL_RendererFlip)flip);
}
*/

/*绘制纹理,可翻转*/
int FlyRenderer::DrawTextureF(SDL_Texture* texture, const SDL_Rect* src_rect, const SDL_FRect* dest_rect, const RendererFlip flip)
{
    return SDL_RenderCopyExF(this->renderer, texture, src_rect, dest_rect, 0, NULL, (SDL_RendererFlip)flip);
}










/*
/*绘制纹理,可翻转
int FlyRenderer::DrawTexture(SDL_Texture* texture, const SDL_Rect src_rect, const SDL_Rect dest_rect, double angle, const RendererFlip flip)
{
    return SDL_RenderCopyEx(this->renderer, texture, &src_rect, &dest_rect, angle, NULL, (SDL_RendererFlip)flip);
}
*/

/*绘制纹理,可翻转*/
int FlyRenderer::DrawTexture(SDL_Texture* texture, const SDL_Rect* src_rect, const SDL_Rect* dest_rect, double angle, const RendererFlip flip)
{
    return SDL_RenderCopyEx(this->renderer, texture, src_rect, dest_rect, angle, NULL, (SDL_RendererFlip)flip);
}


/*
/*绘制纹理,可翻转
int FlyRenderer::DrawTextureF(SDL_Texture* texture, const SDL_Rect src_rect, const SDL_FRect dest_rect, double angle, const RendererFlip flip)
{
    return SDL_RenderCopyExF(this->renderer, texture, &src_rect, &dest_rect, angle, NULL, (SDL_RendererFlip)flip);
}
*/

/*绘制纹理,可翻转*/
int FlyRenderer::DrawTextureF(SDL_Texture* texture, const SDL_Rect* src_rect, const SDL_FRect* dest_rect, double angle, const RendererFlip flip)
{
    return SDL_RenderCopyExF(this->renderer, texture, src_rect, dest_rect, angle, NULL, (SDL_RendererFlip)flip);
}








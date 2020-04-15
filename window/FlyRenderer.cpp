

#include "FlyRenderer.h"
#include "FlyWindow.h"

FlyRenderer *RendererInit(FlyWindow *window, int index, Uint32 flags)//渲染器初始化
{
    FlyRenderer* renderer = (FlyRenderer*)calloc(1, sizeof(FlyRenderer));
    renderer->r = SDL_CreateRenderer(window->GetWindow(), index, flags);//创建SDL渲染器
    renderer->window_id = SDL_GetWindowID(window->GetWindow());//获取窗口id
    return renderer;
}

//设置渲染颜色
int SetRenderDrawColor(FlyRenderer *renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a) { return SDL_SetRenderDrawColor(renderer->r, r, g, b, a); }

//用渲染颜色清空
int RenderClear(FlyRenderer *renderer) { return SDL_RenderClear(renderer->r); }
//交换
void RenderPresent(FlyRenderer *renderer) { SDL_RenderPresent(renderer->r); }

int RenderCopy(FlyRenderer *renderer, SDL_Texture *texture, SDL_Rect *src_rect, SDL_Rect *dest_rect)
{
    return SDL_RenderCopy(renderer->r, texture, src_rect, dest_rect);
}


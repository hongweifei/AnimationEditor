

#ifdef _WIN32
#include <SDL.h>
#endif // _WIN32

#ifdef __linux
#include <SDL2/SDL.h>
#endif // __linux

#ifndef RENDERER
#define RENDERER

#define RENDERER_SOFTWARE       SDL_RENDERER_SOFTWARE       //the renderer is a software fallback
#define RENDERER_ACCELERATED    SDL_RENDERER_ACCELERATED    //the renderer uses hardware acceleration
#define RENDERER_PRESENTVSYNC   SDL_RENDERER_PRESENTVSYNC   //present is synchronized with the refresh rate
#define RENDERER_TARGETTEXTURE  SDL_RENDERER_TARGETTEXTURE  //the renderer supports rendering to texture

extern class FlyWindow;

typedef struct
{
    SDL_Renderer *r;
    Uint32 window_id;
}FlyRenderer;

FlyRenderer *RendererInit(FlyWindow *window, int index, Uint32 flags);//初始化

int SetRenderDrawColor(FlyRenderer *renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);//设置颜色


int RenderClear(FlyRenderer *renderer);//清空
void RenderPresent(FlyRenderer *renderer);//交换

int RenderCopy(FlyRenderer *renderer, SDL_Texture *texture, SDL_Rect *src_rect, SDL_Rect *dest_rect);


#endif

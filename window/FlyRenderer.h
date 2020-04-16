

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

typedef enum
{
    FLIP_NONE = 0x00000000,         /**< Do not flip */
    FLIP_HORIZONTAL = 0x00000001,   /**< flip horizontally */
    FLIP_VERTICAL = 0x00000002      /**< flip vertically */
}RendererFlip;

extern class FlyWindow;

/*

#ifdef _cplusplus
extern "C" {
#endif // _cplusplus


    typedef struct
    {
        SDL_Renderer *r;
        Uint32 window_id;
    }FlyRenderer;

    FlyRenderer *RendererInit(FlyWindow* window, int index, Uint32 flags);//初始化

    int SetRenderDrawColor(FlyRenderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);//设置颜色


    int RenderClear(FlyRenderer *renderer);//清空
    void RenderPresent(FlyRenderer *renderer);//交换

    int RenderCopy(FlyRenderer *renderer, SDL_Texture *texture, SDL_Rect *src_rect, SDL_Rect *dest_rect);



#ifdef _cplusplus
}
#endif // _cplusplus

*/



class FlyRenderer
{
public:
    FlyRenderer(FlyWindow*, Uint32);
	~FlyRenderer();

    SDL_Renderer* GetRenderer() { return this->renderer; }
    Uint32 GetWindowID() { return this->window_id; }

    int SetDrawColor(Uint8, Uint8, Uint8, Uint8);

    int Clear();//清空
    int Flush();
    void Present();//交换

    int DrawLine(int,int,int,int);
    int DrawLines(const SDL_Point*,int);

    int DrawLineF(float, float, float, float);
    int DrawLinesF(const SDL_FPoint*, int);

    int DrawPoint(int,int);
    int DrawPoints(const SDL_Point*, int);

    int DrawPointF(float, float);
    int DrawPointsF(const SDL_FPoint*, int);

    //int DrawRect(const SDL_Rect);
    int DrawRect(const SDL_Rect*);
    int DrawRects(const SDL_Rect*,int);

    //int DrawRectF(const SDL_FRect);
    int DrawRectF(const SDL_FRect*);
    int DrawRectsF(const SDL_FRect*,int);

    //int DrawFillRect(const SDL_Rect);
    int DrawFillRect(const SDL_Rect*);
    int DrawFillRects(const SDL_Rect*, int);

    //int DrawFillRectF(const SDL_FRect);
    int DrawFillRectF(const SDL_FRect*);
    int DrawFillRectsF(const SDL_FRect*, int);


    /*绘制bmp，坐标使用整数*/
    //int DrawImageBMP(const char*, const SDL_Rect);
    int DrawImageBMP(const char*, const SDL_Rect*);
    int DrawImageBMP(const char*, int, int, int, int);


    /*绘制bmp，坐标使用浮点数*/
    //int DrawImageBMP(const char*, const SDL_FRect);
    int DrawImageBMP(const char*, const SDL_FRect*);
    int DrawImageBMP(const char*, float, float, float, float);


    /*绘制纹理，不可翻转*/
    int DrawTexture(SDL_Texture*);

    /*绘制纹理，可翻转*/
    int DrawTexture(SDL_Texture*, const RendererFlip);


    /*绘制纹理，不可翻转*/
    //int DrawTexture(SDL_Texture*,const SDL_Rect);
    int DrawTexture(SDL_Texture*, const SDL_Rect*);
    //int DrawTextureF(SDL_Texture*, const SDL_FRect);
    int DrawTextureF(SDL_Texture*, const SDL_FRect*);


    /*绘制纹理，可翻转*/
    //int DrawTexture(SDL_Texture*, const SDL_Rect, const RendererFlip);
    int DrawTexture(SDL_Texture*, const SDL_Rect*, const RendererFlip);
    //int DrawTextureF(SDL_Texture*, const SDL_FRect, const RendererFlip);
    int DrawTextureF(SDL_Texture*, const SDL_FRect*, const RendererFlip);


    /*绘制纹理，可翻转，可旋转图片*/
    //int DrawTexture(SDL_Texture*, const SDL_Rect, double, const RendererFlip = FLIP_NONE);
    int DrawTexture(SDL_Texture*, const SDL_Rect*, double, const RendererFlip = FLIP_NONE);
    //int DrawTextureF(SDL_Texture*, const SDL_FRect, double, const RendererFlip = FLIP_NONE);
    int DrawTextureF(SDL_Texture*, const SDL_FRect*, double ,const RendererFlip = FLIP_NONE);


    /*绘制纹理，不可翻转，可裁剪源图片*/
    //int DrawTexture(SDL_Texture*, const SDL_Rect, const SDL_Rect);
    int DrawTexture(SDL_Texture*, const SDL_Rect*, const SDL_Rect*);
    //int DrawTextureF(SDL_Texture*, const SDL_Rect, const SDL_FRect);
    int DrawTextureF(SDL_Texture*, const SDL_Rect*, const SDL_FRect*);


    /*绘制纹理，可翻转，可裁剪源图片*/
    //int DrawTexture(SDL_Texture*, const SDL_Rect, const SDL_Rect, const RendererFlip);
    int DrawTexture(SDL_Texture*, const SDL_Rect*, const SDL_Rect*, const RendererFlip);
    //int DrawTextureF(SDL_Texture*, const SDL_Rect, const SDL_FRect, const RendererFlip);
    int DrawTextureF(SDL_Texture*, const SDL_Rect*, const SDL_FRect*, const RendererFlip);


    /*绘制纹理，可翻转，可旋转图片，可裁剪源图片*/
    //int DrawTexture(SDL_Texture*, const SDL_Rect, const SDL_Rect, double, const RendererFlip = FLIP_NONE);
    int DrawTexture(SDL_Texture*, const SDL_Rect*, const SDL_Rect*, double, const RendererFlip = FLIP_NONE);
    //int DrawTextureF(SDL_Texture*, const SDL_Rect, const SDL_FRect, double, const RendererFlip = FLIP_NONE);
    int DrawTextureF(SDL_Texture*, const SDL_Rect*, const SDL_FRect*, double, const RendererFlip = FLIP_NONE);
private:
    SDL_Renderer *renderer;
    Uint32 window_id;
};




#endif





#ifdef _WIN32
#include <SDL.h>
#endif // _WIN32

#ifdef __linux
#include <SDL2/SDL.h>
#endif // __linux

#undef main

#ifndef SYSTEM_HEAD
#define SYSTEM_HEAD

#define INIT_TIMER          SDL_INIT_TIMER
#define INIT_AUDIO          SDL_INIT_AUDIO
#define INIT_VIDEO          SDL_INIT_VIDEO
#define INIT_JOYSTICK       SDL_INIT_JOYSTICK
#define INIT_HAPTIC         SDL_INIT_HAPTIC
#define INIT_GAMECONTROLLER SDL_INIT_GAMECONTROLLER
#define INIT_EVENTS         SDL_INIT_EVENTS
#define INIT_EVERYTHING     SDL_INIT_EVERYTHING
#define INIT_NOPARACHUTE    SDL_INIT_NOPARACHUTE

int SystemInit(Uint32 flags);//初始化各项功能


#endif // !SYSTEM_HEAD
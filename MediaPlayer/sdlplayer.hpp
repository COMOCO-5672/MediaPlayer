#ifndef SDLPLAYER_H
#define SDLPLAYER_H

#include "SDL_hints.h"
#include "SDL_render.h"
#include "SDL_video.h"
#include <mutex>

struct SDL_Window;
struct SDL_Texture;
struct SDL_Renderer;
union SDL_Event;

class sdlplayer {
  private:
    void *m_pUserData_;
    std::recursive_mutex m_openMtx_;
    SDL_Window *m_sWindow_ = nullptr;
    SDL_Texture *m_sTextture_ = nullptr;  // SDL texture
    SDL_Renderer *m_sRenderer_ = nullptr; // SDL renderer
    SDL_Event *m_sEvent_ = nullptr;       // SDL事件，用于退出等操作
    unsigned int m_iHeight_;
    unsigned int m_iWidth_;
    unsigned int m_iRenderCount_;

  public:
    sdlplayer(void *userdata);
    ~sdlplayer();

    int open(const char *title, int x, int y, int width, int height);
    int close();

    int update(const char *yuv, int width, int height);
};

sdlplayer::sdlplayer(void *userdata) { m_pUserData_ = userdata; }

int sdlplayer::open(const char *title, int x, int y, int width, int height)
{
    std::lock_guard<std::recursive_mutex> lock(m_openMtx_);
    int flags = SDL_WINDOW_SHOWN;

    m_iHeight_ = height;
    m_iWidth_ = width;
    m_iRenderCount_ = 0;
    m_sWindow_ = nullptr;
    m_sTextture_ = nullptr;
    m_sRenderer_ = nullptr;
    m_sEvent_ = nullptr;

    flags |= SDL_WINDOW_RESIZABLE;

    if (!m_sWindow_) {
        m_sWindow_ = SDL_CreateWindow(title, x, y, m_iWidth_, m_iHeight_, flags);
        if (!m_sWindow_) {
            printf("In Sdlplayer.open: create window failed.\n");
            return -1;
        }
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        m_sRenderer_ = SDL_CreateRenderer(m_sWindow_, -1,
                                          SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (!m_sRenderer_) {
            if (!m_sRenderer_) {
                printf("Failed to initialize a hardware accelerated renderer: %s\n",
                       SDL_GetError());
                m_sRenderer_ = SDL_CreateRenderer(m_sWindow_, -1, 0);
            }
            if (!m_sRenderer_) {
                printf("In SdlPlayer.open: create renderer failed. \n");
                SDL_DestroyWindow(m_sWindow_);
                m_sWindow_ = nullptr;
                return -2;
            }
        }
        m_sTextture_ = nullptr;
        m_sEvent_ = (SDL_Event *)malloc(sizeof(SDL_Event));
        if (!m_sEvent_) {
            printf("In SdlPlayer.open: malloc m_event failed. \n");
            SDL_DestroyWindow(m_sRenderer_);
            m_sRenderer_ = nullptr;
            SDL_DestroyWindow(m_sWindow_);
            m_sWindow_ = nullptr;
            return -3;
        }
    }

    return 1;
}

sdlplayer::~sdlplayer() {}

#endif
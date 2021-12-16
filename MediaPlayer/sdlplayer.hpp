#ifndef SDLPLAYER_H
#define SDLPLAYER_H

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
    SDL_Texture *m_sTextture = nullptr;
    SDL_Renderer *m_sRender = nullptr;
    SDL_Event *m_sEvent = nullptr;
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

    return 1;
}

sdlplayer::~sdlplayer() {}

#endif
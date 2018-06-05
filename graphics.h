#ifndef __T_GRAPHICS__
#define __T_GRAPHICS__

#include <list>
#include <stack>
#include <string>

#include <SDL2/SDL.h>

#include "callback.h"

using namespace std;

class GameGraphics {
    private:
        SDL_Window* window = NULL;
        SDL_GLContext context = NULL;

        string program_name;

        Uint32 width = 1024;
        Uint32 height = 768;

        TCallbackHandler cb_handler;

    public:
        GameGraphics();
        ~GameGraphics();

        int init();
        void finalize();
        void setProgramName(string name);
        void setWindowDimension(Uint32 width, Uint32 height);

        TCallbackHandler* getHandler();

        SDL_Window* getWindow();
        SDL_GLContext getContext();

        void render();
};

#endif

#ifndef __E_MAINLOOP
#define __E_MAINLOOP

#include <SDL2/SDL.h>

class GameLoop {
    private:
        Uint32 update_frequency = 25;
        Uint32 maxskip = 10;
        Uint32 maxfps = 250;

        bool running = false;

        int loop();
        void update();
        void render();

    public:
        GameLoop();
        ~GameLoop();

        int start();

};


#endif

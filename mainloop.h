#ifndef __E_MAINLOOP
#define __E_MAINLOOP

#include <SDL2/SDL.h>
#include <list>
#include <stack>
#include <string>

#include "callback.h"

using namespace std;

class GameLoop {
    private:
        Uint32 update_frequency = 25;
        Uint32 maxskip = 10;
        Uint32 maxfps = 250;

        bool running = false;

        void* cb_data;
        list<TCallback> callbacks;
        stack<list<TCallback>::iterator> pending_remove;
        Uint32 last_cb_id = 0;

        int loop();
        void update();
        void render();

        TCallbackHandler cb_handler;

    public:
        GameLoop();
        ~GameLoop();

        int start();
        void stop();

        TCallbackHandler* getHandler();
};


#endif

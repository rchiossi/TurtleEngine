#ifndef __E_MAINLOOP
#define __E_MAINLOOP

#include <SDL2/SDL.h>
#include <list>
#include <stack>
#include <string>

using namespace std;

struct TCallback;

typedef int (*t_callback) (const TCallback&, void*);

struct TCallback {
    const Uint32 id;
    const string name;

    t_callback cb;
};

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

    public:
        GameLoop();
        ~GameLoop();

        int start();
        void stop();

        void setData(void *data);
        int registerCallback(string name, t_callback cb);
        bool removeCallback(Uint32 id);
};


#endif

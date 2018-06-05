#include <iostream>

#include "callback.h"
#include "mainloop.h"

using namespace std;

struct GameData {
    GameLoop* gameloop;
};

int test_cb(const TCallback& cb, void* data) {
    static int count = 0;
    GameData* gdata = static_cast<GameData*>(data);

    cout << "Run count: " << count << endl;

    count++;

    if (count >= 50) {
        TCallbackHandler* handler = gdata->gameloop->getHandler();
        handler->removeCallback(cb.id);
        cout << "Callback removed" << endl;

        gdata->gameloop->stop();
        cout << "Program Stopped" << endl;
    }


    return 0;
}

int main(int argc, char* argv[]) {
    GameLoop* gameloop = new GameLoop();

    GameData data;
    data.gameloop = gameloop;

    TCallbackHandler* handler = gameloop->getHandler();

    handler->setData(&data);
    handler->registerCallback("Test Callback", test_cb);

    gameloop->start();

    delete gameloop;

    return 0;
}

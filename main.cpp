#include <iostream>

#include "callback.h"
#include "graphics.h"
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
    GameGraphics* graphics = new GameGraphics();

    GameData data;
    data.gameloop = gameloop;

    TCallbackHandler* handler = gameloop->getHandler();

    handler->setData(&data);
    handler->registerCallback("Test Callback", test_cb);

    graphics->setProgramName("TestProgram");
    graphics->setWindowDimension(640, 480);
    graphics->init();

    gameloop->setGraphics(graphics);

    gameloop->start();

    graphics->finalize();

    delete graphics;
    delete gameloop;

    return 0;
}

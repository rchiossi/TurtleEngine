#include <iostream>

#include <GL/glew.h>

#include "callback.h"
#include "graphics.h"
#include "mainloop.h"

using namespace std;

struct GameData {
    GameLoop* gameloop;
    GameGraphics* graphics;
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

int clear_cb(const TCallback& cb, void* data) {
    GameData* gdata = static_cast<GameData*>(data);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(gdata->graphics->getWindow());

    return 0;
}

int main(int argc, char* argv[]) {
    GameLoop* gameloop = new GameLoop();
    GameGraphics* graphics = new GameGraphics();

    GameData data;
    data.gameloop = gameloop;
    data.graphics = graphics;

    TCallbackHandler* handler = gameloop->getHandler();

    handler->setData(&data);
    handler->registerCallback("Test Callback", CB_PERSISTENT, test_cb);

    graphics->setProgramName("TestProgram");
    graphics->setWindowDimension(640, 480);
    graphics->init();

    handler = graphics->getHandler();
    handler->setData(&data);
    handler->registerCallback("Clear Callback", CB_ONE_SHOT, clear_cb);

    gameloop->setGraphics(graphics);

    gameloop->start();

    graphics->finalize();

    delete graphics;
    delete gameloop;

    return 0;
}

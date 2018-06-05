#include <iostream>

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
        gdata->gameloop->removeCallback(cb.id);
        cout << "Callback removed" << endl;
    }


    return 0;
}

int main(int argc, char* argv[]) {
    GameLoop* gameloop = new GameLoop();

    GameData data;
    data.gameloop = gameloop;

    gameloop->setData(&data);
    gameloop->registerCallback("Test Callback", test_cb);

    gameloop->start();

    delete gameloop;

    return 0;
}

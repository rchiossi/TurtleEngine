#include "mainloop.h"

int main(int argc, char* argv[]) {

    GameLoop* gameloop = new GameLoop();

    gameloop->start();

    delete gameloop;

    return 0;
}

#include <iostream>

#include <GL/glew.h>

#include "callback.h"
#include "graphics.h"
#include "mainloop.h"
#include "shader.h"

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

int input_cb(const TCallback& cb, void* data) {
    GameData* gdata = static_cast<GameData*>(data);

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                gdata->gameloop->stop();
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        gdata->gameloop->stop();
                        break;
				case SDLK_r:
					// Cover with red and update
					glClearColor(1.0, 0.0, 0.0, 1.0);
					glClear(GL_COLOR_BUFFER_BIT);
					SDL_GL_SwapWindow(gdata->graphics->getWindow());
					break;
				case SDLK_g:
					// Cover with green and update
					glClearColor(0.0, 1.0, 0.0, 1.0);
					glClear(GL_COLOR_BUFFER_BIT);
					SDL_GL_SwapWindow(gdata->graphics->getWindow());
					break;
				case SDLK_b:
					// Cover with blue and update
					glClearColor(0.0, 0.0, 1.0, 1.0);
					glClear(GL_COLOR_BUFFER_BIT);
					SDL_GL_SwapWindow(gdata->graphics->getWindow());
					break;
                }
                break;
        }
    }

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
    handler->registerCallback("Input Callback", CB_PERSISTENT, input_cb);

    graphics->setProgramName("TestProgram");
    graphics->setWindowDimension(640, 480);
    graphics->init();

    /*
    handler = graphics->getHandler();
    handler->setData(&data);
    handler->registerCallback("Clear Callback", CB_ONE_SHOT, clear_cb);
    */

    GameScene scene;

    GameObject* obj = new GameObject({1,1}, {0,0});
    scene.addGameObject(*obj);

    GameShader vertex_shader("vertex.glsl", GL_VERTEX_SHADER);
    GameShader fragment_shader("fragment.glsl", GL_FRAGMENT_SHADER);

    int err = vertex_shader.load();
    if (err != 0)
        cout << "Error loading shader" << endl;
    vertex_shader.check();

    err = fragment_shader.load();
    if (err != 0)
        cout << "Error loading shader" << endl;
    fragment_shader.check();

    scene.addShader(vertex_shader);
    scene.addShader(fragment_shader);

    graphics->loadScene(&scene);

    gameloop->setGraphics(graphics);

    gameloop->start();

    graphics->finalize();

    delete graphics;
    delete gameloop;

    return 0;
}

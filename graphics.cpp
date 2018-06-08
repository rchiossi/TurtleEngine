#include "graphics.h"

#include <iostream>
#include <string>

//#define GL3_PROTOTYPES 1
#include <GL/glew.h>

using namespace std;

GameGraphics::GameGraphics() {
}

GameGraphics::~GameGraphics() {
    if (this->activeScene != NULL) {
        this->activeScene->unload();
    }
}

void printSDLError() {
    string err = SDL_GetError();

    if (err != "") {
        cout << err << endl;

        SDL_ClearError();
    }
}

int GameGraphics::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Error initialing SDL" << endl;
        printSDLError();
        return -1;
    }

    this->window = SDL_CreateWindow(this->program_name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            this->width, this->height, SDL_WINDOW_OPENGL);
	if (this->window == NULL) {
		cout << "Error creating window" << endl;
        printSDLError();
		return -1;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    this->context = SDL_GL_CreateContext(this->window);
    if (this->context == NULL) {
        cout << "Error creating OpenGL context" << endl;
        printSDLError();
        return -1;
    }

    glewInit();

    return 0;
}

void GameGraphics::finalize() {
    if (this->context != NULL) {
        SDL_GL_DeleteContext(this->context);
    }

    if (this->window != NULL) {
        SDL_DestroyWindow(this->window);
    }

    SDL_Quit();
}

void GameGraphics::setWindowDimension(Uint32 width, Uint32 height) {
    this->width = width;
    this->height = height;
}

void GameGraphics::setProgramName(string name) {
    this->program_name = name;
}

TCallbackHandler* GameGraphics::getHandler() {
    return &this->cb_handler;
}

void GameGraphics::render() {
    //this->cb_handler.run();

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

    if (this->activeScene != NULL) {
        this->activeScene->render();
    }

	SDL_GL_SwapWindow(this->window);

}

SDL_Window* GameGraphics::getWindow() {
    return this->window;
}

SDL_GLContext GameGraphics::getContext() {
    return this->context;
}

void GameGraphics::loadScene(GameScene* scene) {
    if (this->activeScene != NULL) {
        this->activeScene->unload();
    }

    this->activeScene = scene;

    this->activeScene->load();
}


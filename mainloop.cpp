#include <SDL2/SDL.h>
#include <iostream>

#include "mainloop.h"

using namespace std;

GameLoop::GameLoop() {
}

GameLoop::~GameLoop() {
}

void GameLoop::stop() {
    this->running = false;
}

int GameLoop::start() {
    this->running = true;

    return this->loop();
}

int GameLoop::loop() {
    Uint32 update_step = 1000 / this->update_frequency;

    Uint32 cur_tick = SDL_GetTicks();
    Uint32 last_tick = cur_tick;
    Uint32 last_frame = cur_tick;

    Uint32 last_fps = cur_tick;
    Uint32 fps = 0;
    Uint32 updates = 0;

    while (this->running) {
        cur_tick = SDL_GetTicks();

        /* Update Game State */
        Uint32 skip = 0;
        while (cur_tick >= last_tick + update_step && skip < this->maxskip) {
            this->update();
            last_tick += update_step;
            updates++;

            skip++;
        }

        if (skip >= this->maxskip) {
            cout << "WARNING: Max frame skip reached" << endl;
        }

        /* Render a new frame */
        last_frame = cur_tick;
        this->render();
        fps++;

        //TODO: Remove - Debug only
        if (cur_tick >= last_fps + 1000) {
            cout << "updates: " << updates << endl;
            cout << "fps    : " << fps << endl;

            last_fps = cur_tick;

            updates = 0;
            fps = 0;
        }

        /* Sleep until next update or render */
        cur_tick = SDL_GetTicks();

        /* It is already time to render or update - yield with no timer */
        if (cur_tick >= last_frame + (1000 / this->maxfps) ||
           (cur_tick >= last_tick + update_step)) {
            SDL_Delay(0);
            continue;
        }

        Uint32 time_to_frame = last_frame + (1000 / this->maxfps) - cur_tick;
        Uint32 time_to_update = last_tick + update_step - cur_tick;
        Uint32 sleep_time = time_to_frame < time_to_update ? time_to_frame : time_to_update;

        SDL_Delay(sleep_time);
    }

    return 0;
}

void GameLoop::update() {
    for (const TCallback& tcb : this->callbacks) {
        int err = tcb.cb(tcb, this->cb_data);

        if (err != 0) {
            cout << "Error on update callback: " << tcb.name << endl;
        }
    }

    while (this->pending_remove.size() != 0) {
        this->callbacks.erase(this->pending_remove.top());
        this->pending_remove.pop();
    }
}

void GameLoop::render() {
}

void GameLoop::setData(void* data) {
    this->cb_data = data;
}

int GameLoop::registerCallback(string name, t_callback cb) {
    TCallback tcb = (TCallback) {
        .id = ++this->last_cb_id,
        .name = name,
        .cb = cb,
    };

    this->callbacks.push_back(tcb);

    return tcb.id;
}

bool GameLoop::removeCallback(Uint32 id) {
    for (list<TCallback>::iterator it = this->callbacks.begin(); it != this->callbacks.end(); it++) {
        if (it->id == id) {
            this->pending_remove.push(it);
            return true;
        }
    }

    return false;
}


#include "callback.h"

#include <iostream>
#include <string>

#include <SDL2/SDL.h>

using namespace std;

int TCallbackHandler::registerCallback(string name, TCallbackType type, t_callback cb) {
    TCallback tcb = (TCallback) {
        .id = ++this->last_cb_id,
        .name = name,
        .type = type,
        .cb = cb,
    };

    switch (type) {
        case CB_PERSISTENT:
            this->cb_persistent.push_back(tcb);
            break;
        case CB_ONE_SHOT:
            this->cb_one_shot.push(tcb);
            break;
        default:
            cout << "Unknown Callback type" << endl;
    }

    return tcb.id;
}

bool TCallbackHandler::removeCallback(uint32_t id) {
    for (list<TCallback>::iterator it = this->cb_persistent.begin(); it != this->cb_persistent.end(); it++) {
        if (it->id == id) {
            this->pending_remove.push(it);
            return true;
        }
    }

    return false;
}

int TCallbackHandler::run() {
    while (this->pending_remove.size() != 0) {
        this->cb_persistent.erase(this->pending_remove.top());
        this->pending_remove.pop();
    }

    while (this->cb_one_shot.size() != 0) {
        TCallback cur = this->cb_one_shot.front();
        int err = cur.cb(cur, this->cb_data);
        if (err != 0) {
            cout << "Error on callback: " << cur.name << endl;
        }

        this->cb_one_shot.pop();
    }

    for (const TCallback& tcb : this->cb_persistent) {
        int err = tcb.cb(tcb, this->cb_data);
        if (err != 0) {
            cout << "Error on update callback: " << tcb.name << endl;
            return err;
        }
    }

    return 0;
}

void TCallbackHandler::setData(void* data) {
    this->cb_data = data;
}


#include "callback.h"

#include <iostream>
#include <string>

using namespace std;

int TCallbackHandler::registerCallback(string name, t_callback cb) {
    TCallback tcb = (TCallback) {
        .id = ++this->last_cb_id,
        .name = name,
        .cb = cb,
    };

    this->callbacks.push_back(tcb);

    return tcb.id;
}

bool TCallbackHandler::removeCallback(uint32_t id) {
    for (list<TCallback>::iterator it = this->callbacks.begin(); it != this->callbacks.end(); it++) {
        if (it->id == id) {
            this->pending_remove.push(it);
            return true;
        }
    }

    return false;
}

int TCallbackHandler::run() {
    while (this->pending_remove.size() != 0) {
        this->callbacks.erase(this->pending_remove.top());
        this->pending_remove.pop();
    }

    for (const TCallback& tcb : this->callbacks) {
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


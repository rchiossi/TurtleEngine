#ifndef __T_CALLBACK__
#define __T_CALLBACK__

#include <list>
#include <stack>
#include <string>

#include <stdint.h>

using namespace std;

struct TCallback;

typedef int (*t_callback) (const TCallback&, void*);

struct TCallback {
    const uint32_t id;
    const string name;

    t_callback cb;
};

class TCallbackHandler {
    private:
        list<TCallback> callbacks;
        stack<list<TCallback>::iterator> pending_remove;
        uint32_t last_cb_id = 0;

        void* cb_data;

    public:
        int registerCallback(string name, t_callback cb);
        bool removeCallback(uint32_t id);
        void setData(void* data);

        int run();
};

#endif

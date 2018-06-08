#ifndef __T_SCENE__
#define __T_SCENE__

#include <list>

#include "object.h"

using namespace std;

class GameScene {
    private:
        list<GameObject> objects;

    public:
        GameScene();
        ~GameScene();

        void load();
        void unload();

        void render();

        void addGameObject(GameObject obj);

};

#endif

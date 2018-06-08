#ifndef __T_SCENE__
#define __T_SCENE__

#include <list>

#include "object.h"
#include "shader.h"

using namespace std;

class GameScene {
    private:
        list<GameObject> objects;
        ShaderHandler handler;

    public:
        GameScene();
        ~GameScene();

        void load();
        void unload();

        void render();

        void addGameObject(GameObject obj);
        void addShader(GameShader shader);
};

#endif

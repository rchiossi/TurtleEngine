#ifndef __T_OBJECT__
#define __T_OBJECT__

#include <GL/glew.h>
#include <glm/glm.hpp>

using namespace glm;

class GameObject {
    private:
        vec2 pos;
        vec2 dim;

        vec2 vertexes[4];
        vec4 colors[4];

        /* OpenGL properties */
        GLuint vertexArray;
        GLuint vertexBuffers[2];

    public:
        GameObject(vec2 dim, vec2 pos);

        void load();
        void unload();

        void render();

        vec2 getPosition();
        void setPosition(vec2 pos);
};

#endif

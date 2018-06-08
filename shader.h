#ifndef __T_SHADER__
#define __T_SHADER__

#include <list>
#include <string>

#include <GL/glew.h>

using namespace std;

class GameShader {
    private:
        string filename;
        GLenum type;
        GLuint id;

    public:
        GameShader(string filename, GLenum type);

        int load();
        GLuint getId();
        void check();
};

class ShaderHandler {
    private:
        list<GameShader> shaders;

        GLuint id;

    public:
        ShaderHandler();
        void addShader(GameShader shader);
        void enable();
};

#endif

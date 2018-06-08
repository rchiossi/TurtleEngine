#include "shader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

GameShader::GameShader(string filename, GLenum type) {
    this->filename = filename;
    this->type = type;
}

int GameShader::load() {
    ifstream shader_file(this->filename);

    if(!shader_file.is_open()) {
        return -1;
    }

    stringstream databuf;
    databuf << shader_file.rdbuf();
    string data = databuf.str();

    shader_file.close();

    this->id = glCreateShader(this->type);

    char *src = const_cast<char*>(data.c_str());
    GLint size = data.length();
    glShaderSource(this->id, 1, &src, &size);

    glCompileShader(this->id);

    GLint testval;
    glGetShaderiv(this->id, GL_COMPILE_STATUS, &testval);
    if(testval == GL_FALSE) {
        return -1;
    }

    return 0;
}

GLuint GameShader::getId() {
    return this->id;
}

void GameShader::check() {
    GLint testval;
    glGetShaderiv(this->id, GL_COMPILE_STATUS, &testval);
    if(testval == GL_FALSE)
    {
        char infolog[1024];
        glGetShaderInfoLog(this->id,1024,NULL,infolog);
        cout << "The vertex shader failed to compile with the error:" << endl << infolog << endl;
    } else {
        cout << "Shader OK" << endl;
    }
}

ShaderHandler::ShaderHandler() {
    this->id = glCreateProgram();
}

void ShaderHandler::addShader(GameShader shader) {
    this->shaders.push_back(shader);

    glAttachShader(this->id, shader.getId());
}

void ShaderHandler::enable() {
    glLinkProgram(this->id);

    GLint status;
    glGetProgramiv(this->id,GL_LINK_STATUS,&status);

    if (status == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(this->id, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(this->id, maxLength, &maxLength, &infoLog[0]);

        string log(infoLog.begin(), infoLog.end());

        // The program is useless now. So delete it.
        //glDeleteProgram(program);

        cout << "Link problem" << endl;
        cout << log << endl;
    } else {
        cout << "Link OK" << endl;
    }

    glUseProgram(this->id);
}

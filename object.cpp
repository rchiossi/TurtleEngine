#include "object.h"

GameObject::GameObject(vec2 dim, vec2 pos) {
    this->dim = dim;
    this->pos = pos;
}

void GameObject::load() {

    this->vertexes[0] = (vec2) {-dim.x/2, dim.y/2};
    this->vertexes[1] = (vec2) {dim.x/2, dim.y/2};
    this->vertexes[2] = (vec2) {dim.x/2, -dim.y/2};
    this->vertexes[3] = (vec2) {-dim.x/2, -dim.y/2};
    /*
    this->vertexes[0] = (vec2) {-0.2f, 0.2f};
    this->vertexes[1] = (vec2) {0.2f, 0.2f};
    this->vertexes[2] = (vec2) {0.2f, -0.2f};
    this->vertexes[3] = (vec2) {-0.2f, -0.2f};
    */

    this->colors[0] = (vec4) {1.0, 0.0, 0.0, 1.0};
    this->colors[1] = (vec4) {0.0, 1.0, 0.0, 1.0};
    this->colors[2] = (vec4) {0.0, 0.0, 1.0, 1.0};
    this->colors[3] = (vec4) {1.0, 0.0, 1.0, 1.0};


    glGenBuffers(2, this->vertexBuffers);
    glGenVertexArrays(1, &this->vertexArray);
    glBindVertexArray(this->vertexArray);

    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffers[0]);
    glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(GLfloat), this->vertexes, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0); //position (x, y)

    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffers[1]);
    glBufferData(GL_ARRAY_BUFFER, 4 * 4 * sizeof(GLfloat), this->colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0); //color (r, g, b, a)

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

void GameObject::unload() {
    glBindVertexArray(this->vertexArray);

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    glDeleteBuffers(2,  this->vertexBuffers);
    glDeleteVertexArrays(1, &this->vertexArray);
}

void GameObject::render() {
    glBindVertexArray(this->vertexArray);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

vec2 GameObject::getPosition() {
    return this->pos;
}

void GameObject::setPosition(vec2 pos) {
    this->pos = pos;
}


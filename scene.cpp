#include "scene.h"

GameScene::GameScene() {
}

GameScene::~GameScene() {
}

void GameScene::addGameObject(GameObject obj) {
    this->objects.push_back(obj);
}

void GameScene::addShader(GameShader shader) {
    handler.addShader(shader);
}

void GameScene::load() {
    for (GameObject& obj : this->objects) {
        obj.load();
    }

    this->handler.enable();
}

void GameScene::unload() {
    for (GameObject& obj : this->objects) {
        obj.unload();
    }
}

void GameScene::render() {
    for (GameObject& obj : this->objects) {
        obj.render();
    }
}

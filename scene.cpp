#include "scene.h"

GameScene::GameScene() {
}

GameScene::~GameScene() {
}

void GameScene::addGameObject(GameObject obj) {
    this->objects.push_back(obj);
}

void GameScene::load() {
    for (GameObject& obj : this->objects) {
        obj.load();
    }
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

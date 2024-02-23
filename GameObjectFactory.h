#pragma once
#include <string>
#include <map>
#include <iostream>
#include "GameObject.h"

class BaseCreator {
public:
    virtual GameObject* createGameObject() const = 0;
    virtual ~BaseCreator();
};

class GameObjectFactory {
public:
    static GameObjectFactory* Instance() {
        if (s_pInstance == 0) {
            s_pInstance = new GameObjectFactory();
            return s_pInstance;
        }
        return s_pInstance;
    }

    bool registerType(std::string typeID, BaseCreator* pCreator);

    GameObject* create(std::string typeID);

private:
    GameObjectFactory(); // Private constructor to prevent instantiation
    ~GameObjectFactory();

    std::map<std::string, BaseCreator*> _creators;

    static GameObjectFactory* s_pInstance;

};

typedef GameObjectFactory TheGameObjectFactory;
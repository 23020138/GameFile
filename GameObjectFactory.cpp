#include "GameObjectFactory.h"

GameObjectFactory* GameObjectFactory::s_pInstance = 0;

BaseCreator::~BaseCreator() {}

GameObjectFactory::GameObjectFactory() {} // Private constructor to prevent instantiation
GameObjectFactory::~GameObjectFactory() {}

bool GameObjectFactory::registerType(std::string typeID, BaseCreator* pCreator) {
    std::map<std::string, BaseCreator*>::iterator it = _creators.find(typeID);

    if (it != _creators.end()) {
        delete pCreator;
    }

    _creators[typeID] = pCreator;
    return true;
}

GameObject* GameObjectFactory::create(std::string typeID) {
    std::map<std::string, BaseCreator*>::iterator it = _creators.find(typeID);

    if (it == _creators.end()) {
        std::cout << "Could not find type: " << typeID << "\n";
        return nullptr;
    }

    BaseCreator* pCreator = (*it).second;
    return pCreator->createGameObject();
}
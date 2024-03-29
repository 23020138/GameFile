#include <string>
#include "LevelParser.h"
#include "TextureManager.h"
#include "Game.h"
#include "TileLayer.h"
#include "ObjectLayer.h"
#include "GameObjectFactory.h"
#include "Level.h"
#include "base64.h"
#include "zlib.h"

Level* LevelParser::parseLevel(const char* levelFile)
{
    // create a TinyXML document and load the map XML
    TiXmlDocument levelDocument;
    levelDocument.LoadFile(levelFile);
    // create the level object
    Level* pLevel = new Level();
    // get the root node 
    TiXmlElement* pRoot = levelDocument.RootElement();

    std::cout << "Loading level:\n" << "Version: " << pRoot->Attribute("version") << "\n";
    std::cout << "Width:" << pRoot->Attribute("width") << " - Height:" << pRoot->Attribute("height") << "\n";
    std::cout << "Tile Width:" << pRoot->Attribute("tilewidth") << " - Tile Height:" << pRoot->Attribute("tileheight") << "\n";

    pRoot->Attribute("tilewidth", &_tileSize);
    pRoot->Attribute("width", &_width);
    pRoot->Attribute("height", &_height);

    //properties is the first child of the root
    TiXmlElement* pProperties = pRoot->FirstChildElement();

    //parse the textures needed for this level, which have been added to properties
    for (TiXmlElement* e = pProperties->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("property"))
        {
            parseTextures(e);
        }
    }

    // parse the tilesets
    for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("tileset"))
        {
            parseTilesets(e, pLevel->getTilesets());
        }
    }
    // parse any object layers
    for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("objectgroup") || e->Value() == std::string("layer"))
        {
            if (e->FirstChildElement()->Value() == std::string("object"))
            {
                parseObjectLayer(e, pLevel->getLayers(), pLevel);
            }
            else if (e->FirstChildElement()->Value() == std::string("data") || (e->FirstChildElement()->NextSiblingElement() != 0 && e->FirstChildElement()->NextSiblingElement()->Value() == std::string("data")))
            {
                parseTileLayer(e, pLevel->getLayers(), pLevel->getTilesets(), pLevel->getCollisionLayers());
            }
        }
    }
    return pLevel;
}

void LevelParser::parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets)
{
    // first add the tileset to texture manager
    TheTextureManager::Instance()->load(pTilesetRoot -> FirstChildElement()->Attribute("source"), pTilesetRoot -> Attribute("name"), TheGame::Instance()->getRenderer());
    // create a tileset object
    Tileset tileset;
    pTilesetRoot->FirstChildElement()->Attribute("width", &tileset.width);
    pTilesetRoot->FirstChildElement()->Attribute("height", &tileset.height);
    pTilesetRoot->Attribute("firstgid", &tileset.firstGridID);
    pTilesetRoot->Attribute("tilewidth", &tileset.tileWidth);
    pTilesetRoot->Attribute("tileheight", &tileset.tileHeight);
    pTilesetRoot->Attribute("spacing", &tileset.spacing);
    pTilesetRoot->Attribute("margin", &tileset.margin);
    tileset.name = pTilesetRoot->Attribute("name");
    tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);
    pTilesets->push_back(tileset);
}

void LevelParser::parseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*>* pLayers, const std::vector<Tileset>* pTilesets, std::vector<TileLayer*>* pCollisionLayers)
{
    TileLayer* pTileLayer = new TileLayer(_tileSize, *pTilesets);

    bool collidable = false;

    // tile data
    std::vector<std::vector<int>> data;

    std::string decodedIDs;
    TiXmlElement* pDataNode = pTileElement->FirstChildElement();

    for (TiXmlElement* e = pTileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("properties"))
        {
            for (TiXmlElement* property = e->FirstChildElement(); property != NULL; property = property->NextSiblingElement())
            {
                if (property->Value() == std::string("property"))
                {
                    if (property->Attribute("name") == std::string("collidable"))
                    {
                        collidable = true;
                    }
                }
            }
        }
        if (e->Value() == std::string("data"))
        {
            pDataNode = e;
        }
    }
    for (TiXmlNode* e = pDataNode->FirstChild(); e != NULL; e = e->NextSibling())
    {
        TiXmlText* text = e->ToText();
        std::string t = text->Value();
        decodedIDs = base64_decode(t);
    }
    // uncompress zlib compression
    uLongf sizeofids = _width * _height * sizeof(int);
    std::vector<int> ids(_width * _height);
    uncompress((Bytef*)&ids[0], &sizeofids, (const Bytef*)decodedIDs.c_str(), decodedIDs.size());

    std::vector<int> layerRow(_width);

    for (int j = 0; j < _height; j++)
    {
        data.push_back(layerRow);
    }

    for (int rows = 0; rows < _height; rows++)
    {
        for (int cols = 0; cols < _width; cols++)
        {
            data[rows][cols] = ids[rows * _width + cols];
        }
    }

    pTileLayer->setTileIDs(data);
    pTileLayer->setMapWidth(_width);

    if (collidable)
    {
        pCollisionLayers->push_back(pTileLayer);
    }

    pLayers->push_back(pTileLayer);
}

void LevelParser::parseTextures(TiXmlElement* pTextureRoot)
{
    TheTextureManager::Instance()->load(pTextureRoot->Attribute("value"), pTextureRoot->Attribute("name"), TheGame::Instance()->getRenderer());
}

void LevelParser::parseObjectLayer(TiXmlElement* pObjectElement, std::vector<Layer*>* pLayers, Level* pLevel)
{
    // create an object layer
    ObjectLayer* pObjectLayer = new ObjectLayer();
    std::cout << pObjectElement->FirstChildElement()->Value() << std::endl;
    for (TiXmlElement* e = pObjectElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        std::cout << e->Value() << std::endl;
        if (e->Value() == std::string("object"))
        {
            int x, y, width, height, numFrames;
            int callbackID = 0, animSpeed = 0;
            std::string textureID;
            std::string type;

            // get the initial node values type, x and y
            e->Attribute("x", &x);
            e->Attribute("y", &y);

            type = e->Attribute("type");
            GameObject* pGameObject = TheGameObjectFactory::Instance()->create(e-> Attribute("type"));
            // get the property values
            for (TiXmlElement* properties = e->FirstChildElement(); properties != NULL; properties = properties->NextSiblingElement())
            {
                if (properties->Value() == std::string("properties"))
                {
                    for (TiXmlElement* property = properties-> FirstChildElement(); property != NULL; property = property-> NextSiblingElement())
                    {
                        if (property->Value() == std::string("property"))
                        {
                            if (property->Attribute("name") == std::string("numFrames"))
                            {
                                property->Attribute("value", &numFrames);
                            }
                            else if (property->Attribute("name") == std::string("textureHeight"))
                            {
                                property->Attribute("value", &height);
                            }
                            else if (property->Attribute("name") == std::string("textureID"))
                            {
                                textureID = property->Attribute("value");
                            }
                            else if (property->Attribute("name") == std::string("textureWidth"))
                            {
                                property->Attribute("value", &width);
                            }
                            else if (property->Attribute("name") == std::string("callbackID"))
                            {
                                property->Attribute("value", &callbackID);
                            }
                            else if (e->Attribute("name") == std::string("animSpeed"))
                            {
                                property->Attribute("value", &animSpeed);
                            }
                        }
                    }
                }
            }
            pGameObject->load(std::unique_ptr<LoaderParams>(new LoaderParams(x, y, width, height, textureID, numFrames, callbackID, animSpeed)));
            if (type == "Player") // check if it's the player
            {
                pLevel->setPlayer(dynamic_cast<Player*>(pGameObject));
            }
            pObjectLayer->getGameObjects()->push_back(pGameObject);
        }
    }
    pLayers->push_back(pObjectLayer);
}
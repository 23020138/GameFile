#pragma once

#include <iostream>
#include <vector>
#include "Bullet.h"

class BulletHandler
{
public:

    static BulletHandler* Instance()
    {
        if (s_pInstance == 0)
        {
            s_pInstance = new BulletHandler();
            return s_pInstance;
        }
        return s_pInstance;
    }

    void addPlayerBullet(int x, int y, int width, int height, std::string textureID, int numFrames, Vector2D heading);
    void addEnemyBullet(int x, int y, int width, int height, std::string textureID, int numFrames, Vector2D heading);

    void updateBullets();
    void drawBullets();

    void clearBullets();

    const std::vector<PlayerBullet*> getPlayerBullets() { return _playerBullets; }
    const std::vector<EnemyBullet*> getEnemyBullets() { return _enemyBullets; }

private:

    BulletHandler();
    ~BulletHandler();

    BulletHandler(const BulletHandler&);
    BulletHandler& operator=(const BulletHandler&);

    static BulletHandler* s_pInstance;

    // in play bullets
    std::vector<PlayerBullet*> _playerBullets;
    std::vector<EnemyBullet*> _enemyBullets;
};

typedef BulletHandler TheBulletHandler;
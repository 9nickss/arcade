/* ------------------------------------------------------------------------------------ *
 *                                                                                      *
 * EPITECH PROJECT - Wed, Apr, 2026                                                     *
 * Title           - G-OOP-400-NCE-4-1-arcade-3                                         *
 * Description     -                                                                    *
 *     SpaceInvadersGame                                                                *
 *                                                                                      *
 * ------------------------------------------------------------------------------------ *
 *                                                                                      *
 *       ▄▀▀█▄▄▄▄  ▄▀▀▄▀▀▀▄  ▄▀▀█▀▄    ▄▀▀▀█▀▀▄  ▄▀▀█▄▄▄▄  ▄▀▄▄▄▄   ▄▀▀▄ ▄▄             *
 *      ▐  ▄▀   ▐ █   █   █ █   █  █  █    █  ▐ ▐  ▄▀   ▐ █ █    ▌ █  █   ▄▀            *
 *        █▄▄▄▄▄  ▐  █▀▀▀▀  ▐   █  ▐  ▐   █       █▄▄▄▄▄  ▐ █      ▐  █▄▄▄█             *
 *        █    ▌     █          █        █        █    ▌    █         █   █             *
 *       ▄▀▄▄▄▄    ▄▀        ▄▀▀▀▀▀▄   ▄▀        ▄▀▄▄▄▄    ▄▀▄▄▄▄▀   ▄▀  ▄▀             *
 *       █    ▐   █         █       █ █          █    ▐   █     ▐   █   █               *
 *       ▐        ▐         ▐       ▐ ▐          ▐        ▐         ▐   ▐               *
 *                                                                                      *
 * ------------------------------------------------------------------------------------ */

#ifndef INCLUDED_SPACEINVADERSGAME_HPP
    #define INCLUDED_SPACEINVADERSGAME_HPP

#include "IGameModule/IGameModule.hpp"
#include <vector>
#include <chrono>

namespace Arcade {

    struct Invader {
        int x;
        int y;
        bool alive;
    };

    struct Bullet {
        int x;
        int y;
        bool active;
        bool fromPlayer;
    };

    struct Shield {
        int x;
        int y;
        int health;
    };

    class SpaceInvadersGame : public IGameModule {
        private:
            void spawnInvaders();
            void spawnShields();
            void moveInvaders();
            void movePlayerBullet();
            void moveEnemyBullets();
            void checkCollisions();
            void enemyShoot();
            void buildRenderData();

            static constexpr int WIDTH = 60;
            static constexpr int HEIGHT = 30;

            int _playerX = WIDTH / 2;
            int _playerY = HEIGHT - 2;

            Bullet _playerBullet = {0, 0, false, true};
            std::vector<Bullet> _enemyBullets;

            std::vector<Invader> _invaders;
            int _invaderDirX = 1;
            bool _invaderMoveDown = false;

            int _score = 0;
            bool _gameOver = false;
            bool _win = false;

            std::chrono::steady_clock::time_point _lastInvaderMove;
            std::chrono::steady_clock::time_point _lastEnemyShoot;
            std::chrono::steady_clock::time_point _lastPlayerBulletMove;
            std::chrono::steady_clock::time_point _lastEnemyBulletMove;

            RenderData _renderData;
            std::vector<Shield> _shields;
        public:
            void init() override;
            void reset() override;
            void close() override;
            const std::string &getName() const override;
            void handleInput(Key key) override;
            void update() override;
            const RenderData &getRenderData() override;
            int getScore() const override;
            bool isGameOver() const override;
    };

}

#endif
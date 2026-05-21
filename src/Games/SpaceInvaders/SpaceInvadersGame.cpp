/* ------------------------------------------------------------------------------------ *
 *                                                                                      *
 * EPITECH PROJECT - Fri, Mar, 2026                                                     *
 * Title           - Arcade                                                             *
 * Description     -                                                                    *
 *     SpaceInvadersGame                                                                *
 *                                                                                      *
 * ------------------------------------------------------------------------------------ *
 *                                                                                      *
 *       _|_|_|_|  _|_|_|    _|_|_|  _|_|_|_|_|  _|_|_|_|    _|_|_|  _|    _|           *
 *       _|        _|    _|    _|        _|      _|        _|        _|    _|           *
 *       _|_|_|    _|_|_|      _|        _|      _|_|_|    _|        _|_|_|_|           *
 *       _|        _|          _|        _|      _|        _|        _|    _|           *
 *       _|_|_|_|  _|        _|_|_|      _|      _|_|_|_|    _|_|_|  _|    _|           *
 *                                                                                      *
 * ------------------------------------------------------------------------------------ */

#include "Games/SpaceInvaders/SpaceInvadersGame.hpp"
#include <cstdlib>
#include <ctime>

namespace Arcade {

    void SpaceInvadersGame::init()
    {
        std::srand(std::time(nullptr));
        _score = 0;
        _gameOver = false;
        _win = false;
        _playerX = WIDTH / 2;
        _playerY = HEIGHT - 2;
        _playerBullet = {0, 0, false, true};
        _enemyBullets.clear();
        _invaderDirX = 1;
        _invaderMoveDown = false;
        _lastInvaderMove = std::chrono::steady_clock::now();
        _lastEnemyShoot = std::chrono::steady_clock::now();
        _lastPlayerBulletMove = std::chrono::steady_clock::now();
        _lastEnemyBulletMove = std::chrono::steady_clock::now();
        spawnInvaders();
        spawnShields();
    }

    void SpaceInvadersGame::reset()
    {
        init();
    }

    void SpaceInvadersGame::close()
    {
    }

    const std::string &SpaceInvadersGame::getName() const
    {
        static const std::string name = "space_invaders";
        return name;
    }

    void SpaceInvadersGame::spawnInvaders()
    {
        _invaders.clear();
        for (int row = 0; row < 5; ++row) {
            for (int col = 0; col < 10; ++col) {
                Invader inv;
                inv.x = 5 + col * 5;
                inv.y = 2 + row * 2;
                inv.alive = true;
                _invaders.push_back(inv);
            }
        }
    }

    void SpaceInvadersGame::spawnShields()
    {
        _shields.clear();
        int positions[] = {10, 22, 34, 46};
        for (int pos : positions) {
            for (int i = -1; i <= 1; ++i) {
                Shield s;
                s.x = pos + i;
                s.y = _playerY - 3;
                s.health = 3;
                _shields.push_back(s);
            }
        }
    }

    void SpaceInvadersGame::handleInput(Key key)
    {
        if (_gameOver)
            return;
        if (key == Key::LEFT && _playerX > 1)
            _playerX--;
        if (key == Key::RIGHT && _playerX < WIDTH - 2)
            _playerX++;
        if (key == Key::SPACE && !_playerBullet.active) {
            _playerBullet.x = _playerX;
            _playerBullet.y = _playerY - 1;
            _playerBullet.active = true;
        }
    }

    void SpaceInvadersGame::update()
    {
        if (_gameOver)
            return;

        auto now = std::chrono::steady_clock::now();

        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastInvaderMove).count() > 500) {
            moveInvaders();
            _lastInvaderMove = now;
        }

        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastEnemyShoot).count() > 1500) {
            enemyShoot();
            _lastEnemyShoot = now;
        }

        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastPlayerBulletMove).count() > 100) {
            movePlayerBullet();
            _lastPlayerBulletMove = now;
        }

        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastEnemyBulletMove).count() > 200) {
            moveEnemyBullets();
            _lastEnemyBulletMove = now;
        }
        checkCollisions();

        bool anyAlive = false;
        for (const auto &inv : _invaders)
            if (inv.alive) { anyAlive = true; break; }
        if (!anyAlive) {
            _win = true;
            _gameOver = true;
        }

        for (const auto &inv : _invaders) {
            if (inv.alive && inv.y >= _playerY) {
                _gameOver = true;
                return;
            }
        }

        buildRenderData();
    }

    void SpaceInvadersGame::moveInvaders()
    {
        bool hitWall = false;

        for (const auto &inv : _invaders) {
            if (!inv.alive)
                continue;
            if (inv.x + _invaderDirX <= 0 || inv.x + _invaderDirX >= WIDTH - 1) {
                hitWall = true;
                break;
            }
        }

        if (hitWall) {
            _invaderDirX = -_invaderDirX;
            for (auto &inv : _invaders)
                if (inv.alive)
                    inv.y++;
        } else {
            for (auto &inv : _invaders)
                if (inv.alive)
                    inv.x += _invaderDirX;
        }
    }

    void SpaceInvadersGame::movePlayerBullet()
    {
        if (!_playerBullet.active)
            return;
        _playerBullet.y--;
        if (_playerBullet.y < 0)
            _playerBullet.active = false;
    }

    void SpaceInvadersGame::moveEnemyBullets()
    {
        for (auto &bullet : _enemyBullets) {
            if (!bullet.active)
                continue;
            bullet.y++;
            if (bullet.y >= HEIGHT)
                bullet.active = false;
        }
    }

    void SpaceInvadersGame::enemyShoot()
    {
        std::vector<Invader *> shooters;
        for (int col = 0; col < 10; ++col) {
            Invader *lowest = nullptr;
            for (auto &inv : _invaders) {
                if (!inv.alive)
                    continue;
                if (inv.x >= 5 + col * 5 - 1 && inv.x <= 5 + col * 5 + 1) {
                    if (!lowest || inv.y > lowest->y)
                        lowest = &inv;
                }
            }
            if (lowest)
                shooters.push_back(lowest);
        }

        if (!shooters.empty()) {
            Invader *shooter = shooters[std::rand() % shooters.size()];
            Bullet b;
            b.x = shooter->x;
            b.y = shooter->y + 1;
            b.active = true;
            b.fromPlayer = false;
            _enemyBullets.push_back(b);
        }
    }

    void SpaceInvadersGame::checkCollisions()
    {
        if (_playerBullet.active) {
            for (auto &inv : _invaders) {
                if (!inv.alive)
                    continue;
                if (inv.x == _playerBullet.x && inv.y == _playerBullet.y) {
                    inv.alive = false;
                    _playerBullet.active = false;
                    _score += 10;
                    break;
                }
            }
        }

        for (auto &bullet : _enemyBullets) {
            if (!bullet.active)
                continue;
            if (bullet.x == _playerX && bullet.y == _playerY) {
                _gameOver = true;
                bullet.active = false;
            }
        }

        for (auto &shield : _shields) {
            if (shield.health <= 0)
                continue;
            if (_playerBullet.active &&
                _playerBullet.x == shield.x &&
                _playerBullet.y == shield.y) {
                shield.health--;
                _playerBullet.active = false;
            }
            for (auto &bullet : _enemyBullets) {
                if (!bullet.active)
                    continue;
                if (bullet.x == shield.x && bullet.y == shield.y) {
                    shield.health--;
                    bullet.active = false;
                }
            }
        }
    }

    void SpaceInvadersGame::buildRenderData()
    {
        _renderData = RenderData();
        _renderData.gridWidth = WIDTH;
        _renderData.gridHeight = HEIGHT;
        _renderData.grid.assign(HEIGHT, std::vector<Cell>(WIDTH, {' ', Color::WHITE, Color::BLACK}));

        _renderData.grid[_playerY][_playerX] = {'^', Color::GREEN, Color::BLACK};

        for (const auto &inv : _invaders) {
            if (!inv.alive)
                continue;
            _renderData.grid[inv.y][inv.x] = {'W', Color::RED, Color::BLACK};
        }

        for (const auto &shield : _shields) {
            if (shield.health <= 0)
                continue;
            Color c = (shield.health == 3) ? Color::GREEN
                    : (shield.health == 2) ? Color::YELLOW
                    : Color::RED;
            _renderData.grid[shield.y][shield.x] = {'#', c, Color::BLACK};
        }

        if (_playerBullet.active)
            _renderData.grid[_playerBullet.y][_playerBullet.x] = {'|', Color::YELLOW, Color::BLACK};

        for (const auto &bullet : _enemyBullets) {
            if (!bullet.active)
                continue;
            _renderData.grid[bullet.y][bullet.x] = {'v', Color::MAGENTA, Color::BLACK};
        }

        _renderData.texts.push_back({"Score: " + std::to_string(_score), 0, HEIGHT - 1, Color::WHITE});

        if (_gameOver) {
            if (_win)
                _renderData.texts.push_back({"YOU WIN!", WIDTH / 2 - 4, HEIGHT / 2, Color::GREEN});
            else
                _renderData.texts.push_back({"GAME OVER", WIDTH / 2 - 4, HEIGHT / 2, Color::RED});
        }
    }

    const RenderData &SpaceInvadersGame::getRenderData()
    {
        buildRenderData();
        return _renderData;
    }

    int SpaceInvadersGame::getScore() const
    {
        return _score;
    }

    bool SpaceInvadersGame::isGameOver() const
    {
        return _gameOver;
    }

}

extern "C" Arcade::IGameModule *entryPointGame()
{
    return new Arcade::SpaceInvadersGame();
}

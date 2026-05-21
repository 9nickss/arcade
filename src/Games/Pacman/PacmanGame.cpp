/* ------------------------------------------------------------------------------------ *
 *                                                                                      *
 * EPITECH PROJECT - Mon, Apr, 2026                                                     *
 * Title           - Arcade                                                             *
 * Description     -                                                                    *
 *     PacmanGame                                                                       *
 *                                                                                      *
 * ------------------------------------------------------------------------------------ *
 *                                                                                      *
 *         ░        ░       ░░        ░        ░        ░░      ░░  ░░░░  ░             *
 *         ▒  ▒▒▒▒▒▒▒  ▒▒▒▒  ▒▒▒▒  ▒▒▒▒▒▒▒  ▒▒▒▒  ▒▒▒▒▒▒▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒             *
 *         ▓      ▓▓▓       ▓▓▓▓▓  ▓▓▓▓▓▓▓  ▓▓▓▓      ▓▓▓  ▓▓▓▓▓▓▓        ▓             *
 *         █  ███████  ██████████  ███████  ████  ███████  ████  █  ████  █             *
 *         █        █  ███████        ████  ████        ██      ██  ████  █             *
 *                                                                                      *
 * ------------------------------------------------------------------------------------ */

#include "Games/Pacman/PacmanGame.hpp"

namespace Arcade {

    PacmanGame::PacmanGame()
    {
        reset();
    }

    void PacmanGame::init() { reset(); }

    void PacmanGame::reset()
    {
        _score = 0; _dotsLeft = 0; _gameOver = false; _win = false; _power = false; _ghostsOut = false;
        _px = PX; _py = PY; _dx = 0; _dy = 0;
        _start = _lastPacmanMove = _powerStart = _winStart = std::chrono::steady_clock::now();
        buildMap();
        for (std::size_t i = 0; i < _ghosts.size(); ++i) {
            _ghosts[i] = Ghost{};
            _ghosts[i].homeX = GX; _ghosts[i].homeY = GY;
            _ghosts[i].x = GX - 1 + static_cast<int>(i % 2) * 2;
            _ghosts[i].y = GY - 1 + static_cast<int>(i / 2);
            _ghosts[i].lastMove = _start;
            _ghosts[i].stateStart = _start;
        }
        eatCell();
    }

    void PacmanGame::close()
    {
    }

    const std::string &PacmanGame::getName() const { return _name; }

    void PacmanGame::handleInput(Key key)
    {
        if (key == Key::RESTART) { 
            reset(); 
            return; 
        }
        if (key == Key::UP) { 
            _dx = 0; 
            _dy = -1; 
        }
        if (key == Key::DOWN) { 
            _dx = 0; 
            _dy = 1; 
        }
        if (key == Key::LEFT) { 
            _dx = -1; 
            _dy = 0; 
        }
        if (key == Key::RIGHT) { 
            _dx = 1; 
            _dy = 0; 
        }
    }

    void PacmanGame::update()
    {
        const auto now = std::chrono::steady_clock::now();
        if (_gameOver) {
            if (_win && now - _winStart > WIN_RELOAD) { 
                ++_speedBonus; 
                reset(); 
            }
            buildRenderData();
            return;
        }
        releaseGhosts();
        movePacman();
        moveGhosts();
        checkWin();
        buildRenderData();
    }

    const RenderData &PacmanGame::getRenderData() 
    { 
        buildRenderData(); 
        return _renderData; 
    }

    int PacmanGame::getScore() const { return _score; }
    bool PacmanGame::isGameOver() const { return _gameOver; }
}

extern "C" Arcade::IGameModule *entryPointGame()
{
    return new Arcade::PacmanGame();
}

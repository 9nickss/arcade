/* ------------------------------------------------------------------------------------ *
 *                                                                                      *
 * EPITECH PROJECT - Mon, Apr, 2026                                                     *
 * Title           - Arcade                                                             *
 * Description     -                                                                    *
 *     PacmanMove                                                                       *
 *                                                                                      *
 * ------------------------------------------------------------------------------------ *
 *                                                                                      *
 *             ███████╗██████╗ ██╗████████╗███████╗ ██████╗██╗  ██╗                     *
 *             ██╔════╝██╔══██╗██║╚══██╔══╝██╔════╝██╔════╝██║  ██║                     *
 *             █████╗  ██████╔╝██║   ██║   █████╗  ██║     ███████║                     *
 *             ██╔══╝  ██╔═══╝ ██║   ██║   ██╔══╝  ██║     ██╔══██║                     *
 *             ███████╗██║     ██║   ██║   ███████╗╚██████╗██║  ██║                     *
 *             ╚══════╝╚═╝     ╚═╝   ╚═╝   ╚══════╝ ╚═════╝╚═╝  ╚═╝                     *
 *                                                                                      *
 * ------------------------------------------------------------------------------------ */

#include "Games/Pacman/PacmanGame.hpp"
#include <algorithm>
#include <cstdlib>

namespace Arcade {

    void PacmanGame::eatCell()
    {
        auto [x, y] = wrap(_px, _py);
        char &c = _map[y][x];

        if (c == '.') { 
            c = ' '; 
            ++_score; 
            --_dotsLeft; 
        }
        if (c == 'o') { 
            c = ' ';
            _score += 50; 
            --_dotsLeft; 
            _power = true; 
            _powerStart = std::chrono::steady_clock::now(); 
        }
    }

    void PacmanGame::releaseGhosts()
    {
        const auto now = std::chrono::steady_clock::now();

        if (_ghostsOut || now - _start < std::chrono::seconds(10))
            return;
        _ghostsOut = true;

        for (auto &g : _ghosts) { 
            g.active = true; 
            g.lastMove = now; 
            g.stateStart = now; 
        }
    }

    void PacmanGame::movePacman()
    {
        const auto now = std::chrono::steady_clock::now();
        auto delay = std::max(std::chrono::milliseconds(70), PACMAN_DELAY - std::chrono::milliseconds(_speedBonus * 5));
        
        if (now - _lastPacmanMove < delay)
            return;
        _lastPacmanMove = now;

        auto [nx, ny] = wrap(_px + _dx, _py + _dy);

        if (!wall(nx, ny)) { 
            _px = nx; 
            _py = ny; 
            eatCell(); 
        }
    }

    void PacmanGame::moveGhost(Ghost &g, int index)
    {
        const auto now = std::chrono::steady_clock::now();
        
        auto delay = g.frightened ? FRIGHT_DELAY : GHOST_DELAY;
        
        if (g.returning)
            delay = std::chrono::milliseconds(90);
        if (now - g.lastMove < delay)
            return;
        g.lastMove = now;

        if (_power && now - _powerStart > POWER_TIME) 
            g.frightened = false;

        auto step = g.returning ? toward(g.x, g.y, g.homeX, g.homeY) : (g.frightened ? away(g.x, g.y, _px, _py) : toward(g.x, g.y, _px, _py));

        if (step.first == 0 && step.second == 0) 
            step = {1, 0};
        
        auto [nx, ny] = wrap(g.x + step.first, g.y + step.second);
        
        if (!wall(nx, ny)) { 
            g.x = nx; 
            g.y = ny; 
        }

        if (g.returning && g.x == g.homeX && g.y == g.homeY && now - g.stateStart > GHOST_RETURN) {
            g.returning = false; 
            g.frightened = false; 
            g.active = true; 
            g.stateStart = now;
        }

        if (g.active && g.x == _px && g.y == _py) {

            if (_power && !g.returning) { 
                _score += 200; g.returning = true; 
                g.frightened = false; 
                g.stateStart = now; 
            } else if (!g.returning) { 
                _gameOver = true; 
                _win = false;
            }
        }
    }

    void PacmanGame::moveGhosts()
    {
        const auto now = std::chrono::steady_clock::now();

        if (_power && now - _powerStart > POWER_TIME) 
            _power = false;

        for (std::size_t i = 0; i < _ghosts.size(); ++i) {
            auto &g = _ghosts[i];
            if (!g.active) 
                continue;
            if (_power && !g.returning) 
                g.frightened = true;
            moveGhost(g, static_cast<int>(i));
        }
    }

    void PacmanGame::checkWin()
    {
        if (_dotsLeft <= 0) { _gameOver = true; _win = true; _winStart = std::chrono::steady_clock::now(); }
    }

} // namespace Arcade

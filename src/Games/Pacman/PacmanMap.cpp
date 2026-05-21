/* ------------------------------------------------------------------------------------ *
 *                                                                                      *
 * EPITECH PROJECT - Mon, Apr, 2026                                                     *
 * Title           - Arcade                                                             *
 * Description     -                                                                    *
 *     PacmanMap                                                                        *
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

#include "Games/Pacman/PacmanGame.hpp"
#include <cstdlib>

namespace Arcade {

    void PacmanGame::buildMap()
    {
        _map.assign(H, std::string(W, '.'));
        _dotsLeft = 0;

        for (int y = 0; y < H; ++y) {
            for (int x = 0; x < W; ++x) {
                if (y == 0 || y == H - 1 || x == 0 || x == W - 1)
                    _map[y][x] = '#';
                else
                    ++_dotsLeft;
            }
        }

        for (int x = 2; x < W - 2; ++x)
            if (x != 4 && x != 14) { 
                _map[3][x] = '#'; 
                _map[11][x] = '#'; 
            }
        for (int y = 2; y < H - 2; ++y)
            if (y != 6 && y != 8) { 
                _map[y][4] = '#'; 
                _map[y][14] = '#'; 
            }
        for (int x = 7; x <= 11; ++x) { 
            _map[5][x] = '#'; 
            _map[8][x] = '#'; 
        }
        for (int y = 5; y <= 8; ++y) { 
            _map[y][7] = '#'; 
            _map[y][11] = '#'; 
        }
        _map[8][9] = '.';

        const std::pair<int, int> pellets[4] = {{1, 1}, {17, 1}, {1, 13}, {17, 13}};
        for (const auto &p : pellets)
            _map[p.second][p.first] = 'o';
    }

    std::pair<int, int> PacmanGame::wrap(int x, int y) const
    {
        if (x < 0) x = W - 1;
        if (x >= W) x = 0;
        if (y < 0) y = H - 1;
        if (y >= H) y = 0;
        return {x, y};
    }

    bool PacmanGame::wall(int x, int y) const
    {
        auto [wx, wy] = wrap(x, y);
        return _map[wy][wx] == '#';
    }

    std::pair<int, int> PacmanGame::toward(int x, int y, int tx, int ty) const
    {
        const std::pair<int, int> dirs[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        std::pair<int, int> best{0, 0};
        int bestDist = 9999;

        for (const auto &d : dirs) {
            auto [nx, ny] = wrap(x + d.first, y + d.second);
            if (wall(nx, ny))
                continue;
            const int dist = std::abs(nx - tx) + std::abs(ny - ty);
            if (dist < bestDist) {
                bestDist = dist;
                best = d;
            }
        }
        return best;
    }

    std::pair<int, int> PacmanGame::away(int x, int y, int tx, int ty) const
    {
        auto step = toward(x, y, tx, ty);

        return {-step.first, -step.second};
    }

    void PacmanGame::buildRenderData()
    {
        _renderData = RenderData();
        _renderData.gridWidth = W;
        _renderData.gridHeight = H + 2;
        _renderData.grid.assign(_renderData.gridHeight, std::vector<Cell>(W, {' ', Color::WHITE, Color::BLACK}));

        constexpr int offsetY = 2;

        for (int y = 0; y < H; ++y) {
            for (int x = 0; x < W; ++x) {
                const char c = _map[y][x];
                if (c == '#')
                    _renderData.grid[y + offsetY][x] = {'#', Color::BLUE, Color::BLACK};
                else if (c == '.')
                    _renderData.grid[y + offsetY][x] = {'.', Color::WHITE, Color::BLACK};
                else if (c == 'o')
                    _renderData.grid[y + offsetY][x] = {'O', Color::YELLOW, Color::BLACK};
            }
        }

        _renderData.grid[_py + offsetY][_px] = {'C', _power ? Color::MAGENTA : Color::YELLOW, Color::BLACK};

        for (std::size_t i = 0; i < _ghosts.size(); ++i) {
            const auto &g = _ghosts[i];
            if (!g.active)
                continue;
            const Color color = g.returning ? Color::WHITE
                : (g.frightened ? Color::BLUE
                : (i == 1 ? Color::CYAN : i == 2 ? Color::MAGENTA : i == 3 ? Color::GREEN : Color::RED));
            _renderData.grid[g.y + offsetY][g.x] = {g.returning ? 'o' : 'G', color, Color::BLACK};
        }

        _renderData.texts.push_back({"PACMAN", 1, 0, Color::YELLOW});
        _renderData.texts.push_back({"Score: " + std::to_string(_score), 1, 1, Color::CYAN});

        if (_gameOver)
            _renderData.texts.push_back({_win ? "YOU WIN" : "GAME OVER", W / 2 - 4, offsetY + H / 2, _win ? Color::GREEN : Color::RED});
    }
}
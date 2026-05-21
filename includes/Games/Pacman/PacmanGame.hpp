/* ------------------------------------------------------------------------------------ *
 *                                                                                      *
 * EPITECH PROJECT - Mon, Apr, 2026                                                     *
 * Title           - Arcade                                                             *
 * Description     -                                                                    *
 *     PacmanGame                                                                       *
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

#include <array>
#include <chrono>
#include <string>
#include <vector>
#include <utility>
#include "IGameModule/IGameModule.hpp"

namespace Arcade {

class PacmanGame final : public IGameModule {
    public:
        PacmanGame();
        ~PacmanGame() override = default;

        void init() override;
        void reset() override;
        void close() override;
        const std::string &getName() const override;
        void handleInput(Key key) override;
        void update() override;
        const RenderData &getRenderData() override;
        int getScore() const override;
        bool isGameOver() const override;

    private:
        static constexpr int W = 19;
        static constexpr int H = 15;
        static constexpr int PX = W / 2;
        static constexpr int PY = H - 2;
        static constexpr int GX = W / 2;
        static constexpr int GY = H / 2;
        static constexpr auto PACMAN_DELAY = std::chrono::milliseconds(120);
        static constexpr auto GHOST_DELAY = std::chrono::milliseconds(170);
        static constexpr auto FRIGHT_DELAY = std::chrono::milliseconds(260);
        static constexpr auto GHOST_RELEASE = std::chrono::seconds(10);
        static constexpr auto POWER_TIME = std::chrono::seconds(10);
        static constexpr auto GHOST_RETURN = std::chrono::seconds(2);
        static constexpr auto WIN_RELOAD = std::chrono::seconds(1);

        struct Ghost {
            int x = 0;
            int y = 0;
            int homeX = 0;
            int homeY = 0;
            bool active = false;
            bool frightened = false;
            bool returning = false;
            std::chrono::steady_clock::time_point lastMove{};
            std::chrono::steady_clock::time_point stateStart{};
        };

        void buildMap();
        void buildRenderData();
        void movePacman();
        void moveGhosts();
        void moveGhost(Ghost &ghost, int index);
        void releaseGhosts();
        void eatCell();
        void checkWin();
        bool wall(int x, int y) const;
        std::pair<int, int> wrap(int x, int y) const;
        std::pair<int, int> toward(int x, int y, int tx, int ty) const;
        std::pair<int, int> away(int x, int y, int tx, int ty) const;

        std::string _name = "pacman";
        RenderData _renderData;
        std::vector<std::string> _map;
        std::array<Ghost, 4> _ghosts{};
        int _px = PX;
        int _py = PY;
        int _dx = 0;
        int _dy = 0;
        int _score = 0;
        int _dotsLeft = 0;
        int _speedBonus = 0;
        bool _gameOver = false;
        bool _win = false;
        bool _power = false;
        bool _ghostsOut = false;
        std::chrono::steady_clock::time_point _start{};
        std::chrono::steady_clock::time_point _lastPacmanMove{};
        std::chrono::steady_clock::time_point _powerStart{};
        std::chrono::steady_clock::time_point _winStart{};
    };
}
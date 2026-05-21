/* ------------------------------------------------------------------------------------ *
 *                                                                                      *
 * EPITECH PROJECT - Fri, Mar, 2026                                                     *
 * Title           - Arcade                                                             *
 * Description     -                                                                    *
 *     NCursesDisplay                                                                   *
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

#include <iostream>
#include <ncurses.h>

#include <stdexcept>

#include "Graphics/NCurses/NCursesDisplayModule.hpp"

namespace Arcade {

NCursesDisplayModule::NCursesDisplayModule() : _initialized(false)
{
}

NCursesDisplayModule::~NCursesDisplayModule()
{
    close();
}

void NCursesDisplayModule::init()
{
    if (_initialized)
        return;

    if (::initscr() == nullptr)
        throw std::runtime_error("failed to initialize ncurses");

    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
    _initialized = true;
}

void NCursesDisplayModule::close()
{
    if (!_initialized)
        return;

    endwin();
    _initialized = false;
}

const std::string &NCursesDisplayModule::getName() const
{
    static const std::string name = "NCurses";
    return name;
}

void NCursesDisplayModule::clear()
{
    ensureInitialized();
    ::erase();
}

void NCursesDisplayModule::render(const RenderData &data)
{
    ensureInitialized();

    const int maxY = static_cast<int>(data.grid.size());

    for (int y = 0; y < maxY; ++y) {
        const int maxX = static_cast<int>(data.grid[y].size());
        for (int x = 0; x < maxX; ++x) {
            const Cell &cell = data.grid[y][x];
            mvaddch(y, x, cell.character);
        }
    }

    for (const Text &text : data.texts)
        mvaddnstr(text.y, text.x, text.content.c_str(), static_cast<int>(text.content.size()));
}

void NCursesDisplayModule::display()
{
    ensureInitialized();
    refresh();
}

Key NCursesDisplayModule::pollEvent()
{
    ensureInitialized();
    int ch = getch();

    switch (ch) {
        case KEY_UP:
            return Key::UP;
        case KEY_DOWN:
            return Key::DOWN;
        case KEY_LEFT:
            return Key::LEFT;
        case KEY_RIGHT:
            return Key::RIGHT;
        case '\n':
            return Key::ENTER;
        case KEY_BACKSPACE:
        case 127:
            return Key::BACKSPACE;
        case ' ':
            return Key::SPACE;
        case 27:
            return Key::QUIT;
        case 'n':
            return Key::NEXT_LIB;
        case 'p':
            return Key::PREV_LIB;
        case 'r':
            return Key::RESTART;
        default:
            if (ch >= 'a' && ch <= 'z')
                return static_cast<Key>(static_cast<int>(Key::KEY_A) + (ch - 'a'));
            if (ch >= 'A' && ch <= 'Z')
                return static_cast<Key>(static_cast<int>(Key::KEY_A) + (ch - 'A'));
            return Key::NONE;
    }
}

void NCursesDisplayModule::ensureInitialized() const
{
    if (!_initialized)
        throw std::runtime_error("ncurses display not initialized");
}

} // namespace Arcade

extern "C" Arcade::IDisplayModule *entryPointDisplay()
{
    return new Arcade::NCursesDisplayModule();
}

extern "C" void destroyDisplay(Arcade::IDisplayModule *display)
{
    delete display;
}

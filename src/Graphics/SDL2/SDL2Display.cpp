/* ------------------------------------------------------------------------------------ *
 *                                                                                      *
 * EPITECH PROJECT - Fri, Mar, 2026                                                     *
 * Title           - Arcade                                                             *
 * Description     -                                                                    *
 *     SDL2Display                                                                      *
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

#include "Graphics/SDL2/SDL2DisplayModule.hpp"
#include <stdexcept>

namespace Arcade {

    SDL2DisplayModule::SDL2DisplayModule() : _initialized(false)
    {
    }

    SDL2DisplayModule::~SDL2DisplayModule()
    {
        close();
    }

    void SDL2DisplayModule::init()
    {
        if (_initialized)
            return;

        if (SDL_Init(SDL_INIT_VIDEO) < 0)
            throw std::runtime_error(SDL_GetError());

        if (TTF_Init() < 0)
            throw std::runtime_error(TTF_GetError());

        IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

        _window = SDL_CreateWindow(
            "Arcade",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            1280, 720,
            SDL_WINDOW_SHOWN
        );
        if (!_window)
            throw std::runtime_error(SDL_GetError());

        _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
        if (!_renderer)
            _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_SOFTWARE);
        if (!_renderer)
            throw std::runtime_error(SDL_GetError());

        _font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 16);
        if (!_font)
            _font = TTF_OpenFont("DejaVuSans.ttf", 16);
        if (!_font)
            throw std::runtime_error(TTF_GetError());

        _initialized = true;
    }

    void SDL2DisplayModule::close()
    {
        if (!_initialized)
            return;

        if (_font) {
            TTF_CloseFont(_font);
            _font = nullptr;
        }
        if (_renderer) {
            SDL_DestroyRenderer(_renderer);
            _renderer = nullptr;
        }
        if (_window) {
            SDL_DestroyWindow(_window);
            _window = nullptr;
        }

        for (auto &[path, tex] : _textureCache)
            SDL_DestroyTexture(tex);
        _textureCache.clear();

        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
        _initialized = false;
    }

    SDL_Texture* SDL2DisplayModule::loadTexture(const std::string &path)
    {
        auto it = _textureCache.find(path);
        if (it != _textureCache.end())
            return it->second;
        SDL_Surface *surface = IMG_Load(path.c_str());
        if (!surface)
            return nullptr;
        SDL_Texture *tex = SDL_CreateTextureFromSurface(_renderer, surface);
        SDL_FreeSurface(surface);
        _textureCache[path] = tex;
        return tex;
    }

    const std::string &SDL2DisplayModule::getName() const
    {
        static const std::string name = "SDL2";
        return name;
    }

    SDL_Color SDL2DisplayModule::toSDLColor(Color color) const
    {
        switch (color) {
            case Color::RED:     return {255, 0,   0,   255};
            case Color::GREEN:   return {0,   255, 0,   255};
            case Color::YELLOW:  return {255, 255, 0,   255};
            case Color::BLUE:    return {0,   0,   255, 255};
            case Color::MAGENTA: return {255, 0,   255, 255};
            case Color::CYAN:    return {0,   255, 255, 255};
            case Color::BLACK:   return {0,   0,   0,   255};
            default:             return {255, 255, 255, 255};
        }
    }

    void SDL2DisplayModule::clear()
    {
        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
        SDL_RenderClear(_renderer);
    }

    void SDL2DisplayModule::render(const RenderData &data)
    {
        _renderData = data;
        static const std::unordered_map<char, std::string> SPRITE_MAP = {
            {'^', "assets/player.png"},
            {'W', "assets/invader.png"},
            {'|', "assets/bullet.png"},
            {'v', "assets/enemy_bullet.png"},
        };

        for (int y = 0; y < (int)data.grid.size(); ++y) {
            for (int x = 0; x < (int)data.grid[y].size(); ++x) {
                const Cell &cell = data.grid[y][x];
                SDL_Rect dst = {x * CELL_W, y * CELL_H, CELL_W, CELL_H} ;

                auto spriteIt = SPRITE_MAP.find(cell.character);
                if (spriteIt != SPRITE_MAP.end()) {
                    SDL_Texture *tex = loadTexture(spriteIt->second);
                    if (tex) {
                        SDL_RenderCopy(_renderer, tex, nullptr, &dst);
                        continue;
                    }
                }

                if (cell.character == ' ')
                    continue;
                char str[2] = {cell.character, '\0'};
                SDL_Color fg = toSDLColor(cell.fgColor);
                SDL_Surface *surface = TTF_RenderText_Solid(_font, str, fg);
                if (!surface)
                    continue;
                SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surface);
                SDL_FreeSurface(surface);
                if (!texture)
                    continue;
                SDL_RenderCopy(_renderer, texture, nullptr, &dst);
                SDL_DestroyTexture(texture);
            }
        }

        for (const Text &text : data.texts) {
            if (text.content.empty())
                continue;
            SDL_Color fg = toSDLColor(text.color);
            SDL_Surface *surface = TTF_RenderText_Solid(_font, text.content.c_str(), fg);
            if (!surface)
                continue;
            SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surface);
            int w, h;
            SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
            SDL_FreeSurface(surface);
            if (!texture)
                continue;

            SDL_Rect dst = {text.x * CELL_W, text.y * CELL_H, w, h};
            SDL_RenderCopy(_renderer, texture, nullptr, &dst);
            SDL_DestroyTexture(texture);
        }
    }

    void SDL2DisplayModule::display()
    {
        SDL_RenderPresent(_renderer);
    }

    Key SDL2DisplayModule::pollEvent()
    {
        SDL_Event event;
        if (!SDL_PollEvent(&event))
            return Key::NONE;

        if (event.type == SDL_QUIT)
            return Key::QUIT;

        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_UP:       return Key::UP;
                case SDLK_DOWN:     return Key::DOWN;
                case SDLK_LEFT:     return Key::LEFT;
                case SDLK_RIGHT:    return Key::RIGHT;
                case SDLK_RETURN:   return Key::ENTER;
                case SDLK_BACKSPACE:return Key::BACKSPACE;
                case SDLK_SPACE:    return Key::SPACE;
                case SDLK_m:        return Key::NEXT_LIB;
                case SDLK_p:        return Key::PREV_LIB;
                case SDLK_r:        return Key::RESTART;
                case SDLK_ESCAPE:   return Key::QUIT;
                default:
                    if (event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z)
                        return (Key)((int)Key::KEY_A + (event.key.keysym.sym - SDLK_a));
                    return Key::NONE;
            }
        }

        //if (event.type == SDL_MOUSEBUTTONDOWN) {
        //    const int pixelX = event.button.x;
        //    const int pixelY = event.button.y;
//
        //    for (auto &area : _renderData.clickableAreas) {
        //        if (pixelX >= area.x * CELL_W &&
        //            pixelX <  (area.x + area.width)  * CELL_W &&
        //            pixelY >= area.y * CELL_H &&
        //            pixelY <  (area.y + area.height) * CELL_H) {
        //            _lastClickableArea = &area;
        //            return area.action;
        //        }
        //    }
        //    if (event.button.button == SDL_BUTTON_LEFT)
        //        return Key::MOUSE_LEFT;
        //    if (event.button.button == SDL_BUTTON_RIGHT)
        //        return Key::MOUSE_RIGHT;
        //}

        return Key::NONE;
    }

    //ClickableArea *SDL2DisplayModule::getLastClickableArea()
    //{
    //    ClickableArea *result = _lastClickableArea;
    //    _lastClickableArea = nullptr;
    //    return result;
    //}

}

extern "C" Arcade::IDisplayModule *entryPointDisplay()
{
    return new Arcade::SDL2DisplayModule();
}

extern "C" void destroyDisplay(Arcade::IDisplayModule *display)
{
    delete display;
}
/* ------------------------------------------------------------------------------------ *
 *                                                                                      *
 * EPITECH PROJECT - Thu, Apr, 2026                                                     *
 * Title           - G-OOP-400-NCE-4-1-arcade-3                                         *
 * Description     -                                                                    *
 *     SDL2DisplayModule                                                                *
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

#ifndef INCLUDED_SDL2DISPLAYMODULE_HPP
    #define INCLUDED_SDL2DISPLAYMODULE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <unordered_map>

#include "IDisplayModule/IDisplayModule.hpp"

namespace Arcade {

    class SDL2DisplayModule : public IDisplayModule {
        public:
            SDL2DisplayModule();
            ~SDL2DisplayModule();

            void init() override;
            void close() override;
            const std::string &getName() const override;
            void clear() override;
            void render(const RenderData &data) override;
            void display() override;
            Key pollEvent() override;
            //ClickableArea *getLastClickableArea() override;

        private:
            RenderData _renderData;
            //ClickableArea *_lastClickableArea = nullptr;

            static constexpr int CELL_W = 12;
            static constexpr int CELL_H = 18;

            SDL_Window *_window = nullptr;
            SDL_Renderer *_renderer = nullptr;
            TTF_Font *_font = nullptr;
            bool _initialized = false;

            SDL_Color toSDLColor(Color color) const;

            std::unordered_map<std::string, SDL_Texture*> _textureCache;
            SDL_Texture* loadTexture(const std::string &path);
        };

}

#endif
/* ------------------------------------------------------------------------------------ *
 *                                                                                      *
 * EPITECH PROJECT - Wed, Mar, 2026                                                     *
 * Title           - Arcade                                                             *
 * Description     -                                                                    *
 *     NCursesDisplayModule                                                             *
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

#ifndef INCLUDED_NCURSESDISPLAYMODULE_HPP
    #define INCLUDED_NCURSESDISPLAYMODULE_HPP

#include <string>

#include "IDisplayModule/IDisplayModule.hpp"

namespace Arcade {

class NCursesDisplayModule : public IDisplayModule
{
    public:
        NCursesDisplayModule();
        ~NCursesDisplayModule() override;

        void init() override;
        void close() override;
        const std::string &getName() const override;
        void clear() override;
        void render(const RenderData &data) override;
        void display() override;
        Key pollEvent() override;

        private:
        void ensureInitialized() const;

        bool _initialized;
};

    } // namespace Arcade

#endif
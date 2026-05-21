/*
** EPITECH PROJECT, 2025
** G-OOP-400-NCE-4-1-arcade-3
** File description:
** QT5DisplayModule.hpp
*/

#ifndef INCLUDED_QT5DISPLAYMODULE_HPP_
    #define INCLUDED_QT5DISPLAYMODULE_HPP_

    #include <string>
    #include "IDisplayModule/IDisplayModule.hpp"
    #include "QT5ArcadeView.hpp"

    #include <QApplication>
    #include <QMainWindow>

    namespace Arcade {

        class QT5DisplayModule : public IDisplayModule
        {
            public:
                QT5DisplayModule();
                ~QT5DisplayModule() override;
                void init() override;
                void close() override;
                const std::string &getName() const override;
                void clear() override;
                void render(const RenderData &data) override;
                void display() override;
                Key pollEvent() override;
                //ClickableArea *getLastClickableArea() override;
            private:
                QApplication *_app;
                QMainWindow *_window;
                bool _initialized;
                bool _ownsApp;
                QT5ArcadeView *_view;
        };

    } //namespace arcade
#endif /* INCLUDED_QT5DISPLAYMODULE_HPP_ */
/*
** EPITECH PROJECT, 2025
** G-OOP-400-NCE-4-1-arcade-3
** File description:
** QT5Display.cpp
*/

#include <iostream>
#include "Graphics/Qt5/QT5DisplayModule.hpp"

namespace Arcade {
    QT5DisplayModule::QT5DisplayModule()
        : _app(nullptr), _window(nullptr), _initialized(false), _view(nullptr)
    {}

    QT5DisplayModule::~QT5DisplayModule()
    {
        close();
    }

    void QT5DisplayModule::init()
    {
        if (_initialized)
            return;

        if (QApplication::instance()) {
            _app = static_cast<QApplication *>(QApplication::instance());
            _ownsApp = false;
        } else {
            static int argc = 1;
            static char appName[] = "arcade";
            static char *argv[] = {appName, nullptr};
            _app = new QApplication(argc, argv);
            _app->setApplicationName("arcade");
            _ownsApp = true;
        }

        if (!_window) {
            _window = new QMainWindow();
            _window->setWindowTitle("Arcade");
            _window->resize(800, 600);
            _view = new QT5ArcadeView(_window);
            _window->setCentralWidget(_view);
        }

        _window->show();
        _initialized = true;
    }

    void QT5DisplayModule::close()
    {
        if (!_initialized)
            return;

        if (_window)
            _window->hide();

        _initialized = false;
    }

    void QT5DisplayModule::display()
    {
        if (!_initialized || !_app)
            return;
        QApplication::processEvents();
    }

    void QT5DisplayModule::clear()
    {}

    void QT5DisplayModule::render(const RenderData &data)
    {
        if (_view)
            _view->setRenderData(data);
    }

    Key QT5DisplayModule::pollEvent()
    {
        if (!_initialized || !_app)
            return Key::NONE;
        QApplication::processEvents();
        if (!_window || !_window->isVisible())
            return Key::QUIT;
        if (_view)
            return _view->popKey();
        return Key::NONE;
    }

    const std::string &QT5DisplayModule::getName() const
    {
        static const std::string name = "Qt5";
        return name;
    }

    //ClickableArea *QT5DisplayModule::getLastClickableArea()
    //{
    //    if (!_view)
    //        return nullptr;
    //    return _view->getLastClickableArea();
    //}
}

extern "C" Arcade::IDisplayModule *entryPointDisplay()
{
    return new Arcade::QT5DisplayModule();
}

extern "C" void destroyDisplay(Arcade::IDisplayModule *display)
{
    delete display;
}

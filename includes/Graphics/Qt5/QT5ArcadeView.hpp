/*
** EPITECH PROJECT, 2025
** G-OOP-400-NCE-4-1-arcade-3
** File description:
** QT5AracdeView.hpp
*/

#ifndef QT5ARCADE_VIEW_HPP_
    #define QT5ARCADE_VIEW_HPP_

    #include <queue>
    #include <QWidget>
    #include <QKeyEvent>
    #include <QMouseEvent>
    #include <QCloseEvent>
    #include <QPainter>

    #include "Arcade/Types.hpp"

    namespace Arcade {
        class QT5ArcadeView : public QWidget {
            public:
                explicit QT5ArcadeView(QWidget *parent = nullptr);
                ~QT5ArcadeView() override = default;
                void setRenderData(const Arcade::RenderData &data) ;
                Arcade::Key popKey();
                //Arcade::ClickableArea *getLastClickableArea();
            protected:
                void paintEvent(QPaintEvent *) override;
                void keyPressEvent(QKeyEvent *event) override;
                //void mousePressEvent(QMouseEvent *event) override;
                //void mouseReleaseEvent(QMouseEvent *event) override;
                //void mouseMoveEvent(QMouseEvent *event) override;
                void closeEvent(QCloseEvent *event) override;
            private:
                Arcade::RenderData _data;
                std::queue<Arcade::Key> _keys;
                QMap<QString, QPixmap> _pixmapCache;
                //Arcade::ClickableArea *_lastClickableArea = nullptr;
        };
    } //namespace arcade

#endif /* QT5ARCADE_VIEW_HPP_ */

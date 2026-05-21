/*
** EPITECH PROJECT, 2025
** G-OOP-400-NCE-4-1-arcade-3
** File description:
** QT5AracdeView.cpp
*/

#include "Graphics/Qt5/QT5ArcadeView.hpp"

using namespace Arcade;

QT5ArcadeView::QT5ArcadeView(QWidget *parent) : QWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);
}

void QT5ArcadeView::setRenderData(const RenderData &data)
{
    _data = data;
    update();
}

Key QT5ArcadeView::popKey()
{
    if (_keys.empty())
        return Key::NONE;
    Key key = _keys.front();
    _keys.pop();
    return key;
}

void QT5ArcadeView::paintEvent(QPaintEvent *event)
{
    (void)event;

    static const std::map<char, std::string> SPRITE_MAP = {
        {'^', "assets/player.png"},
        {'W', "assets/invader.png"},
        {'|', "assets/bullet.png"},
        {'v', "assets/enemy_bullet.png"},
    };

    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);
    QFont font("Monospace");
    font.setStyleHint(QFont::TypeWriter);
    font.setPointSize(12);
    painter.setFont(font);
    painter.setPen(Qt::white);
    for (const auto &row : _data.grid) {
        for (const auto &cell : row) {
            const int x = (&cell - row.data()) * Arcade::CELL_WIDTH;
            const int y = (&row - _data.grid.data()) * Arcade::CELL_HEIGHT;
            QRect dst(x, y, Arcade::CELL_WIDTH, Arcade::CELL_HEIGHT);

            auto spriteIt = SPRITE_MAP.find(cell.character);
            if (spriteIt != SPRITE_MAP.end()) {
                QString key = QString::fromStdString(spriteIt->second);
                if (!_pixmapCache.contains(key))
                    _pixmapCache[key] = QPixmap(key);
                if (!_pixmapCache[key].isNull()) {
                    painter.drawPixmap(dst, _pixmapCache[key]);
                    continue;
                }
            }

            painter.drawText(x, y + Arcade::CELL_HEIGHT, QString(cell.character));
        }
    }
    for (const auto &text : _data.texts) {
        const int px = text.x * Arcade::CELL_WIDTH;
        const int py = (text.y + 1) * Arcade::CELL_HEIGHT;
        painter.drawText(px, py, QString::fromStdString(text.content));
    }
}

void QT5ArcadeView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Return:
        case Qt::Key_Enter:
            _keys.push(Key::ENTER);
            break;
        case Qt::Key_Backspace:
            _keys.push(Key::BACKSPACE);
            break;
        case Qt::Key_Space:
            _keys.push(Key::SPACE);
            break;
        case Qt::Key_Escape:
            _keys.push(Key::QUIT);
            break;
        case Qt::Key_N:
            _keys.push(Key::NEXT_LIB);
            break;
        case Qt::Key_P:
            _keys.push(Key::PREV_LIB);
            break;
        case Qt::Key_R:
            _keys.push(Key::RESTART);
            break;
        case Qt::Key_Up:
            _keys.push(Key::UP);
            break;
        case Qt::Key_Down:
            _keys.push(Key::DOWN);
            break;
        case Qt::Key_Left:
            _keys.push(Key::LEFT);
            break;
        case Qt::Key_Right:
            _keys.push(Key::RIGHT);
            break;
        default:
            if (event->key() >= Qt::Key_A && event->key() <= Qt::Key_Z)
                _keys.push(static_cast<Key>(static_cast<int>(Key::KEY_A) + (event->key() - Qt::Key_A)));
            break;
    }
}

void QT5ArcadeView::closeEvent(QCloseEvent *event)
{
    _keys.push(Key::QUIT);
    QWidget::closeEvent(event);
}

//void QT5ArcadeView::mousePressEvent(QMouseEvent *event)
//{
//    const int pixelX = event->pos().x();
//    const int pixelY = event->pos().y();
//
//    for (auto &area : _data.clickableAreas) {
//        if (pixelX >= area.x * Arcade::CELL_WIDTH &&
//            pixelX < (area.x + area.width) * Arcade::CELL_WIDTH &&
//            pixelY >= area.y * Arcade::CELL_HEIGHT &&
//            pixelY < (area.y + area.height) * Arcade::CELL_HEIGHT) {
//            _lastClickableArea = &area;
//            _keys.push(area.action);
//            return;
//        }
//    }
//    if (event->button() == Qt::LeftButton) {
//        _keys.push(Key::MOUSE_LEFT);
//    } else if (event->button() == Qt::RightButton) {
//        _keys.push(Key::MOUSE_RIGHT);
//    }
//}

//void QT5ArcadeView::mouseReleaseEvent(QMouseEvent *event)
//{
//    (void)event;
//}
//
//void QT5ArcadeView::mouseMoveEvent(QMouseEvent *event)
//{
//    int gridX = event->pos().x() / Arcade::CELL_WIDTH;
//    int gridY = event->pos().y() / Arcade::CELL_HEIGHT;
//    
//    (void)gridX;
//    (void)gridY;
//}

//Arcade::ClickableArea *QT5ArcadeView::getLastClickableArea()
//{
//    Arcade::ClickableArea *result = _lastClickableArea;
//    _lastClickableArea = nullptr;
//    return result;
//}

/*
==========
Copyright 2002 Energon Software

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software Foundation,
Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
==========
*/


#if !defined GLWIDGET_H
#define GLWIDGET_H


#include <qgl.h>

#include "Shared.h"


class QWidget;
class QCloseEvent;
class QKeyEvent;
class QTimer;


class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    GLWidget();

public:
    // starts the rendering timer
    void startTimer();

public:
    // returns <width, height>
    const Shared::Coordinates getSize() const;

    const bool getPaddle1Moved() const { return m_paddle1Moved; }
    const bool getPaddle2Moved() const { return m_paddle2Moved; }

public slots:
    void paddle2Moved();

private slots:
    void timesUp();

signals:
    // ball hit a paddle
    void paddle1Collision();
    void paddle2Collision();

    // ball hit the ceiling or floor
    void wallCollision();

    // score for player1
    void score1();

    // score for player2
    void score2();

    // player2 paddle needs to think now
    void paddle2Think();

protected:
    virtual void initializeGL();
    virtual void resizeGL(int width, int height);
    virtual void paintGL();

protected:
    virtual void closeEvent(QCloseEvent* event);
    virtual void keyPressEvent(QKeyEvent* event);

private:
    void render();
    void collisionDetection();
    void renderTable();

private:
    QTimer* m_timer;
    int m_width;
    int m_height;

    bool m_safeUpdate;
    bool m_paddle1Moved;
    bool m_paddle2Moved;
};


#endif

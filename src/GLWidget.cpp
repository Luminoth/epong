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


#include <qgl.h>
#include <qevent.h>
#include <qtimer.h>

#include "GLWidget.h"
#include "Game.h"
#include "Paddle.h"
#include "Ball.h"
#include "Shared.h"


/*
 *  external globals
 *
 */

extern Game g_game;


/*
 *  GLWidget methods
 *
 */


GLWidget::GLWidget() : QGLWidget()
{
    m_width  = 0;
    m_height = 0;
    m_safeUpdate = false;
    m_paddle1Moved = m_paddle2Moved = false;

    setCaption("Pong");

    m_timer = new QTimer();
    connect(m_timer, SIGNAL(timeout()), SLOT(timesUp()));
}


void GLWidget::startTimer()
{
    m_timer->start(100);
}


const Shared::Coordinates GLWidget::getSize() const
{
    return Shared::Coordinates(m_width, m_height);
}


void GLWidget::paddle2Moved()
{
    m_paddle2Moved = true;
}


void GLWidget::timesUp()
{
    m_safeUpdate = true;
    updateGL();
    m_safeUpdate = false;
}


void GLWidget::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}


void GLWidget::resizeGL(int width, int height)
{
    m_width  = width;
    m_height = height;
    if(0 == m_height)
        m_height = 1;

    g_game.reset();

    glViewport(0, 0, static_cast<GLint>(m_width), static_cast<GLint>(m_height));
}


void GLWidget::paintGL()
{
    if(m_safeUpdate) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        g_game.ball()->move();
        emit paddle2Think();

        collisionDetection();

        render();

        m_paddle1Moved = false;
        m_paddle2Moved = false;
    }
}


void GLWidget::closeEvent(QCloseEvent* event)
{
    g_game.stop();
    event->accept();
}


void GLWidget::keyPressEvent(QKeyEvent* event)
{
    const Shared::Coordinates& h = g_game.player1Paddle()->getBoundingBox().second;

    switch(event->key())
    {
    case Key_Escape:
        close();
        break;
    case Key_Up:
        if(h.first < m_height-10.0f) {
            g_game.player1Paddle()->moveUp();
            m_paddle1Moved = true;
        }
        break;
    case Key_Down:
        if(h.second > 10.0f) {
            g_game.player1Paddle()->moveDown();
            m_paddle1Moved = true;
        }
        break;
    case Key_R:
        g_game.reset();
        break;
    };
    event->ignore();
}


void GLWidget::collisionDetection()
{
    const Shared::Coordinates& bw  = g_game.ball()->getBoundingBox().first;
    const Shared::Coordinates& bh  = g_game.ball()->getBoundingBox().second;
    const Shared::Coordinates& p1w = g_game.player1Paddle()->getBoundingBox().first;
    const Shared::Coordinates& p1h = g_game.player1Paddle()->getBoundingBox().second;
    const Shared::Coordinates& p2w = g_game.player2Paddle()->getBoundingBox().first;
    const Shared::Coordinates& p2h = g_game.player2Paddle()->getBoundingBox().second;

    if((bh.first > m_height-20.0f && g_game.ball()->getYDirection() == Shared::UP) ||
       (bh.second < 20.0f && g_game.ball()->getYDirection() == Shared::DOWN))
        emit wallCollision();

    if((bh.first > p1h.second && bh.second < p1h.first) &&
       (bw.first <= p1w.second && bw.first > p1w.first) &&
       (g_game.ball()->getXDirection() == Shared::LEFT))
        emit paddle1Collision();
    else if((bh.first > p2h.second && bh.second < p2h.first) &&
            (bw.second >= p2w.first && bw.second < p2w.second) &&
            (g_game.ball()->getXDirection() == Shared::RIGHT))
        emit paddle2Collision();

    else if((bw.first > m_width+10) && g_game.ball()->getXDirection() == Shared::RIGHT)
        emit score1();
    else if((bw.second < 10.0f) && g_game.ball()->getXDirection() == Shared::LEFT)
        emit score2();
}


void GLWidget::render()
{
    renderTable();

    g_game.player1Paddle()->render(m_width, m_height);
    g_game.player2Paddle()->render(m_width, m_height);

    g_game.ball()->render(m_width, m_height);
}


void GLWidget::renderTable()
{
    bool enableDepth = false;
    if(glIsEnabled(GL_DEPTH_TEST)) {
        glDisable(GL_DEPTH_TEST);
        enableDepth = true;
    }

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();

    glLoadIdentity();
    glOrtho(0, m_width, 0, m_height, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, 0.0f);

    // the table
    glBegin(GL_LINE_LOOP);
        glVertex2f(10.0f, m_height-10.0f);
        glVertex2f(m_width-10.0f, m_height-10.0f);
        glVertex2f(m_width-10.0f, 10.0f);
        glVertex2f(10.0f, 10.0f);
    glEnd();

    // the middle line
    glBegin(GL_LINES);
        glVertex2f(m_width/2.0f, 10.0f);
        glVertex2f(m_width/2.0f, m_height-10.0f);
    glEnd();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    if(enableDepth)
        glEnable(GL_DEPTH_TEST);
}

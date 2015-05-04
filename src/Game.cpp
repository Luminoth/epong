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


#include <qmessagebox.h>

#include "Game.h"
#include "MainWindow.h"
#include "GLWidget.h"
#include "Paddle.h"
#include "Ball.h"
#include "Shared.h"
#include "main.h"


/*
 *  external globals
 *
 */

extern MainWindow* g_window;


/*
 *  Game methods
 *
 */


Game::Game() : m_glWidget(NULL), m_ball(NULL), m_player1Paddle(NULL), m_player2Paddle(NULL)
{
}


Game::~Game() throw()
{
    stop();
}


void Game::wallCollision()
{
    if(m_ball)
        m_ball->reverseY();
}


void Game::paddle1Collision()
{
    if(m_ball)
        m_ball->reverseX(m_glWidget->getPaddle1Moved(), m_player1Paddle->getDirection());
}


void Game::paddle2Collision()
{
    if(m_ball)
        m_ball->reverseX(m_glWidget->getPaddle2Moved(), m_player2Paddle->getDirection());
}


void Game::paddle2Think()
{
    const float py = m_player2Paddle->getCenter().second;
    const Shared::Coordinates& ph = m_player2Paddle->getBoundingBox().second;
    const Shared::Coordinates& bw = m_ball->getBoundingBox().first;
    const Shared::Coordinates& bh = m_ball->getBoundingBox().second;
    const Shared::Coordinates& s = m_glWidget->getSize();

    // only track on our half of the table
    if(bw.second > s.first*0.5555f) {
        if(bh.first > py) {
            if(ph.first < s.second-10.0f) {
                m_player2Paddle->moveUp();
                emit paddle2Moved();
            }
        } else if(bh.second < py) {
            if(ph.second > 10.0f) {
                m_player2Paddle->moveDown();
                emit paddle2Moved();
            }
        }
    }
}


void Game::start()
{
    stop();

    m_glWidget = new GLWidget();
    if(!m_glWidget->isValid()) {
        QMessageBox::critical(NULL, "OpenGL Error", "No OpenGL subsystem found.");
        Main::cleanup();
        exit(1);
    }
    m_glWidget->resize(Main::SCREEN_WIDTH, Main::SCREEN_HEIGHT);
    m_glWidget->show();
    m_glWidget->startTimer();

    g_window->resetScore();

    m_glWidget->connect(m_glWidget, SIGNAL(wallCollision()), this, SLOT(wallCollision()));
    m_glWidget->connect(m_glWidget, SIGNAL(paddle1Collision()), this, SLOT(paddle1Collision()));
    m_glWidget->connect(m_glWidget, SIGNAL(paddle2Collision()), this, SLOT(paddle2Collision()));
    m_glWidget->connect(m_glWidget, SIGNAL(score1()), g_window, SLOT(player1Score()));
    m_glWidget->connect(m_glWidget, SIGNAL(score2()), g_window, SLOT(player2Score()));
    m_glWidget->connect(m_glWidget, SIGNAL(paddle2Think()), this, SLOT(paddle2Think()));
    connect(this, SIGNAL(paddle2Moved()), m_glWidget, SLOT(paddle2Moved()));

    reset();
}


void Game::stop() throw()
{
    if(m_glWidget) {
        delete m_glWidget;
        m_glWidget = NULL;
    }

    if(m_ball) {
        delete m_ball;
        m_ball = NULL;
    }

    if(m_player1Paddle) {
        delete m_player1Paddle;
        m_player1Paddle = NULL;
    }

    if(m_player2Paddle) {
        delete m_player2Paddle;
        m_player2Paddle = NULL;
    }
}


void Game::reset()
{
    const Shared::Coordinates& s = m_glWidget->getSize();

    if(m_ball)
        delete m_ball;
    m_ball = new Ball(static_cast<int>(s.first), static_cast<int>(s.second));

    if(m_player1Paddle)
        delete m_player1Paddle;
    m_player1Paddle = new Paddle(50.0f, s.second/2.0f);

    if(m_player2Paddle)
        delete m_player2Paddle;
    m_player2Paddle = new Paddle(s.first-50.0f, s.second/2.0f);
}

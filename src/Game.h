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


#if !defined GAME_H
#define GAME_H


#include <qobject.h>

#include "Ball.h"
#include "Paddle.h"


class GLWidget;
class Ball;
class Paddle;


class Game : public QObject
{
    Q_OBJECT
public:
    enum GameType { SINGLE_PLAYER, MULTI_PLAYER };

public:
    Game();
    virtual ~Game() throw();

public:
    // start/stop the game
    void start();
    void stop() throw();

    // resets the game except for the score
    void reset();

public:
    // sets the type of game
    void setType(GameType type) { m_type = type; }

    // gets the type of game
    const GameType getType() const { return m_type; }

public:
    Ball* ball()            const { return m_ball; }
    Paddle* player1Paddle() const { return m_player1Paddle; }
    Paddle* player2Paddle() const { return m_player2Paddle; }

signals:
    // emitted when paddle 2 moves
    void paddle2Moved();

public slots:
    void wallCollision();
    void paddle1Collision();
    void paddle2Collision();
    void paddle2Think();

private:
    GLWidget* m_glWidget;
    Ball*     m_ball;
    Paddle*   m_player1Paddle;
    Paddle*   m_player2Paddle;

    GameType m_type;
};


#endif

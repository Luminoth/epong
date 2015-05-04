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


#if !defined BALL_H
#define BALL_H


#include <pair.h>

#include "Game.h"
#include "Paddle.h"
#include "Shared.h"


class Ball
{
private:
    static const float SIZE;
    static const float XACCEL;
    static const float YACCEL;

public:
    Ball(const int windowWidth, const int windowHeight);

public:
    // renders the ball
    void render(const int windowWidth, const int windowHeight) const;

    // moves the ball
    void move();

    // reverses the ball's direction on an axis
    void reverseX(const bool paddleMoved, const Shared::Direction paddleDirection);
    void reverseY();

public:
    // returns < <left, right>, <top, bottom> >
    const std::pair<Shared::Coordinates, Shared::Coordinates> getBoundingBox() const;

    // returns the balls current direction
    const Shared::Direction getXDirection() const { return m_xDirection; }
    const Shared::Direction getYDirection() const { return m_yDirection; }

private:
    float m_x, m_y;
    float m_xAccel, m_yAccel;

    Shared::Direction m_xDirection;
    Shared::Direction m_yDirection;
};


#endif

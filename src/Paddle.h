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


#if !defined PADDLE_H
#define PADDLE_H


#include <pair.h>

#include "Shared.h"


class Paddle
{
private:
    static const float WIDTH;
    static const float HEIGHT;
    static const float ACCEL;

public:
    Paddle();
    Paddle(const float startX, const float startY);

public:
    // renders the paddle
    void render(const int windowWidth, const int windowHeight) const;

    // moves the paddle (TODO: replace with ++ and -- operators)
    void moveUp();
    void moveDown();

public:
    // returns < <left, right>, <top, bottom> >
    const std::pair<Shared::Coordinates, Shared::Coordinates> getBoundingBox() const;

    // returns <x, y>
    const Shared::Coordinates getCenter() const;

    const Shared::Direction getDirection() const { return m_direction; }

private:
    float m_x, m_y;

    Shared::Direction m_direction;
};


#endif

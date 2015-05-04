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


#include <pair.h>

#include <GL/gl.h>

#include "Paddle.h"
#include "Shared.h"


/*
 *  constant initialization
 *
 */

const float Paddle::WIDTH  = 10.0f;
const float Paddle::HEIGHT = 100.0f;
const float Paddle::ACCEL  = 10.0f;


/*
 *  Paddle methods
 *
 */


Paddle::Paddle() : m_x(0.0f), m_y(0.0f), m_direction(Shared::NONE)
{
}


Paddle::Paddle(const float startX, const float startY) : m_x(startX), m_y(startY), m_direction(Shared::NONE)
{
}


void Paddle::render(const int windowWidth, const int windowHeight) const
{
    bool enableDepth = false;
    if(glIsEnabled(GL_DEPTH_TEST)) {
        glDisable(GL_DEPTH_TEST);
        enableDepth = true;
    }

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();

    glLoadIdentity();
    glOrtho(0, windowWidth, 0, windowHeight, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glLoadIdentity();
    glTranslatef(m_x, m_y, 0.0f);

    const float x = WIDTH/2.0f;
    const float y = HEIGHT/2.0f;

    glBegin(GL_QUADS);
        glVertex2f(-x,  y);
        glVertex2f( x,  y);
        glVertex2f( x, -y);
        glVertex2f(-x, -y);
    glEnd();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    if(enableDepth)
        glEnable(GL_DEPTH_TEST);
}


void Paddle::moveUp()
{
    m_y += ACCEL;
    m_direction = Shared::UP;
}


void Paddle::moveDown()
{
    m_y -= ACCEL;
    m_direction = Shared::DOWN;
}


const std::pair<Shared::Coordinates, Shared::Coordinates> Paddle::getBoundingBox() const
{
    using namespace Shared;
    const float x = WIDTH/2.0f;
    const float y = HEIGHT/2.0f;

    return std::pair<Coordinates, Coordinates>(Coordinates(m_x - x, m_x + x), Coordinates(m_y + y, m_y - y));
}


const Shared::Coordinates Paddle::getCenter() const
{
    return Shared::Coordinates(m_x, m_y);
}

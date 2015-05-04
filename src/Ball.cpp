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


#include <cstdlib>

#include <pair.h>

#include <GL/gl.h>

#include "Ball.h"
#include "Shared.h"


/*
 *  constant initialization
 *
 */

const float Ball::SIZE   =  10.0f;
const float Ball::XACCEL = 12.5f;
const float Ball::YACCEL = 9.0f;


/*
 *  constants
 *
 */

// speed up
const float ACCEL_UP_OFFSET = 2.0f;

// slow down
const float ACCEL_DOWN_OFFSET = 0.5f;


/*
 *  Ball methods
 *
 */


Ball::Ball(const int windowWidth, const int windowHeight) : m_x(windowWidth/2.0f), m_y(windowHeight/2.0f), m_xAccel(-XACCEL), m_yAccel(-YACCEL), m_xDirection(Shared::LEFT), m_yDirection(Shared::DOWN)
{
}


void Ball::render(const int windowWidth, const int windowHeight) const
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

    const float s = SIZE/2.0f;

    glBegin(GL_QUADS);
        glVertex2f(-s,  s);
        glVertex2f( s,  s);
        glVertex2f( s, -s);
        glVertex2f(-s, -s);
    glEnd();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    if(enableDepth)
        glEnable(GL_DEPTH_TEST);
}


void Ball::move()
{
    m_x += m_xAccel;
    m_y += m_yAccel;
}


void Ball::reverseX(const bool paddleMoved, const Shared::Direction direction)
{
    using namespace Shared;

    m_xAccel *= -1.0f;
    if(m_xAccel < 0)
        m_xDirection = LEFT;
    else
        m_xDirection = RIGHT;

    if(paddleMoved) {
        switch(direction)
        {
        case NONE:
        case LEFT:
        case RIGHT:
            break;
        case UP:
            if(m_yAccel > 0)
                m_yAccel += ACCEL_UP_OFFSET;
            else
                m_yAccel += ACCEL_DOWN_OFFSET;
            break;
        case DOWN:
            if(m_yAccel < 0)
                m_yAccel -= ACCEL_UP_OFFSET;
            else
                m_yAccel += ACCEL_DOWN_OFFSET;
            break;
        };
    }
}


void Ball::reverseY()
{
    m_yAccel *= -1.0f;
    if(m_yAccel < 0)
        m_yDirection = Shared::DOWN;
    else
        m_yDirection = Shared::UP;

    if(m_yAccel < 0) {
        if(m_yAccel < -YACCEL) m_yAccel += ACCEL_DOWN_OFFSET;
        else m_yAccel = -YACCEL;
    } else {
        if(m_yAccel > YACCEL) m_yAccel -= ACCEL_DOWN_OFFSET;
        else m_yAccel = YACCEL;
    }
}


const std::pair<Shared::Coordinates, Shared::Coordinates> Ball::getBoundingBox() const
{
    using namespace Shared;
    const float s = SIZE/2.0f;

    return std::pair<Coordinates, Coordinates>(Coordinates(m_x - s, m_x + s), Coordinates(m_y + s, m_y - s));
}

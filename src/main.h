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


#if !defined MAIN_H
#define MAIN_H


namespace Main
{
    /*
     *  constants
     *
     */

    // size of the GL window
    const int SCREEN_WIDTH  = 640;
    const int SCREEN_HEIGHT = 480;


    /*
     *  prototypes
     *
     */

    // cleans up after the program
    void cleanup();
};


#endif

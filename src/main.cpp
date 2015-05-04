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

#include <qapplication.h>

#include "main.h"
#include "Game.h"
#include "MainWindow.h"
#include "Shared.h"


/*
 *  globals
 *
 */

MainWindow* g_window = NULL;
Game g_game;


namespace Main
{
    /*
     *  functions
     *
     */

    void cleanup()
    {
        g_game.stop();
        if(g_window) {
            delete g_window;
            g_window = NULL;
        }
    }
};


/*
 *  functions
 *
 */


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    srand(time(NULL));

    g_window = new MainWindow(150, 80, Shared::PROGNAME);
    app.setMainWidget(g_window);
    g_window->show();

    int ret = app.exec();
    Main::cleanup();
    return ret;
}

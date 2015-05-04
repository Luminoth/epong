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


#if !defined MAINWINDOW_H
#define MAINWINDOW_H


#include <string>

#include <qmainwindow.h>


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(const int width, const int height, const std::string& title);

public slots:
    void resetScore();

private slots:
    void newGame();
    void about();
    void aboutQt();
    void player1Score();
    void player2Score();
};


#endif

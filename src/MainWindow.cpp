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


#include <string>

#include <qapplication.h>
#include <qmainwindow.h>
#include <qsizepolicy.h>
#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qmessagebox.h>
#include <qlayout.h>
#include <qlabel.h>
#include <qstring.h>
#include <qkeycode.h>

#include "MainWindow.h"
#include "Game.h"
#include "Shared.h"


/*
 *  globals
 *
 */

int g_player1Score = 0;
int g_player2Score = 0;
QLabel* g_player1ScoreLbl = NULL;
QLabel* g_player2ScoreLbl = NULL;


/*
 *  external globals
 *
 */

extern Game g_game;


/*
 *  functions
 *
 */


void createHelpMenu(QMenuBar* menubar, MainWindow* window)
{
    QPopupMenu* help = new QPopupMenu(menubar);
    help->insertItem("&About", window, SLOT(about()));
    help->insertItem("About Qt", window, SLOT(aboutQt()));

    menubar->insertItem("&Help", help);
}


void createFileMenu(QMenuBar* menubar, MainWindow* window)
{
    QPopupMenu* file = new QPopupMenu(menubar);
    file->insertItem("&New Game", window, SLOT(newGame()), Qt::CTRL+Qt::Key_N);
    file->insertSeparator();
    file->insertItem("E&xit", qApp, SLOT(quit()), Qt::CTRL+Qt::Key_Q);

    menubar->insertItem("&File", file);
}


void createMenubar(QMenuBar* menubar, MainWindow* window)
{
    createFileMenu(menubar, window);
    menubar->insertSeparator();
    createHelpMenu(menubar, window);
}


/*
 *  MainWindow methods
 *
 */


MainWindow::MainWindow(const int width, const int height, const std::string& title) : QMainWindow(NULL, title.c_str())
{
    createMenubar(menuBar(), this);

    QWidget* centerWidget = new QWidget(this, "center widget");
    centerWidget->setMaximumWidth(width); centerWidget->setMinimumWidth(width);
    centerWidget->setMaximumHeight(height); centerWidget->setMinimumHeight(height);
    centerWidget->resize(width, height);
    setCentralWidget(centerWidget);

    g_player1ScoreLbl = new QLabel(QString::number(g_player1Score), centerWidget);
    g_player2ScoreLbl = new QLabel(QString::number(g_player2Score), centerWidget);

    QGridLayout* layout = new QGridLayout(centerWidget);
    layout->setSpacing(10);
    layout->setMargin(10);
    layout->addWidget(new QLabel("Player 1 Score:", centerWidget), 0, 0);
    layout->addWidget(g_player1ScoreLbl, 0, 1);
    layout->addWidget(new QLabel("Player 2 Score:", centerWidget), 1, 0);
    layout->addWidget(g_player2ScoreLbl, 1, 1);

    resize(width, height);
}


void MainWindow::resetScore()
{
    g_player1Score = 0;
    g_player2Score = 0;
    g_player1ScoreLbl->setText(QString::number(g_player1Score));
    g_player2ScoreLbl->setText(QString::number(g_player2Score));
}


void MainWindow::newGame()
{
    g_game.start();
}


void MainWindow::about()
{
    std::string title = "About " + Shared::PROGNAME;
    std::string text = Shared::PROGNAME + "\nVersion: " + Shared::VERSION + "\n\n(c) 2002 Energon Software\n\nAuthors:\n\n" + Shared::AUTHORS + "\n" + Shared::WEB + "\n\n";

    QMessageBox::about(this, title.c_str(), text.c_str());
}


void MainWindow::aboutQt()
{
    QMessageBox::aboutQt(this, "About Qt");
}


void MainWindow::player1Score()
{
    g_player1ScoreLbl->setText(QString::number(++g_player1Score));
    g_game.reset();
}


void MainWindow::player2Score()
{
    g_player2ScoreLbl->setText(QString::number(++g_player2Score));
    g_game.reset();
}

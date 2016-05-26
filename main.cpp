/* Copyright 2016 Jonas Schenke
 *
 * This file is part of tictactoe.
 *
 * tictactoe is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * tictactoe is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with tictactoe.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>

#include "include/HumanPlayer.h"
#include "include/RandomPlayer.h"

using namespace std;

int main()
{
    cout << "Let's start the match!" << endl;

//    HumanPlayer *one = new HumanPlayer();
    RandomPlayer *one = new RandomPlayer();
    RandomPlayer *two = new RandomPlayer();
    Board board;

    board.registerPlayer(PLAYER_CIRCLE, *one);
    board.registerPlayer(PLAYER_CROSS, *two);

    board.play();

    delete one;
    delete two;

    return 0;
}

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

#include "../include/RandomPlayer.h"

/**
 * RandomPlayer constructor.
 */
RandomPlayer::RandomPlayer()
{
    srand(time(NULL));
    std::cout << "Starting random player!" << std::endl;
}

/**
 * RandomPlayer destructor.
 */
RandomPlayer::~RandomPlayer()
{
    std::cout << "Shutting down random player" << std::endl;
}

/**
 * Randomly generates a move. If there are still free fields, the function will return the position of an empty field.
 * @return position of a free field
 */
struct Position RandomPlayer::getMove()
{
    std::cout << "Deciding ... " << std::endl;
    char x = rand() % 3;
    char y = rand() % 3;
    char fails = 0;
    while(((board->getField((FieldNum)x, (FieldNum)0) != FIELD_EMPTY ||
        board->getField((FieldNum)x, (FieldNum)1) != FIELD_EMPTY) ||
        board->getField((FieldNum)x, (FieldNum)2) != FIELD_EMPTY) &&
        fails < 2)
    {
        x = (x + 1) % 3;
        ++fails;
    }
    fails = 0;
    while(this->board->getField((FieldNum)x, (FieldNum)y) != FIELD_EMPTY &&
        fails < 2)
    {
        y = (y + 1) % 3;
        ++fails;
    }
    std::cout << "Setting (" << (int)x << "|" << (int)y << ")!" << std::endl;
    return (struct Position){(FieldNum)x, (FieldNum)y};
}

/**
 * Print a message on the screen depending on the result of the game.
 * @param the result of the match
 */
void RandomPlayer::setResult(enum Result won)
{
    std::cout << "I'm done! ";
    if(won == RESULT_DRAW)
        std::cout << "It's a draw!";
    else if(won == RESULT_LOST)
        std::cout << "I lost!";
    else
        std::cout << "I won!";
    std::cout << std::endl;
}

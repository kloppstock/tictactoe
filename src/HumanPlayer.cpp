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

#include "../include/HumanPlayer.h"

/**
 * RandomPlayer constructor.
 */
HumanPlayer::HumanPlayer() {
    std::cout << "Let's begin!\n";
}

/**
 * RandomPlayer destructor.
 */
HumanPlayer::~HumanPlayer() {
    std::cout << "See you later!\n";
}

/**
 * Read input from user and report them to the board.
 * @param position
 */
struct Position HumanPlayer::getMove() {
    unsigned int x, y;
	
    std::cout << "Make a move (" << ((this->player == PLAYER_CIRCLE) ? 'O' : 'X') << ")!\n";
    std::cout  << "X = ";
    std::cin >> x;
    std::cout << "Y = ";
    std::cin >> y;
	std::cout << "\n";
	
    return (struct Position){(uint8_t)x, (uint8_t)y};
}

/**
 * Print a message on the screen depending on the result of the game.
 * @param result of the game
 */
void HumanPlayer::setResult(enum Result won) {
    if(won == RESULT_DRAW)
        std::cout << "Looks like a draw!\n";
    else if(won == RESULT_WON)
        std::cout << "Yay! You won!\n";
    else
        std::cout << "Looser!\n";
}

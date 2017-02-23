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

#include "../include/Game.h"

/**
 * Game constructor.
 */
Game::Game() {
    board = new Board();
    player[0] = NULL;
    player[1] = NULL;
}

/**
 * Game destructor.
 */
Game::~Game() {
    delete board;
	
    //detach players from board
    if(player[PLAYER_CIRCLE] != NULL)
        player[PLAYER_CIRCLE]->unsetBoard();
    if(player[PLAYER_CROSS] != NULL)
        player[PLAYER_CROSS]->unsetBoard();
}

/**
 * Function to register new players. This also sets the current board in given players.
 * @param player
 */
void Game::registerPlayer(enum PlayerNum which, Player &player) {
    //attach player to board
    this->player[which] = &player;
	this->player[which]->setBoard(*board, which);
}

/**
 * Run the main game loop until the game is finished. This function also notifies the players of the result of the game.
 */
void Game::play() {
    //check if 2 players are registered
    if(player[PLAYER_CIRCLE] == NULL || player[PLAYER_CROSS] == NULL) {
		std::cerr << "Some players are missing!" << std::endl;
		return;
	}
	
    //start loop until game is finished
    char number_of_moves = 0;
    struct Position last = (struct Position){0, 0};
    while(won(last) == FIELD_EMPTY && number_of_moves < 9) {
		//let individual players think about their next move and print the field
		for(unsigned char i = 0; i < 2 && won(last) == FIELD_EMPTY && number_of_moves < 9; ++i) {
			//let player make moves until one move is valid
			bool move_successful = false;
			while(!move_successful) {
				last = player[i]->getMove();
				move_successful = board->setMove((PlayerNum)i, last);
			}
			
			board->printBoard();
			
			//stop the game if all fields are taken
			++number_of_moves;
		}
	}
	
    //decide who the winner is
    enum Field winner = won(last);
	
    if(winner == FIELD_CIRCLE) {
		player[PLAYER_CIRCLE]->setResult(RESULT_WON);
		player[PLAYER_CROSS]->setResult(RESULT_LOST);
	} else if(winner == FIELD_CROSS) {
		player[PLAYER_CIRCLE]->setResult(RESULT_LOST);
		player[PLAYER_CROSS]->setResult(RESULT_WON);
	} else {
		player[PLAYER_CIRCLE]->setResult(RESULT_DRAW);
		player[PLAYER_CROSS]->setResult(RESULT_DRAW);
	}
}

/**
 * Checks if the game is already won.
 * @param last changed position
 * @return FIELD_EMPTY if nobody has one or else FIELD_CROSS or FIELD_CIRCLE
 */
enum Field Game::won(struct Position last) const {
    //check vertical
    if((board->getField(last.x, 0) == board->getField(last.x, 1)) &&
	   (board->getField(last.x, 1) == board->getField(last.x, 2)))
        return board->getField(last.x, last.y);
	
    //check horizontal
    if((board->getField(0, last.y) == board->getField(1, last.y)) &&
	   (board->getField(1, last.y) == board->getField(2, last.y)))
        return board->getField(last.x, last.y);
	
    //check if top left to bottom right is possible
    if(((last.x == 1 && last.y == 1) ||
        (last.x == 0 && last.y == 0)) ||
	   (last.x == 2 && last.y == 2)) {
		//check top left to bottom right
		if((board->getField(0, 0) == board->getField(1, 1)) &&
		   (board->getField(1, 1) == board->getField(2, 2)))
			return board->getField(last.x, last.y);	
		//check if top right to bottom left is possible
    } else if(((last.x == 1 && last.y == 1) ||
			   (last.x == 0 && last.y == 2)) ||
			  (last.x == 2 && last.y == 0)) {
		//top right to bottom left
		if((board->getField(0, 2) == board->getField(1, 1)) &&
		   (board->getField(1, 1) == board->getField(2, 0)))
			return board->getField(last.x, last.y);
	}
	
    //return Field.EMPTY if nobody has won yet
    return FIELD_EMPTY;
}

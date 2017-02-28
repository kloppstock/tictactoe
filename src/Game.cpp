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
struct Statistic Game::play(bool printBoard) {
	struct Statistic result = {{0.0, 0.0}, FIELD_EMPTY};
	int err = 0;
	struct timespec begin[2] = {{0, 0}, {0, 0}};
	struct timespec end[2] = {{0, 0}, {0, 0}};
	unsigned int number_of_turns[2] = {0, 0};
	
    //check if 2 players are registered
    if(player[PLAYER_CIRCLE] == NULL || player[PLAYER_CROSS] == NULL) {
		std::cerr << "Some players are missing!" << std::endl;
		result.winner = FIELD_EMPTY;
		return result;
	}
	
    //start loop until game is finished
    char number_of_moves = 0;
    struct Position last = (struct Position){0, 0};
    while(won(last) == FIELD_EMPTY && number_of_moves < 9) {
		//let individual players think about their next move and print the field
		for(unsigned char i = 0; i < 2 && won(last) == FIELD_EMPTY && number_of_moves < 9; ++i) {
			//let player make moves until one move is valid
			bool move_successful = false;
			
			if(printBoard)
				board->printBoard();

			++number_of_turns[i];
			//start timer
			err = clock_gettime(CLOCK_REALTIME, &begin[i]);
			if(err == -1) {
					printf("ERROR: couldn't get time!\n");
					exit(EXIT_FAILURE);
			}
					
			while(!move_successful) {
				last = player[i]->getMove();
				move_successful = board->setMove((PlayerNum)i, last);
			}
			
			//read timer
			err = clock_gettime(CLOCK_REALTIME, &end[i]);
			if(err == -1) {
					printf("ERROR: couldn't get time!\n");
					exit(EXIT_FAILURE);
			}
			
			result.avg_move_time[i] += (double)(end[i].tv_sec - begin[i].tv_sec) * 1000000.0
				+ (double)(end[i].tv_nsec - begin[i].tv_nsec) / 1000.0;; 
			
			//stop the game if all fields are taken
			++number_of_moves;
		}
	}
	
    //decide who the winner is
    enum Field winner = won(last);
	result.winner = winner;
	result.avg_move_time[0] /= number_of_turns[0];
   	result.avg_move_time[1] /= number_of_turns[1];
	
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
	return result;
}

/*
 * Play x number of games and return the average winner.
 * @param number of games
 * @return best player
 */
enum Field Game::bench(unsigned int games) {
	unsigned number_of_wins[2] = {0, 0};
	double avg_move_time[2] = {0.0, 0.0};
	struct Statistic stat;
	
	for(unsigned int i = 0; i < games; ++i) {
		stat = play(true);
		board->clear();
		
		if(stat.winner == FIELD_CROSS) {
			++number_of_wins[0];
		} else if(stat.winner == FIELD_CIRCLE) {
			++number_of_wins[1];
		}
		avg_move_time[0] += stat.avg_move_time[0];
		avg_move_time[1] += stat.avg_move_time[1];
	}
   
	if(number_of_wins[0] > number_of_wins[1])
		return FIELD_CROSS;
	else if(number_of_wins[0] < number_of_wins[1])
		return FIELD_CIRCLE;
	else if(avg_move_time[0] < avg_move_time[1])
		return FIELD_CROSS;
	else if(avg_move_time[0] > avg_move_time[1])
		return FIELD_CIRCLE;
	return FIELD_EMPTY;
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

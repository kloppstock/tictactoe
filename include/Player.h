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

#pragma once

#include "include.h"
#include "Board.h"

class Player {
 public:
	Player() {}
	virtual ~Player() {}

	virtual struct Position getMove() = 0;
	virtual void setResult(enum Result won) = 0;
	void setBoard(Board &board, enum PlayerNum player) {
		this->board = &board;
		this->player = player;
	}
	void unsetBoard() {this->board = NULL;}
 protected:
	Board *board;
	enum PlayerNum player;
 private:
};

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

#include <iostream>
#include <time.h>
#include <stdlib.h>

/**
 * Enumeration for the player.
 */
enum PlayerNum
{
    PLAYER_CROSS,
    PLAYER_CIRCLE
};

/**
 * Enumeration for the fields.
 */
enum Field
{
    FIELD_EMPTY,
    FIELD_CROSS,
    FIELD_CIRCLE
};

/**
 * Enumeration for the field numbers.
 */
enum FieldNum
{
    FIELD_NUM_ONE,
    FIELD_NUM_TWO,
    FIELD_NUM_THREE
};

/**
 * Enumeration for the result.
 */
enum Result
{
    RESULT_WON,
    RESULT_LOST,
    RESULT_DRAW
};

/**
 * Enumeration for the position.
 */
struct Position
{
    enum FieldNum x, y;
};

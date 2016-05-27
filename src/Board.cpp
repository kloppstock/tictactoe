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

 #include "../include/Board.h"

/**
 * Board constructor.
 */
Board::Board()
{
    //clear the fields and players
    for(unsigned char x = 0; x < 3; ++x)
        for(unsigned char y = 0; y < 3; ++y)
            this->fields[x][y] = (char)' ';
}

/**
 * Board destructor.
 */
Board::~Board()
{
}

/**
 * Getter for a specific field.
 * @param x position
 * @param y position
 * @return state of the field (FIELD_EMPTY, FIELD_CROSS or FIELD_CIRCLE)
 */
enum Field Board::getField(enum FieldNum x, enum FieldNum y) const
{
    enum Field result;
    switch(this->fields[x][y])
    {
        case 'X':
            result = FIELD_CROSS;
            break;
        case 'O':
            result = FIELD_CIRCLE;
            break;
        default:
            result = FIELD_EMPTY;
            break;
    }
    return result;
}

/**
 * Set a move on the game board.
 * @param position
 * @return true, if the requested field is empty
 */
bool Board::setMove(enum PlayerNum player, struct Position position)
{
    //return false if this field is already set
    if(this->fields[position.x][position.y] != ' ')
    {
        std::cerr << "Invalid move!" << std::endl;
        return false;
    }
    //otherwise set it and return true
    this->fields[position.x][position.y] = ((player == PLAYER_CIRCLE) ? 'O' : 'X');
    return true;
}

/**
 * Prints the current state of the board.
 */
void Board::printBoard() const
{
    std::cout << "Y\\X 0 1 2" << std::endl;
    std::cout << "   +-+-+-+" << std::endl;
    for(unsigned char y = 0; y < 3; ++y)
    {
        std::cout << " " << (int)y << " |";
        for(unsigned char x = 0; x < 3; ++x)
            std::cout << fields[x][y] << "|";
        std::cout << std::endl;
        std::cout << "   +-+-+-+" << std::endl;
    }
}

/**
 * A static function to convert a character to the associated field value.
 * @param character
 * @return field
 */
enum Field Board::CharToField(char c)
{
    return ((c == ' ') ? FIELD_EMPTY : ((c == 'X') ? FIELD_CROSS : FIELD_CIRCLE));
}

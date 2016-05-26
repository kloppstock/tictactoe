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
    this->player[0] = NULL;
    this->player[1] = NULL;
}

/**
 * Board destructor.
 */
Board::~Board()
{
    //detach players from board
    if(this->player[PLAYER_CIRCLE] != NULL)
        this->player[PLAYER_CIRCLE]->unsetBoard();
    if(this->player[PLAYER_CROSS] != NULL)
        this->player[PLAYER_CROSS]->unsetBoard();
}

/**
 * Function to register new players. This also sets the current board in given players.
 * @param player
 */
void Board::registerPlayer(enum PlayerNum which, Player &player)
{
    //attach player to board
    this->player[which] = &player;
    this->player[which]->setBoard(*this);
}

/**
 * Run the main game loop until the game is finished. This function also notifies the players of the result of the game.
 */
void Board::play()
{
    //check if 2 players are registered
    if(this->player[PLAYER_CIRCLE] == NULL || this->player[PLAYER_CROSS] == NULL)
    {
        std::cerr << "Some players are missing!" << std::endl;
        return;
    }
    //start loop until game is finished
    char number_of_moves = 0;
    struct Position last = (struct Position){FIELD_NUM_ONE, FIELD_NUM_ONE};
    while(this->won(last) == FIELD_EMPTY && number_of_moves < 9)
    {
        //let individual players think about their next move and print the field
        for(unsigned char i = 0; i < 2 && (this->won(last) == FIELD_EMPTY && number_of_moves < 9); ++i)
        {
            //let player make moves until one move is valid
            bool move_successful = false;
            while(!move_successful)
            {
                last = this->player[i]->getMove();
                move_successful = this->setMove((PlayerNum)i, last);
            }
            this->printBoard();
            //stop the game if all fields are taken
            ++number_of_moves;
        }
    }
    //decide who the winner is
    enum Field winner = this->won(last);
    if(winner == FIELD_CIRCLE)
    {
        this->player[PLAYER_CIRCLE]->setResult(RESULT_WON);
        this->player[PLAYER_CROSS]->setResult(RESULT_LOST);
    }
    else if(winner == FIELD_CIRCLE)
    {
        this->player[PLAYER_CIRCLE]->setResult(RESULT_LOST);
        this->player[PLAYER_CROSS]->setResult(RESULT_WON);
    }
    else
    {
        this->player[PLAYER_CIRCLE]->setResult(RESULT_DRAW);
        this->player[PLAYER_CROSS]->setResult(RESULT_DRAW);
    }
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
    std::cout << "+-+-+-+" << std::endl;
    for(unsigned char y = 0; y < 3; ++y)
    {
        std::cout << "|";
        for(unsigned char x = 0; x < 3; ++x)
            std::cout << fields[x][y] << "|";
        std::cout << std::endl;
        std::cout << "+-+-+-+" << std::endl;
    }
}

/**
 * Checks if the game is already won.
 * @param last changed position
 * @return FIELD_EMPTY if nobody has one or else FIELD_CROSS or FIELD_CIRCLE
 */
enum Field Board::won(struct Position last) const
{
    //check vertical
    if((this->fields[last.x][0] == this->fields[last.x][1]) &&
        (this->fields[last.x][1] == this->fields[last.x][2]))
        return Board::CharToField(this->fields[last.x][0]);
    //check horizontal
    if((this->fields[0][last.y] == this->fields[1][last.y]) &&
        (this->fields[1][last.y] == this->fields[2][last.y]))
        return Board::CharToField(this->fields[0][last.y]);
    //check if top left to bottom right is possible
    if(((last.x == 1 && last.y == 1) ||
        (last.x == 0 && last.y == 0)) ||
        (last.x == 2 && last.y == 2))
    {
        //check top left to bottom right
        if((this->fields[0][0] == this->fields[1][1]) &&
            (this->fields[1][1] == this->fields[2][2]))
            return Board::CharToField(this->fields[0][0]);
    }
    //check if top right to bottom left is possible
    else if(((last.x == 1 && last.y == 1) ||
        (last.x == 0 && last.y == 2)) ||
        (last.x == 2 && last.y == 0))
    {
        //top right to bottom left
        if((this->fields[0][2] == this->fields[1][1]) &&
            (this->fields[1][1] == this->fields[2][0]))
            return Board::CharToField(this->fields[0][2]);
    }
    //return Field.EMPTY if nobody has won yet
    return FIELD_EMPTY;
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

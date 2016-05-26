#include "../include/Game.h"

/**
 * Game constructor.
 */
Game::Game()
{
    this->board = new Board();
    this->player[0] = NULL;
    this->player[1] = NULL;
}

/**
 * Game destructor.
 */
Game::~Game()
{
    delete this->board;
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
void Game::registerPlayer(enum PlayerNum which, Player &player)
{
    //attach player to board
    this->player[which] = &player;
    this->player[which]->setBoard(*this->board);
}

/**
 * Run the main game loop until the game is finished. This function also notifies the players of the result of the game.
 */
void Game::play()
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
                move_successful = this->board->setMove((PlayerNum)i, last);
            }
            this->board->printBoard();
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
 * Checks if the game is already won.
 * @param last changed position
 * @return FIELD_EMPTY if nobody has one or else FIELD_CROSS or FIELD_CIRCLE
 */
enum Field Game::won(struct Position last) const
{
    //check vertical
    if((this->board->getField(last.x, FIELD_NUM_ONE) == this->board->getField(last.x, FIELD_NUM_TWO)) &&
        (this->board->getField(last.x, FIELD_NUM_TWO) == this->board->getField(last.x, FIELD_NUM_THREE)))
            return this->board->getField(last.x, FIELD_NUM_ONE);
    //check horizontal
    if((this->board->getField(FIELD_NUM_ONE, last.y) == this->board->getField(FIELD_NUM_TWO, last.y)) &&
        (this->board->getField(FIELD_NUM_TWO, last.y) == this->board->getField(FIELD_NUM_THREE, last.y)))
        return this->board->getField(FIELD_NUM_ONE, last.y);
    //check if top left to bottom right is possible
    if(((last.x == 1 && last.y == 1) ||
        (last.x == 0 && last.y == 0)) ||
        (last.x == 2 && last.y == 2))
    {
        //check top left to bottom right
        if((this->board->getField(FIELD_NUM_ONE, FIELD_NUM_ONE) == this->board->getField(FIELD_NUM_TWO, FIELD_NUM_TWO)) &&
            (this->board->getField(FIELD_NUM_TWO, FIELD_NUM_TWO) == this->board->getField(FIELD_NUM_THREE, FIELD_NUM_THREE)))
            return this->board->getField(FIELD_NUM_ONE, FIELD_NUM_ONE);
    }
    //check if top right to bottom left is possible
    else if(((last.x == 1 && last.y == 1) ||
        (last.x == 0 && last.y == 2)) ||
        (last.x == 2 && last.y == 0))
    {
        //top right to bottom left
        if((this->board->getField(FIELD_NUM_ONE, FIELD_NUM_THREE) == this->board->getField(FIELD_NUM_TWO, FIELD_NUM_TWO)) &&
            (this->board->getField(FIELD_NUM_TWO, FIELD_NUM_TWO) == this->board->getField(FIELD_NUM_THREE, FIELD_NUM_ONE)))
            return this->board->getField(FIELD_NUM_ONE, FIELD_NUM_THREE);
    }
    //return Field.EMPTY if nobody has won yet
    return FIELD_EMPTY;
}

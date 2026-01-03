#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{
    
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;

    boardSizeX = 30; //default board size
    boardSizeY = 15;

    
}

GameMechs::GameMechs(int boardX, int boardY)
{
    
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;

    boardSizeX = boardX;
    boardSizeY = boardY;

}

// do you need a destructor?
GameMechs::~GameMechs()
{
    //no destruction needed
}
GameMechs::GameMechs(const GameMechs &other) // copy constructor
{
    input = other.input;
    exitFlag = other.exitFlag;
    loseFlag = other.loseFlag;
    score = other.score;
    boardSizeX = other.boardSizeX;
    boardSizeY = other.boardSizeY;
}

GameMechs &GameMechs::operator=(const GameMechs &other) // assignment operator
{
    if(this != nullptr)
    {
        input = other.input;
        exitFlag = other.exitFlag;
        loseFlag = other.loseFlag;
        score = other.score;
        boardSizeX = other.boardSizeX;
        boardSizeY = other.boardSizeY;
    }
    return *this;
}


bool GameMechs::getExitFlagStatus() const
{
   return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}
    

char GameMechs::getInput() const
{
    
    return input;

}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;
}

void GameMechs::decrementScore() // new function to decrease score using special food
{
    score--;
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
    exitFlag = true; //game ends when you lose
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

// More methods should be added here
void GameMechs::collectAsyncInput()
{
    if(MacUILib_hasChar()){
        input = MacUILib_getChar();
    }
}
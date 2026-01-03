#include "Player.h"



Player::Player(GameMechs* thisGMRef, Food* thisFood)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP; //player should spawn in  not moving
    playerPosList = new objPosArrayList();
    // more actions to be included
    myFood = thisFood;

    objPos *headPos = new objPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '*');

    playerPosList->insertHead(*headPos);

    delete headPos;
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

Player::Player(const Player& other) //copy constructor
{
    playerPosList = new objPosArrayList();
    mainGameMechsRef = other.mainGameMechsRef;
    myDir = other.myDir;
    playerPosList = other.playerPosList;
    myFood = other.myFood;
}
Player &Player::operator=(const Player& other) //assignment constructor
{
    if (this != nullptr) {
        delete playerPosList;
        playerPosList = new objPosArrayList();
        mainGameMechsRef = other.mainGameMechsRef;
        myDir = other.myDir;
        playerPosList = other.playerPosList;
        myFood = other.myFood;
    }
    return *this;
}

objPosArrayList* Player::getPlayerPosList() const    
{
    return playerPosList;
}

void Player::updatePlayerDir()
{
    
        // PPA3 input processing logic  
        char input = mainGameMechsRef->getInput();
        //use switch case
        switch(input)
        {                      
            case 'W':
            case 'w': 
                if (myDir != DOWN){
                    myDir = UP;
                }
                break;
            case 'A':
            case 'a': 
                if (myDir != RIGHT){
                    myDir = LEFT;
                }
                break;
            case 'S':
            case 's': 
                if (myDir != UP){
                    myDir = DOWN;
                }
                break;
            case 'D':
            case 'd': 
                if (myDir != LEFT){
                    myDir = RIGHT;
                }
                break;
            default:
                break;
        }

}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    objPos headPos = playerPosList->getHeadElement();
    switch (myDir)
    {
        case UP:
        headPos.pos->y--;
        playerPosList->insertHead(headPos);
        playerPosList->removeTail();
        break;
        case DOWN:
        headPos.pos->y++;
        playerPosList->insertHead(headPos);
        playerPosList->removeTail();
        break;
        case LEFT:
        headPos.pos->x--;
        playerPosList->insertHead(headPos);
        playerPosList->removeTail();
        break;
        case RIGHT:
        headPos.pos->x++;
        playerPosList->insertHead(headPos);
        playerPosList->removeTail();
        break;
        default:
        break;
    }
    //check if player is going out of bounds and do warparound
    if (headPos.pos->x < 1) {
        headPos.pos->x = mainGameMechsRef->getBoardSizeX() - 2;
        playerPosList->removeHead();
        playerPosList->insertHead(headPos); //if the player is going out of bounds, move them to the other side of the board
    }
    else if (headPos.pos->x > mainGameMechsRef->getBoardSizeX() - 2) {
        headPos.pos->x = 1;
        playerPosList->removeHead();
        playerPosList->insertHead(headPos);
    }
    else if (headPos.pos->y < 1) {
        headPos.pos->y = mainGameMechsRef->getBoardSizeY() - 2;
        playerPosList->removeHead();
        playerPosList->insertHead(headPos);
    }
    else if (headPos.pos->y > mainGameMechsRef->getBoardSizeY() - 2) {
        headPos.pos->y = 1;
        playerPosList->removeHead();
        playerPosList->insertHead(headPos);
    }

    if (checkSelfCollision())
    {
        mainGameMechsRef->setLoseFlag(); //self collision causes losing
    }

    
}

// More methods to be added

bool Player::checkFoodConsumption()
{
    objPosArrayList *foodPos = myFood->getFoodPos();
    objPos tempPos = playerPosList->getHeadElement();

    for(int i = 0 ; i < foodPos->getSize() ; i++)
    {
        char sym = foodPos->getElement(i).getSymbolIfPosEqual(&tempPos);
        if (sym == 'o'){ // check if the food consumed is normal food
            mainGameMechsRef->incrementScore();
            incrementPlayerLength();
            return true;
        }
        else if (sym == 'S'){ // check if the food consumed is special food

            int scoreIncrease = (rand() % 13)-2; // generate a random score increase between -2 and 10
            int playerIncrease = (rand() % 8)-2; // generate a random player length increase between -2 and 5

            if(playerIncrease > 0) 
            {
                for(int j = 0; j < playerIncrease; j++) { //increase player length by randomly generated amount
                    incrementPlayerLength();
                }
            }
            else if(playerIncrease < 0)
            {
                for(int j = 0; j < -playerIncrease; j++) { //decrease player length by randomly generated amount
                    if(playerPosList->getSize() > 1) //make sure snake is not completely removed
                    {
                        playerPosList->removeTail();
                    }
                }
            }

            if(scoreIncrease > 0) 
            {
                for(int k = 0; k < scoreIncrease; k++){ //increase score by randomly generated amount
                    
                    mainGameMechsRef->incrementScore();
                }
            }
            else if(scoreIncrease < 0)
            {
                for(int k = 0; k < -scoreIncrease; k++){ //decrease score by randomly generated amount
                    if(mainGameMechsRef->getScore() > 0) //make sure we dont go below 0
                    {
                        mainGameMechsRef->decrementScore();
                    }
                }
            }
            return true;
        }
    }
    return false;
}

void Player::incrementPlayerLength()
{
    playerPosList->insertTail(playerPosList->getTailElement()); // add a new player element at the tail
}

bool Player::checkSelfCollision()
{
    int i = 0; 
    for (i = 1 ; i < playerPosList->getSize(); i++) //set to 1 so the head does not collide with itself
    {
        objPos tempPos = playerPosList->getElement(i);
        if (playerPosList->getHeadElement().isPosEqual(&tempPos))
        {
            return true;
        }
    }

    return false;
}
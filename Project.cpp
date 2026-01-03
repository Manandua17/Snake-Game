#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h" //implicitly calls #include "Food.h"

using namespace std;

#define DELAY_CONST 100000

Player *myPlayer;
GameMechs *myGM;
Food *myFood;
objPosArrayList *playerPos;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    myGM = new GameMechs(); //exit flag is automatically set to false in this constructor
    myFood = new Food(myGM);
    myPlayer = new Player(myGM, myFood);
    playerPos = myPlayer->getPlayerPosList();
    myFood->generateFood(playerPos);
}

void GetInput(void)
{
    myGM->collectAsyncInput();
}

void RunLogic(void)
{  
    if (myGM->getInput() == ' ') //key to exit program
    {
        myGM->setExitTrue();
    }

    myPlayer-> updatePlayerDir(); //process direction key input

    if(myPlayer->checkFoodConsumption())
    {
        myFood->generateFood(playerPos);
    }

    myPlayer-> movePlayer();
    
    myGM->clearInput(); //reset the input so that it is not double processed
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    objPosArrayList *foodPos = myFood->getFoodPos();
    bool playerFound = false, foodFound = false;
    int elementCount = 0;
    
    
    int boardX = myGM->getBoardSizeX();
    int boardY = myGM->getBoardSizeY();
    if (myGM->getExitFlagStatus() == false)
    {
        for (int row = 0; row < boardY; row++)
        {
            for (int col = 0; col < boardX; col++)
            {
                playerFound = false;
                foodFound = false;
                objPos *tempPos = new objPos(col, row, 0);
                for(int i = 0 ; i < playerPos->getSize() ; i++) //first, check for player elemnts
                {
                    if(playerPos->getElement(i).isPosEqual(tempPos)){
                        MacUILib_printf("%c", playerPos->getElement(i).getSymbolIfPosEqual(tempPos)); //print player elemets
                        playerFound = true;
                        break;
                    }
                }
                if(!playerFound){
                    for(int i = 0 ; i < foodPos->getSize() ; i++) //second, check for food elements
                    {
                        if(foodPos->getElement(i).isPosEqual(tempPos)){
                            MacUILib_printf("%c", foodPos->getElement(i).getSymbolIfPosEqual(tempPos)); //print food elements
                            foodFound = true;
                        }
                    }
                    if(!foodFound){
                        if (row == 0 || row == boardY-1 || col == 0 || col ==  boardX-1)   // print border elemets
                        {
                            MacUILib_printf("%c", '#');  // print a border character
                        }                        
                        else 
                        {
                            MacUILib_printf("%c", ' ');  // print a space character
                        }
                    }
                }
                delete tempPos;
            }
            MacUILib_printf("\n");
        }

    //UI messages
    MacUILib_printf("Your current score is: %d.\n", myGM->getScore());
    MacUILib_printf("The current snake length is: %d.\n", playerPos->getSize());
    MacUILib_printf("\nPress space to exit game.");
    MacUILib_printf("\nSpecial food denoted by, S, can increase/decrease both length and score.\n");
    MacUILib_printf("Normal food is denoted by, o.\n");
    }

    else if (myGM->getLoseFlagStatus() == true) //game was lost
    {
        MacUILib_clearScreen();
        MacUILib_printf("You lose! Your total score before losing was %d.\n", myGM->getScore());
    }
    
    else //game was ended by player
    {
        MacUILib_clearScreen();
        MacUILib_printf("The game ended! Your total score is %d.\n", myGM->getScore());
    }


}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    delete myPlayer; // delete any objects created on the heap
    delete myGM;
    delete myFood;

    MacUILib_uninit();
}

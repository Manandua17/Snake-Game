#include "Food.h"


Food::Food(GameMechs* GM) 
{
    foodBucket = new objPosArrayList(); //holds the position and symbol of each food generated
    myGM = GM;
}

Food::~Food()
{
    delete foodBucket;
}

Food::Food(const Food& other)
{
    foodBucket = new objPosArrayList(*other.foodBucket);
    myGM = other.myGM;
}

Food &Food::operator=(const Food &other)
{
    if (this != nullptr) 
    {
        delete foodBucket;
        foodBucket = new objPosArrayList(*other.foodBucket);
        myGM = other.myGM;
    }
    return *this;
}

void Food::generateFood(objPosArrayList* blockOff)
{
    srand(time(NULL)); //set see using current time
    
    int i = 0, j = 0;
    int X,Y, xRange, yRange, specialFood;
    xRange = myGM->getBoardSizeX();
    yRange = myGM->getBoardSizeY();
    bool valid = true;
    int size = blockOff->getSize();
 
    specialFood = (rand() % (foodNum/2)) + 1; //decide how many special foods to generate this time

    //generate random coordinates
    //iterate through each player semgment
    //check to see if generated coordinates intersect
    while(foodBucket->getSize() > 0)
    {
        foodBucket->removeTail(); //remove all previous food
    }
    
    for (int k = 0; k < foodNum; k++) 
    {

        do
        {
            valid = true; //assume coordinates are valid until proven otherwise
            
            X = (rand() % (xRange-2)) + 1; //make the range each blank space then add 1 to align coordinates
            Y = (rand() % (yRange-2)) + 1; //make the range each blank space then add 1 to align coordinates
            objPos *tempPos = new objPos(X, Y, 0);

            for (i = 0; i < size; i++) // check with current player location
            {
                if(blockOff->getElement(i).isPosEqual(tempPos)){
                    valid = false;
                    break;
                }
            }
            for (j = 0; j < foodBucket->getSize(); j++) // check with current food location
            {
                if(foodBucket->getElement(j).isPosEqual(tempPos)){
                    valid = false;
                    break;
                }
            }
            delete tempPos;

        } while (!valid);
            
        if (k < specialFood)
        {
            objPos *tempPos = new objPos(X,Y,'S'); //create special food object
            foodBucket->insertHead(*tempPos);
            delete tempPos;
        }
        else
        {
            objPos *tempPos = new objPos(X,Y,'o'); //create normal food object
            foodBucket->insertHead(*tempPos);
            delete tempPos;
        }
    }
}


objPosArrayList* Food::getFoodPos() const
{
    return foodBucket;
}

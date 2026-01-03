#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    arrayCapacity = ARRAY_MAX_CAP;
    aList = new objPos[arrayCapacity];
    listSize = 0;
    
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;

}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if (listSize < arrayCapacity)
    {
        for (int i = listSize; i > 0; i--) // shift all elements down one position
        {
            aList[i] = aList[i - 1];
        }
        aList[0] = thisPos;
        listSize++;  
    }  
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if (listSize < arrayCapacity) // check if array is not full
    {
        aList[listSize] = thisPos;
        listSize++;    
    }
}

void objPosArrayList::removeHead()
{
    if (listSize > 0) // check if list is not empty
    {
        for (int i = 0; i < listSize - 1; i++) // shift all elements up one position
        {
            aList[i] = aList[i + 1];
        }
        listSize--;
    }
    
}

void objPosArrayList::removeTail()
{
    if (listSize > 0) //Check if list is not empty
    {
        listSize--;
    }
    
}

objPos objPosArrayList::getHeadElement() const
{
    return aList[0];
}

objPos objPosArrayList::getTailElement() const
{
    if (listSize < 1) //check if list is empty
    {
        return objPos();
    }
    return aList[listSize - 1];
}

objPos objPosArrayList::getElement(int index) const
{
    if (index < 0 || index >= listSize) //Check if index is within bounds
    {
        return objPos();
    }
    return aList[index];
}
#include "objPosArrayList.h"
#include <iostream>

using namespace std;


objPosArrayList::objPosArrayList()
{
    //creates the default object array list
    aList = new objPos[ARRAY_MAX_CAP];
    sizeList=0;
    sizeArray=ARRAY_MAX_CAP;
}

objPosArrayList::~objPosArrayList()
{
    //deletes heap member aList
    delete[] aList;
}

int objPosArrayList::getSize()
{
    //returns the size of the list (this returns how many elements are in the snake body)
    return sizeList;
}

void objPosArrayList::insertHead(objPos thisPos)
{

    //checks if the array is full to prevent seg fault
    if (sizeList == sizeArray)
    {
        cout << "array full.." << endl;
        return;
    }

    //shuffles the entire snake body down by 1 starting at the tail
    for (int i = sizeList; i > 0; i--)
    {
        aList[i].setObjPos(aList[i-1]);
    }

    //because we started at the tail there is now an open position at the head, so we insert the new head here
    aList[0].setObjPos(thisPos);

    //we also need to increase the size of the list by 1 since we have a new element
    sizeList++;
}

void objPosArrayList::insertTail(objPos thisPos)
{

    //checks if the array is full to prevent seg fault
    if (sizeList == sizeArray)
    {
        cout << "array full.." << endl;
        return;
    }

    //just adds an new object at the end of the snake and increases list size by 1 
    aList[sizeList++].setObjPos(thisPos);
}

void objPosArrayList::removeHead()
{

    //checks if the array is empty
    if(sizeList <= 0)
    {
       cout << "list empty" << endl;
       return;
    }

    //iterates through the snake body and shuffles it down to remove the head
    for (int i=0; i<sizeList-1; i++)
    {
        aList[i].setObjPos(aList[i+1]);
    }

    sizeList--;
}

void objPosArrayList::removeTail()
{
    //checks if the array is empty
    if(sizeList <=0)
    {
        cout << "list empty" << endl;
        return;
    }
    
    //dont even need to remove the tail, just reduce list size by 1 to not print it 
    sizeList--;
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    //returns the head element of the snake
    returnPos.setObjPos(aList[0]);
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    //returns the tail element of the snake
    returnPos.setObjPos(aList[sizeList-1]);
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    //returns any wanted element of the snake
    returnPos.setObjPos(aList[index]);
}
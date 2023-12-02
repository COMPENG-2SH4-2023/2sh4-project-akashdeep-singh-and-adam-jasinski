#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = NONE;

    //creating the default snake
    objPos tempPos;
    tempPos.setObjPos((mainGameMechsRef->getBoardSizeX()-2)/2,(mainGameMechsRef->getBoardSizeY()-2)/2,'*');
    playerPos = new objPosArrayList();
    playerPos->insertHead(tempPos);
}


Player::~Player()
{
    //deletes the player position heap member
    delete playerPos;
}

objPosArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPos arrray list
    return playerPos;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic  
    char input = mainGameMechsRef->getInput();
    switch(input)
    {
        case 'w':
        case 'W':
            if (myDir != DOWN)
            {
                myDir = UP;
            } 
            break;
        case 'a':
        case 'A':
            if (myDir != RIGHT)
            {
                myDir = LEFT;
            }
            break;
        case 's':
        case 'S':
            if (myDir != UP)
            {
                myDir = DOWN;
            }
            break;
        case 'd':
        case 'D':
            if (myDir != LEFT)
            {
                myDir = RIGHT;
            }
            break;
    }
    mainGameMechsRef->clearInput();
         
}

void Player::movePlayer()
{
    
    //creating a new food position object for snake eating logic
    objPos foodPos;
    mainGameMechsRef->getFoodPos(foodPos);

    //creating a new head position object for snake movement + growth logic
    objPos currentHead; 
    playerPos->getHeadElement(currentHead);


    // PPA3 Finite State Machine logic
    if (myDir != NONE)
    {
        switch (myDir)
        {
            case UP:
                currentHead.y--;
                break;
            case DOWN:
                currentHead.y++;
                break;
            case LEFT:
                currentHead.x--;
                break;
            case RIGHT:
                currentHead.x++;
                break;
        }
    }

    //getting heights and widths for ppa2/3 wraparound logic
    int height = mainGameMechsRef->getBoardSizeY();
    int width = mainGameMechsRef->getBoardSizeX();

    //ppa2/3 wraparound logic
    if(currentHead.x <=0)
    {
        currentHead.x = width-2;
    }

    else if(currentHead.x >= width-1)
    {
        currentHead.x = 1;
    }

    else if(currentHead.y <=0)
    {
        currentHead.y= height-2;
    }

    else if(currentHead.y >=height-1)
    {
        currentHead.y = 1;
    }


    //checks if a player collision has occured
    if (checkSelfCollision() == true)
    {
        mainGameMechsRef->setLoseTrue();
    }

    //snake eating logic
    if(currentHead.isPosEqual(&foodPos)) //checks if the head is at the same position as the food
    {
        //if head is the same position as the food, insert a head, generate a new food object, and then +1 to score
        playerPos->insertHead(currentHead);
        mainGameMechsRef->generateFood(*playerPos);
        mainGameMechsRef->incrementScore();
    }
    
    else
    {
        //this is the player move logic (just add a new head at the next position and remove the tail)
        playerPos->insertHead(currentHead);
        playerPos->removeTail();
    }


}

bool Player::checkSelfCollision()
{
    //creates a new copy of the snake body
    objPosArrayList* body = getPlayerPos();  

    //gets the head element of the snake body copy
    objPos currentHead;
    body->getHeadElement(currentHead);

    for (int i = 1; i < body->getSize(); i++) //iterates through the entire snake body
    {

        //creates a new "block" object to store current player body segement for comparison
        objPos block;
        body->getElement(block, i);

        //if a collision is detected, return true, otherwise return false
        if (currentHead.isPosEqual(&block))
        {
            return true;  
        }
    }
    return false;  
}






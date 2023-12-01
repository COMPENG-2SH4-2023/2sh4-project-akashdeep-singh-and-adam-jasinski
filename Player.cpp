#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = NONE;

    // more actions to be included
    objPos tempPos;
    tempPos.setObjPos((mainGameMechsRef->getBoardSizeX()-2)/2,(mainGameMechsRef->getBoardSizeY()-2)/2,'*');
    playerPos = new objPosArrayList();
    playerPos->insertHead(tempPos);
}


Player::~Player()
{
    delete playerPos;
    // delete any heap members here
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
    
    objPos foodPos;
    mainGameMechsRef->getFoodPos(foodPos);

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

    int height = mainGameMechsRef->getBoardSizeY();
    int width = mainGameMechsRef->getBoardSizeX();

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


    if (checkSelfCollision() == true)
    {
        mainGameMechsRef->setLoseTrue();
    }

    if(currentHead.isPosEqual(&foodPos))
    {
        playerPos->insertHead(currentHead);
        mainGameMechsRef->generateFood(*playerPos);
        mainGameMechsRef->incrementScore();
    }
    else
    {
        playerPos->insertHead(currentHead);
        playerPos->removeTail();
    }


}

bool Player::checkSelfCollision()
{
    objPosArrayList* body = getPlayerPos();  
    objPos currentHead;
    body->getHeadElement(currentHead);

    for (int i = 1; i < body->getSize(); i++)
    {
        objPos block;
        body->getElement(block, i);
        if (currentHead.isPosEqual(&block))
        {
            return true;  
        }
    }
    return false;  
}






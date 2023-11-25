#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = NONE;

    // more actions to be included
    playerPos.setObjPos((mainGameMechsRef->getBoardSizeX()-2)/2,(mainGameMechsRef->getBoardSizeY()-2)/2,'@');
}


Player::~Player()
{
    // delete any heap members here
}

void Player::getPlayerPos(objPos &returnPos)
{
    returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);
    // return the reference to the playerPos arrray list
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
    // PPA3 Finite State Machine logic
    if (myDir != NONE)
    {
        switch (myDir)
        {
            case UP:
                playerPos.y--;
                break;
            case DOWN:
                playerPos.y++;
                break;
            case LEFT:
                playerPos.x--;
                break;
            case RIGHT:
                playerPos.x++;
                break;
        }
    }

    int height = mainGameMechsRef->getBoardSizeY();
    int width = mainGameMechsRef->getBoardSizeX();

    if(playerPos.x <=0)
    {
        playerPos.x = width-2;
    }

    else if(playerPos.x >= width-1)
    {
        playerPos.x = 1;
    }

    else if(playerPos.y <=0)
    {
        playerPos.y= height-2;
    }

    else if(playerPos.y >=height-1)
    {
        playerPos.y = 1;
    }
}


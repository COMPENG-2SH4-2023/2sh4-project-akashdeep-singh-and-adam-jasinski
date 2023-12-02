#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "objPosArrayList.h"


using namespace std;

#define DELAY_CONST 100000

GameMechs* myGM;
Player* myPlayer;
objPosArrayList* playerBody;

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
        if(myGM->getExitFlagStatus() || myGM->getLoseFlagStatus()) //these if statements make it so that the loop breaks instantly when
            break;                                                 //one of the loss conditions is met, and checks at every stage of the game

        RunLogic();
        if(myGM->getExitFlagStatus() || myGM->getLoseFlagStatus())
            break;

        DrawScreen();
        if(myGM->getExitFlagStatus() || myGM->getLoseFlagStatus())
            break;

        LoopDelay();

    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    //Initializing all the class objects and also the first piece of random food
    myGM = new GameMechs();
    myPlayer = new Player(myGM);
    playerBody = myPlayer->getPlayerPos();
    myGM->generateFood(*playerBody);

}

void GetInput(void)
{
    //these 2 lines simply check if the exit/loss flag are ever true so it can break the loop
    myGM->getExitFlagStatus();
    myGM->getLoseFlagStatus();

    //checks input 
    myGM->getInput();

    //will do nothing if the conditions in game mechs isnt met (exit key or collision)
    myGM->setExitTrue(); 
}

void RunLogic(void)
{
    //logic for moving the player and then clearing input
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
    myGM->clearInput();
}

void DrawScreen(void)
{
   MacUILib_clearScreen(); 
   bool drawn;

   //gets the gameboard width and height 
   int height = myGM->getBoardSizeY();
   int width = myGM->getBoardSizeX();

    //sets up temp objects to deal with printing food and the player body
    objPos tempBody;
    objPos foodPos;
    myGM->getFoodPos(foodPos);

   for(int i = 0; i < height; i++)
   {
        for(int j = 0; j < width; j++)
        {

            drawn=false;

            //for loop that draws the player body
            for(int k = 0; k<playerBody->getSize();k++)
            {
                playerBody->getElement(tempBody,k); //gets the current object of the body at position k

                //checks if current body segement matches with i,j
                if(tempBody.x ==j and tempBody.y == i)
                {
                    //draws body segment and then sets flag to true to indicate part is drawn
                    MacUILib_printf("%c",tempBody.symbol);
                    drawn=true;
                    break;
                }
            }
            
            //checks if the body segement is drawn, and if it is, skip the remainder of the loop as to not overwrite the body
            if(drawn)
            {
                continue;
            }

            if(i == 0 || i== height-1 || j==0 || j==width-1)
            {
                MacUILib_printf("#");
            }
            
            else if (i == foodPos.y && j == foodPos.x)
            {
                MacUILib_printf("%c",foodPos.symbol); //prints the food
            }

            else
            {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
   } 

   //displays the game score
   MacUILib_printf("Your score is: %d",myGM->getScore());

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();

    //displays a custom message if the user ended the game or lost
    myGM->displayMessage(); 

    MacUILib_uninit();

}

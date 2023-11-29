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

    myGM = new GameMechs(20,10);
    myPlayer = new Player(myGM);
    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    myGM->generateFood(*playerBody);

}

void GetInput(void)
{
    myGM->getExitFlagStatus();
    myGM->getLoseFlagStatus();
    myGM->getInput();
    myGM->setExitTrue();
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
    myGM->clearInput();
}

void DrawScreen(void)
{
   MacUILib_clearScreen(); 
   bool drawn;
   int i;
   int j;
   int height = myGM->getBoardSizeY();
   int width = myGM->getBoardSizeX();

    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    objPos tempBody;
    
    objPos foodPos;
    myGM->getFoodPos(foodPos);

   
   for(i = 0; i < height; i++)
   {
        for(j = 0; j < width; j++)
        {

            drawn=false;

            for(int k = 0; k<playerBody->getSize();k++)
            {
                playerBody->getElement(tempBody,k);
                if(tempBody.x ==j and tempBody.y == i)
                {
                    MacUILib_printf("%c",tempBody.symbol);
                    drawn=true;
                    break;
                }
            }
            
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
                MacUILib_printf("%c",foodPos.symbol);
            }

            else
            {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
   }  

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
  
    MacUILib_uninit();

}

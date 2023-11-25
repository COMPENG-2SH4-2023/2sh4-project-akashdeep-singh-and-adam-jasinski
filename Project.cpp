#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"


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

}

void GetInput(void)
{
    myGM->getInput();
    myGM->setExitTrue();
    myGM->getExitFlagStatus();
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
   int i;
   int j;
   int height = myGM->getBoardSizeY();
   int width = myGM->getBoardSizeX();

   objPos tempPos;
   myPlayer->getPlayerPos(tempPos);
   
   for(i = 0; i < height; i++)
   {
        for(j = 0; j < width; j++)
        {
            if(i == 0 || i== height-1 || j==0 || j==width-1)
            {
                MacUILib_printf("#");
            }
            
            else if (i == tempPos.y && j == tempPos.x)
            {
                MacUILib_printf("%c",tempPos.symbol);
            }

            else
            {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
   }  
   MacUILib_printf("X: %d Y: %d\n", tempPos.x, tempPos.y); 

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

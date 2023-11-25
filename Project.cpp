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

    myGM = new GameMechs(10,20);
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
   int cols = myGM->getBoardSizeY();
   int rows = myGM->getBoardSizeX();

   objPos tempPos;
   myPlayer->getPlayerPos(tempPos);
   
   for(i = 0; i < rows; i++)
   {
        for(j = 0; j < cols; j++)
        {
            if(i == 0 || i== rows-1 || j==0 || j==cols-1)
            {
                MacUILib_printf("#");
            }
            
            else if (i == tempPos.x && j == tempPos.y)
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
   MacUILib_printf("X: %d Y: %d\n", tempPos.y, tempPos.x); 

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

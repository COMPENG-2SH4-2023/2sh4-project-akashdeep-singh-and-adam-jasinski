#include "GameMechs.h"
#include "MacUILib.h"
//Two Constructor methods
GameMechs::GameMechs()
{
  input = 0;
  exitFlag = false;
  boardSizeX = 20;
  boardSizeY = 10;
  score = 0;
  loseFlag=false;

  foodPos.setObjPos(-1, -1, 'o');

  srand(time(nullptr));

}

GameMechs::GameMechs(int boardX, int boardY)
{
  input = 0;
  exitFlag = false;
  boardSizeX = boardX;
  boardSizeY = boardY;
  score = 0;
  loseFlag=false;

  foodPos.setObjPos(-1, -1, 'o');

  srand(time(nullptr));
  
}

// do you need a destructor?


// getter and setter for each parameter
//exit flag
bool GameMechs::getExitFlagStatus()
{
  return exitFlag;
}

void GameMechs::setExitTrue()
{
  if(input == 27 || getLoseFlagStatus()==true)
  {
    exitFlag = true;
  }
}

//lose flag
bool GameMechs::getLoseFlagStatus() 
{
  return loseFlag;
}

void GameMechs::setLoseTrue() 
{
  loseFlag = true;
}

//input 
char GameMechs::getInput()
{
  if (MacUILib_hasChar()) {
    input = MacUILib_getChar();
  }
  return input;
}

void GameMechs::setInput(char this_input)
{
  input = this_input;  
}

//getting game board size
int GameMechs::getBoardSizeX()
{
  return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
  return boardSizeY;
}

int GameMechs::getScore() const
{
  return score;
}

//can be changed later to increase the score by more than 1 at a time
void GameMechs::incrementScore() 
{
  score += 1;
}

//clear the last input to allow the next input to be registered
void GameMechs::clearInput()
{
  setInput(0);
}

void GameMechs::generateFood(objPosArrayList &blockoff)
{
  int targetPos;
  bool flag = true;


  do
  {

    foodPos.setObjPos((rand()%(boardSizeX-2))+1, (rand()%(boardSizeY-2))+1, 'o');
    flag = false;    
    for(int i = 0; i <blockoff.getSize(); i++)
    
    {
      objPos currPos;
      blockoff.getElement(currPos,i);
      if(foodPos.isPosEqual(&currPos))
      {
        flag=true;
        break;
      }
    }
  } while(flag);

}

void GameMechs::getFoodPos(objPos &returnPos)
{
  foodPos.getObjPos(returnPos);
}



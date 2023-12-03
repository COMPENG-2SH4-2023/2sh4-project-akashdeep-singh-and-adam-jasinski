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

// a destructor was not needed since no new element is being allocated


// getter and setter for each parameter
//exit flag
bool GameMechs::getExitFlagStatus()
{
  return exitFlag;
}



void GameMechs::setExitTrue()
{
  //exit flag setter, exits the game when 'esc' is pressed or loseflag is true
  if(input == 27 || getLoseFlagStatus()==true)
  {
    exitFlag = true;
  }
}


bool GameMechs::getLoseFlagStatus() 
{
  //lose flag getter
  return loseFlag;
}


void GameMechs::setLoseTrue() 
{
  //lose flag to true setter
  loseFlag = true;
}


char GameMechs::getInput()
{
  //input getter 
  if (MacUILib_hasChar()) {
    input = MacUILib_getChar();
  }
  return input;
}


void GameMechs::setInput(char this_input)
{
  //input setter 
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
  //score getter, declared as const since it's not meant to modify the object's internal state
  return score;
}


void GameMechs::incrementScore() 
{
  //can be changed later to increase the score by more than 1 at a time
  score += 1;
}


void GameMechs::clearInput()
{
  //clear the last input to allow the next input to be registered
  setInput(0);
}

//food generating routine, 
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
  //return reference to the object position of the food item
  foodPos.getObjPos(returnPos);
}

void GameMechs::exitMessage()
{
  //message diplayed when exiting the game
  cout << "Thanks for playing!" << endl;
}

void GameMechs::loseMessage()
{
  //message displayed if the game is lost
  cout << "You lost, you can do better!" << endl;
}

void GameMechs::displayMessage()
{
  //choosing which message to display based on the loseflagstatus
  if(getLoseFlagStatus()==true)
    loseMessage();
  else
    exitMessage();

}



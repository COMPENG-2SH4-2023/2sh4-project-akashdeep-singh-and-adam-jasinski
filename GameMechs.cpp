#include "GameMechs.h"
#include "MacUILib.h"
//Two Constructor methods
GameMechs::GameMechs()
{
  input = NULL;
  exitFlag = false;
  boardSizeX = 20;
  boardSizeY = 10;
}

GameMechs::GameMechs(int boardX, int boardY)
{
  input = NULL;
  exitFlag = false;
  boardSizeX = boardX;
  boardSizeY = boardY;
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
  if(input == 27)
  {
    exitFlag = true;
  }
  ;
}

//lose flag
bool GameMechs::getLoseFlagStatus() 
{
  return loseFlag;
}

void GameMechs::setLoseFlag() {
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



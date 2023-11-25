#include "GameMechs.h"

//Two Constructor methods
GameMechs::GameMechs()
{
  input(0);
  exitFlag(false);
  loseFlag(false);
  score(0);
  boardSizeX(30);
  boardSizeY(15);
}

GameMechs::GameMechs(int boardX, int boardY)
{
  input(0);
  exitFlag(false);
  loseFlag(false);
  score(0);
  boardSizeX(boardX);
  boardSizeY(boardY);
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
  exitFlag = true;
}

//lose flag
bool GameMechs::getLoseFlagStatus() const //const modifier added to not modify the state of the GameMechanics object
{
  return loseFlag;
}

void GameMechs::setLoseFlag() {
  loseFlag = true;
}

//input 
char GameMechs::getInput()
{
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
  score++;
}

//clear the last input to allow the next input to be registered
void GameMechs::clearInput()
{
  input = 0;
}



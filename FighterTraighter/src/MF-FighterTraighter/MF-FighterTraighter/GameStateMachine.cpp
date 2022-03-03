#include "GameStateMachine.h"

GameStateMachine::GameStateMachine(){ }

GameStateMachine::~GameStateMachine()
{
	while (!states.empty()) {
		GameState* s = states.top();
		delete s;
		states.pop();
	}
}

GameState* GameStateMachine::getCurrentState() //if there is a state then returns the top of the stack
{
	if (!states.empty()) { 
		return states.top();
	}
	else {
		return nullptr;
	}
}

void GameStateMachine::popState()
{
	GameState* state = states.top();
	toDelete.push(state);
	states.pop();
	stackSize_--;
#ifdef _DEBUG
	std::cout << "Stack size: " << stackSize_ << std::endl;
#endif 	
}

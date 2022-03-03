#pragma once
#include <vector>
#include "Component.h"

class InputState: public Component {
public:
	InputState() : Component(ecs::InputState) {};
	void setInput(int index, bool value) {
		inputVec[index] = value;
	}
	/*void setInput(bool activo,int index)
	{
		if (activo)
		{
			inputVecHeld[index] ++;
			
		}
		else
		{
			inputVecHeld[index] = 0;

		}
	}*/
	
	bool getInput(int index) {
		return inputVec[index];
	}
	virtual void init() override {
		inputVec = std::vector<bool>(inputsSize);
		//inputVecHeld = std::vector<int>(inputsSize);
		 for(auto e: inputVec) {
			 e = false;
		}
		 /*for (auto e : inputVecHeld) {
			 e = 0;
		 }*/
	}
private:
	//left, right, up, down, hit1, hit2, hit3, hit4, ab1, ab2, block, guardbreak
	int inputsSize = 12;
	
	std::vector<bool> inputVec;
	//to control forze abilities
	//std::vector<int>inputVecHeld;
	/**/
	
	
};
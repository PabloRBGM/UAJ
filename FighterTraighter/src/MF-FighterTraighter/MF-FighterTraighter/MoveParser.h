#pragma once
#include "AnimationChain.h"

class MoveParser
{
public:
	static std::vector<AnimationChain*> parseFile(string filePath);
private:
	MoveParser() {};
	~MoveParser() {};
};


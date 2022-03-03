#pragma once
#include "Move.h"

class AnimationChain
{
public:
	AnimationChain(vector<Move*> chain) : chain_(chain) {};
	~AnimationChain() {
		for (int i = 0; i < chain_.size(); i++) {
			delete chain_[i];
		}
		chain_.clear();
	};
	bool update();
	void reset() { 
		for (int i = 0; i < chain_.size(); i++) {
			chain_[i]->resetIndex();
		}
		index_ = 0; 
	};
private:
	vector<Move*> chain_;
	int index_ = 0;
};


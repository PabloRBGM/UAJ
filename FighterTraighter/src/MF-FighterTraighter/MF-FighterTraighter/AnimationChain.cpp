#include "AnimationChain.h"


bool AnimationChain::update()
{
	if (index_ >= chain_.size()) {
		for (auto mov : chain_) {
			mov->resetIndex();
		}
		index_ = 0;
		return true;
	}else if (chain_[index_]->update()) {

		++index_;
		return false;
	}
	else {
		return false;
	}

}

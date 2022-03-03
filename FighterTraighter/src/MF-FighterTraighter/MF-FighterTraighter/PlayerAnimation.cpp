#include "PlayerAnimation.h"

void PlayerAnimation::update()
{
	if (currStateInt_ != currState_->getState()) {
		activeFrame_ = 0;
		timeSinceLastIncrement_ = 0;
		currStateInt_ = currState_->getState();
	}
	else {
		//render (currently testing)
		imgR_->setFrame(activeFrame_, currStateInt_);
		timeSinceLastIncrement_++;
		if (timeSinceLastIncrement_ >= data_->getAnimVelocity(currStateInt_)) {	//If it's time to change frame
			if (data_->getAnimLoops(currStateInt_)) {	//If it loops make the active frame loop simply
				activeFrame_ = (activeFrame_ + 1) % data_->getAnimLength(currStateInt_);	 
			}
			else {	//If not, check if it suprasses de maximum and if it does take it back so it it stuck at the end
				activeFrame_++;
				if (activeFrame_ >= data_->getAnimLength(currStateInt_)) activeFrame_ = data_->getAnimLength(currStateInt_) - 1;
			}
			timeSinceLastIncrement_ = 0;	//This should be independent
		}
	}
}

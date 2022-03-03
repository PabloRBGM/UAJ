#include "UIRoundRenderer.h"
#include "Entity.h"
#include "RenderImage.h"
#include <stdexcept>

void UIRoundRenderer::setRoundsWon(int rounds)
{
	if (rounds <= images_.size()) {
		for (int i = roundsWon_; i < rounds; ++i) {
			images_[i]->getComponent<RenderImage>(ecs::RenderImage)->setFrame(1, 0);
		}
	}
	else throw out_of_range("New number of won rounds too big!");
	if (rounds >= 0) {
		for (int i = rounds; i < roundsWon_; ++i) {
			images_[i]->getComponent<RenderImage>(ecs::RenderImage)->setFrame(0, 0);
		}
	}
	else throw out_of_range("New number of won rounds negative!");
	roundsWon_ = rounds;
}

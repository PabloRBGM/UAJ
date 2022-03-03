#include "UIFactory.h"
#include "GameState.h"
#include "EntityManager.h"
#include "Entity.h"

#include "Texture.h"

#include "Transform.h"
#include "Button.h"
#include "TextComponent.h"
#include "RenderImage.h"
#include "App.h"
#include "Slider.h"
#include "IndexSlider.h"
#include "UITransform.h"
#include "ButtonControl.h"

//create a button with their callbacks
std::tuple<Entity*, Entity*> UIFactory::createButton
	(App* app, GameState* state, Texture* buttonTex, 
	Font* font, Vector2D position, Vector2D anchor, Vector2D pivot, double width, double height, double rotation, 
	CallBackOnClick* clickCallback, CallBackOnClick* stopClickCallback, std::string text, int fontSize, TextComponent::TextAlignment alignment)
{
	Entity* button = state->getEntityManager().addEntity();
	button->addComponent<UITransform>(position, anchor, pivot, Vector2D(width, height));
	button->addComponent<RenderImage>(buttonTex);
	button->addComponent<Button>(clickCallback, stopClickCallback);

	Entity* textEnt = state->getEntityManager().addEntity();
	textEnt->addComponent<UITransform>(position, anchor, pivot, Vector2D(width, height));
	textEnt->addComponent<TextComponent>(text, font, fontSize, alignment);

	return std::make_tuple(button, textEnt);
}

Entity* UIFactory::createButton(int n,App* app, GameState* state, Texture* buttonTex, Font* font, Vector2D position, Vector2D anchor, Vector2D pivot, double width, double height, double rotation, SetOnClick* click, SetOnClick* stop)
{
	Entity* button = state->getEntityManager().addEntity();
	button->addComponent<UITransform>(position, anchor, pivot, Vector2D(width, height));
	button->addComponent<RenderImage>(buttonTex);
	button->addComponent<Button>(n,click, stop);

	return button;
}
	
std::tuple<Entity*, Entity*>UIFactory::createButtonControl(App* app, GameState* state, Texture* buttonTex, Font* font, Vector2D position, Vector2D anchor, Vector2D pivot, double width, double height, double rotation, SetIndexOnClick* clickCallback, std::string text, int fontSize, TextComponent::TextAlignment alignment, int index, int control,int player)
{



	Entity* button = state->getEntityManager().addEntity();
	button->addComponent<UITransform>(position, anchor, pivot, Vector2D(width, height));
	button->addComponent<RenderImage>(buttonTex);

	Entity* textEnt = state->getEntityManager().addEntity();
	textEnt->addComponent<UITransform>(position, anchor, pivot, Vector2D(width, height));

	button->addComponent<ButtonControl>(clickCallback, index, control, player,textEnt->addComponent<TextComponent>(text, font, fontSize, alignment));





	return std::make_tuple(button, textEnt);
};

// create the structure of  slider (bar, buttons and the index)
std::tuple<Entity*, Entity*, Entity*, Entity*> UIFactory::createSlider
	(App* app, GameState* state, double min, double max, int steps, 
	Texture* texture_, Texture* reg_texture, Font* font,
	Vector2D position, Vector2D anchor, Vector2D pivot, double width, double height,
	SetValueOnClick* valueOnClickCallback,
	std::string text, int fontSize,
	std::string valueText, int valueFontSize)
{
	Entity* slider = state->getEntityManager().addEntity();
	slider->addComponent<UITransform>(position, anchor, pivot, Vector2D(width, height));
	slider->addComponent<RenderImage>(texture_);
	slider->addComponent<Slider>(min, max, steps, valueOnClickCallback);

	Entity* reg_ = state->getEntityManager().addEntity();
	reg_->addComponent<UITransform>(position, Vector2D(), Vector2D(), Vector2D(25, height * 5));
	reg_->addComponent<RenderImage>(reg_texture);
	reg_->addComponent<IndexSlider>(slider);
	
	Entity* text_ = state->getEntityManager().addEntity();
	text_->addComponent<UITransform>(Vector2D(position.getX(), position.getY() - fontSize - 20), anchor, pivot, Vector2D(width, fontSize));
	text_->addComponent<TextComponent>(text, font, fontSize);
	
	Entity* ValueText_ = state->getEntityManager().addEntity();
	ValueText_->addComponent<UITransform>(Vector2D(position.getX() + width + 10, position.getY() - fontSize / 2), anchor, pivot, Vector2D(width, fontSize));
	ValueText_->addComponent<TextComponent>(valueText, font, valueFontSize);

	return std::make_tuple(slider, reg_, text_, ValueText_);
}
Entity* UIFactory::createPanel(App* app, GameState* state, Texture* texture_, Vector2D position, Vector2D anchor, Vector2D pivot, double width, double height, double rotation)
{
	Entity* panel = state->getEntityManager().addEntity();
	panel->addComponent<UITransform>(position, anchor, pivot, Vector2D(width, height));
	panel->addComponent<RenderImage>(texture_);

	return panel;
}
Entity* UIFactory::createText(App* app, GameState* state, Vector2D pos, Vector2D anchor, Vector2D pivot, Font* font, std::string text, int textSize, TextComponent::TextAlignment textAlignment, double width, double height, int wrapCharNumber)
{
	Entity* ent = state->getEntityManager().addEntity();

	ent->addComponent<UITransform>(pos, anchor, pivot, Vector2D(width, height));
	ent->addComponent<TextComponent>(text, font, textSize, textAlignment, font->getFontSize() * wrapCharNumber * font->getWidthRatio());

	return ent;
}

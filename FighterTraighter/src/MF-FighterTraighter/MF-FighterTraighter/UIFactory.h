#pragma once
#include <tuple>
class Entity;
class Texture;
class App;
class GameState;
class Font;
#include "Vector2D.h"
#include <string>
#include "TextComponent.h"

using CallBackOnClick = void(App * app);//method with a reference to app
using SetValueOnClick = void(App * app, double value); //method with a reference to app and a value
using SetOnClick = void(App * app, int n);
using SetIndexOnClick = void(App* app, int index, int control,int player);

class UIFactory
{
public:
	//creates a button with functionality
	static std::tuple<Entity*, Entity*> createButton(App* app, GameState* state, Texture* buttonTex, Font* font, Vector2D position = Vector2D(), Vector2D anchor = Vector2D(), Vector2D pivot = Vector2D(), double width = 0, double height = 0, double rotation = 0, CallBackOnClick* clickCallback = nullptr, CallBackOnClick* stopClickCallback = nullptr, std::string text = "", int fontSize = 20, TextComponent::TextAlignment alignment = TextComponent::TextAlignment::Left);
	
	//creates a button with functionality
	static Entity* createButton(int owner,App* app, GameState* state, Texture* buttonTex, Font* font, Vector2D position = Vector2D(), Vector2D anchor = Vector2D(), Vector2D pivot = Vector2D(), double width = 0, double height = 0, double rotation = 0, SetOnClick* click = nullptr, SetOnClick* stop = nullptr);

	//creates a button with functionality

	static std::tuple<Entity*, Entity*> createButtonControl(App* app, GameState* state, Texture* buttonTex, Font* font, Vector2D position = Vector2D(), Vector2D anchor = Vector2D(), Vector2D pivot = Vector2D(), double width = 0, double height = 0, double rotation = 0, SetIndexOnClick* clickCallback = nullptr, std::string text = "", int fontSize = 20, TextComponent::TextAlignment alignment = TextComponent::TextAlignment::Left, int index = 0, int control = 0,int player=0);


	// Creates a slider with two texts
	static std::tuple<Entity*, Entity*, Entity*, Entity*> createSlider
	(App* app, GameState* state, double min, double max, int steps,
		Texture* texture_, Texture* reg_texture, Font* font,
		Vector2D position, Vector2D anchor, Vector2D pivot, double width, double height,
		SetValueOnClick* valueOnClickCallback = nullptr,
		std::string text = "", int fontSize = 20,
		std::string valueText = "", int valueFontSize = 20);


	static Entity* createText(App* app, GameState* state, Vector2D pos, Vector2D anchor, Vector2D pivot, Font* font, std::string text, int fontSize, TextComponent::TextAlignment textAlignment, double width, double height, int wrapLength);
	static Entity* createPanel(App* app, GameState* state, Texture* texture_, Vector2D position, Vector2D anchor, Vector2D pivot, double width, double height, double rotation);


	
protected:
	UIFactory() = delete;
	~UIFactory() {};
};


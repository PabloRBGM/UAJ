#pragma once
#include "Component.h"
#include "Text.h"
#include "Transform.h"
class TextComponent :
	public Component
{
public:
	enum TextAlignment {
		Left,
		Center,
		Right
	};
public:
	//constructor
	TextComponent(std::string text, Font* font, int size = 20, TextAlignment alignment = Left, int wrapLength = 9000);
	//destructor
	virtual ~TextComponent();

	//methods overrided from the component class
	void init() override;
	void render() override;

	//set the different values of the textcomponent
	void setText(std::string text);
	void setSize(int size);
	void setFont(Font* font);
	inline void setAlignment(TextAlignment al) { alignment_ = al; }

protected:
	Transform* transform_ = nullptr;
	Text* text_ = nullptr;
	Font* font_ = nullptr;

	std::string textString_ = "";
	TextAlignment alignment_;
	int textSize_ = 0;
	int longText_;
};


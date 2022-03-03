#pragma once
#include "Component.h"
#include "TextComponent.h"
#include "NavigationController.h"
#include "RenderImage.h"
class CharacterSelectionLogic : public Component
{
public:

	CharacterSelectionLogic(int player, TextComponent* j_desc, RenderImage* im, string aisha_desc, string mkwhoop_desc, string flor_desc, string mock_desc, NavigationController* nav, Entity* aisha, Entity* flor, Entity* mkwhoop, Entity* mock, Entity* random, Texture* aishatexture, Texture* flortexture, Texture* mkwhooptexture, Texture* mocktexture, Texture* randomTexture) : Component(ecs::CharacterSelectionLogic),
		desc_(j_desc), aisha_(aisha), aisha_desc_(aisha_desc), flor_(flor), flor_desc_(flor_desc), mock_(mock), mock_desc_(mock_desc), mkwhoop_(mkwhoop), mkwhoop_desc_(mkwhoop_desc), nav_(nav),
		aisha_texture(aishatexture), flor_texture(flortexture), mkwhoop_texture(mkwhooptexture), mock_texture(mocktexture), image_(im), playerNumber_(player), random_(random), random_texture(randomTexture) { }
	~CharacterSelectionLogic();
	void init() override;
	void update() override;
	void handleInput() override;

	void SetElements();

	//returns true if the plCharacterSelectionLogicayer chose a character
	inline bool getChosen() { return chose; }
private:

	TextComponent* desc_ = nullptr;
	RenderImage* image_ = nullptr;
	string aisha_desc_, flor_desc_, mkwhoop_desc_, mock_desc_;
	NavigationController* nav_ = nullptr;

	Entity* aisha_ = nullptr;
	Entity* flor_ = nullptr;
	Entity* mkwhoop_ = nullptr;
	Entity* mock_ = nullptr;
	Entity* random_ = nullptr;

	Texture* aisha_texture = nullptr;
	Texture* flor_texture = nullptr;
	Texture* mkwhoop_texture = nullptr;
	Texture* mock_texture = nullptr;
	Texture* random_texture = nullptr;

	int curNavX = -1, curNavY = -1;
	int playerNumber_;

	bool chose = false;
};


#pragma once
#include "Component.h"
#include "NavigationController.h"
#include "RenderImage.h"
class InventoryLogic :
	public Component
{
public:
	InventoryLogic(NavigationController* nav, int player, RenderImage* left, RenderImage* right);
	~InventoryLogic() { delete ent; }
	void init() override;
	void update() override;
	void render() override;
	void handleInput() override;

	inline bool getPressed() { return pressed; }
private:
	Entity* ent = nullptr;
	Vector2D offset = Vector2D();

	RenderImage* left_;
	RenderImage* right_;

	NavigationController* nav_;
	int player_;
	bool pressed = false;

	int abs_size = 0,
		ab1_index = 0,
		ab2_index = 0;

	void swapIndex();
};


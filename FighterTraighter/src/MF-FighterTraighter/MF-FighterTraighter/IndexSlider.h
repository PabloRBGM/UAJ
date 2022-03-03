#pragma once
#include "Component.h"
#include "Transform.h"
#include "Slider.h"
class IndexSlider :
	public Component
{
public:
	//constructor
	IndexSlider(Entity* slider) : Component(ecs::IndexSlider), sliderEnt_(slider) {}
	//destructor
	virtual ~IndexSlider();

	//methods overrided from Component
	void init() override;
	void update() override;


private:
	
	Transform* transform_ = nullptr; //transform of this entity

	//reference of the slider Entity
	Entity* sliderEnt_ = nullptr; 
	Transform* transform_slider = nullptr;
	Slider* slider_ = nullptr;
};


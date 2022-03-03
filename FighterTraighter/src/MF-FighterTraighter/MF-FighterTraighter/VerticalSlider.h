#pragma once
#include "Slider.h"
class VerticalSlider :
	public Slider
{
public:
	//constructor
	VerticalSlider(double minValue, double maxValue);
	VerticalSlider(double minValue, double maxValue, int steps, CallbackOnValueChanged* valueChanged);
	//destructor
	virtual ~VerticalSlider();

	void handleInput() override;
protected:
};


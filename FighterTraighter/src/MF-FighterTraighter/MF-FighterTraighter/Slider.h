#pragma once
#include "Component.h"
#include "Transform.h"
#include "UIElement.h"
#include "Entity.h"
#include "RenderImage.h"

using CallbackOnValueChanged = void(App * app, double value);

class Slider :
	public UIElement
{
public:
	//constructor
	Slider(double minValue, double maxValue, int steps = 10, CallbackOnValueChanged* valueChanged = nullptr, HID* owner = nullptr);

	//destructor
	virtual ~Slider();

	//set different parameters
	inline void setCallbackOnValueChanged(CallbackOnValueChanged* callback) { valueChanged_ = callback; }
	inline void setSteps(int steps) { steps_ = steps; }
	inline void setMinValue(int minValue) { minValue_ = minValue; }
	inline void setMaxValue(int maxValue) { maxValue_ = maxValue; }
	void setValue(double newValue);
	
	//methods overrided from Component
	void init() override;
	void handleInput() override;
	void update() override;
	void render() override;

	virtual void Press() {};
	virtual void Select() { if (Buttonstate_ != Selected) Buttonstate_ = Selected; entity_->getComponent<RenderImage>(ecs::RenderImage)->setFrame(1, 0); };
	virtual void Disable() { Buttonstate_ = Disabled; };
	virtual void Deselect() { Buttonstate_ = Normal; entity_->getComponent<RenderImage>(ecs::RenderImage)->setFrame(0, 0); };

	//different get 
	double getValue() { return value_; }
	double getMinValue() { return minValue_; }
	double getMaxValue() { return maxValue_; }
	int getSteps() { return steps_; }

	void setinValue(double initValue) {
		value_ = initValue;
		if (value_ < minValue_)
			value_ = minValue_;
		else if (value_ > maxValue_)
			value_ = maxValue_;
	}
protected:
	Transform* transform_ = nullptr;

	CallbackOnValueChanged* valueChanged_ = nullptr;

	double minValue_, maxValue_, value_ = 0;
	int steps_ = 0; // if steps < 1, continuous
};
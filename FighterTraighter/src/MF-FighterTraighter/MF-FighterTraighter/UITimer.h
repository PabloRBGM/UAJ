#pragma once
#include "Component.h"
#include <SDL.h>
#include "TextComponent.h"
#include <functional>
class UITimer :
	public Component
{
public:
	enum Format {
		Miliseconds, // miliseconds
		Seconds, // seconds
		Minutes, // minutes:seconds
		Clock // hours:minutes:seconds
	};
public:
	// Note: this timer is frame independent
	UITimer(Format format, bool isCountdown = false, int countdownAmount = 0, std::function<void()> timerEndCallback = nullptr)
		: Component(ecs::UITimer), format_(format), countdown_(isCountdown), countdownAmount_(countdownAmount), timerEndCallback(timerEndCallback) {}

	void init() override;
	void update() override;

	inline void setFormat(Format f) { format_ = f; }
	// Sets the countdown to c, resets the timer and sets it to a countdown timer
	inline void setCountdown(int c) {
		countdown_ = true;
		countdownAmount_ = c;
		resetTimer();
		//resumeTimer();
	}

	inline void setInvisible(bool inv) { invisibleText = inv; };

	void resetTimer();
	void stopTimer();
	bool isTimerStopped();
	void resumeTimer();
	virtual ~UITimer() {}
protected:
	void setText();

	int timerStart_ = 0; // ms
	int timerNow_ = 0; // ms
	bool timerStopped_ = false;
	bool countdown_; // if true, the timer will countdown from countdownAmount_ to 0
	int countdownAmount_ = 0; // amount in miliseconds
	Format format_;
	TextComponent* text_ = nullptr;
	bool invisibleText;

	std::function<void()> timerEndCallback; // Only called if timer is a countdown
};


#pragma once
#include "Transform.h"
class UITransform :
	public Transform
{
public:
	enum PositionPreset
	{
		TopLeft,
		Top,
		TopRight,
		CenterLeft,
		Center,
		CenterRight,
		BottomLeft,
		Bottom,
		bottomRight
	};

	void init() override;
	void update() override;

	void setAnchor(Vector2D anchor) { anchor_ = anchor; }
	void setAnchorPreset(PositionPreset preset);

	void setPivot(Vector2D pivot) { pivot_ = pivot; }
	void setPivotPreset(PositionPreset preset);


	Vector2D getPosition() const override { return position_ + anchor_ - pivot_; }
	void setPosition(const Vector2D& v) override { position_ = v; }
	void setPosition(double x, double y) override { position_ = { x,y }; }

	virtual void WindowResized(double newW, double newH);

	UITransform(Vector2D pos, Vector2D anchor, Vector2D pivot, Vector2D size) : Transform(pos, Vector2D(), size.getX(), size.getY(), 0), anchor_(anchor), pivot_(pivot) {};
protected:
	WindowManager* windowMngr_ = nullptr;
	Vector2D anchor_; // from where in the window the position is calculated
	Vector2D windowSize_;
	Vector2D pivot_; // where in the rectangle the position is
};


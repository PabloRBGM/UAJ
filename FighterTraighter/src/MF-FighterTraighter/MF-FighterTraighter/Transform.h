#pragma once

#include "Vector2D.h"
#include "Component.h"
#include "ecs.h"

class Transform: public Component
{
public:
	//default constructor
	Transform();
	//constructor
	Transform(Vector2D position, Vector2D speed, double width, double height, double rotation);
	//destructor
	virtual ~Transform();

	// get and set for position
	virtual Vector2D getPosition() const { return position_; }
	virtual void setPosition(const Vector2D& v) { position_ = v; }
	virtual void setPosition(double x, double y) { position_ = { x,y }; }

	//get and set for speed
	virtual  Vector2D getSpeed() const { return speed_; }
	virtual void setSpeed(const Vector2D& v) { speed_ = v; }
	virtual void setSpeed(double x, double y) { speed_ = { x,y }; }

	// get and set for width and height
	virtual double getWidth() const { return width_; }
	virtual double getHeight() const { return height_; }

	//get and set for the scale of the object
	virtual double getWMult() const { return wMult_; }
	virtual double getHMult() const { return hMult_; }
	virtual void setHMult(double i) { hMult_ = i; }
	virtual void setWMult(double i) { wMult_ = i; }

	//set the width of the object
	virtual void setWidth(double width) { width_ = width; }
	//set the height of the object
	virtual void setHeight(double height) { height_ = height; }

	//set width and height
	virtual void setWidthHeight(double width, double height) {
		setWidth(width);
		setHeight(height); 
	}

	//get the rotation of the object
	virtual double getRotation() { return rotation_; }
	//set the rotation of the object
	virtual void setRotation(double rotation) { rotation_ = rotation; }

	virtual int getOrientation() { return orientation_; };
	virtual void setOrientation(int orient) { orientation_ = orient; };

protected:
	Vector2D position_;
	Vector2D speed_;
	double width_=0, height_=0, rotation_=0;
	double wMult_ = 1, hMult_ = 1;
	int orientation_ = 1; //1 for right, -1 for left
};


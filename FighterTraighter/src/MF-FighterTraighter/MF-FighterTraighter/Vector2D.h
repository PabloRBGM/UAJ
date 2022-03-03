#pragma once
#include <Box2D/Box2D.h>

class Vector2D
{
public:
	Vector2D() :_x(0), _y(0) {}
	Vector2D(double x, double y) : _x(x), _y(y) {}
	Vector2D(const Vector2D& v) : _x(v._x), _y(v._y) {}

	inline double getX() const { return _x; };
	inline double getY() const { return _y; };

	inline void setX(double x) { _x = x; };
	inline void setY(double y) { _y = y; };
	inline void set(double x, double y) {
		_x = x;
		_y = y;
	};
	inline void set(const Vector2D& v) {
		_x = v._x;
		_y = v._y;
	};

	inline Vector2D operator+(const Vector2D& v) const {
		return Vector2D(this->_x + v._x, this->_y + v._y);
	}
	inline Vector2D operator-(const Vector2D& v) const {
		return Vector2D(this->_x - v._x, this->_y - v._y);
	}
	inline Vector2D operator*(double d) const {
		return Vector2D(this->_x * d, this->_y * d);
	}
	inline double operator*(const Vector2D& v) const {
		return this->_x * v._x + this->_y * v._y;
	}
	inline Vector2D operator=(const Vector2D& v) {
		set(v);
		return *this;
	}
	inline bool operator==(const Vector2D& v) const {
		return _x == v._x && _y == v._y;
	}
	inline bool operator!=(const Vector2D& v) const {
		return !(*this == v);
	}

	inline operator b2Vec2() {
		return b2Vec2((float32)_x, (float32)_y);
	}

	virtual ~Vector2D() {}
private:
	double _x = 0, _y = 0;
};

#pragma once
#include <math.h>
#include <iostream>

class Vector2D
{
public:
	Vector2D() {
		_x = 0; _y = 0;
	}

	Vector2D(float x, float y) {
		_x = x; _y = y;
	}

	virtual const float getX() {
		return _x;
	}

	virtual const float getY() {
		return _y;
	}

	virtual void setX(float x) {
		_x = x;
	}

	virtual void setY(float y) {
		_y = y;
	}

	virtual float length() {
		return sqrt(_x * _x + _y * _y);
	}

    Vector2D operator+(const Vector2D& v2) const { return Vector2D(_x + v2._x, _y + v2._y); }
    friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2)
    {
        v1._x += v2._x;
        v1._y += v2._y;

        return v1;
    }

    Vector2D operator-(const Vector2D& v2) const { return Vector2D(_x - v2._x, _y - v2._y); }
    friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2)
    {
        v1._x -= v2._x;
        v1._y -= v2._y;

        return v1;
    }


    Vector2D operator*(float scalar)
    {
        return Vector2D(_x * scalar, _y * scalar);
    }

    Vector2D& operator*=(float scalar)
    {
        _x *= scalar;
        _y *= scalar;

        return *this;
    }

    Vector2D operator/(float scalar)
    {
        return Vector2D(_x / scalar, _y / scalar);
    }

    Vector2D& operator/=(float scalar)
    {
        _x /= scalar;
        _y /= scalar;

        return *this;
    }

    void normalize() // set to unit vector(length = 1)
    {
        int l = length();
        if (l > 0)
        {
            (*this) *= 1 / l;
        }
    }

    float _x;
    float _y;
};


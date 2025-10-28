#include<iostream>

struct Vector2
{
	float x, y;

	Vector2(float x, float y) : x(x), y(y) {};
	Vector2 Add(const Vector2& other) const{
		return Vector2(x + other.x, y + other.y);
	}

	Vector2 operator+(const Vector2& other)const {
		return Add(other);
	}

	Vector2 Mutliply(const Vector2& other)const {
		return Vector2(x * other.x, y * other.y);
	}
	Vector2 operator*(const Vector2& other)const {
	}
};

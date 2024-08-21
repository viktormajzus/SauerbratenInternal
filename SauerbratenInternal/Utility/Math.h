#pragma once
#include <utility>

static struct Vector4
{
	float x, y, z, w;
}vector4, Vec4, vec4;

static struct Vector3
{
	float x, y, z;
}vector3, Vec3, vec3;

static struct Matrix
{
	Vector4 column1;
	Vector4 column2;;
	Vector4 column3;;
	Vector4 column4;;
};

namespace math
{
float Magnitude(const Vector3& vector);
float ToDegrees(float radValue);
float DotProduct(const Vector3& vector1, const Vector3& operand2);
bool WorldToScreen(const Vector3& position, Vector3& screen, const Matrix& matrix, std::pair<int, int> window);
}

inline Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
{
	return { lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z };
}
inline Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
{
	return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
}

inline Vector3 operator/(const Vector3& lhs, float num)
{
	return { lhs.x / num, lhs.y / num, lhs.z / num };
}
inline Vector3 operator/(const Vector4& lhs, float num)
{
	return { lhs.x / num, lhs.y / num, lhs.z / num };
}

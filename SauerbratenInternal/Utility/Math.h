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

static struct Vector2
{
	float yaw, pitch;
}vector2, Vec2, vec2;

namespace math
{
float Magnitude(const Vector2& vector);
float Magnitude(const Vector3& vector);
float ToDegrees(float radValue);
float DotProduct(const Vector3& vector1, const Vector3& operand2);
bool WorldToScreen(const Vector3& position, Vector3& screen, std::array<float, 16> matrix, std::pair<int, int> window);
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

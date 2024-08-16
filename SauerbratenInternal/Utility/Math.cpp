#include "../pch.h"
#include "Math.h"

float math::Magnitude(const Vector2& vector)
{
  float sum{ std::powf(vector.yaw, 2) + std::powf(vector.pitch, 2) };
  return sqrt(sum);
}
float math::Magnitude(const Vector3& vector)
{
  float sum{ std::powf(vector.x, 2) + std::powf(vector.y, 2) + std::powf(vector.z, 2) };
  return sqrt(sum);
}

float math::ToDegrees(float radValue)
{
  return radValue * 180.0f / std::numbers::pi_v<float>;
}

float math::DotProduct(const Vector3& operand1, const Vector3& operand2)
{
  return operand1.x * operand2.x + operand1.y * operand2.y + operand1.z * operand2.z;
}

bool math::WorldToScreen(const Vector3& position, Vector3& screen, std::array<float, 16> matrix, std::pair<int, int> window)
{
  Vector4 clip{};
  clip.x = position.x * matrix[0] + position.y * matrix[4] + position.z * matrix[8] + matrix[12];
  clip.y = position.x * matrix[1] + position.y * matrix[5] + position.z * matrix[9] + matrix[13];
  clip.z = position.x * matrix[2] + position.y * matrix[6] + position.z * matrix[10] + matrix[14];
  clip.w = position.x * matrix[3] + position.y * matrix[7] + position.z * matrix[11] + matrix[15];

  if (clip.w < 0.1f)
    return false;

  Vector3 NDC{ clip / clip.w };

  screen.x = (window.first / 2 * NDC.x) + (NDC.x + window.first / 2);
  screen.y = -(window.second / 2 * NDC.y) + (NDC.y + window.first / 2);

  return true;
}
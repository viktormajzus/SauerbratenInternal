#include "../pch.h"
#include "Math.h"

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

bool math::WorldToScreen(const Vector3& position, Vector3& screen, const Matrix& matrix, std::pair<int, int> window)
{
  Vector4 clip{};
  clip.x = position.x * matrix.column1.x + position.y * matrix.column2.x + position.z * matrix.column3.x + matrix.column4.x;
  clip.y = position.x * matrix.column1.y + position.y * matrix.column2.y + position.z * matrix.column3.y + matrix.column4.y;
  clip.z = position.x * matrix.column1.z + position.y * matrix.column2.z + position.z * matrix.column3.z + matrix.column4.z;
  clip.w = position.x * matrix.column1.w + position.y * matrix.column2.w + position.z * matrix.column3.w + matrix.column4.w;

  if (clip.w < 0.1f)
    return false;

  Vector3 NDC{ clip / clip.w };

  screen.x = (window.first / 2 * NDC.x) + (NDC.x + window.first / 2);
  screen.y = -(window.second / 2 * NDC.y) + (NDC.y + window.first / 2);

  return true;
}
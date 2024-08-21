#include "../pch.h"
#include "ESP.h"

#include "../Utility/memory.h"
#include "../Offsets/Offsets.h"

void ESP::DrawLine(Vector3 target, HDC hdc, std::uintptr_t moduleBaseAddress)
{
  std::pair<int, int> window{};
  window.first = *reinterpret_cast<int*>(moduleBaseAddress + offsets::window.first) / 2;
  window.second = *reinterpret_cast<int*>(moduleBaseAddress + offsets::window.second);

  HPEN pen{ CreatePen(PS_SOLID, 2, RGB(200, 50, 50)) };
  HPEN oldPen{ reinterpret_cast<HPEN>(SelectObject(hdc, pen)) };

  MoveToEx(hdc, window.first, window.second, NULL);
  LineTo(hdc, target.x, target.y);

  SelectObject(hdc, oldPen);
  DeleteObject(pen);
}

void feature::ESP(std::uintptr_t moduleBaseAddress, Entity* localPlayer, HWND hwnd)
{
  Vector3 screen{};
  HDC hdc{ GetDC(hwnd) };

  std::pair<int, int> window{};
  window.first = *reinterpret_cast<int*>(moduleBaseAddress + offsets::window.first);
  window.second = *reinterpret_cast<int*>(moduleBaseAddress + offsets::window.second);

  for (auto i{ 0 }; i < *reinterpret_cast<int*>(moduleBaseAddress + offsets::playerCount); ++i)
  {
    std::uintptr_t* entityList{ reinterpret_cast<std::uintptr_t*>(moduleBaseAddress + offsets::entityList) };
    Entity* currentEntity{ memory::GetEntity(*entityList, i * 0x8) };

    if (currentEntity == localPlayer)
      continue;

    if (!currentEntity)
      continue;

    if (currentEntity->entityState == 1)
      continue;

    Matrix matrix{ *reinterpret_cast<Matrix*>(moduleBaseAddress + offsets::viewMatrix) };

    if (math::WorldToScreen(currentEntity->position2, screen, matrix, window))
      ESP::DrawLine(screen, hdc, moduleBaseAddress);
  }

  DeleteObject(hdc);
}
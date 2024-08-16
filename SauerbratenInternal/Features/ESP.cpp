#include "../pch.h"
#include "ESP.h"

#include "../Utility/memory.h"
#include "../Offsets/Offsets.h"

void ESP::DrawLine(Vector3 target, HDC hdc, std::uintptr_t moduleBaseAddress)
{
  std::pair<int, int> window{};
  window.first = memory::Read<int>(moduleBaseAddress, offsets::window.first) / 2;
  window.second = memory::Read<int>(moduleBaseAddress, offsets::window.second);

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
  window.first = memory::Read<int>(moduleBaseAddress, offsets::window.first);
  window.second = memory::Read<int>(moduleBaseAddress, offsets::window.second);

  for (auto i{ 0 }; i < memory::Read<int>(moduleBaseAddress, offsets::playerCount); i++)
  {
    Entity* currentEntity{ memory::Read<Entity*>(memory::Read<std::uintptr_t>(moduleBaseAddress, offsets::entityList), i * 0x8) };
    if (currentEntity == localPlayer)
      continue;

    if (!currentEntity)
      continue;

    if (currentEntity->entityState == 1)
      continue;

    std::array<float, 16> matrix{ memory::Read<float, 16>(moduleBaseAddress, offsets::viewMatrix) };

    if (math::WorldToScreen(currentEntity->position2, screen, matrix, window))
      ESP::DrawLine(screen, hdc, moduleBaseAddress);
  }

  DeleteObject(hdc);
}
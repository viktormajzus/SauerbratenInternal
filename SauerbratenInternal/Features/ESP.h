#pragma once
#include <utility>
#include <cstdint>
#include "../Utility/Math.h"
#include "../Offsets/Structs.h"

namespace ESP
{
void DrawLine(Vector3 target, HDC hdc, std::uintptr_t moduleBaseAddress);
}

namespace feature
{
void ESP(std::uintptr_t moduleBaseAddress, Entity* localPlayer, HWND hwnd);
}

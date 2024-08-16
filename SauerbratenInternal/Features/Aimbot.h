#pragma once
#include "../Offsets/Structs.h"

namespace AimbotMath
{
void AimAt(Entity* localPlayer, Entity* targetPlayer);
}

namespace feature
{
void Aimbot(std::uintptr_t moduleBaseAddress, Entity* localPlayer);
}

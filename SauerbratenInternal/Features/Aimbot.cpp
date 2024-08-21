#include "../pch.h"
#include "Aimbot.h"

#include "../Utility/Math.h"
#include "../Utility/memory.h"
#include "../Offsets/Offsets.h"

void AimbotMath::AimAt(Entity* localPlayer, Entity* targetPlayer)
{
  Vector3 direction{ targetPlayer->position2 - localPlayer->position2 };

  Vector3 viewAngle{};
  viewAngle.x = -math::ToDegrees(std::atan2(direction.x, direction.y));
  viewAngle.y = math::ToDegrees(std::asinf(direction.z / math::Magnitude(direction)));

  localPlayer->viewAngle = viewAngle;
}

void feature::Aimbot(std::uintptr_t moduleBaseAddress, Entity* localPlayer)
{
  for (auto i{ 0 }; i < *reinterpret_cast<int*>(moduleBaseAddress + offsets::playerCount); i++)
  {
    std::uintptr_t* entityList{ reinterpret_cast<std::uintptr_t*>(moduleBaseAddress + offsets::entityList) };
    Entity* currentEntity{ memory::GetEntity(*entityList, i * 0x8) };

    if (currentEntity == localPlayer)
      continue;

    if (!currentEntity)
      continue;

    if (currentEntity->entityState == 1)
      continue;

    AimbotMath::AimAt(localPlayer, currentEntity);
  }
}
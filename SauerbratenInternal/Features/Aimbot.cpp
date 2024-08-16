#include "../pch.h"
#include "Aimbot.h"

#include "../Utility/Math.h"
#include "../Utility/memory.h"
#include "../Offsets/Offsets.h"

void AimbotMath::AimAt(Entity* localPlayer, Entity* targetPlayer)
{
  Vector3 direction{ targetPlayer->position2 - localPlayer->position2 };

  Vector2 viewAngle{};
  viewAngle.yaw = -math::ToDegrees(std::atan2(direction.x, direction.y));
  viewAngle.pitch = math::ToDegrees(std::asinf(direction.z / math::Magnitude(direction)));

  localPlayer->viewAngle = viewAngle;
}

void feature::Aimbot(std::uintptr_t moduleBaseAddress, Entity* localPlayer)
{
  for (auto i{ 0 }; i < memory::Read<int>(moduleBaseAddress, offsets::playerCount); i++)
  {
    Entity* currentEntity{ memory::Read<Entity*>(memory::Read<std::uintptr_t>(moduleBaseAddress, offsets::entityList), i * 0x8) };
    if (currentEntity == localPlayer)
      continue;

    if (!currentEntity)
      continue;

    if (currentEntity->entityState == 1)
      continue;

    AimbotMath::AimAt(localPlayer, currentEntity);
  }
}
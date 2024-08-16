#pragma once
#include <cstdint>
#include <utility>

namespace offsets
{
constexpr std::uintptr_t localPlayer{ 0x2A2560 };
constexpr std::uintptr_t entityList{ 0x346C90 };
constexpr std::uintptr_t playerCount{ 0x346C9C };
constexpr std::uintptr_t shootFunction{ 0x1DB5E0 };
constexpr std::uintptr_t viewMatrix{ 0x32D040 };

constexpr std::pair<std::uintptr_t, std::uintptr_t> window{ 0x345468 , 0x34546C };
}
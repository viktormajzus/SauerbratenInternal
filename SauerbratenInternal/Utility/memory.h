#pragma once
#include <vector>
#include <cstdint>

#include "ErrorHandling.h"
#include "Offsets/Structs.h"

namespace memory
{
std::expected<std::uintptr_t, Error> GetModuleBaseAddress(std::wstring_view moduleName);

// Deprecated
/*
Entity* GetEntity(std::uintptr_t moduleBaseAddress, std::uintptr_t offset);

int GetPlayerCount(std::uintptr_t moduleBaseAddress, std::uintptr_t offset);

std::uintptr_t GetEntityList(std::uintptr_t moduleBaseAddress, std::uintptr_t offset);
*/

template<typename T>
T Read(std::uintptr_t moduleBaseAddress, std::uintptr_t offset)
{
  std::uintptr_t* objectPtr{
    reinterpret_cast<std::uintptr_t*>(moduleBaseAddress + offset)
  };
  return (T)*objectPtr;
}

template<typename T, std::size_t N>
std::array<T, N> Read(std::uintptr_t moduleBaseAddress, std::uintptr_t offset)
{
  std::array<T, N> result;
  std::memcpy(result.data(), reinterpret_cast<void*>(moduleBaseAddress + offset), sizeof(T) * N);
  return result;
}


void Cleanup(FILE*& f, HMODULE hModule, BOOL isConsoleAllocated);
void Cleanup(FILE*& f, HMODULE hModule, BOOL isConsoleAllocated, Error e);

std::expected<void, Error> Patch(std::uintptr_t dst, const std::vector<std::uint8_t>& bytes);
std::expected<void, Error> Patch(std::uintptr_t dst, std::uint8_t byte, std::size_t size);
}
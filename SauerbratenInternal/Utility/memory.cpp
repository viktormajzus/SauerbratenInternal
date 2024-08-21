#include "../pch.h"
#include "memory.h"

std::expected<std::uintptr_t, Error> memory::GetModuleBaseAddress(std::wstring_view moduleName)
{
  HANDLE snapshot{ CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, 0) };
  if (!snapshot)
    return std::unexpected(Error::failed_module_snapshot);

  MODULEENTRY32 moduleEntry{
    .dwSize{sizeof(moduleEntry)}
  };

  Module32First(snapshot, &moduleEntry);

  do
  {
    if (moduleName.compare(moduleEntry.szModule) != 0)
      continue;

    CloseHandle(snapshot);
    return reinterpret_cast<std::uintptr_t>(moduleEntry.modBaseAddr);
  } while (Module32Next(snapshot, &moduleEntry));

  CloseHandle(snapshot);
  return std::unexpected(Error::module_not_found);
}

void memory::Cleanup(FILE*& f, HMODULE hModule, BOOL isConsoleAllocated)
{
  if (f)
    fclose(f);
  if (isConsoleAllocated)
    FreeConsole();

  MessageBoxW(0, L"Successful termination!", L"Success!", 
              MB_OK | MB_ICONINFORMATION | MB_TOPMOST);

  FreeLibraryAndExitThread(hModule, EXIT_SUCCESS);
}

void memory::Cleanup(FILE*& f, HMODULE hModule, BOOL isConsoleAllocated, Error e)
{
  if (f)
    fclose(f);
  if (isConsoleAllocated)
    FreeConsole();

  MessageBoxW(NULL, error::ErrorParser(e).data(), L"Fatal Error!", 
              MB_OK | MB_ICONERROR | MB_TOPMOST);

  FreeLibraryAndExitThread(hModule, EXIT_FAILURE);
}

Entity* memory::GetEntity(std::uintptr_t moduleBaseAddress, std::uintptr_t offset)
{
  std::uintptr_t* entityPtr{
    reinterpret_cast<std::uintptr_t*>(moduleBaseAddress + offset) };
  return reinterpret_cast<Entity*>(*entityPtr);
}

std::expected<void, Error> memory::Patch(std::uintptr_t dst, const std::vector<std::uint8_t>& bytes)
{
  DWORD oldProtect{};

  std::pair<bool, bool> errorPair{};

  errorPair.first = VirtualProtect(reinterpret_cast<void*>(dst), 
                                   bytes.size(), PAGE_EXECUTE_READWRITE, 
                                   &oldProtect);

  std::memcpy(reinterpret_cast<void*>(dst), bytes.data(), bytes.size());

  errorPair.second = VirtualProtect(reinterpret_cast<void*>(dst), 
                                    bytes.size(), oldProtect, 
                                    &oldProtect);

  if (errorPair.first == false || errorPair.second == false)
    return std::unexpected(Error::virtual_protect_failed);
}

std::expected<void, Error> memory::Patch(std::uintptr_t dst, std::uint8_t byte, std::size_t size)
{
  DWORD oldProtect{};

  std::pair<bool, bool> errorPair{};

  errorPair.first = VirtualProtect(reinterpret_cast<void*>(dst), 
                                   size, PAGE_EXECUTE_READWRITE, 
                                   &oldProtect);

  std::memset(reinterpret_cast<void*>(dst), byte, size);

  errorPair.second = VirtualProtect(reinterpret_cast<void*>(dst), 
                                    size, oldProtect, 
                                    &oldProtect);

  if (errorPair.first == false || errorPair.second == false)
    return std::unexpected(Error::virtual_protect_failed);
}


// Deprecated
/*


int memory::GetPlayerCount(std::uintptr_t moduleBaseAddress, std::uintptr_t offset)
{
  std::uintptr_t* playerCountPtr{
    reinterpret_cast<std::uintptr_t*>(moduleBaseAddress + offset)
  };
  return *playerCountPtr;
}

std::uintptr_t memory::GetEntityList(std::uintptr_t moduleBaseAddress, std::uintptr_t offset)
{
  std::uintptr_t* entityListPtr{
    reinterpret_cast<std::uintptr_t*>(moduleBaseAddress + offset) };
  return *entityListPtr;
}
*/
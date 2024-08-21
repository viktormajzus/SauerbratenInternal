// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "Utility/memory.h"
#include "Features/Aimbot.h"
#include "Offsets/Offsets.h"
#include "Features/ESP.h"

void HackThread(HMODULE hModule)
{
  BOOL console{ AllocConsole() };
  FILE* f;
  freopen_s(&f, "CONOUT$", "w", stdout);

  HWND hwnd{ FindWindow(0, L"Cube 2: Sauerbraten") };
  if (!hwnd)
  {
    memory::Cleanup(f, hModule, console, Error::unknown);
    return;
  }

  std::wstring_view moduleName{ L"sauerbraten.exe" };
  std::expected moduleBaseAddress{ 
    memory::GetModuleBaseAddress(moduleName) };
  if (!moduleBaseAddress)
  {
    memory::Cleanup(f, hModule, console, moduleBaseAddress.error());
    return;
  }

  Entity* localPlayer{
    memory::Read<Entity*>(moduleBaseAddress.value(), offsets::localPlayer)
  };

  bool bAmmo{ false };
  bool bAimbot{ false };
  bool bESP{ false };

  while (!GetAsyncKeyState(VK_DELETE) & 1)
  {
    if (!localPlayer)
      continue;

    if (GetAsyncKeyState(VK_NUMPAD1) & 1)
      bAimbot = !bAimbot;
    if (GetAsyncKeyState(VK_NUMPAD2) & 1)
      bESP = !bESP;

    std::println("Player count: {}", memory::Read<int>(*moduleBaseAddress, offsets::playerCount));

    if (bAimbot)
      feature::Aimbot(*moduleBaseAddress, localPlayer);
    if (bESP)
      feature::ESP(*moduleBaseAddress, localPlayer, hwnd);

    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    system("cls");
  }

  CloseWindow(hwnd);
  memory::Cleanup(f, hModule, console);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
      HANDLE thread{ CreateThread(NULL, 0, 
                                  reinterpret_cast<LPTHREAD_START_ROUTINE>(HackThread), 
                                  hModule, 0, 0) };

      if (thread)
        CloseHandle(thread);
      break;
    }
    case DLL_PROCESS_DETACH:
      
        break;
    }
    return TRUE;
}

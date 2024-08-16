#include "../pch.h"
#include "ErrorHandling.h"

std::wstring_view error::ErrorParser(Error e)
{
  switch (e)
  {
  case Error::failed_module_snapshot:
    return L"Failed to create a module snapshot!";
  case Error::module_not_found:
    return L"Failed to find a matching module!";
  case Error::virtual_protect_failed:
    return L"VirtualProtect function failed!";
  default:
    return L"Unknown error!";
  }
}
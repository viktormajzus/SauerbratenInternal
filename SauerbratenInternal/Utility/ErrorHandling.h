#pragma once
#include <string_view>

enum class Error
{
  failed_module_snapshot, // CreateToolhelp32Snapshot returned an invalid handle
  module_not_found,       // After iterating through the module snapshot, not a single valid module was found
  virtual_protect_failed,  // Used in memory::Patch() functions, when the function failed to chnage page protection
  unknown
};

namespace error
{
std::wstring_view ErrorParser(Error e);
}
#pragma once
#include <string>

namespace imagelite
{

  // Get the name of the platform we're running on
  std::string getPlatformName();

  // Check if running on a specific platform
  bool isWindows();
  bool isMacOS();
  bool isLinux();

  // Get platform-specific image path
  std::string getPlatformDefaultImagePath();

} // namespace imagelite
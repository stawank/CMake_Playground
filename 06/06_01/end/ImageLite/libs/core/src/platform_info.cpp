#include "imagelite/platform_info.h"

namespace imagelite
{

  std::string getPlatformName()
  {
    return IL_PLATFORM_NAME;
  }

  bool isWindows()
  {
#ifdef IL_PLATFORM_WINDOWS
    return true;
#else
    return false;
#endif
  }

  bool isMacOS()
  {
#ifdef IL_PLATFORM_MACOS
    return true;
#else
    return false;
#endif
  }

  bool isLinux()
  {
#ifdef IL_PLATFORM_LINUX
    return true;
#else
    return false;
#endif
  }

  std::string getPlatformDefaultImagePath()
  {
#ifdef IL_PLATFORM_WINDOWS
    return "C:\\Users\\Public\\Pictures\\Sample.jpg";
#elif defined(IL_PLATFORM_MACOS)
    return "/Users/Shared/Sample.jpg";
#elif defined(IL_PLATFORM_LINUX)
    return "/usr/share/backgrounds/sample.jpg";
#else
    return "sample.jpg";
#endif
  }

} // namespace imagelite
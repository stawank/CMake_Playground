#pragma once
#include <iostream>
#include <string>

namespace imagelite
{

#ifdef IMAGELITE_ENABLE_LOGGING
#define LOG_INFO(msg) std::cout << "[INFO] " << msg << std::endl
#define LOG_DEBUG(msg) std::cout << "[DEBUG] " << msg << std::endl
#define LOG_ERROR(msg) std::cerr << "[ERROR] " << msg << std::endl
#else
// In Release mode, these become no-ops
#define LOG_INFO(msg) \
  do                  \
  {                   \
  } while (0)
#define LOG_DEBUG(msg) \
  do                   \
  {                    \
  } while (0)
#define LOG_ERROR(msg) \
  do                   \
  {                    \
  } while (0)
#endif

} // namespace imagelite
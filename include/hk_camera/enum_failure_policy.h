#ifndef HK_CAMERA_ENUM_FAILURE_POLICY_H_
#define HK_CAMERA_ENUM_FAILURE_POLICY_H_

#include <stdexcept>

#include "libMVSapi/MvErrorDefine.h"

namespace hk_camera
{
inline bool canContinueAfterDeviceEnumeration(int result) noexcept
{
  return result == MV_OK;
}

inline void throwOnDeviceEnumerationFailure(int result)
{
  if (!canContinueAfterDeviceEnumeration(result))
  {
    throw std::runtime_error("MV_CC_EnumDevices failed");
  }
}
}  // namespace hk_camera

#endif  // HK_CAMERA_ENUM_FAILURE_POLICY_H_

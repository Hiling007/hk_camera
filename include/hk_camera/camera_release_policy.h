#ifndef HK_CAMERA_CAMERA_RELEASE_POLICY_H_
#define HK_CAMERA_CAMERA_RELEASE_POLICY_H_

namespace hk_camera
{
struct CameraReleasePolicy
{
  bool stop_grabbing;
  bool close_device;
};

// On a disconnected U3V handle, Stop/Close wait for USB transport timeouts;
// DestroyHandle performs the required stale-handle cleanup directly.
inline CameraReleasePolicy cameraReleasePolicy(bool device_connected) noexcept
{
  return CameraReleasePolicy{device_connected, device_connected};
}
}  // namespace hk_camera

#endif  // HK_CAMERA_CAMERA_RELEASE_POLICY_H_

#include <gtest/gtest.h>

#include <hk_camera/camera_release_policy.h>

TEST(CameraReleasePolicy, GracefullyStopsAndClosesConnectedDevice)
{
  const hk_camera::CameraReleasePolicy policy = hk_camera::cameraReleasePolicy(true);

  EXPECT_TRUE(policy.stop_grabbing);
  EXPECT_TRUE(policy.close_device);
}

TEST(CameraReleasePolicy, DirectlyDestroysDisconnectedDevice)
{
  const hk_camera::CameraReleasePolicy policy = hk_camera::cameraReleasePolicy(false);

  EXPECT_FALSE(policy.stop_grabbing);
  EXPECT_FALSE(policy.close_device);
}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

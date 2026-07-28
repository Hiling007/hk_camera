#include <gtest/gtest.h>

#include <hk_camera/enum_failure_policy.h>

namespace
{
class DestructionMarker
{
public:
  explicit DestructionMarker(bool* destroyed) : destroyed_(destroyed) {}

  ~DestructionMarker()
  {
    *destroyed_ = true;
  }

private:
  bool* destroyed_;
};
}  // namespace

TEST(DeviceEnumerationFailurePolicy, SuccessfulEnumerationDoesNotThrow)
{
  EXPECT_TRUE(hk_camera::canContinueAfterDeviceEnumeration(MV_OK));
  EXPECT_NO_THROW(hk_camera::throwOnDeviceEnumerationFailure(MV_OK));
}

TEST(DeviceEnumerationFailurePolicy, InitializationFailureThrowsAndUnwindsStack)
{
  bool destroyed = false;

  try
  {
    DestructionMarker marker(&destroyed);
    hk_camera::throwOnDeviceEnumerationFailure(-1);
    FAIL() << "expected failed device enumeration to throw";
  }
  catch (const std::runtime_error&)
  {
  }

  EXPECT_TRUE(destroyed);
}

TEST(DeviceEnumerationFailurePolicy, ConnectionCheckFailureThrowsBeforeReconnectLogic)
{
  bool reconnect_logic_entered = false;

  try
  {
    hk_camera::throwOnDeviceEnumerationFailure(-1);
    reconnect_logic_entered = true;
    FAIL() << "expected failed device enumeration to throw";
  }
  catch (const std::runtime_error&)
  {
  }

  EXPECT_FALSE(reconnect_logic_entered);
}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

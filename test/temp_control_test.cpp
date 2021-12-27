#include "temp_control.hpp"
#include <gtest/gtest.h>
#include "gmock/gmock.h"
#include "error_numbers.h"


using ::testing::AtLeast;
using ::testing::Return;

class MockTempSensor: public TempSensor
{
public:
    MOCK_METHOD(int32_t, Init, (), (override));
    MOCK_METHOD(int32_t, Deinit, (), (override));
    MOCK_METHOD(int32_t, GetTemp, (int32_t& s32_temp_value), (override));
};

class MockTempActuator: public TempActuator
{
public:
    MOCK_METHOD(int32_t, Init, (), (override));
    MOCK_METHOD(int32_t, Deinit, (), (override));
    MOCK_METHOD(int32_t, GetAction, (eTempActuatorAction& e_action), (override));
};


class TempControlTest : public ::testing::Test
{
protected:
    MockTempSensor mocked_temp_sensor_obj;
    MockTempActuator mocked_temp_actuator_obj;
    TempControl temp_control_obj;

    TempControlTest() : temp_control_obj(mocked_temp_sensor_obj, mocked_temp_actuator_obj){}


    virtual void SetUp() override
    {
        EXPECT_CALL(mocked_temp_sensor_obj, Init()).
        Times(1).WillOnce(Return(SUCCESS));

        EXPECT_CALL(mocked_temp_actuator_obj, Init()).
        Times(1).WillOnce(Return(SUCCESS));

        /* Initialize the module */
        ASSERT_EQ(SUCCESS, temp_control_obj.Init());
    }

    virtual void TearDown() override
    {
        EXPECT_CALL(mocked_temp_sensor_obj, Deinit()).
        Times(1).WillOnce(Return(SUCCESS));

        EXPECT_CALL(mocked_temp_actuator_obj, Deinit()).
        Times(1).WillOnce(Return(SUCCESS));

        /* De-initialize the module */
        ASSERT_EQ(SUCCESS, temp_control_obj.Deinit());
    }
};

TEST_F(TempControlTest, SetMinMaxT)
{
    /* Test valid +ve values */
    EXPECT_EQ(SUCCESS, temp_control_obj.SetMinMaxTemp(20, 30));
    EXPECT_EQ(SUCCESS, temp_control_obj.SetMinMaxTemp(20, 20));

    /* Test valid -ve values */
    EXPECT_EQ(SUCCESS, temp_control_obj.SetMinMaxTemp(-2, -1));
    EXPECT_EQ(SUCCESS, temp_control_obj.SetMinMaxTemp(-2, -2));

    /* Test valid 0 values */
    EXPECT_EQ(SUCCESS, temp_control_obj.SetMinMaxTemp(0, 0));
    
    /* Test invalid +ve values */
    EXPECT_EQ(ERROR_INV_INPUTS, temp_control_obj.SetMinMaxTemp(30, 20));

    /* Test invalid -ve values */
    EXPECT_EQ(ERROR_INV_INPUTS, temp_control_obj.SetMinMaxTemp(-1, -2));
}

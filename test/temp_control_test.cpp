#include "temp_control.hpp"
#include <gtest/gtest.h>
#include "gmock/gmock.h"
#include "error_numbers.hpp"


using ::testing::AtLeast;
using ::testing::Return;
using ::testing::DoAll;
using ::testing::SetArgReferee;
using ::testing::_;

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
    MOCK_METHOD(int32_t, GetStatus, (eTempActuatorStatus& e_status), (override));
    MOCK_METHOD(int32_t, TakeAction, (eTempActuatorAction e_action), (override));
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


TEST_F(TempControlTest, UpdateTmaxGreatherThanTmin)
{
    ASSERT_EQ(SUCCESS, temp_control_obj.SetMinMaxTemp(20, 30));

    /* Test current temperature > Tmax */
    EXPECT_CALL(mocked_temp_sensor_obj, GetTemp(_)).
        Times(1).WillOnce(DoAll(SetArgReferee<0>(35), Return(SUCCESS)));

    EXPECT_CALL(mocked_temp_actuator_obj, TakeAction(TempActuator::ACTION_COOL)).
        Times(1).WillOnce(Return(SUCCESS));

    EXPECT_EQ(SUCCESS, temp_control_obj.Update());


    /* Test current temperature = Tmax */
    EXPECT_CALL(mocked_temp_sensor_obj, GetTemp(_)).
        Times(1).WillOnce(DoAll(SetArgReferee<0>(30), Return(SUCCESS)));

    EXPECT_CALL(mocked_temp_actuator_obj, TakeAction(TempActuator::ACTION_STOP)).
        Times(1).WillOnce(Return(SUCCESS));

    EXPECT_EQ(SUCCESS, temp_control_obj.Update());


    /* Test current temperature < Tmax and > Tmin */
    EXPECT_CALL(mocked_temp_sensor_obj, GetTemp(_)).
        Times(1).WillOnce(DoAll(SetArgReferee<0>(25), Return(SUCCESS)));

    EXPECT_CALL(mocked_temp_actuator_obj, TakeAction(TempActuator::ACTION_STOP)).
        Times(1).WillOnce(Return(SUCCESS));

    EXPECT_EQ(SUCCESS, temp_control_obj.Update());


    /* Test current temperature = Tmin */
    EXPECT_CALL(mocked_temp_sensor_obj, GetTemp(_)).
        Times(1).WillOnce(DoAll(SetArgReferee<0>(20), Return(SUCCESS)));

    EXPECT_CALL(mocked_temp_actuator_obj, TakeAction(TempActuator::ACTION_STOP)).
        Times(1).WillOnce(Return(SUCCESS));

    EXPECT_EQ(SUCCESS, temp_control_obj.Update());


    /* Test current temperature < Tmin */
    EXPECT_CALL(mocked_temp_sensor_obj, GetTemp(_)).
        Times(1).WillOnce(DoAll(SetArgReferee<0>(10), Return(SUCCESS)));

    EXPECT_CALL(mocked_temp_actuator_obj, TakeAction(TempActuator::ACTION_HEAT)).
        Times(1).WillOnce(Return(SUCCESS));

    EXPECT_EQ(SUCCESS, temp_control_obj.Update());
}


TEST_F(TempControlTest, UpdateTmaxEqualTmin)
{
    ASSERT_EQ(SUCCESS, temp_control_obj.SetMinMaxTemp(20, 20));

    /* Test current temperature > T */
    EXPECT_CALL(mocked_temp_sensor_obj, GetTemp(_)).
        Times(1).WillOnce(DoAll(SetArgReferee<0>(25), Return(SUCCESS)));

    EXPECT_CALL(mocked_temp_actuator_obj, TakeAction(TempActuator::ACTION_COOL)).
        Times(1).WillOnce(Return(SUCCESS));

    EXPECT_EQ(SUCCESS, temp_control_obj.Update());


    /* Test current temperature = T */
    EXPECT_CALL(mocked_temp_sensor_obj, GetTemp(_)).
        Times(1).WillOnce(DoAll(SetArgReferee<0>(20), Return(SUCCESS)));

    EXPECT_CALL(mocked_temp_actuator_obj, TakeAction(TempActuator::ACTION_STOP)).
        Times(1).WillOnce(Return(SUCCESS));

    EXPECT_EQ(SUCCESS, temp_control_obj.Update());


    /* Test current temperature < T */
    EXPECT_CALL(mocked_temp_sensor_obj, GetTemp(_)).
        Times(1).WillOnce(DoAll(SetArgReferee<0>(15), Return(SUCCESS)));

    EXPECT_CALL(mocked_temp_actuator_obj, TakeAction(TempActuator::ACTION_HEAT)).
        Times(1).WillOnce(Return(SUCCESS));

    EXPECT_EQ(SUCCESS, temp_control_obj.Update());
}

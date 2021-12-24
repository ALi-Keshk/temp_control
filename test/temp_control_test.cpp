#include "temp_control.hpp"
#include <gtest/gtest.h>
#include "gmock/gmock.h"
#include "error_numbers.h"


using ::testing::AtLeast;
using ::testing::Return;

class Mock_temp_sensor: public temp_sensor
{
public:
    MOCK_METHOD(int32_t, init, (), (override));
};


struct temp_control_test : public ::testing::Test
{
    temp_control temp_control_obj;
    Mock_temp_sensor mocked_temp_sensor_obj;

    virtual void SetUp() override
    {
        EXPECT_CALL(mocked_temp_sensor_obj, init()).
        Times(1).WillOnce(Return(SUCCESS));
        /* Initialize the module */
        ASSERT_EQ(SUCCESS, temp_control_obj.init(mocked_temp_sensor_obj));
    }

    virtual void TearDown() override
    {
        /* De-initialize the module */
        ASSERT_EQ(SUCCESS, temp_control_obj.deinit());
    }
};

TEST_F(temp_control_test, set_min_max_test)
{
    /* Test valid +ve values */
    EXPECT_EQ(SUCCESS, temp_control_obj.set_min_max_temp(20, 30));
    EXPECT_EQ(SUCCESS, temp_control_obj.set_min_max_temp(20, 20));

    /* Test valid -ve values */
    EXPECT_EQ(SUCCESS, temp_control_obj.set_min_max_temp(-2, -1));
    EXPECT_EQ(SUCCESS, temp_control_obj.set_min_max_temp(-2, -2));

    /* Test valid 0 values */
    EXPECT_EQ(SUCCESS, temp_control_obj.set_min_max_temp(0, 0));
    
    /* Test invalid +ve values */
    EXPECT_EQ(ERROR_INV_INPUTS, temp_control_obj.set_min_max_temp(30, 20));

    /* Test invalid -ve values */
    EXPECT_EQ(ERROR_INV_INPUTS, temp_control_obj.set_min_max_temp(-1, -2));
}

#include <gtest/gtest.h>
#include "../temp_control.hpp"

struct temp_control_test : public ::testing::Test
{
    virtual void SetUp() override
    {
        /* Initialize the module */
        ASSERT_EQ(TEMP_CONTROL_SUCCESS, temp_control_init());
    }

    virtual void TearDown() override
    {
        /* De-initialize the module */
        ASSERT_EQ(TEMP_CONTROL_SUCCESS, temp_control_deinit());
    }
};

TEST_F(temp_control_test, set_min_max_test)
{
    /* Test valid +ve values */
    EXPECT_EQ(TEMP_CONTROL_SUCCESS, temp_control_set_min_max_temp(20, 30));
    EXPECT_EQ(TEMP_CONTROL_SUCCESS, temp_control_set_min_max_temp(20, 20));

    /* Test valid -ve values */
    EXPECT_EQ(TEMP_CONTROL_SUCCESS, temp_control_set_min_max_temp(-2, -1));
    EXPECT_EQ(TEMP_CONTROL_SUCCESS, temp_control_set_min_max_temp(-2, -2));

    /* Test valid 0 values */
    EXPECT_EQ(TEMP_CONTROL_SUCCESS, temp_control_set_min_max_temp(0, 0));
    
    /* Test invalid +ve values */
    EXPECT_EQ(TEMP_CONTROL_ERR_INV_INPUTS, temp_control_set_min_max_temp(30, 20));

    /* Test invalid -ve values */
    EXPECT_EQ(TEMP_CONTROL_ERR_INV_INPUTS, temp_control_set_min_max_temp(-1, -2));
}

#include <gtest/gtest.h>
#include "../temp_control.hpp"

TEST(ExampleTest, DemonstrateGTestMacros)
{
    int32_t s32_return_value = temp_control_init();
    EXPECT_EQ(TEMP_CONTROL_SUCCESS, s32_return_value);
    
    EXPECT_EQ(TEMP_CONTROL_SUCCESS, temp_control_set_min_max_temp(20, 30));
    EXPECT_EQ(TEMP_CONTROL_SUCCESS, temp_control_set_min_max_temp(20, 20));
    EXPECT_EQ(TEMP_CONTROL_ERR_INV_INPUTS, temp_control_set_min_max_temp(20, 19));
}
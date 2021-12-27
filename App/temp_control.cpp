
/*******************************************************/
/*                 Includes                            */
/*******************************************************/
#include "temp_control.hpp"
#include "error_numbers.h"
#include <cstdio>

/*******************************************************/
/*                 MACROS                              */
/*******************************************************/

/* Macros used for logging to the standard output */

/* TODO: Support levels for logging */

/* comment this line to disable logging */
#define LOGGING_ENABLED

#ifdef LOGGING_ENABLED
/* Default log function */
#define LOG(msg, ...)           printf("[TEMP_CTRL]: " msg, __VA_ARGS__)
/* Log information in Blue */
#define LOG_INFO(msg, ...)      printf("\u001b[34m" "[TEMP_CTRL: INFO]: " msg "\u001b[0m", __VA_ARGS__)
/* Log Warnings in yelow */
#define LOG_WARNING(msg, ...)   printf("\u001b[33m" "[TEMP_CTRL: WARNING]: " msg "\u001b[0m", __VA_ARGS__)
/* Log Errors in Red */
#define LOG_ERROR(msg, ...)     printf("\u001b[31m" "[TEMP_CTRL: ERROR]: " msg "\u001b[0m", __VA_ARGS__)
#else
#define LOG(msg, ...)
#define LOG_INFO(msg, ...)
#define LOG_WARNING(msg, ...)
#define LOG_ERROR(msg, ...)
#endif

/*******************************************************/
/*  private and protected functions Implementation     */
/*******************************************************/


/*******************************************************/
/*                 APIs Implementation                 */
/*******************************************************/
/* @brief The constructor to the temp_control module.
 *  @param _temp_sensor_obj reference to TempSensor object to be used by this class
 *  @param _temp_actuator_obj reference to TempActuator object to be used by this class
 *  @return None
*/
TempControl::TempControl(TempSensor& _temp_sensor_obj, TempActuator& _temp_actuator_obj) : temp_sensor_obj(_temp_sensor_obj), temp_actuator_obj(_temp_actuator_obj)
{
    b_initialized = false;
    s32_min_temp = 0;
    s32_max_temp = 0;
}

/*  @brief Initializes the temp_control module.
 *  @param void
 *  @return TEMP_CONTROL_SUCCESS for success 
 *          Otherwise refer to @ref Return Values
*/
int32_t TempControl::Init(void)
{
    int32_t s32_return_value = ERROR_DEFAULT;
    if(!b_initialized)
    {
        /* TODO: initialization sequence */
        s32_return_value = temp_sensor_obj.Init();
        if(SUCCESS == s32_return_value)
        {
            s32_return_value = temp_actuator_obj.Init();
            if(SUCCESS == s32_return_value)
            {
                b_initialized = true;
                LOG_INFO("Initialization Succeeded.\r\n");
            }
            else
            {
                LOG_ERROR("Initialization Failed (temp actuator) with error %d\r\n", s32_return_value);
            }
        }
        else
        {
            LOG_ERROR("Initialization Failed (temp sensor) with error %d\r\n", s32_return_value);
        }
    }
    else
    {
        LOG_ERROR("Already Initialized.\r\n");
        s32_return_value = ERROR_ALREADY_INITALIZED;
    }

    return s32_return_value;
}

/*  @brief De-initializes the temp_control module.
 *  @param void
 *  @return TEMP_CONTROL_SUCCESS for success 
 *          Otherwise refer to @ref Return Values
*/
int32_t TempControl::Deinit(void)
{
    int32_t s32_return_value = ERROR_DEFAULT;
    if(b_initialized)
    {
        /* TODO: deinitialization sequence */

        s32_return_value = temp_sensor_obj.Deinit();
        if(SUCCESS == s32_return_value)
        {
            s32_return_value = temp_actuator_obj.Deinit();
            if(SUCCESS == s32_return_value)
            {
                b_initialized = false;
                LOG_INFO("De-Initialization Succeeded.\r\n");
            }
            else
            {
                LOG_ERROR("De-Initialization Failed (temp actuator) with error %d\r\n", s32_return_value);
            }
        }
        else
        {
            LOG_ERROR("De-Initialization Failed (temp sensor) with error %d\r\n", s32_return_value);
        }
    }
    else
    {
        /* Here, we can return "Already de_initialized error" or return success
         * This depends on the design
         * We will return success here to 
         * allow this method to be called multiple times without returning an error
         */

        s32_return_value = SUCCESS;
    }

    return s32_return_value;
}

/*  @brief Adjusts the required minimum and maximum values of the temperature.
 *  @param s32_min_val Minimum temperature value
 *  @param s32_max_val Maximum temperature value
 *  @return TEMP_CONTROL_SUCCESS for success 
 *          Otherwise refer to @ref Return Values
*/
int32_t TempControl::SetMinMaxTemp(int32_t s32_min_val, int32_t s32_max_val)
{
    int32_t s32_return_value = ERROR_DEFAULT;

    if(b_initialized)
    {
        if(s32_max_val >= s32_min_val)
        {
            s32_min_temp = s32_min_val;
            s32_max_temp = s32_max_val;

            /* TODO: update the current action */

            s32_return_value = SUCCESS;
        }
        else
        {
            s32_return_value = ERROR_INV_INPUTS;
        }
    }
    else
    {
        s32_return_value = ERROR_NOT_INITALIZED;
    }

    return s32_return_value;
}


/*  @brief Run the temp_control module dispatcher to handle events.
 *  @param void
 *  @return void
*/
void TempControl::Dispatch(void)
{
    /* read temperature */
    /* read current action */
    /* calculate action */
    /* take action (if required) */

    return;
}


/*******************************************************/
/*                 Includes                            */
/*******************************************************/
#include "temp_control.hpp"
#include "error_numbers.hpp"
#include <cstdio>

/*******************************************************/
/*                 MACROS                              */
/*******************************************************/

/* Macros used for logging to the standard output */

/* TODO: Support levels for logging and log errors to standard error*/

/* comment this line to disable logging */
//#define LOGGING_ENABLED

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
/*            private functions Implementation         */
/*******************************************************/

/*  @brief Calculate the required action.
 *  @param s32_current_temp the current temperature value
 *  @return the requied action
*/
TempActuator::eTempActuatorAction TempControl::CalculateAction(int32_t s32_current_temp)
{
    /** Calculating action is based only on the curretn temperature in this approach for simpilicity
     *  and checking the current status is left for the TempActuator class to check before taking the action 
     *  A different approch could be based on both, the current temperature and the current status for the 
     *  TempActuator class
     *  in this case, the TempActuator class will directly apply the required action without checking the status
    */
   
    TempActuator::eTempActuatorAction e_required_action = TempActuator::ACTION_INVALID;

    if((s32_current_temp <= s32_max_temp) && (s32_current_temp >= s32_min_temp))
    {
        /* Reached required temperature >>> stop current action */
        e_required_action = TempActuator::ACTION_STOP;
    }
    else if ((s32_current_temp > s32_max_temp))
    {
        /* temperature is higher than required >>> start cooling */
        e_required_action = TempActuator::ACTION_COOL;
    }
    else
    {
        /* temperature is lower than required >>> start heating */
        e_required_action = TempActuator::ACTION_HEAT;
    }

    return e_required_action;
}

/*******************************************************/
/*                 APIs Implementation                 */
/*******************************************************/
/*  @brief The constructor to the temp_control module.
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
            /** TODO: handle the equaliy case to prevent rapid changing between actions 
             *  One way to handle this is by setting s32_min_val = s32_min_val - OFFSET
             *  and setting s32_max_val = s32_max_val + OFFSET
            */
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


/*  @brief calculate and update the current state required.
 *  @note Call this method periodically (every 10 min for example) to update the current module state.
 *  @param void
 *  @return SUCCESS for success 
 *          Otherwise refer to @ref Return Values
*/
int32_t TempControl::Update(void)
{
    int32_t s32_return_value = ERROR_DEFAULT;

    /* read temperature */
    int32_t s32_temp_value = 0;
    s32_return_value = temp_sensor_obj.GetTemp(s32_temp_value);
    if(SUCCESS == s32_return_value)
    {
        LOG_INFO("Read temperature = %d\r\n", s32_temp_value);
        
        /* Calculate action */
        TempActuator::eTempActuatorAction e_required_action = TempActuator::ACTION_INVALID;

        e_required_action = CalculateAction(s32_temp_value);
        LOG_INFO("Required Action = %d\r\n", e_required_action);

        /* take action (if required) */
        s32_return_value = temp_actuator_obj.TakeAction(e_required_action);
        if(SUCCESS == s32_return_value)
        {
            LOG_INFO("Take action success.\r\n");
        }
        else
        {
            LOG_ERROR("Take action failed with error %d", s32_return_value);
        }
    }
    else
    {
        LOG_ERROR("Failed in reading temperature with error %d", s32_return_value);
    }

    return s32_return_value;
}

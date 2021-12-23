
/*******************************************************/
/*                 Includes                            */
/*******************************************************/
#include "temp_control.hpp"

/*******************************************************/
/*                 MACROS                              */
/*******************************************************/

/*******************************************************/
/*                 ENUMS and STRUCTS                   */
/*******************************************************/


/*******************************************************/
/*             Global static Variables                 */
/*******************************************************/
static bool gb_initialized;
static int32_t gs32_settings_min_temp;
static int32_t gs32_settings_max_temp;

/*******************************************************/
/*             static functions Implementation         */
/*******************************************************/

/*******************************************************/
/*                 APIs Implementation                 */
/*******************************************************/


/*  @brief Initializes the temp_control module.
 *  @param void
 *  @return TEMP_CONTROL_SUCCESS for success 
 *          Otherwise refer to @ref Return Values
*/
int32_t temp_control_init(void)
{
    int32_t s32_return_value = TEMP_CONTROL_ERR;
    if(!gb_initialized)
    {
        /* TODO: initialization sequence */

        gb_initialized = true;
        s32_return_value = TEMP_CONTROL_SUCCESS;
    }
    else
    {
        /* Here, we can return "Already initialized error" or return success
         * This depends on the design
         * We will return success here to allow this module to be used by multiple upper layer 
         */

        s32_return_value = TEMP_CONTROL_SUCCESS;
    }

    return s32_return_value;
}

/*  @brief Adjusts the required minimum and maximum values of the temperature.
 *  @param s32_min_val Minimum temperature value
 *  @param s32_max_val Maximum temperature value
 *  @return TEMP_CONTROL_SUCCESS for success 
 *          Otherwise refer to @ref Return Values
*/
int32_t temp_control_set_min_max_temp(int32_t s32_min_val, int32_t s32_max_val)
{
    int32_t s32_return_value = TEMP_CONTROL_ERR;

    if(gb_initialized)
    {
        if(s32_max_val >= s32_min_val)
        {
            gs32_settings_min_temp = s32_min_val;
            gs32_settings_max_temp = s32_max_val;

            /* TODO: update the current action */

            s32_return_value = TEMP_CONTROL_SUCCESS;
        }
        else
        {
            s32_return_value = TEMP_CONTROL_ERR_INV_INPUTS;
        }
    }
    else
    {
        s32_return_value = TEMP_CONTROL_ERR_NOT_INITALIZED;
    }

    return s32_return_value;
}


/*  @brief Run the temp_control module dispatcher to handle events.
 *  @param void
 *  @return void
*/
void temp_control_dispatch(void)
{
    /* read temperature */
    /* read current action */
    /* calculate action */
    /* take action (if required) */

    return;
}

#ifndef __TEMP_SENSOR__
#define __TEMP_SENSOR__


/*******************************************************/
/*                 Includes                            */
/*******************************************************/
#include <stdint.h>
#include "error_numbers.hpp"

/*******************************************************/
/*                 MACROS                              */
/*******************************************************/

/*******************************************************/
/*                 ENUMS and STRUCTS                   */
/*******************************************************/


/*******************************************************/
/*                 Class Declaration                   */
/*******************************************************/

class TempSensor
{
public:
    /** @brief Initializes the temp_sensor module.
     *  @param void
     *  @return TEMP_SENSOR_SUCCESS for success 
     *          Otherwise refer to @ref Return Values
    */
    virtual int32_t Init(void)
    {
        return SUCCESS;
    }
    /** @brief De-initializes the temp_sensor module.
     *  @param void
     *  @return TEMP_SENSOR_SUCCESS for success 
     *          Otherwise refer to @ref Return Values
    */
    virtual int32_t Deinit(void)
    {
        return SUCCESS;
    }

    /** @brief  Reads the current temperature.
     *  @param  s32_temp_value reference to signed 32-bit variable to store the temperature value
     *  @return TEMP_SENSOR_SUCCESS for success.
     *          Otherwise refer to @ref Return Values
    */
    virtual int32_t GetTemp(int32_t& s32_temp_value)
    {
        return SUCCESS;
    }


    /** @brief Run the temp_sensor module dispatcher to handle events.
     *  @param void
     *  @return void
    */
    virtual void Dispatch(void)
    {
        return;
    }
};


#endif  /* __TEMP_SENSOR__ */

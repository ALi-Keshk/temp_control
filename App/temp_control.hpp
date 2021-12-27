#ifndef __TEMP_CONTROL__
#define __TEMP_CONTROL__


/*******************************************************/
/*                 Includes                            */
/*******************************************************/
#include <stdint.h>
#include "temp_sensor.hpp"

/*******************************************************/
/*                 MACROS                              */
/*******************************************************/


/*******************************************************/
/*                 ENUMS and STRUCTS                   */
/*******************************************************/


/*******************************************************/
/*                 Class Declaration                   */
/*******************************************************/

class TempControl
{
private:
    bool b_initialized;
    int32_t s32_min_temp;
    int32_t s32_max_temp;
    TempSensor& temp_sensor_obj;

public:
    /** @brief The constructor to the temp_control module.
     *  @param _temp_sensor_obj reference to temp_sensor object to be used by this class
     *  @return None
    */
    TempControl(TempSensor& _temp_sensor_obj);


    /** @brief Initializes the temp_control module.
     *  @param void
     *  @return TEMP_CONTROL_SUCCESS for success 
     *          Otherwise refer to @ref Return Values
    */
    int32_t Init(void);

    /** @brief De-initializes the temp_control module.
     *  @param void
     *  @return TEMP_CONTROL_SUCCESS for success 
     *          Otherwise refer to @ref Return Values
    */
    int32_t Deinit(void);

    /** @brief  Adjusts the required minimum and maximum values of the temperature.
     *  @note   The maximum temperature value must be >= the Minmum temperature value.
     *  @param  s32_min_val Minimum temperature value
     *  @param  s32_max_val Maximum temperature value
     *  @return TEMP_CONTROL_SUCCESS for success.
     *          TEMP_CONTROL_ERR_INV_INPUTS if s32_max_val < s32_min_val.
    */
    int32_t SetMinMaxTemp(int32_t s32_min_val, int32_t s32_max_val);


    /** @brief Run the temp_control module dispatcher to handle events.
     *  @param void
     *  @return void
    */
    void Dispatch(void);

};

#endif  /* __TEMP_CONTROL__ */

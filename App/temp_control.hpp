#ifndef __TEMP_CONTROL__
#define __TEMP_CONTROL__


/*******************************************************/
/*                 Includes                            */
/*******************************************************/
#include <stdint.h>
#include "error_numbers.hpp"
#include "temp_sensor.hpp"
#include "temp_actuator.hpp"

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
    TempActuator& temp_actuator_obj;

    /** @brief Calculate the required action.
     *  @param s32_current_temp the current temperature value
     *  @return the requied action
    */
    TempActuator::eTempActuatorAction CalculateAction(int32_t s32_current_temp);

public:
    /** @brief The constructor to the temp_control module.
     *  @param _temp_sensor_obj reference to temp_sensor object to be used by this class
     *  @return None
    */
    TempControl(TempSensor& _temp_sensor_obj, TempActuator& _temp_actuator_obj);


    /** @brief Initializes the temp_control module.
     *  @param void
     *  @return SUCCESS for success 
     *          Otherwise refer to @ref Return Values
    */
    int32_t Init(void);

    /** @brief De-initializes the temp_control module.
     *  @param void
     *  @return SUCCESS for success 
     *          Otherwise refer to @ref Return Values
    */
    int32_t Deinit(void);

    /** @brief  Adjusts the required minimum and maximum values of the temperature.
     *  @note   The maximum temperature value must be >= the Minmum temperature value.
     *  @param  s32_min_val Minimum temperature value
     *  @param  s32_max_val Maximum temperature value
     *  @return SUCCESS for success.
     *          ERROR_INV_INPUTS if s32_max_val < s32_min_val.
    */
    int32_t SetMinMaxTemp(int32_t s32_min_val, int32_t s32_max_val);


    /** @brief calculate and update the current state required.
     *  @note Call this method periodically (every 10 min for example) to update the current module state.
     *  @param void
     *  @return SUCCESS for success 
     *          Otherwise refer to @ref Return Values
    */
    int32_t Update(void);

};

#endif  /* __TEMP_CONTROL__ */

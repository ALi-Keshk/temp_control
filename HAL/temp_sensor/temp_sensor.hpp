#ifndef __TEMP_SENSOR__
#define __TEMP_SENSOR__


/*******************************************************/
/*                 Includes                            */
/*******************************************************/
#include <stdint.h>

/*******************************************************/
/*                 MACROS                              */
/*******************************************************/

/*******************************************************/
/*                 ENUMS and STRUCTS                   */
/*******************************************************/


/*******************************************************/
/*                 Class Declaration                   */
/*******************************************************/

class temp_sensor
{
public:
    /** @brief Initializes the temp_sensor module.
     *  @param void
     *  @return TEMP_SENSOR_SUCCESS for success 
     *          Otherwise refer to @ref Return Values
    */
    virtual int32_t init(void) = 0;
#if 0
    /** @brief De-initializes the temp_sensor module.
     *  @param void
     *  @return TEMP_SENSOR_SUCCESS for success 
     *          Otherwise refer to @ref Return Values
    */
    virtual int32_t deinit(void);

    /** @brief  Reads the current temperature.
     *  @param  ps32_temp_value pointer to signed 32-bit variable to store the temperature value
     *  @return TEMP_SENSOR_SUCCESS for success.
     *          Otherwise refer to @ref Return Values
    */
    virtual int32_t get_temp(int32_t * ps32_temp_value);


    /** @brief Run the temp_sensor module dispatcher to handle events.
     *  @param void
     *  @return void
    */
    virtual void dispatch(void);
#endif
};


#endif  /* __TEMP_SENSOR__ */

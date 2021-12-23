#ifndef __TEMP_CONTROL__
#define __TEMP_CONTROL__


/*******************************************************/
/*                 Includes                            */
/*******************************************************/
#include <stdint.h>

/*******************************************************/
/*                 MACROS                              */
/*******************************************************/
/**
 * @brief Return Values
 */

#define TEMP_CONTROL_SUCCESS                (0)
#define TEMP_CONTROL_ERR                    (-1)
#define TEMP_CONTROL_ERR_INV_INPUTS         (-2)
#define TEMP_CONTROL_ERR_NOT_INITALIZED     (-2)

/*******************************************************/
/*                 ENUMS and STRUCTS                   */
/*******************************************************/


/*******************************************************/
/*                 APIs Declarations                   */
/*******************************************************/


/** @brief Initializes the temp_control module.
 *  @param void
 *  @return TEMP_CONTROL_SUCCESS for success 
 *          Otherwise refer to @ref Return Values
*/
int32_t temp_control_init(void);

/** @brief  Adjusts the required minimum and maximum values of the temperature.
 *  @note   The maximum temperature value must be >= the Minmum temperature value.
 *  @param  s32_min_val Minimum temperature value
 *  @param  s32_max_val Maximum temperature value
 *  @return TEMP_CONTROL_SUCCESS for success.
 *          TEMP_CONTROL_ERR_INV_INPUTS if s32_max_val < s32_min_val.
*/
int32_t temp_control_set_min_max_temp(int32_t s32_min_val, int32_t s32_max_val);


/** @brief Run the temp_control module dispatcher to handle events.
 *  @param void
 *  @return void
*/
void temp_control_dispatch(void);


#endif  /* __TEMP_CONTROL__ */

#ifndef __TEMP_ACTUATOR__
#define __TEMP_ACTUATOR__


/*******************************************************/
/*                 Includes                            */
/*******************************************************/
#include <stdint.h>
#include "error_numbers.h"

/*******************************************************/
/*                 MACROS                              */
/*******************************************************/

/*******************************************************/
/*                 ENUMS and STRUCTS                   */
/*******************************************************/


/*******************************************************/
/*                 Class Declaration                   */
/*******************************************************/

class TempActuator
{
public:
    enum eTempActuatorAction
    {
        ACTION_IDLE = 0,
        ACTION_STOP,
        ACTION_COOL,
        ACTION_HEAT
    };

    /** @brief Initializes the TempActuator class.
     *  @param void
     *  @return SUCCESS for success 
     *          Otherwise refer to @ref Return Values
    */
    virtual int32_t Init(void)
    {
        return SUCCESS;
    }
    /** @brief De-initializes the TempActuator class.
     *  @param void
     *  @return SUCCESS for success 
     *          Otherwise refer to @ref Return Values
    */
    virtual int32_t Deinit(void)
    {
        return SUCCESS;
    }

    /** @brief  take action to start cooling, heating or stop the current operation.
     *  @param  e_action the required action to be handled by the method
     *  @return SUCCESS for success.
     *          Otherwise refer to @ref Return Values
    */
    virtual int32_t TakeAction(eTempActuatorAction e_action)
    {
        return SUCCESS;
    }

    /** @brief  return the current action.
     *  @param  e_action reference to enum to hold the current action.
     *  @return SUCCESS for success.
     *          Otherwise refer to @ref Return Values
    */
    virtual int32_t GetAction(eTempActuatorAction& e_action)
    {
        return SUCCESS;
    }
    


    /** @brief Run the TempActuator class dispatcher to handle events.
     *  @param void
     *  @return void
    */
    virtual void Dispatch(void)
    {
        return;
    }
};


#endif  /* __TEMP_ACTUATOR__ */

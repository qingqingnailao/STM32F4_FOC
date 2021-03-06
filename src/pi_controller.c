/*
 * pi_controller.c
 *
 *  Created on: 08.02.2016
 *      Author: Michael Meiler
 */

/*------------------------------------------------- PI Controller -----
|  Function:	PI_control (float32_t ref, float32_t var)
|
|  Purpose:		Proportional and Integral controller
|
|  Parameters:	[in]	float32_t ref: reference value
|				[in]	float32_t var: controlled variable = actual value
|
|
|  Returns:		float32_t out: controller output
|
*-------------------------------------------------------------------*/


/*********************************************************************
*
*                   Includes
*
*********************************************************************/
#include <stdint.h>
#include <math.h>
#include <arm_math.h>
#include <pi_controller.h>


float32_t error_sum = 0;


/*********************************************************************
*
*                   Functions
*
*********************************************************************/
float PI_control(float32_t ref, float32_t real)  {

	float32_t out, pi_error;

    pi_error = ref - real;
    error_sum += pi_error;

    /* Limiting Error */
    if (error_sum < _ERRORMIN)  {
      error_sum = _ERRORMIN;
    }
    else if (error_sum > _ERRORMAX)  {
      error_sum = _ERRORMAX;
    }

    out = _K_p*pi_error + _K_i*error_sum;

    /* Limiting output */
    if (out < _OUTMIN)  {
      out = _OUTMIN;
    }
    else if (out > _OUTMAX) {
      out = _OUTMAX;
    }

    return (out);

}

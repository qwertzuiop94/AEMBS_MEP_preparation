/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : C21.h
**     Project     : FRDM-K64F_Generator
**     Processor   : MK64FN1M0VLL12
**     Component   : SDK_BitIO
**     Version     : Component 01.027, Driver 01.00, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2021-09-18, 09:57, # CodeGen: 748
**     Abstract    :
**          GPIO component usable with NXP SDK
**     Settings    :
**          Component name                                 : C21
**          SDK                                            : McuLib
**          GPIO Name                                      : GPIOA
**          PORT Name                                      : PORTA
**          Pin Number                                     : 0
**          Pin Symbol                                     : LED_RED
**          Do Pin Muxing                                  : no
**          Init Direction                                 : Output
**          Pull Resistor                                  : no pull resistor
**          Init Value                                     : 0
**     Contents    :
**         GetDir    - bool C21_GetDir(void);
**         SetDir    - void C21_SetDir(bool Dir);
**         SetInput  - void C21_SetInput(void);
**         SetOutput - void C21_SetOutput(void);
**         GetVal    - bool C21_GetVal(void);
**         PutVal    - void C21_PutVal(bool Val);
**         ClrVal    - void C21_ClrVal(void);
**         SetVal    - void C21_SetVal(void);
**         NegVal    - void C21_NegVal(void);
**         Init      - void C21_Init(void);
**         Deinit    - void C21_Deinit(void);
**
** * Copyright (c) 2015-2022, Erich Styger
**  * Web:         https://mcuoneclipse.com
**  * SourceForge: https://sourceforge.net/projects/mcuoneclipse
**  * Git:         https://github.com/ErichStyger/McuOnEclipse_PEx
**  * All rights reserved.
**  *
**  * Redistribution and use in source and binary forms, with or without modification,
**  * are permitted provided that the following conditions are met:
**  *
**  * - Redistributions of source code must retain the above copyright notice, this list
**  *   of conditions and the following disclaimer.
**  *
**  * - Redistributions in binary form must reproduce the above copyright notice, this
**  *   list of conditions and the following disclaimer in the documentation and/or
**  *   other materials provided with the distribution.
**  *
**  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**  * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**  * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**  * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**  * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**  * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**  * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
** ###################################################################*/
/*!
** @file C21.h
** @version 01.00
** @brief
**          GPIO component usable with NXP SDK
*/         
/*!
**  @addtogroup C21_module C21 module documentation
**  @{
*/         

/* MODULE C21. */

#include "C21.h"
#if McuLib_CONFIG_NXP_SDK_2_0_USED
  #if C21_CONFIG_DO_PIN_MUXING
    #if McuLib_CONFIG_CPU_IS_LPC
      #include "fsl_iocon.h" /* include SDK header file for I/O connection muxing */
    #else /* Kinetis */
      #include "fsl_port.h" /* include SDK header file for port muxing */
    #endif
  #endif
  #include "fsl_gpio.h" /* include SDK header file for GPIO */
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_KINETIS_1_3
  #include "fsl_gpio_driver.h" /* include SDK header file for GPIO */
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_S32K
  #include "pins_gpio_hw_access.h"
  #include "pins_driver.h" /* include SDK header file for GPIO */
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_NORDIC_NRF5
  #include "nrf_gpio.h"
#else
  #error "Unsupported SDK!"
#endif

#if McuLib_CONFIG_NXP_SDK_2_0_USED
  static const gpio_pin_config_t C21_configOutput = {
    kGPIO_DigitalOutput,  /* use as output pin */
    C21_CONFIG_INIT_PIN_VALUE,  /* initial value */
  };

  static const gpio_pin_config_t C21_configInput = {
    kGPIO_DigitalInput,  /* use as input pin */
    C21_CONFIG_INIT_PIN_VALUE,  /* initial value */
  };
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_KINETIS_1_3
  const gpio_output_pin_user_config_t C21_OutputConfig[] = {
    {
      .pinName = C21_CONFIG_PIN_SYMBOL,
      .config.outputLogic = C21_CONFIG_INIT_PIN_VALUE,
    #if FSL_FEATURE_PORT_HAS_SLEW_RATE
      .config.slewRate = kPortSlowSlewRate,
    #endif
    #if FSL_FEATURE_PORT_HAS_OPEN_DRAIN
      .config.isOpenDrainEnabled = true,
    #endif
    #if FSL_FEATURE_PORT_HAS_DRIVE_STRENGTH
      .config.driveStrength = kPortLowDriveStrength,
    #endif
    },
    {
      .pinName = GPIO_PINS_OUT_OF_RANGE,
    }
  };

  const gpio_input_pin_user_config_t C21_InputConfig[] = {
    {
      .pinName = C21_CONFIG_PIN_SYMBOL,
    #if FSL_FEATURE_PORT_HAS_PULL_ENABLE
      #if C21_CONFIG_PULL_RESISTOR==0 /* 0: no pull resistor, 1: pull-up, 2: pull-down, 3: pull-up or no pull, 4: pull-down or no pull: 4: autoselect-pull */
      .config.isPullEnable = false,
      #else
      .config.isPullEnable = true,
      #endif
    #endif
    #if FSL_FEATURE_PORT_HAS_PULL_SELECTION
      #if C21_CONFIG_PULL_RESISTOR==1
      .config.pullSelect = kPortPullUp,
      #else
      .config.pullSelect = kPortPullDown,
      #endif
    #endif
    #if FSL_FEATURE_PORT_HAS_PASSIVE_FILTER
      .config.isPassiveFilterEnabled = true,
    #endif
    #if FSL_FEATURE_PORT_HAS_DIGITAL_FILTER
      .config.isDigitalFilterEnabled = true,
    #endif
    #if FSL_FEATURE_GPIO_HAS_INTERRUPT_VECTOR
      .config.interrupt = kPortIntDisabled
    #endif
    },
    {
      .pinName = GPIO_PINS_OUT_OF_RANGE,
    }
  };
#endif

static bool C21_isOutput = false;
/*
** ===================================================================
**     Method      :  ClrVal (component SDK_BitIO)
**
**     Description :
**         Clears the pin value (sets it to a low level)
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void C21_ClrVal(void)
{
#if McuLib_CONFIG_NXP_SDK_2_0_USED
  #if McuLib_CONFIG_CPU_IS_LPC
  GPIO_PortClear(C21_CONFIG_GPIO_NAME, C21_CONFIG_PORT_NAME, 1<<C21_CONFIG_PIN_NUMBER);
  #elif McuLib_CONFIG_SDK_VERSION < 250
  GPIO_ClearPinsOutput(C21_CONFIG_GPIO_NAME, 1<<C21_CONFIG_PIN_NUMBER);
  #else
  GPIO_PortClear(C21_CONFIG_GPIO_NAME, 1<<C21_CONFIG_PIN_NUMBER);
  #endif
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_KINETIS_1_3
  GPIO_DRV_ClearPinOutput(C21_CONFIG_PIN_SYMBOL);
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_S32K
  PINS_GPIO_WritePin(C21_CONFIG_PORT_NAME, C21_CONFIG_PIN_NUMBER, 0);
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_NORDIC_NRF5
  nrf_gpio_pin_clear(C21_CONFIG_PIN_NUMBER);
#endif
}

/*
** ===================================================================
**     Method      :  SetVal (component SDK_BitIO)
**
**     Description :
**         Sets the pin value to a high value.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void C21_SetVal(void)
{
#if McuLib_CONFIG_NXP_SDK_2_0_USED
  #if McuLib_CONFIG_CPU_IS_LPC
  GPIO_PortSet(C21_CONFIG_GPIO_NAME, C21_CONFIG_PORT_NAME, 1<<C21_CONFIG_PIN_NUMBER);
  #elif McuLib_CONFIG_SDK_VERSION < 250
  GPIO_SetPinsOutput(C21_CONFIG_GPIO_NAME, 1<<C21_CONFIG_PIN_NUMBER);
  #else
  GPIO_PortSet(C21_CONFIG_GPIO_NAME, 1<<C21_CONFIG_PIN_NUMBER);
  #endif
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_KINETIS_1_3
  GPIO_DRV_SetPinOutput(C21_CONFIG_PIN_SYMBOL);
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_S32K
  PINS_GPIO_WritePin(C21_CONFIG_PORT_NAME, C21_CONFIG_PIN_NUMBER, 1);
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_NORDIC_NRF5
  nrf_gpio_pin_set(C21_CONFIG_PIN_NUMBER);
#endif
}

/*
** ===================================================================
**     Method      :  NegVal (component SDK_BitIO)
**
**     Description :
**         Toggles/negates the pin value
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void C21_NegVal(void)
{
#if McuLib_CONFIG_NXP_SDK_2_0_USED
  #if McuLib_CONFIG_CPU_IS_LPC
  GPIO_PortToggle(C21_CONFIG_GPIO_NAME, C21_CONFIG_PORT_NAME, 1<<C21_CONFIG_PIN_NUMBER);
  #elif McuLib_CONFIG_SDK_VERSION < 250
  GPIO_TogglePinsOutput(C21_CONFIG_GPIO_NAME, 1<<C21_CONFIG_PIN_NUMBER);
  #else
  GPIO_PortToggle(C21_CONFIG_GPIO_NAME, 1<<C21_CONFIG_PIN_NUMBER);
  #endif
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_KINETIS_1_3
  GPIO_DRV_TogglePinOutput(C21_CONFIG_PIN_SYMBOL);
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_S32K
  pins_channel_type_t val;

  val = PINS_GPIO_GetPinsOutput(C21_CONFIG_PORT_NAME);
  if (val&(1<<C21_CONFIG_PIN_NUMBER)) {
    PINS_GPIO_WritePin(C21_CONFIG_PORT_NAME, C21_CONFIG_PIN_NUMBER, 0);
  } else {
    PINS_GPIO_WritePin(C21_CONFIG_PORT_NAME, C21_CONFIG_PIN_NUMBER, 1);
  }
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_NORDIC_NRF5
  nrf_gpio_pin_toggle(C21_CONFIG_PIN_NUMBER);
#endif
}

/*
** ===================================================================
**     Method      :  GetVal (component SDK_BitIO)
**
**     Description :
**         Returns the pin value
**     Parameters  : None
**     Returns     :
**         ---             - Returns the value of the pin:
**                           FALSE/logical level '0' or TRUE/logical
**                           level '1'
** ===================================================================
*/
bool C21_GetVal(void)
{
#if McuLib_CONFIG_CPU_IS_LPC
  return GPIO_PinRead(C21_CONFIG_GPIO_NAME, C21_CONFIG_PORT_NAME, C21_CONFIG_PIN_NUMBER);
#elif McuLib_CONFIG_NXP_SDK_2_0_USED
  #if McuLib_CONFIG_SDK_VERSION < 250
  return GPIO_ReadPinInput(C21_CONFIG_GPIO_NAME, C21_CONFIG_PIN_NUMBER)!=0;
  #else
  return GPIO_PinRead(C21_CONFIG_GPIO_NAME, C21_CONFIG_PIN_NUMBER)!=0;
  #endif
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_KINETIS_1_3
  return GPIO_DRV_ReadPinInput(C21_CONFIG_PIN_SYMBOL)!=0;
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_S32K
  return (PINS_DRV_ReadPins(C21_CONFIG_PORT_NAME)&(1<<C21_CONFIG_PIN_NUMBER))!=0;
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_NORDIC_NRF5
  return nrf_gpio_pin_read(C21_CONFIG_PIN_NUMBER)!=0;
#else
  return FALSE;
#endif
}

/*
** ===================================================================
**     Method      :  GetDir (component SDK_BitIO)
**
**     Description :
**         Return the direction of the pin (input/output)
**     Parameters  : None
**     Returns     :
**         ---             - FALSE if port is input, TRUE if port is
**                           output
** ===================================================================
*/
bool C21_GetDir(void)
{
  return C21_isOutput;
}

/*
** ===================================================================
**     Method      :  SetDir (component SDK_BitIO)
**
**     Description :
**         Sets the direction of the pin (input or output)
**     Parameters  :
**         NAME            - DESCRIPTION
**         Dir             - FALSE: input, TRUE: output
**     Returns     : Nothing
** ===================================================================
*/
void C21_SetDir(bool Dir)
{
  if (Dir) {
    C21_SetOutput();
  } else {
    C21_SetInput();
  }
}

/*
** ===================================================================
**     Method      :  SetInput (component SDK_BitIO)
**
**     Description :
**         Sets the pin as input
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void C21_SetInput(void)
{
#if McuLib_CONFIG_CPU_IS_LPC
  GPIO_PinInit(C21_CONFIG_GPIO_NAME, C21_CONFIG_PORT_NAME, C21_CONFIG_PIN_NUMBER, &C21_configInput);
#elif McuLib_CONFIG_NXP_SDK_2_0_USED
  GPIO_PinInit(C21_CONFIG_GPIO_NAME, C21_CONFIG_PIN_NUMBER, &C21_configInput);
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_KINETIS_1_3
  GPIO_DRV_SetPinDir(C21_CONFIG_PIN_SYMBOL, kGpioDigitalInput);
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_S32K
  pins_channel_type_t val;

  val = PINS_GPIO_GetPinsDirection(C21_CONFIG_PORT_NAME); /* bit 0: pin is input; 1: pin is output */
  val &= ~(1<<C21_CONFIG_PIN_NUMBER); /* clear bit ==> input */
  PINS_DRV_SetPinsDirection(C21_CONFIG_PORT_NAME, val);
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_NORDIC_NRF5
  nrf_gpio_cfg_input(C21_CONFIG_PIN_NUMBER, NRF_GPIO_PIN_NOPULL);
#endif
  C21_isOutput = false;
}

/*
** ===================================================================
**     Method      :  SetOutput (component SDK_BitIO)
**
**     Description :
**         Sets the pin as output
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void C21_SetOutput(void)
{
#if McuLib_CONFIG_CPU_IS_LPC
  GPIO_PinInit(C21_CONFIG_GPIO_NAME, C21_CONFIG_PORT_NAME, C21_CONFIG_PIN_NUMBER, &C21_configOutput);
#elif McuLib_CONFIG_NXP_SDK_2_0_USED
  GPIO_PinInit(C21_CONFIG_GPIO_NAME, C21_CONFIG_PIN_NUMBER, &C21_configOutput);
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_KINETIS_1_3
  GPIO_DRV_SetPinDir(C21_CONFIG_PIN_SYMBOL, kGpioDigitalOutput);
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_S32K
  pins_channel_type_t val;

  val = PINS_GPIO_GetPinsDirection(C21_CONFIG_PORT_NAME); /* bit 0: pin is input; 1: pin is output */
  val |= (1<<C21_CONFIG_PIN_NUMBER); /* set bit ==> output */
  PINS_DRV_SetPinsDirection(C21_CONFIG_PORT_NAME, val);
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_NORDIC_NRF5
  nrf_gpio_cfg_output(C21_CONFIG_PIN_NUMBER);
#endif
  C21_isOutput = true;
}

/*
** ===================================================================
**     Method      :  PutVal (component SDK_BitIO)
**
**     Description :
**         Sets the pin value
**     Parameters  :
**         NAME            - DESCRIPTION
**         Val             - Value to set. FALSE/logical '0' or
**                           TRUE/logical '1'
**     Returns     : Nothing
** ===================================================================
*/
void C21_PutVal(bool Val)
{
#if McuLib_CONFIG_CPU_IS_LPC
  if (Val) {
    GPIO_PortSet(C21_CONFIG_GPIO_NAME, C21_CONFIG_PORT_NAME, 1<<C21_CONFIG_PIN_NUMBER);
  } else {
    GPIO_PortClear(C21_CONFIG_GPIO_NAME, C21_CONFIG_PORT_NAME, 1<<C21_CONFIG_PIN_NUMBER);
  }
#elif McuLib_CONFIG_NXP_SDK_2_0_USED
  #if McuLib_CONFIG_SDK_VERSION < 250
  if (Val) {
    GPIO_SetPinsOutput(C21_CONFIG_GPIO_NAME, 1<<C21_CONFIG_PIN_NUMBER);
  } else {
    GPIO_ClearPinsOutput(C21_CONFIG_GPIO_NAME, 1<<C21_CONFIG_PIN_NUMBER);
  }
  #else
  if (Val) {
    GPIO_PortSet(C21_CONFIG_GPIO_NAME, 1<<C21_CONFIG_PIN_NUMBER);
  } else {
    GPIO_PortClear(C21_CONFIG_GPIO_NAME, 1<<C21_CONFIG_PIN_NUMBER);
  }
  #endif
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_KINETIS_1_3
  GPIO_DRV_WritePinOutput(C21_CONFIG_PIN_SYMBOL, Val);
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_S32K
  PINS_DRV_WritePin(C21_CONFIG_PORT_NAME, C21_CONFIG_PIN_NUMBER, Val);
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_NORDIC_NRF5
  /* NYI */
#endif
}

/*
** ===================================================================
**     Method      :  Init (component SDK_BitIO)
**
**     Description :
**         Driver initialization method
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void C21_Init(void)
{
#if McuLib_CONFIG_NXP_SDK_2_0_USED
  #if C21_CONFIG_DO_PIN_MUXING
      #if McuLib_CONFIG_CPU_IS_LPC
        #define IOCON_PIO_DIGITAL_EN 0x0100u  /*!<@brief Enables digital function */
        #define IOCON_PIO_FUNC0 0x00u         /*!<@brief Selects pin function 0 */
        #define IOCON_PIO_INV_DI 0x00u        /*!<@brief Input function is not inverted */
        #define IOCON_PIO_MODE_PULLUP 0x20u   /*!<@brief Selects pull-up function */
        #define IOCON_PIO_OPENDRAIN_DI 0x00u  /*!<@brief Open drain is disabled */
        #define IOCON_PIO_SLEW_STANDARD 0x00u /*!<@brief Standard mode, output slew rate control is enabled */

        const uint32_t port_pin_config = (/* Pin is configured as PI<portname>_<pinnumber> */
                                      IOCON_PIO_FUNC0 |
                                      /* Selects pull-up function */
                                      IOCON_PIO_MODE_PULLUP |
                                      /* Standard mode, output slew rate control is enabled */
                                      IOCON_PIO_SLEW_STANDARD |
                                      /* Input function is not inverted */
                                      IOCON_PIO_INV_DI |
                                      /* Enables digital function */
                                      IOCON_PIO_DIGITAL_EN |
                                      /* Open drain is disabled */
                                      IOCON_PIO_OPENDRAIN_DI);
        #if (McuLib_CONFIG_CPU_IS_LPC && McuLib_CONFIG_CORTEX_M==0)
          IOCON_PinMuxSet(C21_CONFIG_PORT_NAME, C21_CONFIG_PIN_NUMBER, port_pin_config);
        #else
          IOCON_PinMuxSet(IOCON, C21_CONFIG_PORT_NAME, C21_CONFIG_PIN_NUMBER, port_pin_config);
        #endif
      #else
        PORT_SetPinMux(C21_CONFIG_PORT_NAME, C21_CONFIG_PIN_NUMBER, kPORT_MuxAsGpio); /* mux as GPIO */
      #endif
  #endif
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_KINETIS_1_3
  /*! Pin Muxing not implemented */
  GPIO_DRV_Init(C21_InputConfig, C21_OutputConfig);
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_S32K
  /* the following needs to be called in the application first:
  PINS_DRV_Init(NUM_OF_CONFIGURED_PINS, g_pin_mux_InitConfigArr);
  */
#elif McuLib_CONFIG_SDK_VERSION_USED == McuLib_CONFIG_SDK_NORDIC_NRF5
  /* nothing needed */
#endif
#if C21_CONFIG_INIT_PIN_DIRECTION == C21_CONFIG_INIT_PIN_DIRECTION_INPUT
  C21_SetInput();
#elif C21_CONFIG_INIT_PIN_DIRECTION == C21_CONFIG_INIT_PIN_DIRECTION_OUTPUT
  C21_SetOutput();
#endif
}

/*
** ===================================================================
**     Method      :  Deinit (component SDK_BitIO)
**
**     Description :
**         Driver de-initialization method
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void C21_Deinit(void)
{
  /* nothing needed */
}

/* END C21. */

/*!
** @}
*/

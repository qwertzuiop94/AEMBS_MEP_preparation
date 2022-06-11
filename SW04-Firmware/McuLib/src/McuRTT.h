/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : McuRTT.h
**     Project     : FRDM-K64F_Generator
**     Processor   : MK64FN1M0VLL12
**     Component   : SeggerRTT
**     Version     : Component 01.092, Driver 01.00, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2021-12-17, 13:26, # CodeGen: 759
**     Abstract    :
**
**     Settings    :
**          Component name                                 : McuRTT
**          Version                                        : V6.86e
**          Number of Up Channels                          : 3
**          Number of Down Channels                        : 3
**          Max Blocked Interrupt Level                    : 3
**          Syscalls                                       : no
**          Channel 0                                      : Enabled
**            Name                                         : "Terminal"
**            Up Buffer Size (Tx)                          : 512
**            Down Buffer Size (Rx)                        : 64
**            Up Buffer Mode                               : Skip (Default)
**            Down Buffer Mode                             : Skip (Default)
**            Blocking Send                                : Disabled
**            Printf Buffer Size                           : 64
**          SDK                                            : McuLib
**          Shell                                          : McuShell
**          Source Folders                                 : 
**            Source Folder                                : SEGGER_RTT
**            Config Folder                                : SEGGER_RTT
**     Contents    :
**         Read             - int McuRTT_Read(unsigned BufferIndex, const char* pBuffer, unsigned NumBytes);
**         Write            - int McuRTT_Write(unsigned BufferIndex, char* pBuffer, unsigned BufferSize);
**         WriteString      - unsigned McuRTT_WriteString(unsigned BufferIndex, const char* s);
**         printf           - int McuRTT_printf(unsigned BufferIndex, const char* sFormat, ...);
**         GetKey           - dword McuRTT_GetKey(void);
**         WaitKey          - long McuRTT_WaitKey(void);
**         HasKey           - long McuRTT_HasKey(void);
**         SetTerminal      - int McuRTT_SetTerminal(char TerminalId);
**         TerminalOut      - int McuRTT_TerminalOut(char TerminalId, const char* s);
**         ConfigUpBuffer   - int McuRTT_ConfigUpBuffer(unsigned BufferIndex, const char* sName, char*...
**         ConfigDownBuffer - int McuRTT_ConfigDownBuffer(unsigned BufferIndex, const char* sName, char*...
**         RecvChar         - uint8_t McuRTT_RecvChar(uint8_t *c);
**         SendChar         - uint8_t McuRTT_SendChar(uint8_t ch);
**         GetCharsInRxBuf  - uint16_t McuRTT_GetCharsInRxBuf(void);
**         StdIOKeyPressed  - bool McuRTT_StdIOKeyPressed(void);
**         StdIOReadChar    - void McuRTT_StdIOReadChar(uint8_t *c);
**         StdIOSendChar    - void McuRTT_StdIOSendChar(uint8_t ch);
**         GetStdio         - %@Shell@'ModuleName'%.ConstStdIOTypePtr McuRTT_GetStdio(void);
**         Deinit           - void McuRTT_Deinit(void);
**         Init             - void McuRTT_Init(void);
**
** * (c) Copyright Segger, 2020-2021
**  * http      : www.segger.com
**  * See separate Segger licensing terms.
**  *
**  * Processor Expert port: Copyright (c) 2016-2021 Erich Styger
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
** @file McuRTT.h
** @version 01.00
** @brief
**
*/         
/*!
**  @addtogroup McuRTT_module McuRTT module documentation
**  @{
*/         

#ifndef __McuRTT_H
#define __McuRTT_H

/* MODULE McuRTT. */
#include "McuLib.h" /* SDK and API used */
#include "McuRTTconfig.h" /* configuration */

/* Include inherited components */
#include "McuLib.h"
#include "McuShell.h"


#include "SEGGER_RTT.h"


#define McuRTT_RTT_CHANNEL_0_ENABLED   1  /* 0: channel disabled, 1: channel enabled */

extern uint8_t McuRTT_DefaultShellBuffer[McuShell_DEFAULT_SHELL_BUFFER_SIZE]; /* default buffer which can be used by the application */
extern McuShell_ConstStdIOType McuRTT_stdio; /* default standard I/O */

#ifdef __cplusplus
extern "C" {
#endif

#define McuRTT_Read(BufferIndex, pBuffer, NumBytes) \
  SEGGER_RTT_Read(BufferIndex, pBuffer, NumBytes)

/*
** ===================================================================
**     Method      :  Read (component SeggerRTT)
**
**     Description :
**         Read from buffer
**     Parameters  :
**         NAME            - DESCRIPTION
**         BufferIndex     - Buffer/channel to be used.
**                           0 for terminal.
**       * pBuffer         - Pointer to buffer
**         BufferSize      - Number of bytes to write
**     Returns     :
**         ---             - Number of bytes that have been read
** ===================================================================
*/

#define McuRTT_Write(BufferIndex, pBuffer, BufferSize) \
  SEGGER_RTT_Write(BufferIndex, pBuffer, BufferSize)

/*
** ===================================================================
**     Method      :  Write (component SeggerRTT)
**
**     Description :
**         Write to buffer
**     Parameters  :
**         NAME            - DESCRIPTION
**         BufferIndex     - Buffer/channel to be used.
**                           0 for terminal.
**       * pBuffer         - Pointer to buffer
**         BufferSize      - Size of buffer
**     Returns     :
**         ---             - Number of bytes which have been written to
**                           the up buffer
** ===================================================================
*/

#define McuRTT_WriteString(BufferIndex, s) \
  SEGGER_RTT_WriteString(BufferIndex, s)

/*
** ===================================================================
**     Method      :  WriteString (component SeggerRTT)
**
**     Description :
**         Write to buffer
**     Parameters  :
**         NAME            - DESCRIPTION
**         BufferIndex     - Buffer/channel to be used.
**                           0 for terminal.
**       * s               - Pointer to 
**     Returns     :
**         ---             - Number of bytes which have been stored in
**                           the "Up"-buffer.
** ===================================================================
*/

#define McuRTT_GetKey() \
  SEGGER_RTT_GetKey()

/*
** ===================================================================
**     Method      :  GetKey (component SeggerRTT)
**
**     Description :
**         Returns a character/key
**     Parameters  : None
**     Returns     :
**         ---             - character code
** ===================================================================
*/

#define McuRTT_WaitKey() \
  SEGGER_RTT_WaitKey()

/*
** ===================================================================
**     Method      :  WaitKey (component SeggerRTT)
**
**     Description :
**         Waits for a key and returns it.
**     Parameters  : None
**     Returns     :
**         ---             - >=0    Character which has been read.
** ===================================================================
*/

#define McuRTT_HasKey() \
  SEGGER_RTT_HasKey()

/*
** ===================================================================
**     Method      :  HasKey (component SeggerRTT)
**
**     Description :
**         Checks if at least one character for reading is available in
**         the SEGGER RTT buffer
**     Parameters  : None
**     Returns     :
**         ---             - 0: No characters are available to read; 1:
**                           At least one character is available.
** ===================================================================
*/

bool McuRTT_StdIOKeyPressed(void);
/*
** ===================================================================
**     Method      :  StdIOKeyPressed (component SeggerRTT)
**
**     Description :
**         StdIO handler for Shell
**     Parameters  : None
**     Returns     :
**         ---             - True if there are characters in teh input
**                           buffer
** ===================================================================
*/

void McuRTT_StdIOReadChar(uint8_t *c);
/*
** ===================================================================
**     Method      :  StdIOReadChar (component SeggerRTT)
**
**     Description :
**         StdIO Handler for reading a character. It returns a zero
**         byte if there is no character in input buffer.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * c               - Pointer to where to store the received
**                           character
**     Returns     : Nothing
** ===================================================================
*/

void McuRTT_StdIOSendChar(uint8_t ch);
/*
** ===================================================================
**     Method      :  StdIOSendChar (component SeggerRTT)
**
**     Description :
**         StdIO handler to sends a character.
**     Parameters  :
**         NAME            - DESCRIPTION
**         ch              - Character to send
**     Returns     : Nothing
** ===================================================================
*/

uint8_t McuRTT_RecvChar(uint8_t *c);
/*
** ===================================================================
**     Method      :  RecvChar (component SeggerRTT)
**
**     Description :
**         Receives a character from channel 0. Returns ERR_RXEMPTY if
**         no character available
**     Parameters  :
**         NAME            - DESCRIPTION
**       * c               - Pointer to where to store the received
**                           character
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

uint8_t McuRTT_SendChar(uint8_t ch);
/*
** ===================================================================
**     Method      :  SendChar (component SeggerRTT)
**
**     Description :
**         Sends a character to channel 0.
**     Parameters  :
**         NAME            - DESCRIPTION
**         ch              - Character to send
**     Returns     :
**         ---             - Error code. ERR_OK if character has been
**                           sent, ERR_TXFULL otherwise.
** ===================================================================
*/

#define McuRTT_GetCharsInRxBuf() \
  SEGGER_RTT_HasKey()

/*
** ===================================================================
**     Method      :  GetCharsInRxBuf (component SeggerRTT)
**
**     Description :
**         Returns the number of characters in the receive buffer.
**     Parameters  : None
**     Returns     :
**         ---             - Number of characters in the input buffer,
**                           zero for none available.
** ===================================================================
*/

void McuRTT_Init(void);

/*
** ===================================================================
**     Method      :  Init (component SeggerRTT)
**
**     Description :
**         Initializes the RTT Control Block.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

#define McuRTT_TerminalOut(TerminalId, s) \
  SEGGER_RTT_TerminalOut(TerminalId, s)

/*
** ===================================================================
**     Method      :  TerminalOut (component SeggerRTT)
**
**     Description :
**         Writes a string to the given terminal without changing the
**         terminal for channel 0.
**     Parameters  :
**         NAME            - DESCRIPTION
**         TerminalId      - TerminalId, 0..15
**       * s               - Pointer to string
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

#define McuRTT_SetTerminal(TerminalId) \
  SEGGER_RTT_SetTerminal(TerminalId)

/*
** ===================================================================
**     Method      :  SetTerminal (component SeggerRTT)
**
**     Description :
**          Sets the terminal to be used for output on channel 0.
**     Parameters  :
**         NAME            - DESCRIPTION
**         TerminalId      - Terminal ID, 0..15
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

#define McuRTT_ConfigUpBuffer(BufferIndex, sName, pBuffer, BufferSize, Flags) \
  SEGGER_RTT_ConfigUpBuffer(BufferIndex, sName, pBuffer, BufferSize, Flags)

/*
** ===================================================================
**     Method      :  ConfigUpBuffer (component SeggerRTT)
**
**     Description :
**         Configures the Up (device to host) buffer
**     Parameters  :
**         NAME            - DESCRIPTION
**         BufferIndex     - Buffer index
**         sName           - Buffer name
**       * pBuffer         - Pointer to buffer
**         intBufferSize   - Size of buffer in bytes
**         Flags           - SEGGER_RTT_MODE_NO_BLOCK_SKIP,
**                           SEGGER_RTT_MODE_NO_BLOCK_TRIM or
**                           SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL
**     Returns     :
**         ---             - Error code, >=0 OK, <0 Error
** ===================================================================
*/

#define McuRTT_ConfigDownBuffer(BufferIndex, sName, pBuffer, BufferSize, Flags) \
  SEGGER_RTT_ConfigDownBuffer(BufferIndex, sName, pBuffer, BufferSize, Flags)

/*
** ===================================================================
**     Method      :  ConfigDownBuffer (component SeggerRTT)
**
**     Description :
**         Configures the Down (host to device) buffer
**     Parameters  :
**         NAME            - DESCRIPTION
**         BufferIndex     - Buffer index
**         sName           - Buffer name
**       * pBuffer         - Pointer to buffer
**         intBufferSize   - Size of buffer in bytes
**         Flags           - SEGGER_RTT_MODE_NO_BLOCK_SKIP,
**                           SEGGER_RTT_MODE_NO_BLOCK_TRIM or
**                           SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL
**     Returns     :
**         ---             - Error code, >=0 OK, <0 Error
** ===================================================================
*/

#define McuRTT_printf \
  SEGGER_RTT_printf

/*
** ===================================================================
**     Method      :  printf (component SeggerRTT)
**
**     Description :
**         Stores a formatted string in SEGGER RTT control block. This
**         data is sent to the host.
**     Parameters  :
**         NAME            - DESCRIPTION
**         BufferIndex     - Index of "Up"-buffer to be
**                           used. (e.g. 0 for "Terminal")
**         sFormat         - Pointer to format string, followed
**                           by the arguments for conversion
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

void McuRTT_Deinit(void);
/*
** ===================================================================
**     Method      :  Deinit (component SeggerRTT)
**
**     Description :
**         Driver deinitialization
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

McuShell_ConstStdIOTypePtr McuRTT_GetStdio(void);
/*
** ===================================================================
**     Method      :  GetStdio (component SeggerRTT)
**
**     Description :
**         Returns a pointer to the standard I/O
**     Parameters  : None
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

/* END McuRTT. */

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif
/* ifndef __McuRTT_H */
/*!
** @}
*/

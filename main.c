/**********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO
 * THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2020, 2021 Renesas Electronics Corporation. All rights reserved.
 *********************************************************************************************************************/
/***********************************************************************/
/*                                                                     */
/*  FILE        :Main.c                                                */
/*  DATE        :Mon, JUN 09, 2025                                     */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :						       */
/* 
 *
 *  Created on: Jun 10, 2025
 *      Author: Aditya Garg                                   */                                                                   
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/*                                                                     */
/***********************************************************************/
#include "HS_SPI_Master_CSIH0.h"
#include "TJA1145_CAN_Config.h"
#include "SPI_CSIH_USER_CONFIG.h"
#include "iodefine.h"
#include "TJA1145_Safety.h"
#include "Clk.h"
#include "System_Init.h"
#include "SchM.h"
#include "App_Tasks.h"

//extern void TJA1145_SendCANFrame(unsigned char *data); - Required when used in TJA1145 stand alone mode

int main(void) {
    // Init BSP + Drivers
    Clk_Init();
    Timer_Init();
    CSIHSPI_Master_Init();
    TJA1145_Init();

    // Init Services
    SchM_Init();

    // Register App tasks with the scheduler
    SchM_RegisterTask(App_Task_1ms, 1);
    SchM_RegisterTask(App_Task_10ms, 10);
    SchM_RegisterTask(App_Task_100ms, 100);

    while (1) {
        SchM_MainFunction();
    }
}
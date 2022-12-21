/**********************************************************************************************************
 * @file tdf8546.h
 * @brief TDF8546 I2C Amp Header File
 * @date 30-Dec-2020
 * @version 01.00.00
 * @author Halit Çetin (halitcetin@live.com)
 * @copyright Copyright (c) 2020, All rights reserved.
 * 
 * This file contains:
 * - Definitions
 * - Types
 * - Function Prototypes
 * 
 * which are relevant for TDF8546 I2C Amp.
 **********************************************************************************************************/

/**********************************************************************************************************
 * Version History   
 * @version 01.00.00        @date 30-Dec-2020       @note File creation
 **********************************************************************************************************/

    #ifndef __TDF8546_H__
    #define __TDF8546_H__

/**********************************************************************************************************
 * Include Libraries                                              
 **********************************************************************************************************/
    #include <stdint.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include "stm32f4xx_hal.h"
    
/**********************************************************************************************************
 * Include Statics                                            
 **********************************************************************************************************/
    #define TDF8546_ADRESS  0xD8

/**********************************************************************************************************
 * Define Variables                                               
 **********************************************************************************************************/
    static uint8_t device_address = TDF8546_ADRESS;
    static I2C_HandleTypeDef hi2c1;

    /**
     * @note TDF8546 expects five instruction bytes; IB1, IB2, IB3, IB4, IB5 and these bytes 
     * defined below as bitfield.
     */
    
    static union
    {
        uint8_t IB1Data;
        struct
        {
            uint8_t chipDetection : 1;          /** D7 - Enable or disable clip detection below VP = 10 V,      0 = disable, 1 = enable         */
            uint8_t channel3Info : 1;           /** D6 - Channel 3 clip information on pin DIAG or pin STB,     0 = DIAG, 1 = cSTB              */
            uint8_t channel1Info : 1;           /** D5 - Channel 1 clip information on pin DIAG or pin STB,     0 = DIAG, 1 = cSTB              */
            uint8_t channel4Info : 1;           /** D4 - Channel 4 clip information on pin DIAG or pin STB,     0 = DIAG, 1 = cSTB              */
            uint8_t channel2Info : 1;           /** D3 - Channel 2 clip information on pin DIAG or pin STB,     0 = DIAG, 1 = cSTB              */
            uint8_t acLoadDetection : 1;        /** D2 - Enable or disable AC load detection,                   0 = disabled, 1 = enabled       */
            uint8_t startUpDiag : 1;            /** D1 - Enable or disable start-up diagnostics,                0 = disabled, 1 = enabled       */
            uint8_t ampStart : 1;               /** D0 - Enable or disable amplifier start,                     0 = disabled, 1 = enabled       */
        } B;
    } IB1;

    static union
    {
        uint8_t IB2Data;
        struct
        {
            uint8_t chipDetection1 : 1;     /** D7 - Clip detection level (LSB)                                                                             */
            uint8_t chipDetection0 : 1;     /** D6 - Clip detection level (MSB), 00 = level 2 %, 01 = level 5 %, 10 = level 10 %, 11 = level disabled.      */
            uint8_t tempDiag : 1;           /** D5 - Temperature information on pin DIAG,           0 = enable, 1 = disable                                 */
            uint8_t shortDiag : 1;          /** D4 - Load fault information (shorts) on pin DIAG    0 = enable, 1 = disable                                 */
            uint8_t emptyBit : 1;           /** D3 - Empty                                                                                                  */
            uint8_t softMuteCh1Ch3 : 1;     /** D2 - Soft mute channel 1 and channel 3,             0 = unmute, 1 = soft mute                               */
            uint8_t softMuteCh2Ch4 : 1;     /** D1 - Soft mute channel 2 and channel 4,             0 = unmute, 1 = soft mute                               */
            uint8_t fastMuteAll : 1;        /** D0 - Fast mute all amplifier channels,              0 = unmute, 1 = fast mute                               */
        } B;
    } IB2;

    static union
    {
        uint8_t IB3Data;
        struct
        {
            uint8_t emptyBit : 1;           /** D7 - Empty                                                                                                  */
            uint8_t gainCh1Ch3 : 1;         /** D6 - Amplifier channel 1 and channel 3 gain select, 0 = 26 dB, 1 = 16 dB                                    */
            uint8_t gainCh2Ch4 : 1;         /** D5 - Amplifier channel 2 and channel 4 gain select, 0 = 26 dB, 1 = 16 dB                                    */
            uint8_t tempPreWarning : 1;     /** D4 - Temperature pre-warning level,                 0 = 160 C, 1 = 135 C                                    */
            uint8_t disableCh3 : 1;         /** D3 - Enable or disable channel 3,                   0 = enabled, 1 = disabled                               */
            uint8_t disableCh1 : 1;         /** D2 - Enable or disable channel 1,                   0 = enabled, 1 = disabled                               */
            uint8_t disableCh4 : 1;         /** D1 - Enable or disable channel 4,                   0 = enabled, 1 = disabled                               */
            uint8_t disableCh2 : 1;         /** D0 - Enable or disable channel 2,                   0 = enabled, 1 = disabled                               */
        } B;
    } IB3;

    static union
    {
        uint8_t IB4Data;
        struct
        {
            uint8_t useSvrCap : 1;              /** D7 - Use of SVR capacitor,                                  0 = filter common-mode voltage 1 = SVR capacitor used       */
            uint8_t shutDownMuteSel : 1;        /** D6 - Soft or fast mute select during shut-down via pin STB, 0 = fast mute, 1 = slow mute during shut-down               */
            uint8_t overVoltageWarn : 1;        /** D5 - 16 V overvoltage warning on pin DIAG,                  0 = disable, 1 = enable                                     */
            uint8_t loadInfo : 1;               /** D4 - AC or DC load information on bits DBx[D5:D4]           0 = DC load, 1 = AC load                                    */
            uint8_t emptyBit : 1;               /** D3 - Empty                                                                                                              */
            uint8_t driverOrGain : 1;           /** D2 - Line driver mode or low gain mode selection,           0 = Line driver mode, 1 = low gain mode                     */
            uint8_t acLoadDetect : 1;           /** D1 - AC load detection measurement current selection,       0 = Low measurement current, 1 = high measurement current   */
            uint8_t muteUnderVoltage : 1;       /** D0 - Low VP mute undervoltage level setting,                0 = 5.5 V, 1 = 7.2 V                                        */
        } B;
    } IB4;

    static union
    {
        uint8_t IB5Data;
        struct
        {
            uint8_t bestEfficent : 1;       /** D7 - Best efficiency mode,                                  0 = disable, 1 = enable                 */
            uint8_t bestEffChSel : 1;       /** D6 - Best efficiency mode channels,                         0 = 4 channels, 1 = 2 x 2 channels      */
            uint8_t emptyBit4 : 1;          /** D5 - Empty                                                                                          */
            uint8_t bestEffLoadImp : 1;     /** D4 - Best efficiency switch level load impedance setting    0 = 2 ohm load, 1 = 4 ohm load          */
            uint8_t emptyBit3 : 1;          /** D3 - Empty                                                                                          */
            uint8_t emptyBit2 : 1;          /** D2 - Empty                                                                                          */
            uint8_t emptyBit1 : 1;          /** D1 - Empty                                                                                          */
            uint8_t emptyBit0 : 1;          /** D0 - Empty                                                                                          */
        } B;
    } IB5;


/**********************************************************************************************************
 * Function Declerations                                            
 **********************************************************************************************************/
    #ifdef __cplusplus
        extern "C" {
    #endif
    /** 
     * @fn void tdf8546_init(void)
     * @brief Initialzes TDF8546 module.
     *
     * This function initialzes I2C controlled 4 channel TDF8546 module.
     */
    uint8_t tdf8546_init(void);

    /** 
     * @fn void tdf8546_mute(void)
     * @brief Mutes TDF8546 module.
     *
     * This function mutes I2C controlled 4 channel TDF8546 module.
     */
    uint8_t tdf8546_mute(void);
    
    /** 
     * @fn void tdf8546_unmute(void)
     * @brief Unmutes TDF8546 module.
     *
     * This function unmutes I2C controlled 4 channel TDF8546 module.
     */
    uint8_t tdf8546_unmute(void);

    /** 
     * @fn void tdf8546_init(void)
     * @brief Gets TDF8546 module status.
     *
     * This function gets I2C controlled 4 channel TDF8546 module status through pointer.
     *
     * @param[in] *p_amp_status: Amplifier status pointer.
     */
    uint8_t tdf8546_get_amp_status(uint8_t *p_amp_status);

    /** 
     * @fn static void prvSendDataTotdf8546(void)
     * @brief Sends data to TDF8546 module.
     *
     * This function Sends data to TDF8546 module.
     */
    static uint8_t prvSendDataTotdf8546(void);
    #ifdef __cplusplus
        }
    #endif
    #endif

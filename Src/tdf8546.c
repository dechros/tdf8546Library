/***********************************************************************************************************
 * @file tdf8546.c
 * @brief TDF8546 I2C Amp Library
 * @date 02-Dec-2020
 * @version 01.00.00
 * @author Halit Çetin (halitcetin@live.com)
 * @copyright Copyright (c) 2020, All rights reserved.
 *
 * @note This file contains:
 * - TDF8546 I2C Amp Functions
 * - TDF8546 I2C Amp Related Sub Functions
 * 
 * which are relevant for TDF8546 I2C Amp.
 **********************************************************************************************************/

/***********************************************************************************************************
 * Version History   
 * @version 01.00.00        @date  02-Dec-2020       @note File creation
 **********************************************************************************************************/

/***********************************************************************************************************
 * Include Libraries                                              
 **********************************************************************************************************/
  #include "tdf8546.h"
  #include "stm32f4xx_hal.h"
	
/***********************************************************************************************************
 * Sub Functions                                           
 **********************************************************************************************************/
    uint8_t tdf8546_init(void)
    {
        IB1.B.ampStart = 1;
        IB1.B.startUpDiag = 0;
        IB1.B.acLoadDetection = 0;
        IB1.B.channel2Info = 0;
        IB1.B.channel4Info = 0;
        IB1.B.channel1Info = 0;
        IB1.B.channel3Info = 0;
        IB1.B.chipDetection = 0;

        IB2.B.fastMuteAll = 0;
        IB2.B.softMuteCh2Ch4 = 0;
        IB2.B.softMuteCh1Ch3 = 0;
        IB2.B.emptyBit = 0;
        IB2.B.shortDiag = 1;
        IB2.B.tempDiag = 0;
        IB2.B.chipDetection0 = 0;
        IB2.B.chipDetection1 = 0;

        IB3.B.disableCh2 = 0;
        IB3.B.disableCh4 = 0;
        IB3.B.disableCh1 = 0;
        IB3.B.disableCh3 = 0;
        IB3.B.tempPreWarning = 1;
        IB3.B.gainCh2Ch4 = 0;
        IB3.B.gainCh1Ch3 = 0;
        IB3.B.emptyBit = 0;

        IB4.B.muteUnderVoltage = 0;
        IB4.B.acLoadDetect = 1;
        IB4.B.driverOrGain = 0;
        IB4.B.emptyBit = 0;
        IB4.B.loadInfo = 0;
        IB4.B.overVoltageWarn = 1;
        IB4.B.shutDownMuteSel = 1;
        IB4.B.useSvrCap = 1;

        IB5.B.emptyBit0 = 0;
        IB5.B.emptyBit1 = 0;
        IB5.B.emptyBit2 = 0;
        IB5.B.emptyBit3 = 0;
        IB5.B.bestEffLoadImp = 1;
        IB5.B.emptyBit4 = 0;
        IB5.B.bestEffChSel = 0;
        IB5.B.bestEfficent = 1;

        int returnVal = prvSendDataTotdf8546();
        return returnVal;
    }

    uint8_t tdf8546_mute(void)
    {
		IB1.B.ampStart = 1;
        IB1.B.startUpDiag = 0;
        IB1.B.acLoadDetection = 0;
        IB1.B.channel2Info = 0;
        IB1.B.channel4Info = 0;
        IB1.B.channel1Info = 0;
        IB1.B.channel3Info = 0;
        IB1.B.chipDetection = 0;

        IB2.B.fastMuteAll = 1;
        IB2.B.softMuteCh2Ch4 = 0;
        IB2.B.softMuteCh1Ch3 = 0;
        IB2.B.emptyBit = 0;
        IB2.B.shortDiag = 1;
        IB2.B.tempDiag = 0;
        IB2.B.chipDetection0 = 0;
        IB2.B.chipDetection1 = 0;

        IB3.B.disableCh2 = 0;
        IB3.B.disableCh4 = 0;
        IB3.B.disableCh1 = 0;
        IB3.B.disableCh3 = 0;
        IB3.B.tempPreWarning = 1;
        IB3.B.gainCh2Ch4 = 0;
        IB3.B.gainCh1Ch3 = 0;
        IB3.B.emptyBit = 0;

        IB4.B.muteUnderVoltage = 0;
        IB4.B.acLoadDetect = 1;
        IB4.B.driverOrGain = 0;
        IB4.B.emptyBit = 0;
        IB4.B.loadInfo = 0;
        IB4.B.overVoltageWarn = 1;
        IB4.B.shutDownMuteSel = 1;
        IB4.B.useSvrCap = 1;

        IB5.B.emptyBit0 = 0;
        IB5.B.emptyBit1 = 0;
        IB5.B.emptyBit2 = 0;
        IB5.B.emptyBit3 = 0;
        IB5.B.bestEffLoadImp = 1;
        IB5.B.emptyBit4 = 0;
        IB5.B.bestEffChSel = 0;
        IB5.B.bestEfficent = 1;

        if (HAL_I2C_IsDeviceReady(&hi2c1, (uint16_t)device_address, 3, 1000) != HAL_OK) 
        {
		    return 0;
		}
        else
        {
            int returnVal = prvSendDataTotdf8546();
            return returnVal;
        }
    }

    uint8_t tdf8546_unmute(void)
    {
        IB1.B.ampStart = 1;
        IB1.B.startUpDiag = 0;
        IB1.B.acLoadDetection = 0;
        IB1.B.channel2Info = 0;
        IB1.B.channel4Info = 0;
        IB1.B.channel1Info = 0;
        IB1.B.channel3Info = 0;
        IB1.B.chipDetection = 0;

        IB2.B.fastMuteAll = 0;
        IB2.B.softMuteCh2Ch4 = 0;
        IB2.B.softMuteCh1Ch3 = 0;
        IB2.B.emptyBit = 0;
        IB2.B.shortDiag = 1;
        IB2.B.tempDiag = 0;
        IB2.B.chipDetection0 = 0;
        IB2.B.chipDetection1 = 0;

        IB3.B.disableCh2 = 0;
        IB3.B.disableCh4 = 0;
        IB3.B.disableCh1 = 0;
        IB3.B.disableCh3 = 0;
        IB3.B.tempPreWarning = 1;
        IB3.B.gainCh2Ch4 = 0;
        IB3.B.gainCh1Ch3 = 0;
        IB3.B.emptyBit = 0;

        IB4.B.muteUnderVoltage = 0;
        IB4.B.acLoadDetect = 1;
        IB4.B.driverOrGain = 0;
        IB4.B.emptyBit = 0;
        IB4.B.loadInfo = 0;
        IB4.B.overVoltageWarn = 1;
        IB4.B.shutDownMuteSel = 1;
        IB4.B.useSvrCap = 1;

        IB5.B.emptyBit0 = 0;
        IB5.B.emptyBit1 = 0;
        IB5.B.emptyBit2 = 0;
        IB5.B.emptyBit3 = 0;
        IB5.B.bestEffLoadImp = 1;
        IB5.B.emptyBit4 = 0;
        IB5.B.bestEffChSel = 0;
        IB5.B.bestEfficent = 1;

        int returnVal = prvSendDataTotdf8546();
        return returnVal;
    }

    uint8_t tdf8546_get_amp_status(uint8_t *p_amp_status)
    {
	    return 0;
	}

    static uint8_t prvSendDataTotdf8546(void)
    {
        while(HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)device_address, &IB1.IB1Data, 1, 1000) != HAL_OK)
        {
            if (HAL_I2C_GetError(&hi2c1) != HAL_I2C_ERROR_AF)
            {
                return 0;
            }
        }
        while(HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)device_address, &IB2.IB2Data, 1, 1000) != HAL_OK)
        {
            if (HAL_I2C_GetError(&hi2c1) != HAL_I2C_ERROR_AF)
            {
                return 0;
            }
        }
        while(HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)device_address, &IB3.IB3Data, 1, 1000) != HAL_OK)
        {
            if (HAL_I2C_GetError(&hi2c1) != HAL_I2C_ERROR_AF)
            {
                return 0;
            }
        }
        while(HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)device_address, &IB4.IB4Data, 1, 1000) != HAL_OK)
        {
            if (HAL_I2C_GetError(&hi2c1) != HAL_I2C_ERROR_AF)
            {
                return 0;
            }
        }
        while(HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)device_address, &IB5.IB5Data, 1, 1000) != HAL_OK)
        {
            if (HAL_I2C_GetError(&hi2c1) != HAL_I2C_ERROR_AF)
            {
                return 0;
            }
        }
		return 1;
    }


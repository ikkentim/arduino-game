#ifndef ARDUINOGAME_TFTDEF_H
#define ARDUINOGAME_TFTDEF_H

# define LED_PIN        9 //PB1
# define RST_PIN        8
# define CS_PIN         7 //SPI_SW_SS_PIN
# define RS_PIN         5
# define ADSCS_PIN      6
# define MOSI_PIN       SPI_SW_MOSI_PIN
# define MISO_PIN       SPI_SW_MISO_PIN
# define SCK_PIN        SPI_SW_SCK_PIN

#ifndef LCD_WIDTH
# define LCD_WIDTH      320
# define LCD_HEIGHT     240
#endif

#ifndef CAL_POINT_X1
# define CAL_POINT_X1   20
# define CAL_POINT_Y1   20
# define CAL_POINT1     {CAL_POINT_X1,CAL_POINT_Y1}
# define CAL_POINT_X2   LCD_WIDTH-20 //300
# define CAL_POINT_Y2   LCD_HEIGHT/2 //120
# define CAL_POINT2     {CAL_POINT_X2,CAL_POINT_Y2}
# define CAL_POINT_X3   LCD_WIDTH/2   //160
# define CAL_POINT_Y3   LCD_HEIGHT-20 //220
# define CAL_POINT3     {CAL_POINT_X3,CAL_POINT_Y3}
#endif

//LCD commands
#define LCD_CMD_NOP                    0x00
#define LCD_CMD_RESET                  0x01
#define LCD_CMD_SLEEPIN                0x10
#define LCD_CMD_SLEEPOUT               0x11
#define LCD_CMD_PARTIAL_MODE           0x12
#define LCD_CMD_NORMAL_MODE            0x13
#define LCD_CMD_INV_OFF                0x20
#define LCD_CMD_INV_ON                 0x21
#define LCD_CMD_GAMMA                  0x26
#define LCD_CMD_DISPLAY_OFF            0x28
#define LCD_CMD_DISPLAY_ON             0x29
#define LCD_CMD_COLUMN                 0x2A
#define LCD_CMD_PAGE                   0x2B
#define LCD_CMD_WRITE                  0x2C
#define LCD_CMD_READ                   0x2E
#define LCD_CMD_PARTIAL_AREA           0x30
#define LCD_CMD_TEARING_OFF            0x34
#define LCD_CMD_TEARING_ON             0x35
#define LCD_CMD_MEMACCESS_CTRL         0x36
#define LCD_CMD_IDLE_OFF               0x38
#define LCD_CMD_IDLE_ON                0x39
#define LCD_CMD_PIXEL_FORMAT           0x3A
#define LCD_CMD_WRITE_CNT              0x3C
#define LCD_CMD_READ_CNT               0x3E
#define LCD_CMD_BRIGHTNESS             0x51
#define LCD_CMD_BRIGHTNESS_CTRL        0x53
#define LCD_CMD_RGB_CTRL               0xB0
#define LCD_CMD_FRAME_CTRL             0xB1 //normal mode
#define LCD_CMD_FRAME_CTRL_IDLE        0xB2 //idle mode
#define LCD_CMD_FRAME_CTRL_PART        0xB3 //partial mode
#define LCD_CMD_INV_CTRL               0xB4
#define LCD_CMD_DISPLAY_CTRL           0xB6
#define LCD_CMD_ENTRY_MODE             0xB7
#define LCD_CMD_POWER_CTRL1            0xC0
#define LCD_CMD_POWER_CTRL2            0xC1
#define LCD_CMD_VCOM_CTRL1             0xC5
#define LCD_CMD_VCOM_CTRL2             0xC7
#define LCD_CMD_POWER_CTRLA            0xCB
#define LCD_CMD_POWER_CTRLB            0xCF
#define LCD_CMD_POS_GAMMA              0xE0
#define LCD_CMD_NEG_GAMMA              0xE1
#define LCD_CMD_DRV_TIMING_CTRLA       0xE8
#define LCD_CMD_DRV_TIMING_CTRLB       0xEA
#define LCD_CMD_POWERON_SEQ_CTRL       0xED
#define LCD_CMD_ENABLE_3G              0xF2
#define LCD_CMD_INTERF_CTRL            0xF6
#define LCD_CMD_PUMP_RATIO_CTRL        0xF7

//ADS commands
#define ADS_CMD_START                  0x80
#define ADS_CMD_12BIT                  0x00
#define ADS_CMD_8BIT                   0x08
#define ADS_CMD_DIFF                   0x00
#define ADS_CMD_SINGLE                 0x04
#define ADS_CMD_X_POS                  0x10
#define ADS_CMD_Z1_POS                 0x30
#define ADS_CMD_Z2_POS                 0x40
#define ADS_CMD_Y_POS                  0x50
#define ADS_CMD_PWD                    0x00
#define ADS_CMD_ALWAYSON               0x03


#define lcd_width 320
#define lcd_height 240

#define MEM_Y   (7) //MY row address order
#define MEM_X   (6) //MX column address order
#define MEM_V   (5) //MV row / column exchange
#define MEM_L   (4) //ML vertical refresh order
#define MEM_H   (2) //MH horizontal refresh order
#define MEM_BGR (3) //RGB-BGR Order


const uint8_t initdataQT9[] PROGMEM =
    {
        //0x40| 1, LCD_CMD_RESET,
        //0xC0|60, //60ms
        //0xC0|60, //60ms
        0x40 | 1, LCD_CMD_DISPLAY_OFF,
        0xC0 | 20, //20ms
        0x40 | 1, LCD_CMD_POWER_CTRLB,
        0x80 | 3, 0x00, 0x83, 0x30, //0x83 0x81 0xAA
        0x40 | 1, LCD_CMD_POWERON_SEQ_CTRL,
        0x80 | 4, 0x64, 0x03, 0x12, 0x81, //0x64 0x67
        0x40 | 1, LCD_CMD_DRV_TIMING_CTRLA,
        0x80 | 3, 0x85, 0x01, 0x79, //0x79 0x78
        0x40 | 1, LCD_CMD_POWER_CTRLA,
        0x80 | 5, 0x39, 0x2C, 0x00, 0x34, 0x02,
        0x40 | 1, LCD_CMD_PUMP_RATIO_CTRL,
        0x80 | 1, 0x20,
        0x40 | 1, LCD_CMD_DRV_TIMING_CTRLB,
        0x80 | 2, 0x00, 0x00,
        0x40 | 1, LCD_CMD_POWER_CTRL1,
        0x80 | 1, 0x26, //0x26 0x25
        0x40 | 1, LCD_CMD_POWER_CTRL2,
        0x80 | 1, 0x11,
        0x40 | 1, LCD_CMD_VCOM_CTRL1,
        0x80 | 2, 0x35, 0x3E,
        0x40 | 1, LCD_CMD_VCOM_CTRL2,
        0x80 | 1, 0xBE, //0xBE 0x94
        0x40 | 1, LCD_CMD_FRAME_CTRL,
        0x80 | 2, 0x00, 0x1B, //0x1B 0x70
        0x40 | 1, LCD_CMD_ENABLE_3G,
        0x80 | 1, 0x08, //0x08 0x00
        0x40 | 1, LCD_CMD_GAMMA,
        0x80 | 1, 0x01, //G2.2
        0x40 | 1, LCD_CMD_POS_GAMMA,
        0x80 | 15, 0x1F, 0x1A, 0x18, 0x0A, 0x0F, 0x06, 0x45, 0x87, 0x32, 0x0A, 0x07, 0x02, 0x07, 0x05, 0x00,
//0x80|15, 0x0F, 0x1A, 0x18, 0x0A, 0x0F, 0x06, 0x45, 0x87, 0x32, 0x0A, 0x07, 0x02, 0x07, 0x05, 0x00,
        0x40 | 1, LCD_CMD_NEG_GAMMA,
        0x80 | 15, 0x00, 0x25, 0x27, 0x05, 0x10, 0x09, 0x3A, 0x78, 0x4D, 0x05, 0x18, 0x0D, 0x38, 0x3A, 0x1F,
//0x80|15, 0x00, 0x25, 0x27, 0x05, 0x10, 0x09, 0x3A, 0x78, 0x4D, 0x05, 0x18, 0x0D, 0x38, 0x3A, 0x0F,
        0x40 | 1, LCD_CMD_DISPLAY_CTRL,
        0x80 | 4, 0x0A, 0x82, 0x27, 0x00,
        0x40 | 1, LCD_CMD_ENTRY_MODE,
        0x80 | 1, 0x07,
        0x40 | 1, LCD_CMD_PIXEL_FORMAT,
        0x80 | 1, 0x55, //16bit
        0x40 | 1, LCD_CMD_MEMACCESS_CTRL,
        0x80 | 1, (1 << MEM_BGR) | (1 << MEM_X) | (1 << MEM_Y) | (1 << MEM_V),
        0x40 | 1, LCD_CMD_COLUMN,
        0x80 | 2, 0x00, 0x00,
        0x80 | 2, ((LCD_WIDTH - 1) >> 8) & 0xFF, (LCD_WIDTH - 1) & 0xFF,
        0x40 | 1, LCD_CMD_PAGE,
        0x80 | 2, 0x00, 0x00,
        0x80 | 2, ((LCD_HEIGHT - 1) >> 8) & 0xFF, (LCD_HEIGHT - 1) & 0xFF,
        0x40 | 1, LCD_CMD_SLEEPOUT,
        0xC0 | 60, //60ms
        0xC0 | 60, //60ms
        0x40 | 1, LCD_CMD_DISPLAY_ON,
        0xC0 | 20, //20ms
        0xFF, 0xFF
    };

#endif //ARDUINOGAME_TFTDEF_H
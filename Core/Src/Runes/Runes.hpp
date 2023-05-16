#pragma once
#include "Pins.hpp"

DMA_HandleTypeDef hdma_adc1;
DMA_HandleTypeDef hdma_adc2;
DMA_HandleTypeDef hdma_adc3;
DMA_HandleTypeDef hdma_i2c2_rx;
DMA_HandleTypeDef hdma_i2c2_tx;
I2C_HandleTypeDef hi2c2;
ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc2;
ADC_HandleTypeDef hadc3;
LPTIM_HandleTypeDef hlptim1;
LPTIM_HandleTypeDef hlptim2;
LPTIM_HandleTypeDef hlptim3;
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim5;
TIM_HandleTypeDef htim7;
TIM_HandleTypeDef htim8;
TIM_HandleTypeDef htim12;
TIM_HandleTypeDef htim16;
TIM_HandleTypeDef htim17;
TIM_HandleTypeDef htim15;
TIM_HandleTypeDef htim23;
TIM_HandleTypeDef htim24;
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
SPI_HandleTypeDef hspi3;
FDCAN_HandleTypeDef hfdcan1;


/************************************************
 *              Communication-FDCAN
 ***********************************************/

#ifdef HAL_FDCAN_MODULE_ENABLED

extern FDCAN_HandleTypeDef hfdcan1;

FDCAN::Instance FDCAN::instance1 = { .TX = PD1, .RX = PD0, .hfdcan = &hfdcan1,
									 .instance = FDCAN1, .dlc = DLC::BYTES_64,
									 .rx_location = FDCAN_RX_FIFO0, .fdcan_number = 1
									};

FDCAN::Peripheral FDCAN::fdcan1 = FDCAN::Peripheral::peripheral1;

unordered_map<FDCAN::Peripheral, FDCAN::Instance*> FDCAN::available_fdcans = {
		{FDCAN::fdcan1, &FDCAN::instance1}
};

unordered_map<FDCAN_HandleTypeDef*, FDCAN::Instance*> FDCAN::handle_to_fdcan = {
		{FDCAN::instance1.hfdcan, &FDCAN::instance1}
};

#endif

/************************************************
 *              Communication-SPI
 ***********************************************/
#ifdef HAL_SPI_MODULE_ENABLED

SPI::Instance SPI::instance3 = { .SCK = &PC10, .MOSI = &PC12, .MISO = &PC11, .SS = &PD0,
                                 .hspi = &hspi3, .instance = SPI3,
								 .baud_rate_prescaler = SPI_BAUDRATEPRESCALER_256,
                               };

SPI::Peripheral SPI::spi3 = SPI::Peripheral::peripheral3;

unordered_map<SPI::Peripheral, SPI::Instance*> SPI::available_spi = {
	{SPI::spi3, &SPI::instance3}
};
#endif
/************************************************
 *              Communication-UART
 ***********************************************/
#ifdef HAL_UART_MODULE_ENABLED

UART::Instance UART::instance1 = { .TX = PA9, .RX = PA10, .huart = &huart1,
								   .instance = USART1, .baud_rate = 115200, .word_length = UART_WORDLENGTH_8B,
                               };


UART::Instance UART::instance2 = { .TX = PD5, .RX = PD6, .huart = &huart2,
								   .instance = USART2, .baud_rate = 115200, .word_length = UART_WORDLENGTH_8B,
                               };


UART::Peripheral UART::uart1 = UART::Peripheral::peripheral1;
UART::Peripheral UART::uart2 = UART::Peripheral::peripheral2;


unordered_map<UART::Peripheral, UART::Instance*> UART::available_uarts = {
	{UART::uart1, &UART::instance1},
	{UART::uart2, &UART::instance2},
};

uint8_t UART::printf_uart = 0;
bool UART::printf_ready = false;

#endif
/************************************************
 *                 	  Encoder
 ***********************************************/
#ifdef HAL_TIM_MODULE_ENABLED
#define BASE TimerPeripheral::TIM_TYPE::BASE

TimerPeripheral encoder_timer(&htim8, {BASE, 0, 65535}, "TIM 8");

map<pair<Pin, Pin>, TimerPeripheral*> Encoder::pin_timer_map = {
		{{PC6, PC7}, &encoder_timer}
};

#endif
/************************************************
 *                     Timer
 ***********************************************/
#ifdef HAL_TIM_MODULE_ENABLED

#define BASE TimerPeripheral::TIM_TYPE::BASE
#define ADVANCED TimerPeripheral::TIM_TYPE::ADVANCED

TimerPeripheral timer1(&htim1, {ADVANCED}, "TIM 1");
TimerPeripheral timer2(&htim2, {BASE}, "TIM 2");
TimerPeripheral timer3(&htim3, {ADVANCED}, "TIM 3");
TimerPeripheral timer4(&htim4, {ADVANCED}, "TIM 4");
TimerPeripheral timer12(&htim12, {ADVANCED}, "TIM 12");
TimerPeripheral timer16(&htim16, {BASE}, "TIM 16");
TimerPeripheral timer17(&htim17, {BASE}, "TIM 17");
TimerPeripheral timer15(&htim15, {ADVANCED}, "TIM 15");
TimerPeripheral timer23(&htim23, {BASE, 275, UINT32_MAX - 1}, "TIM 23");

vector<reference_wrapper<TimerPeripheral>> TimerPeripheral::timers = {
		timer1,
		timer2,
		timer3,
		timer4,
		timer12,
		timer15,
		timer16,
		timer17,
		timer23
};


#endif

/************************************************
 *                     PWM
 ***********************************************/
#ifdef HAL_TIM_MODULE_ENABLED

#define NORMAL TimerPeripheral::PWM_MODE::NORMAL
#define PHASED TimerPeripheral::PWM_MODE::PHASED

PWMmap TimerPeripheral::available_pwm  = {
	{PB14, {timer12, {TIM_CHANNEL_1, NORMAL}}},
	{PB15, {timer12, {TIM_CHANNEL_2, NORMAL}}},
	{PB4, {timer3, {TIM_CHANNEL_1, PHASED}}},
	{PB5, {timer3, {TIM_CHANNEL_2, NORMAL}}},
	{PC8, {timer3, {TIM_CHANNEL_3, NORMAL}}},
	{PD12, {timer4, {TIM_CHANNEL_1, NORMAL}}},
	{PD13, {timer4, {TIM_CHANNEL_2, NORMAL}}},
	{PD15, {timer4, {TIM_CHANNEL_4, NORMAL}}},
	{PE14, {timer1, {TIM_CHANNEL_4, PHASED}}},
	{PE6, {timer15, {TIM_CHANNEL_2, NORMAL}}},
	{PF1, {timer23, {TIM_CHANNEL_2, NORMAL}}},
	{PF2, {timer23, {TIM_CHANNEL_3, NORMAL}}},
	{PF3, {timer23, {TIM_CHANNEL_4, NORMAL}}},
	{PE5, {timer15, {TIM_CHANNEL_1, NORMAL}}},
	{PE11, {timer1, {TIM_CHANNEL_2, NORMAL}}},
};

DualPWMmap TimerPeripheral::available_dual_pwms = {
	{{PB8,PB6}, {timer16, {TIM_CHANNEL_1, NORMAL}}},
	{{PB9,PB7}, {timer17, {TIM_CHANNEL_1, PHASED}}},
	{{PE11,PE10}, {timer1, {TIM_CHANNEL_2, PHASED}}},
	{{PE13,PE12}, {timer1, {TIM_CHANNEL_3, PHASED}}},
	{{PE5,PE4}, {timer15, {TIM_CHANNEL_1, NORMAL}}},
	{{PE9,PE8}, {timer1, {TIM_CHANNEL_1, NORMAL}}},
};

#endif

/************************************************
 *                 Input Capture
 ***********************************************/
#ifdef HAL_TIM_MODULE_ENABLED


map<Pin, InputCapture::Instance> InputCapture::available_instances = {
		{PF0, InputCapture::Instance(PF0, &timer23, TIM_CHANNEL_1, TIM_CHANNEL_2)}
};

#endif


/************************************************
 *					   ADC
 ***********************************************/
#if defined(HAL_ADC_MODULE_ENABLED) && defined(HAL_LPTIM_MODULE_ENABLED)

uint16_t adc_buf1[ADC_BUF_LEN];
uint16_t adc_buf2[ADC_BUF_LEN];
uint16_t adc_buf3[ADC_BUF_LEN];

LowPowerTimer lptim1(*LPTIM1, hlptim1, LPTIM1_PERIOD, "LPTIM 1");
LowPowerTimer lptim2(*LPTIM2, hlptim2, LPTIM2_PERIOD, "LPTIM 2");
LowPowerTimer lptim3(*LPTIM3, hlptim3, LPTIM3_PERIOD, "LPTIM 3");

vector<uint32_t> channels1 = {};
vector<uint32_t> channels2 = {};
vector<uint32_t> channels3 = {};

ADC::InitData init_data1(ADC1, ADC_RESOLUTION_16B, ADC_EXTERNALTRIG_LPTIM1_OUT, channels1, DMA::Stream::DMA1Stream0, "ADC 1");
ADC::InitData init_data2(ADC2, ADC_RESOLUTION_16B, ADC_EXTERNALTRIG_LPTIM2_OUT, channels2, DMA::Stream::DMA1Stream1, "ADC 2");
ADC::InitData init_data3(ADC3, ADC_RESOLUTION_12B, ADC_EXTERNALTRIG_LPTIM3_OUT, channels3, DMA::Stream::DMA1Stream2, "ADC 3");

ADC::Peripheral ADC::peripherals[3] = {
		ADC::Peripheral(&hadc1, adc_buf1, lptim1, init_data1),
		ADC::Peripheral(&hadc2, adc_buf2, lptim2, init_data2),
		ADC::Peripheral(&hadc3, adc_buf3, lptim3, init_data3)
};

map<Pin, ADC::Instance> ADC::available_instances = {
		{PF11, Instance(&peripherals[0], ADC_CHANNEL_2)},
		{PF12, Instance(&peripherals[0], ADC_CHANNEL_6)},
		{PF13, Instance(&peripherals[1], ADC_CHANNEL_2)},
		{PF14, Instance(&peripherals[1], ADC_CHANNEL_6)},
		{PF5, Instance(&peripherals[2], ADC_CHANNEL_4)},
		{PF6, Instance(&peripherals[2], ADC_CHANNEL_8)},
		{PF7, Instance(&peripherals[2], ADC_CHANNEL_3)},
		{PF8, Instance(&peripherals[2], ADC_CHANNEL_7)},
		{PF9, Instance(&peripherals[2], ADC_CHANNEL_2)},
		{PF10, Instance(&peripherals[2], ADC_CHANNEL_6)},
		{PC2, Instance(&peripherals[2], ADC_CHANNEL_0)},
		{PC3, Instance(&peripherals[2], ADC_CHANNEL_1)},
		{PF10, Instance(&peripherals[2], ADC_CHANNEL_6)},
		{PC0, Instance(&peripherals[0], ADC_CHANNEL_10)},
		{PA0, Instance(&peripherals[0], ADC_CHANNEL_16)},
		{PA3, Instance(&peripherals[0], ADC_CHANNEL_15)},
		{PA4, Instance(&peripherals[0], ADC_CHANNEL_18)},
		{PA5, Instance(&peripherals[0], ADC_CHANNEL_19)},
		{PA6, Instance(&peripherals[0], ADC_CHANNEL_3)},
		{PB0, Instance(&peripherals[0], ADC_CHANNEL_9)},
		{PB1, Instance(&peripherals[0], ADC_CHANNEL_5)}
};

uint32_t ADC::ranks[16] = {
		ADC_REGULAR_RANK_1,
		ADC_REGULAR_RANK_2,
		ADC_REGULAR_RANK_3,
		ADC_REGULAR_RANK_4,
		ADC_REGULAR_RANK_5,
		ADC_REGULAR_RANK_6,
		ADC_REGULAR_RANK_7,
		ADC_REGULAR_RANK_8,
		ADC_REGULAR_RANK_9,
		ADC_REGULAR_RANK_10,
		ADC_REGULAR_RANK_11,
		ADC_REGULAR_RANK_12,
		ADC_REGULAR_RANK_13,
		ADC_REGULAR_RANK_14,
		ADC_REGULAR_RANK_15,
		ADC_REGULAR_RANK_16
};



#endif

/************************************************
 *					   EXTI
 ***********************************************/
#ifdef HAL_EXTI_MODULE_ENABLED

map<uint16_t, ExternalInterrupt::Instance> ExternalInterrupt::instances = {
	{PE0.gpio_pin, Instance(EXTI0_IRQn)},
	{PE1.gpio_pin, Instance(EXTI1_IRQn)}
};

#endif

/************************************************
 *					   I2C
 ***********************************************/

#ifdef HAL_I2C_MODULE_ENABLED
extern I2C_HandleTypeDef hi2c2;
I2C::Instance I2C::instance2 = { .SCL = PF1, .SDA = PB11, .hi2c = &hi2c2, .instance = I2C2, .RX_DMA = DMA::Stream::DMA1Stream3, .TX_DMA = DMA::Stream::DMA1Stream4};
I2C::Peripheral I2C::i2c2 = I2C::Peripheral::peripheral2;
unordered_map<I2C::Peripheral, I2C::Instance*> I2C::available_i2cs = {
	{I2C::i2c2, &I2C::instance2}
};
unordered_map<uint32_t, uint32_t> I2C::available_speed_frequencies = {
	{100, 0x60404E72}
};
#endif

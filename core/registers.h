// The engineergorman\lpc1114fn28 framework is licensed under the MIT license:
// 
// Copyright (C) 2013 by Chris Gorman
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.


#include <LPC11xx.h>

/////////////////////////////////////////////////
//	LPC_FLASHCTRL Section
/////////////////////////////////////////////////

// LPC_FLASHCTRL->FLASHCFG
struct _FLASHCFG
{
	uint32_t FLASHTIM : 2;
	uint32_t reserved : 30;
};

#define FLASHTIM_1CLK 0x0
#define FLASHTIM_2CLK 0x1
#define FLASHTIM_3CLK 0x2

inline void FLASHCTRL_FLASHCFG_FLASHTIM(uint32_t val)
{
	((_FLASHCFG*)&LPC_FLASHCTRL->FLASHCFG)->FLASHTIM = val;
}

/////////////////////////////////////////////////
//	LPC_SYSCON Section
/////////////////////////////////////////////////

// LPC_SYSCON->SYSOSCCTRL
struct _SYSOSCCTRL
{
	uint32_t BYPASS : 1;
	uint32_t FREQRANGE : 1;
	uint32_t reserved : 30;
};

#define FREQRANGE_1_20_RANGE 0x0
#define FREQRANGE_15_25_RANGE 0x1

inline void SYSCON_SYSOSCCTRL_FREQRANGE(uint32_t val)
{
	((_SYSOSCCTRL*)&LPC_SYSCON->SYSOSCCTRL)->FREQRANGE = val;
}

// LPC_SYSCON->PDRUNCFG
struct _PDRUNCFG
{
	uint32_t IRCOUT : 1;
	uint32_t IRC : 1;
	uint32_t FLASH : 1;
	uint32_t BOD : 1;
	uint32_t ADC : 1;
	uint32_t SYSOSC : 1;
	uint32_t WDTOSC : 1;
	uint32_t SYSPLL : 1;
	uint32_t reserved : 24;
};
#define POWER_UP 0x0
#define POWER_DOWN 0x1

inline void SYSCON_PDRUNCFG_IRCOUT(uint32_t val)
{
	((_PDRUNCFG*)&LPC_SYSCON->PDRUNCFG)->IRCOUT = val;
}
inline void SYSCON_PDRUNCFG_SYSOSC(uint32_t val)
{
	((_PDRUNCFG*)&LPC_SYSCON->PDRUNCFG)->SYSOSC = val;
}
inline void SYSCON_PDRUNCFG_ADC(uint32_t val)
{
	((_PDRUNCFG*)&LPC_SYSCON->PDRUNCFG)->ADC = val;
}
inline void SYSCON_PDRUNCFG_SYSPLL(uint32_t val)
{
	((_PDRUNCFG*)&LPC_SYSCON->PDRUNCFG)->SYSPLL = val;
}

// LPC_SYSCON->SYSPLLCLKSEL
struct _SYSPLLCLKSEL
{
	uint32_t SEL : 2;
	uint32_t reserved : 30;
};

#define SYSPLLCLKSEL_IRC_OSCILLATOR 0x0
#define SYSPLLCLKSEL_SYSTEM_OSCILLATOR 0x1

inline void SYSCON_SYSPLLCLKSEL(uint32_t val)
{
	((_SYSPLLCLKSEL*)&LPC_SYSCON->SYSPLLCLKSEL)->SEL = val;
}

// LPC_SYSCON->SYSPLLCLKUEN
struct _SYSPLLCLKUEN
{
	uint32_t ENA : 1;
	uint32_t reserved : 31;
};

inline void SYSCON_SYSPLLCLKUEN_TOGGLE()
{
	//Toggle the system PLL clock source update enable register
	_SYSPLLCLKUEN* pBits =(_SYSPLLCLKUEN*)&LPC_SYSCON->SYSPLLCLKUEN;
	pBits->ENA = 0;
	pBits->ENA = 1;
}

// LPC_SYSCON->SYSPLLCTRL
struct _SYSPLLCTRL
{
	uint32_t MSEL : 5;
	uint32_t PSEL : 2;
	uint32_t reserved : 25;
};

inline void SYSCON_SYSPLLCTRL(uint32_t m, uint32_t p)
{
	// System PLL control register
	_SYSPLLCTRL* pBits =(_SYSPLLCTRL*)&LPC_SYSCON->SYSPLLCTRL;
	pBits->MSEL = m;
	pBits->PSEL = p;
}

// LPC_SYSCON->SYSPLLSTAT (read only)
struct _SYSPLLSTAT
{
	uint32_t LOCK : 1;
	uint32_t reserved : 31;
};

#define PLL_NOTLOCKED 0x0
#define PLL_LOCKED 0x1

inline void WAIT_SYSCON_SYSPLLSTAT_LOCK()
{
	// wait for PLL lock
	while( PLL_NOTLOCKED == ((_SYSPLLSTAT*)&LPC_SYSCON->SYSPLLSTAT)->LOCK );
}

// LPC_SYSCON->MAINCLKSEL
struct _MAINCLKSEL
{
	uint32_t SEL : 2;
	uint32_t reserved : 30;
};

#define MAINCLKSEL_IRC_OSCILATOR 0x0
#define MAINCLKSEL_INPUT_CLOCK_SYS_PLL 0x1
#define MAINCLKSEL_WDT_OSCILATOR 0x2
#define MAINCLKSEL_SYS_PLL_CLOCK_OUT 0x3

inline void SYSCON_MAINCLKSEL(uint32_t val)
{
	((_MAINCLKSEL*)&LPC_SYSCON->MAINCLKSEL)->SEL = val;
}

// LPC_SYSCON->MAINCLKUEN
struct _MAINCLKUEN
{
	uint32_t ENA : 1;
	uint32_t reserved : 31;
};

inline void SYSCON_MAINCLKUEN_TOGGLE()
{
	//Toggle main clock source update enable register
	_MAINCLKUEN* pBits =(_MAINCLKUEN*)&LPC_SYSCON->MAINCLKUEN;
	pBits->ENA = 0;
	pBits->ENA = 1;
}

// LPC_SYSCON->SYSAHBCLKCTRL
struct _SYSAHBCLKCTRL
{
	uint32_t SYS : 1;
	uint32_t ROM : 1;
	uint32_t RAM : 1;
	uint32_t FLASHREG : 1;
	uint32_t FLASHARRAY : 1;
	uint32_t I2C : 1;
	uint32_t GPIO : 1;
	uint32_t CT16B0 : 1;
	uint32_t CT16B1 : 1;
	uint32_t CT32B0 : 1;
	uint32_t CT32B1 : 1;
	uint32_t SSP0 : 1;
	uint32_t UART : 1;
	uint32_t ADC : 1;
	uint32_t reserved0 : 1;
	uint32_t WDT : 1;
	uint32_t IOCON : 1;
	uint32_t CAN : 1;
	uint32_t SSP1 : 1;
	uint32_t reserved1 : 13;
};

#define SYSAHBCLKCTRL_DISABLE 0x0
#define SYSAHBCLKCTRL_ENABLE 0x1

inline void SYSCON_SYSAHBCLKCTRL_I2C(uint32_t val)
{
	((_SYSAHBCLKCTRL*)&LPC_SYSCON->SYSAHBCLKCTRL)->I2C = val;
}

inline void SYSCON_SYSAHBCLKCTRL_GPIO(uint32_t val)
{
	((_SYSAHBCLKCTRL*)&LPC_SYSCON->SYSAHBCLKCTRL)->GPIO = val;
}

inline void SYSCON_SYSAHBCLKCTRL_CT16B0(uint32_t val)
{
	((_SYSAHBCLKCTRL*)&LPC_SYSCON->SYSAHBCLKCTRL)->CT16B0 = val;
}

inline void SYSCON_SYSAHBCLKCTRL_CT16B1(uint32_t val)
{
	((_SYSAHBCLKCTRL*)&LPC_SYSCON->SYSAHBCLKCTRL)->CT16B1 = val;
}

inline void SYSCON_SYSAHBCLKCTRL_CT32B0(uint32_t val)
{
	((_SYSAHBCLKCTRL*)&LPC_SYSCON->SYSAHBCLKCTRL)->CT32B0 = val;
}

inline void SYSCON_SYSAHBCLKCTRL_CT32B1(uint32_t val)
{
	((_SYSAHBCLKCTRL*)&LPC_SYSCON->SYSAHBCLKCTRL)->CT32B1 = val;
}

inline void SYSCON_SYSAHBCLKCTRL_SSP0(uint32_t val)
{
	((_SYSAHBCLKCTRL*)&LPC_SYSCON->SYSAHBCLKCTRL)->SSP0 = val;
}

inline void SYSCON_SYSAHBCLKCTRL_UART(uint32_t val)
{
	((_SYSAHBCLKCTRL*)&LPC_SYSCON->SYSAHBCLKCTRL)->UART = val;
}

inline void SYSCON_SYSAHBCLKCTRL_ADC(uint32_t val)
{
	((_SYSAHBCLKCTRL*)&LPC_SYSCON->SYSAHBCLKCTRL)->ADC = val;
}

inline void SYSCON_SYSAHBCLKCTRL_IOCON(uint32_t val)
{
	((_SYSAHBCLKCTRL*)&LPC_SYSCON->SYSAHBCLKCTRL)->IOCON = val;
}

// LPC_SYSCON->SYSAHBCLKDIV
struct _SYSAHBCLKDIV
{
	uint32_t DIV : 8;
	uint32_t reserved : 24;
};

inline void SYSCON_SYSAHBCLKDIV(uint32_t val)
{
	((_SYSAHBCLKDIV*)&LPC_SYSCON->SYSAHBCLKDIV)->DIV = val;
}

/////////////////////////////////////////////////
//	LPC_GPIOn Section
/////////////////////////////////////////////////

// LPC_GPIO0->DIR
struct _GPIODIR
{
	uint32_t IO : 12;
	uint32_t reserved : 20;	
};

#define GPIO_INPUT 0x0
#define GPIO_OUTPUT 0x1

inline void GPIO0_DIR(uint32_t pin, uint32_t dir)
{
	if (dir)
		((_GPIODIR*)&LPC_GPIO0->DIR)->IO |= 1 << pin;
	else
		((_GPIODIR*)&LPC_GPIO0->DIR)->IO &= ~ (1 << pin);
}

inline void GPIO1_DIR(uint32_t pin, uint32_t dir)
{
	if (dir)
		((_GPIODIR*)&LPC_GPIO1->DIR)->IO |= 1 << pin;
	else
		((_GPIODIR*)&LPC_GPIO1->DIR)->IO &= ~ (1 << pin);
}

// LPC_GPIO0->IS
// Interrupt sense Register (R/W)
struct _GPIOIS
{
	uint32_t ISENSE : 12;	// Selects interrupt on pin x as level or edge sensitive
	uint32_t reserved : 20;	
};

#define GPIO_EDGE_SENSITIVE	0x0
#define GPIO_LEVEL_SENSITIVE	0x1

inline void GPIO0_IS(uint32_t pin, uint32_t dir)
{
	if (dir)
		((_GPIOIS*)&LPC_GPIO0->IS)->ISENSE |= 1 << pin;
	else
		((_GPIOIS*)&LPC_GPIO0->IS)->ISENSE &= ~ (1 << pin);
}

inline void GPIO1_IS(uint32_t pin, uint32_t dir)
{
	if (dir)
		((_GPIOIS*)&LPC_GPIO1->IS)->ISENSE |= 1 << pin;
	else
		((_GPIOIS*)&LPC_GPIO1->IS)->ISENSE &= ~ (1 << pin);
}

// LPC_GPIO0->IBE
// Interrupt both edges Register (R/W)
struct _GPIOIBE
{
	uint32_t IBE : 12;	// Selects interrupt on pin x to be triggered on both edges
	uint32_t reserved : 20;	
};

#define GPIO_SINGLE_EDGE	0x0
#define GPIO_BOTH_EDGES 0x1

inline void GPIO0_IBE(uint32_t pin, uint32_t dir)
{
	if (dir)
		((_GPIOIBE*)&LPC_GPIO0->IBE)->IBE |= 1 << pin;
	else
		((_GPIOIBE*)&LPC_GPIO0->IBE)->IBE &= ~ (1 << pin);
}

inline void GPIO1_IBE(uint32_t pin, uint32_t dir)
{
	if (dir)
		((_GPIOIBE*)&LPC_GPIO1->IBE)->IBE |= 1 << pin;
	else
		((_GPIOIBE*)&LPC_GPIO1->IBE)->IBE &= ~ (1 << pin);
}

// LPC_GPIO0->IEV
// Interrupt Event Register  (R/W)
struct _GPIOIEV
{
	uint32_t IEV : 12;	// Selects interrupt on pin x to be triggered rising or falling edges
	uint32_t reserved : 20;	
};

// If GPIO_EDGE_SENSITIVE set, then:
#define GPIO_FALLING_EDGE	0x0
#define GPIO_RISING_EDGES 0x1
// If GPIO_LEVEL_SENSITIVE set, then:
#define GPIO_LOW_LEVEL 0x0
#define GPIO_HIGH_LEVEL 0x1

inline void GPIO0_IEV(uint32_t pin, uint32_t dir)
{
	if (dir)
		((_GPIOIEV*)&LPC_GPIO0->IEV)->IEV |= 1 << pin;
	else
		((_GPIOIEV*)&LPC_GPIO0->IEV)->IEV &= ~ (1 << pin);
}

inline void GPIO1_IEV(uint32_t pin, uint32_t dir)
{
	if (dir)
		((_GPIOIEV*)&LPC_GPIO1->IEV)->IEV |= 1 << pin;
	else
		((_GPIOIEV*)&LPC_GPIO1->IEV)->IEV &= ~ (1 << pin);
}

// LPC_GPIO0->IE
// Interrupt mask Register (R/W) 
struct _GPIOIE
{
	uint32_t MASK : 12;	// Selects interrupt on pin x to be masked
	uint32_t reserved : 20;	
};

#define GPIO_INTERRUPT_DISABLE 0x0
#define GPIO_INTERRUPT_ENABLE 0x1

inline void GPIO0_IE(uint32_t pin, uint32_t dir)
{
	if (dir)
		((_GPIOIE*)&LPC_GPIO0->IE)->MASK |= 1 << pin;
	else
		((_GPIOIE*)&LPC_GPIO0->IE)->MASK &= ~ (1 << pin);
}

inline void GPIO1_IE(uint32_t pin, uint32_t dir)
{
	if (dir)
		((_GPIOIE*)&LPC_GPIO1->IE)->MASK |= 1 << pin;
	else
		((_GPIOIE*)&LPC_GPIO1->IE)->MASK &= ~ (1 << pin);
}

// LPC_GPIO0->MIS
// GPIO masked interrupt status register (R)
struct _GPIOMIS
{
	uint32_t MASK : 12;	// interrupt status bits
	uint32_t reserved : 20;	
};

// returns 1 if interrupt on GPIO0_x; 0 if no interrupt (or was masked)
inline uint32_t GPIO0_MIS(uint32_t pin)
{
	return (((_GPIOMIS*)&LPC_GPIO0->MIS)->MASK >> pin) & 0x1;
}

inline uint32_t GPIO1_MIS(uint32_t pin)
{
	return (((_GPIOMIS*)&LPC_GPIO1->MIS)->MASK >> pin) & 0x1;
}

// LPC_GPIO0->IC
// GPIO interrupt clear register (W)
struct _GPIOIC
{
	uint32_t CLR : 12;	// clears the interrupt edge detection logic
	uint32_t reserved : 20;	
};

// clears interrupt on pin x
//		Note:  It is recommended to add two NOPs after the clear of the interrupt edge 
//		detection logic before the exit of the interrupt service routine, ex: __NOP();__NOP();

inline void GPIO0_IC(uint32_t pin)
{
	((_GPIOIC*)&LPC_GPIO0->IC)->CLR |= 1 << pin;
}

inline void GPIO1_IC(uint32_t pin)
{
	((_GPIOIC*)&LPC_GPIO1->IC)->CLR |= 1 << pin;
}

// LPC_GPIO0->MASKED_ACCESS
// write value at GPIOn, pin = n
inline void GPIO0_DATA( uint32_t pin, uint32_t val )
{
  LPC_GPIO0->MASKED_ACCESS[(1 << pin)] = (val << pin);
}
// read value at GPIOn, pin = n
inline uint32_t GPIO0_DATA( uint32_t pin )
{
  return LPC_GPIO0->MASKED_ACCESS[(1 << pin)];
}

inline void GPIO1_DATA( uint32_t pin, uint32_t val )
{
  LPC_GPIO1->MASKED_ACCESS[(1 << pin)] = (val << pin);
}

inline uint32_t GPIO1_DATA( uint32_t pin )
{
  return LPC_GPIO1->MASKED_ACCESS[(1 << pin)];
}

#include "timers16bit.h"
#include "timers32bit.h"

/////////////////////////////////////////////////
//	LPC_IOCON Section
/////////////////////////////////////////////////


// LPC_IOCON->PIO0_2
// I/O configuration for pin (25) PIO0_2/SSEL0/CT16B0_CAP0 (R/W)
struct _PIO0_2
{
	uint32_t FUNC : 3;	// pin function
	uint32_t MODE : 2;	// pull up/down resistor mode
	uint32_t HYS : 1;		// Hysteresis.
	uint32_t reserved0 : 4;
	uint32_t OD : 1;		// Selects pseudo open-drain mode
	uint32_t reserved1 : 21;
};

#define PIO0_2_FUNC_GPIO 0x0
#define PIO0_2_FUNC_SSEL 0x1
#define PIO0_2_FUNC_TIMER 0x2
inline void IOCON_PIO0_2_FUNC(uint32_t val)
{
	((_PIO0_2*)&LPC_IOCON->PIO0_2)->FUNC = val;
}

#define PIO0_2_MODE_NO_RESISTOR 0x0
#define PIO0_2_MODE_PULLDOWN_RESISTOR 0x1
#define PIO0_2_MODE_PULLUP_RESISTOR 0x2
#define PIO0_2_MODE_REPEATER 0x3
inline void IOCON_PIO0_2_MODE(uint32_t val)
{
	((_PIO0_2*)&LPC_IOCON->PIO0_2)->MODE = val;
}


// LPC_IOCON->PIO0_8
// I/O configuration for pin (1) PIO0_8/MISO0/CT16B0_MAT0 (R/W)
struct _PIO0_8
{
	uint32_t FUNC : 3;	// pin function
	uint32_t MODE : 2;	// pull up/down resistor mode
	uint32_t HYS : 1;		// Hysteresis.
	uint32_t reserved0 : 4;
	uint32_t OD : 1;		// Selects pseudo open-drain mode
	uint32_t reserved1 : 21;
};

#define PIO0_8_FUNC_GPIO 0x0
#define PIO0_8_FUNC_MISO 0x1
#define PIO0_8_FUNC_TIMER 0x2
inline void IOCON_PIO0_8_FUNC(uint32_t val)
{
	((_PIO0_8*)&LPC_IOCON->PIO0_8)->FUNC = val;
}

#define PIO0_8_MODE_NO_RESISTOR 0x0
#define PIO0_8_MODE_PULLDOWN_RESISTOR 0x1
#define PIO0_8_MODE_PULLUP_RESISTOR 0x2
#define PIO0_8_MODE_REPEATER 0x3
inline void IOCON_PIO0_8_MODE(uint32_t val)
{
	((_PIO0_8*)&LPC_IOCON->PIO0_8)->MODE = val;
}


// LPC_IOCON->PIO0_9
// I/O configuration for pin (2) PIO0_9/MOSI0/CT16B0_MAT1 (R/W)
struct _PIO0_9
{
	uint32_t FUNC : 3;	// pin function
	uint32_t MODE : 2;	// pull up/down resistor mode
	uint32_t HYS : 1;		// Hysteresis.
	uint32_t reserved0 : 4;
	uint32_t OD : 1;		// Selects pseudo open-drain mode
	uint32_t reserved1 : 21;
};

#define PIO0_9_FUNC_GPIO 0x0
#define PIO0_9_FUNC_MOSI 0x1
#define PIO0_9_FUNC_TIMER 0x2
inline void IOCON_PIO0_9_FUNC(uint32_t val)
{
	((_PIO0_9*)&LPC_IOCON->PIO0_9)->FUNC = val;
}

#define PIO0_9_MODE_NO_RESISTOR 0x0
#define PIO0_9_MODE_PULLDOWN_RESISTOR 0x1
#define PIO0_9_MODE_PULLUP_RESISTOR 0x2
#define PIO0_9_MODE_REPEATER 0x3
inline void IOCON_PIO0_9_MODE(uint32_t val)
{
	((_PIO0_9*)&LPC_IOCON->PIO0_9)->MODE = val;
}


// LPC_IOCON->PIO0_5
// I/O configuration for pin (5) PIO0_5/SDA (R/W)
struct _PIO0_5
{
	uint32_t FUNC : 3;	// pin function
	uint32_t reserved0 : 5;
	uint32_t I2CMODE : 2;		// Selects I2C mode
	uint32_t reserved1 : 22;
};

#define PIO0_5_FUNC_GPIO 0x0
#define PIO0_5_FUNC_I2C_SDA 0x1
inline void IOCON_PIO0_5_FUNC(uint32_t val)
{
	((_PIO0_5*)&LPC_IOCON->PIO0_5)->FUNC = val;
}

#define PIO0_5_I2CMODE_FAST 0x0
#define PIO0_5_I2CMODE_GPIO 0x1
#define PIO0_5_I2CMODE_FAST_PLUS 0x2
inline void IOCON_PIO0_5_I2CMODE(uint32_t val)
{
	((_PIO0_5*)&LPC_IOCON->PIO0_5)->I2CMODE = val;
}


// LPC_IOCON->PIO0_4
// I/O configuration for pin (27) PIO0_4/SCL (R/W)
struct _PIO0_4
{
	uint32_t FUNC : 3;	// pin function
	uint32_t reserved0 : 5;
	uint32_t I2CMODE : 2;		// Selects I2C mode
	uint32_t reserved1 : 22;
};

#define PIO0_4_FUNC_GPIO 0x0
#define PIO0_4_FUNC_I2C_SCL 0x1
inline void IOCON_PIO0_4_FUNC(uint32_t val)
{
	((_PIO0_4*)&LPC_IOCON->PIO0_4)->FUNC = val;
}

#define PIO0_4_I2CMODE_FAST 0x0
#define PIO0_4_I2CMODE_GPIO 0x1
#define PIO0_4_I2CMODE_FAST_PLUS 0x2
inline void IOCON_PIO0_4_I2CMODE(uint32_t val)
{
	((_PIO0_4*)&LPC_IOCON->PIO0_4)->I2CMODE = val;
}


// LPC_IOCON->R_PIO1_0
// I/O configuration for pin R_PIO1_0/AD1/CT32B1_CAP0 (R/W)
struct _PIO1_0
{
	uint32_t FUNC : 3;	// pin function
	uint32_t MODE : 2;	// pull up/down resistor mode
	uint32_t HYS : 1;		// Hysteresis.
	uint32_t reserved0 : 1;
	uint32_t ADMODE : 1;		// Selects Analog/Digital mode
	uint32_t reserved1 : 2;
	uint32_t OD : 1;		// Selects pseudo open-drain mode
	uint32_t reserved2 : 21;
};

#define PIO1_0_FUNC_R 0x0		// reserved
#define PIO1_0_FUNC_GPIO 0x1
#define PIO1_0_FUNC_ADC 0x2
#define PIO1_0_FUNC_TIMER 0x3
inline void IOCON_PIO1_0_FUNC(uint32_t val)
{
	((_PIO1_0*)&LPC_IOCON->R_PIO1_0)->FUNC = val;
}

#define PIO1_0_MODE_NO_RESISTOR 0x0
#define PIO1_0_MODE_PULLDOWN_RESISTOR 0x1
#define PIO1_0_MODE_PULLUP_RESISTOR 0x2
#define PIO1_0_MODE_REPEATER 0x3
inline void IOCON_PIO1_0_MODE(uint32_t val)
{
	((_PIO1_0*)&LPC_IOCON->R_PIO1_0)->MODE = val;
}

#define PIO1_0_ADMODE_ANALOG_INPUT 0x0
#define PIO1_0_ADMODE_DIGITAL 0x1
inline void IOCON_PIO1_0_ADMODE(uint32_t val)
{
	((_PIO1_0*)&LPC_IOCON->R_PIO1_0)->ADMODE = val;
}


// LPC_IOCON->R_PIO1_1
// I/O configuration for pin R_PIO1_1/AD2/CT32B1_MAT0 (R/W)
struct _PIO1_1
{
	uint32_t FUNC : 3;	// pin function
	uint32_t MODE : 2;	// pull up/down resistor mode
	uint32_t HYS : 1;		// Hysteresis.
	uint32_t reserved0 : 1;
	uint32_t ADMODE : 1;		// Selects Analog/Digital mode
	uint32_t reserved1 : 2;
	uint32_t OD : 1;		// Selects pseudo open-drain mode
	uint32_t reserved2 : 21;
};

#define PIO1_1_FUNC_R 0x0		// reserved
#define PIO1_1_FUNC_GPIO 0x1
#define PIO1_1_FUNC_ADC 0x2
#define PIO1_1_FUNC_TIMER 0x3
inline void IOCON_PIO1_1_FUNC(uint32_t val)
{
	((_PIO1_1*)&LPC_IOCON->R_PIO1_1)->FUNC = val;
}

#define PIO1_1_MODE_NO_RESISTOR 0x0
#define PIO1_1_MODE_PULLDOWN_RESISTOR 0x1
#define PIO1_1_MODE_PULLUP_RESISTOR 0x2
#define PIO1_1_MODE_REPEATER 0x3
inline void IOCON_PIO1_1_MODE(uint32_t val)
{
	((_PIO1_1*)&LPC_IOCON->R_PIO1_1)->MODE = val;
}

#define PIO1_1_ADMODE_ANALOG_INPUT 0x0
#define PIO1_1_ADMODE_DIGITAL 0x1
inline void IOCON_PIO1_1_ADMODE(uint32_t val)
{
	((_PIO1_1*)&LPC_IOCON->R_PIO1_1)->ADMODE = val;
}


/////////////////////////////////////////////////
//	LPC_ADC Section
/////////////////////////////////////////////////

// LPC_ADC->CR
struct _ADC_CR
{
	uint32_t SEL : 8;	// Selects which of the AD7:0 pins is sampled and converted.
	uint32_t CLKDIV : 8;	// PCLK divided by CLKDIV +1 to produce the ADC clock (<= 4.5MHz)
	uint32_t BURST : 1;		// Burst mode.
	uint32_t CLKS : 3;	// number of clocks used for each conversion (Burst mode)
	uint32_t reserved0 : 4;
	uint32_t START : 3;	// control whether/when A/D conversion is started (Burst mode)	uint32_t CLKS : 3;
	uint32_t EDGE : 1;
	uint32_t reserved1 : 4;
};

#define ADC_DISABLE 0x0
#define ADC_ENABLE 0x1
// first param is the ADn index, second param is enable/disable
inline void ADC_CR_SEL(uint32_t idx, uint32_t val)
{
	if (val)
		((_ADC_CR*)&LPC_ADC->CR)->SEL |= (1 << idx);
	else
		((_ADC_CR*)&LPC_ADC->CR)->SEL &= ~(1<< idx);
}

inline void ADC_CR_CLKDIV(uint32_t val)
{
	((_ADC_CR*)&LPC_ADC->CR)->CLKDIV = val;
}

#define ADC_BURST_DISABLE 0x0
#define ADC_BURST_ENABLE 0x1
inline void ADC_CR_BURST(uint32_t val)
{
	((_ADC_CR*)&LPC_ADC->CR)->BURST = val;
}

#define ADC_CLKS_11	0x0		// 10 bits accuracy
#define ADC_CLKS_10	0x1		// 9 bits accuracy
#define ADC_CLKS_9	0x2		// 8 bits accuracy
#define ADC_CLKS_8	0x3		// 7 bits accuracy
#define ADC_CLKS_7	0x4		// 6 bits accuracy
#define ADC_CLKS_6	0x5		// 5 bits accuracy
#define ADC_CLKS_5	0x6		// 4 bits accuracy
#define ADC_CLKS_4	0x7		// 3 bits accuracy
inline void ADC_CR_CLKS(uint32_t val)
{
	((_ADC_CR*)&LPC_ADC->CR)->CLKS = val;
}

// When the BURST bit is 0, these bits control whether and when an A/D conversion is started
#define ADC_START_STOP 0x0	// No start (this value should be used when clearing PDN to 0).
#define ADC_START_START_NOW 0x1	// Start conversion now.
#define ADC_START_ON_EDGE_PIO0_2 0x2		// Start conversion when edge on PIO0_2/SSEL/CT16B0_CAP0
#define ADC_START_ON_EDGE_PIO1_5 0x3		// Start conversion when edge on PIO1_5/DIR/CT32B0_CAP0
#define ADC_START_ON_EDGE_PIO1_6 0x4		// Start conversion when edge on CT32B0_MAT0
#define ADC_START_ON_EDGE_PIO1_7 0x5		// Start conversion when edge on CT32B0_MAT1
#define ADC_START_ON_EDGE_PIO0_8 0x6		// Start conversion when edge on CT16B0_MAT0
#define ADC_START_ON_EDGE_PIO0_9 0x7		// Start conversion when edge on CT16B0_MAT1
inline void ADC_CR_START(uint32_t val)
{
	((_ADC_CR*)&LPC_ADC->CR)->START = val;
}

// LPC_ADC->GDR
// A/D Global Data Register
// contains the result of the most recent A/D conversion
// Note: Reading this register resets the DONE bit to zero
struct _ADC_GDR
{
	uint32_t reserved0 : 6;
	uint32_t V_VREF : 10;	// voltage sample
	uint32_t reserved1 : 8;
	uint32_t CHN : 3;	// channel from which the result bits V_VREF were converted.
	uint32_t reserved2 : 3;
	uint32_t OVERRUN : 1;
	uint32_t DONE : 1;	// This bit is set to 1 when an A/D conversion completes.
};

#define ADC_GDR_DONE	0x1

inline _ADC_GDR ADC_GDR_Sample()
{
	return (_ADC_GDR&)LPC_ADC->GDR;
}















/////////////////////////////////////////////////
//	LPC_UART Section
/////////////////////////////////////////////////

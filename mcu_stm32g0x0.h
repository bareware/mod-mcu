#ifndef MCU_STM32G0x0
#define MCU_STM32G0x0

#include <stdint.h>

// COMMON

static inline uint32_t mask_x2(uint32_t mask) {
    mask = (mask | (mask << 8 )) & 0x00ff00ff;
    mask = (mask | (mask << 4 )) & 0x0f0f0f0f;
    mask = (mask | (mask << 2 )) & 0x33333333;
    mask = (mask | (mask << 1 )) & 0x55555555;
    mask |= mask << 1;
    return mask;
}

// RCC

typedef enum {
    rcc_gpio_a = (1 << 0),
    rcc_gpio_b = (1 << 1),
    rcc_gpio_c = (1 << 2),
    rcc_gpio_d = (1 << 3),
    rcc_gpio_e = (1 << 4),
    rcc_gpio_f = (1 << 5),
} rcc_gpio_t;

typedef struct {
    volatile uint32_t cr;           // (RCC_CR)         Clock control register
    volatile uint32_t icscr;        // (RCC_ICSCR)      Internal clock source calibration register
    volatile uint32_t cfgr;         // (RCC_CFGR)       Clock configuration register
    volatile uint32_t pllicfgr;     // (RCC_PLLCFGR)    PLL configuration register
    volatile uint32_t _reserved0;   // Reserved
    volatile uint32_t _reserved1;   // Reserved
    volatile uint32_t cier;         // (RCC_CIER)       Clock interrupt enable register
    volatile uint32_t cifr;         // (RCC_CIFR)       Clock interrupt flag register
    volatile uint32_t cicr;         // (RCC_CICR)       Clock interrupt clear register
    volatile uint32_t ioprstr;      // (RCC_IOPRSTR)    I/O port reset register
    volatile uint32_t ahbrstr;      // (RCC_AHBRSTR)    AHB peripheral reset register
    volatile uint32_t apbrstr1;     // (RCC_APBRSTR1)   APB peripheral reset register 1
    volatile uint32_t apbrstr2;     // (RCC_APBRSTR2)   APB peripheral reset register 2
    volatile uint32_t iopenr;       // (RCC_IOPENR)     I/O port clock enable register
    volatile uint32_t ahbenr;       // (RCC_AHBENR)     AHB peripheral clock enable register
    volatile uint32_t apbenr1;      // (RCC_APBENR1)    APB peripheral clock enable register 1
    volatile uint32_t apbenr2;      // (RCC_APBENR2)    APB peripheral clock enable register 2
    volatile uint32_t iopsmenr;     // (RCC_IOPSMENR)   I/O port in Sleep mode clock enable register
    volatile uint32_t ahbsmenr;     // (RCC_AHBSMENR)   AHB peripheral clock enable in Sleep/Stop mode register
    volatile uint32_t apbsmenr1;    // (RCC_APBSMENR1)  APB peripheral clock enable in Sleep/Stop mode register 1
    volatile uint32_t apbsmenr2;    // (RCC_APBSMENR2)  APB peripheral clock enable in Sleep/Stop mode register 2
    volatile uint32_t ccipr;        // (RCC_CCIPR)      Peripherals independent clock configuration register
    volatile uint32_t ccipr2;       // (RCC_CCIPR2)     Peripherals independent clock configuration register 2
    volatile uint32_t _reserved2;   // Reserved
    volatile uint32_t bdcr;         // (RCC_BDCR)       Backup domain control register
    volatile uint32_t csr;          // (RCC_CSR)        Control/status register
} rcc_t;

static volatile rcc_t* const rcc = ((rcc_t*)(0x40021000));

static inline void rcc_gpio_clk_enable(rcc_gpio_t gpio) {
    rcc->iopenr |= gpio;
}

static inline void rcc_gpio_clk_disable(rcc_gpio_t gpio) {
    rcc->iopenr &= gpio;
}

// GPIO

typedef enum {
    gpio_mode_input         = 0x00000000,
    gpio_mode_output        = 0x55555555,
    gpio_mode_af            = 0xAAAAAAAA,
    gpio_mode_analog        = 0xFFFFFFFF,
} gpio_mode_t;

typedef enum {
    gpio_output_push_pull   = 0x00000000,
    gpio_output_open_drain  = 0x0000FFFF,
} gpio_output_type_t;

typedef enum {
    gpio_speed_low          = 0x00000000,
    gpio_speed_medium       = 0x55555555,
    gpio_speed_high         = 0xAAAAAAAA,
    gpio_speed_very_high    = 0xFFFFFFFF,
} gpio_speed_t;

typedef struct {
    volatile uint32_t moder;     // (GPIOx_MODER)   GPIO port mode register
    volatile uint32_t otyper;    // (GPIOx_OTYPER)  GPIO port output type register
    volatile uint32_t ospeedr;   // (GPIOx_OSPEEDR) GPIO port output speed register
    volatile uint32_t pupdr;     // (GPIOx_PUPDR)   GPIO port pull-up/pull-down register
    volatile uint32_t idr;       // (GPIOx_IDR)     GPIO port input data register
    volatile uint32_t odr;       // (GPIOx_ODR)     GPIO port output data register
    volatile uint32_t bsrr;      // (GPIOx_BSRR)    GPIO port bit set/reset register
    volatile uint32_t lckr;      // (GPIOx_LCKR)    GPIO port configuration lock register
    volatile uint32_t afrl;      // (GPIOx_AFRL)    GPIO alternate function low register
    volatile uint32_t afrh;      // (GPIOx_AFRH)    GPIO alternate function high register
    volatile uint32_t brr;       // (GPIOx_BRR)     GPIO bit reset register
} gpio_t;

static gpio_t* const gpio_a = (gpio_t*)0x50000000;
static gpio_t* const gpio_b = (gpio_t*)0x50000400;
static gpio_t* const gpio_c = (gpio_t*)0x50000800;
static gpio_t* const gpio_d = (gpio_t*)0x50000C00;
static gpio_t* const gpio_e = (gpio_t*)0x50001000;
static gpio_t* const gpio_f = (gpio_t*)0x50001400;

typedef enum {
    gpio_pin_0  = 0x0001,
    gpio_pin_1  = 0x0002,
    gpio_pin_2  = 0x0004,
    gpio_pin_3  = 0x0008,
    gpio_pin_4  = 0x0010,
    gpio_pin_5  = 0x0020,
    gpio_pin_6  = 0x0040,
    gpio_pin_7  = 0x0080,
    gpio_pin_8  = 0x0100,
    gpio_pin_9  = 0x0200,
    gpio_pin_10 = 0x0400,
    gpio_pin_11 = 0x0800,
    gpio_pin_12 = 0x1000,
    gpio_pin_13 = 0x2000,
    gpio_pin_14 = 0x4000,
    gpio_pin_15 = 0x8000,
} gpio_pin_t;

static inline void gpio_setup_output(gpio_t* port, gpio_output_type_t type, gpio_speed_t speed, gpio_pin_t pins) {
    const uint32_t pins2 = mask_x2(pins);

    port->otyper  = (port->otyper  & ~pins ) | (pins  & type);
    port->ospeedr = (port->ospeedr & ~pins2) | (pins2 & speed);
    port->moder   = (port->moder   & ~pins2) | (pins2 & gpio_mode_output);
}

static inline uint16_t gpio_read(gpio_t* port, gpio_pin_t pins) {
    return port->idr & pins;
}

static inline void gpio_write(gpio_t* port, uint16_t vals, gpio_pin_t pins) {
    port->bsrr = vals & pins;
    port->brr = (uint32_t)(~vals) & pins;
}

static inline void gpio_set(gpio_t* port, gpio_pin_t pins) {
    port->bsrr = pins;
}

static inline void gpio_clear(gpio_t* port, gpio_pin_t pins) {
    port->bsrr = (pins << 16);
}

#endif


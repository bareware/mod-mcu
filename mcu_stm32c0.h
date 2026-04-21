/* SPDX-License-Identifier: MIT-0 | Copyright (c) 2026 bareware */

#ifndef MCU_STM32C0
#define MCU_STM32C0

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

// Utilities

[[gnu::error("Mask must be a compile-time constant!")]]
extern void _error_not_constant(void);

#define _const_mask_x2(mask) ({                         \
        const uint32_t res =                            \
            (((mask) & (1<<0x0)) ? (0x3 <<  0) : 0) |   \
            (((mask) & (1<<0x1)) ? (0x3 <<  2) : 0) |   \
            (((mask) & (1<<0x2)) ? (0x3 <<  4) : 0) |   \
            (((mask) & (1<<0x3)) ? (0x3 <<  6) : 0) |   \
            (((mask) & (1<<0x4)) ? (0x3 <<  8) : 0) |   \
            (((mask) & (1<<0x5)) ? (0x3 << 10) : 0) |   \
            (((mask) & (1<<0x6)) ? (0x3 << 12) : 0) |   \
            (((mask) & (1<<0x7)) ? (0x3 << 14) : 0) |   \
            (((mask) & (1<<0x8)) ? (0x3 << 16) : 0) |   \
            (((mask) & (1<<0x9)) ? (0x3 << 18) : 0) |   \
            (((mask) & (1<<0xA)) ? (0x3 << 20) : 0) |   \
            (((mask) & (1<<0xB)) ? (0x3 << 22) : 0) |   \
            (((mask) & (1<<0xC)) ? (0x3 << 24) : 0) |   \
            (((mask) & (1<<0xD)) ? (0x3 << 26) : 0) |   \
            (((mask) & (1<<0xE)) ? (0x3 << 28) : 0) |   \
            (((mask) & (1<<0xF)) ? (0x3 << 30) : 0);    \
        if (!__builtin_constant_p(res)) {               \
            _error_not_constant();                      \
        }                                               \
        res;                                            \
    })

#define _const_mask_x4(mask) ({                         \
        const uint32_t res =                            \
            (((mask) & (1<<0x0)) ? (0xF <<  0) : 0) |   \
            (((mask) & (1<<0x1)) ? (0xF <<  4) : 0) |   \
            (((mask) & (1<<0x2)) ? (0xF <<  8) : 0) |   \
            (((mask) & (1<<0x3)) ? (0xF << 12) : 0) |   \
            (((mask) & (1<<0x4)) ? (0xF << 16) : 0) |   \
            (((mask) & (1<<0x5)) ? (0xF << 20) : 0) |   \
            (((mask) & (1<<0x6)) ? (0xF << 24) : 0) |   \
            (((mask) & (1<<0x7)) ? (0xF << 28) : 0);    \
        if (!__builtin_constant_p(res)) {               \
            _error_not_constant();                      \
        }                                               \
        res;                                            \
    })

// RCC

typedef struct {
    volatile uint32_t cr;           // (RCC_CR)         Clock control register
    volatile uint32_t icscr;        // (RCC_ICSCR)      Internal clock source calibration register
    volatile uint32_t cfgr;         // (RCC_CFGR)       Clock configuration register
    volatile uint32_t _reserved0;   // Reserved
    volatile uint32_t _reserved1;   // Reserved
    volatile uint32_t crrcr;        // (RCC_CRRCR)      Clock recovery RC register
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
    volatile uint32_t csr1;         // (RCC_CSR1)       Control/status register 1
    volatile uint32_t csr2;         // (RCC_CSR2)       Control/status register 2
} rcc_t;

static volatile rcc_t* const rcc = ((rcc_t*)(0x40021000));

typedef enum {
    rcc_clk_gpio_a  = (offsetof(rcc_t, ioprstr)  << 16) | (offsetof(rcc_t, iopenr)  << 8) | 0x00,
    rcc_clk_gpio_b  = (offsetof(rcc_t, ioprstr)  << 16) | (offsetof(rcc_t, iopenr)  << 8) | 0x01,
    rcc_clk_gpio_c  = (offsetof(rcc_t, ioprstr)  << 16) | (offsetof(rcc_t, iopenr)  << 8) | 0x02,
    rcc_clk_gpio_d  = (offsetof(rcc_t, ioprstr)  << 16) | (offsetof(rcc_t, iopenr)  << 8) | 0x03,
    rcc_clk_gpio_f  = (offsetof(rcc_t, ioprstr)  << 16) | (offsetof(rcc_t, iopenr)  << 8) | 0x05,
    rcc_clk_usart_1 = (offsetof(rcc_t, apbrstr2) << 16) | (offsetof(rcc_t, apbenr2) << 8) | 0x0E,
    rcc_clk_usart_2 = (offsetof(rcc_t, apbrstr1) << 16) | (offsetof(rcc_t, apbenr1) << 8) | 0x11,
    rcc_clk_usart_3 = (offsetof(rcc_t, apbrstr1) << 16) | (offsetof(rcc_t, apbenr1) << 8) | 0x12,
    rcc_clk_usart_4 = (offsetof(rcc_t, apbrstr1) << 16) | (offsetof(rcc_t, apbenr1) << 8) | 0x13,
} rcc_clk_t;

static inline void rcc_clk_enable(rcc_clk_t clk) {
    *(volatile uint32_t*)((uint8_t*)rcc + ((clk >>  8) & 0xFF)) |= 1 << (clk & 0xFF);
}

static inline void rcc_clk_disable(rcc_clk_t clk) {
    *(volatile uint32_t*)((uint8_t*)rcc + ((clk >> 16) & 0xFF)) |= 1 << (clk & 0xFF);
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

typedef enum {
    gpio_pull_none          = 0x00000000,
    gpio_pull_up            = 0x55555555,
    gpio_pull_down          = 0xAAAAAAAA,
} gpio_pull_t;

typedef enum {
    gpio_af_0               = 0x00000000,
    gpio_af_1               = 0x11111111,
    gpio_af_2               = 0x22222222,
    gpio_af_3               = 0x33333333,
    gpio_af_4               = 0x44444444,
    gpio_af_5               = 0x55555555,
    gpio_af_6               = 0x66666666,
    gpio_af_7               = 0x77777777,
} gpio_af_t;

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
    const uint32_t pins2 = _const_mask_x2(pins);

    port->otyper  = (port->otyper  & ~pins ) | (pins  & type);
    port->ospeedr = (port->ospeedr & ~pins2) | (pins2 & speed);
    port->moder   = (port->moder   & ~pins2) | (pins2 & gpio_mode_output);
}

static inline void gpio_setup_input(gpio_t* port, gpio_pull_t pull, gpio_pin_t pins) {
    const uint32_t pins2  = _const_mask_x2(pins);

    port->pupdr = (port->pupdr & ~pins2) | (pins2 & pull);
    port->moder = (port->moder & ~pins2) | (pins2 & gpio_mode_input);
}

static inline void gpio_setup_alt_func(gpio_t* port, gpio_af_t af, gpio_pull_t pull, gpio_output_type_t type, gpio_speed_t speed, gpio_pin_t pins) {
    const uint32_t pins2  = _const_mask_x2(pins);
    const uint32_t pins4l = _const_mask_x4(pins);
    const uint32_t pins4h = _const_mask_x4(pins >> 8);

    port->otyper  = (port->otyper  & ~pins ) | (pins  & type);
    port->ospeedr = (port->ospeedr & ~pins2) | (pins2 & speed);
    port->moder   = (port->moder   & ~pins2) | (pins2 & gpio_mode_af);
    port->pupdr   = (port->pupdr   & ~pins2) | (pins2 & pull);

    if (pins4l) {
        port->afrl = (port->afrl & ~pins4l) | (af & pins4l);
    }
    if (pins4h) {
        port->afrh = (port->afrh & ~pins4h) | (af & pins4h);
    }
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

// USART

typedef struct {
    volatile uint32_t cr1;          // (USART_CR1)   USART control register 1
    volatile uint32_t cr2;          // (USART_CR2)   USART control register 2
    volatile uint32_t cr3;          // (USART_CR3)   USART control register 3
    volatile uint32_t brr;          // (USART_BRR)   USART baud rate register
    volatile uint32_t gtpr;         // (USART_GRPR)  USART guard time and prescaler register
    volatile uint32_t rtor;         // (USART_RTOR)  USART receiver timeout register
    volatile uint32_t rqr;          // (USART_RQR)   USART request register
    volatile uint32_t isr;          // (USART_ISR)   USART interrupt and status register
    volatile uint32_t icr;          // (USART_ICR)   USART interrupt flag clear register
    volatile uint32_t rdr;          // (USART_RDR)   USART receive data register
    volatile uint32_t tdr;          // (USART_TDR)   USART transmit data register
    volatile uint32_t presc;        // (USART_PRESC) USART prescaler register
} usart_t;

typedef enum {
    usart_databits_7 = 0x01000000,
    usart_databits_8 = 0x00000000,
    usart_databits_9 = 0x00001000,
} usart_databits_t;

typedef enum {
    usart_parity_none = 0x00000000,
    usart_parity_even = 0x00000400,
    usart_parity_odd  = 0x00000600,
} usart_parity_t;

typedef enum {
    usart_stopbits_0_5 = 0x00001000,
    usart_stopbits_1   = 0x00000000,
    usart_stopbits_1_5 = 0x00003000,
    usart_stopbits_2   = 0x00002000,
} usart_stopbits_t;

typedef enum {
    usart_mode_rx = 0x00000004,
    usart_mode_tx = 0x00000008,
} usart_mode_t;

typedef enum {
    usart_flowcontrol_none = 0x00000000,
    usart_flowcontrol_rts  = 0x00000100,
    usart_flowcontrol_cts  = 0x00000200,
} usart_flowcontrol_t;

typedef struct {
    uint32_t baud;
    usart_databits_t databits;
    usart_parity_t parity;
    usart_stopbits_t stopbits;
    usart_mode_t mode;
    usart_flowcontrol_t flowcontrol;
} usart_config_t;

static usart_t* const usart_1 = (usart_t*)0x40013800;
static usart_t* const usart_2 = (usart_t*)0x40004400;

static inline void usart_enable(usart_t* usart, uint32_t apb_clk, usart_config_t config) {
    const uint32_t usart_cr1_ue = 0x00000001;

    const uint64_t inv_baud_q32 = (4294967296ull + (config.baud) / 2) / (config.baud);
    const uint32_t brr = (uint32_t)((apb_clk * inv_baud_q32 + 0x80000000) >> 32);

    usart->brr = brr;
    usart->cr3 = config.flowcontrol;
    usart->cr2 = config.stopbits;
    usart->cr1 = config.databits | config.parity | config.mode | usart_cr1_ue;
}

static inline void usart_disable(usart_t* usart) {
    usart->cr1 = 0;
}

static inline void usart_send(usart_t* usart, uint16_t data) {
    const uint32_t usart_isr_txe = 0x00000080;
    while (!(usart->isr & usart_isr_txe)) { }
    usart->tdr = data;
}

static inline uint16_t usart_recv(usart_t* usart) {
    const uint32_t usart_isr_rxnf = 0x00000020;
    while (!(usart->isr & usart_isr_rxnf)) { }
    return usart->rdr;
}

#undef _const_mask_x2
#undef _const_mask_x4

#endif


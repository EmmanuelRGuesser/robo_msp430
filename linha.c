/*
 * linha.c
 *
 *  Created on: 21 de nov de 2022
 *      Author: EmmanuelRG
 */

/* System includes */
#include <msp430.h>
#include <stdint.h>

/* Project includes */
#include "gpio.h"
#include "bits.h"
#include "linha.h"

#define BUTTON_PORT_1 P3
#define BUTTON_1 BIT0

#define BUTTON_PORT_2 P5
#define BUTTON_2 BIT4

#define BUTTON_SAMPLES (12)

volatile uint8_t s_esquerda, s_direita;

void init_S_linha(){

    /* Configura botões */
    /* BUTTON_PORT totalmente como entrada */
    PORT_DIR(BUTTON_PORT_1) = 0x00;
    PORT_DIR(BUTTON_PORT_2) = 0x00;

    /* Configura Timer */
    TB0CTL = TBSSEL_2 | MC_1;

    /* IRQ por comparação entre contagem e comparador 0 */
    TB0CCTL0 = CCIE;
    /* Valor de comparação é 5000 */
    TB0CCR0 = 50000;
}

/* Retorna o valor do sensor esquerdo*/
uint8_t read_l_ESQ(){
    return s_esquerda;
}

/* Retorna o valor do sensor direito*/
uint8_t read_l_DIR(){
    return s_direita;
}


/* ISR0 do Timer B: executado no evento de comparação  comparador 0 (TBCCR0)
 *
 * Utilizado para o debouncer por amostragem: faz a verificação de botão
 * periodicamente e caso ativo escreve 1.
 *
 * */
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER0_B0_VECTOR
__interrupt void TIMER0_B0_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER0_B0_VECTOR))) Timer_B (void)
#else
#error Compiler not supported!
#endif
{

    static uint8_t counter_1 = BUTTON_SAMPLES, counter_2 = BUTTON_SAMPLES;

    /* Se botão_1 apertado: borda de descida */
    if (!TST_BIT(PORT_IN(BUTTON_PORT_1), BUTTON_1))
    {
        /* Se contagem = 0, debounce terminado */
        if (!(--counter_1))
        {
            s_esquerda = 1;
        }
    }
    else {
        counter_1 = BUTTON_SAMPLES;
        s_esquerda = 0;
    }

    /* Se botão_2 apertado: borda de descida */
    if (!TST_BIT(PORT_IN(BUTTON_PORT_2), BUTTON_2))
    {
        /* Se contagem = 0, debounce terminado */
        if (!(--counter_2))
        {
            s_direita = 1;
        }
    }
    else {
        counter_2 = BUTTON_SAMPLES;
        s_direita = 0;
    }
}

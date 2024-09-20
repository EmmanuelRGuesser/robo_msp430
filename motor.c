/*
 * motor.c
 *
 *  Created on: 27 de out de 2022
 *      Author: EmmanuelRG
 */


#include <msp430.h>
#include <stdint.h>
#include "bits.h"
#include "motor.h"

/**
 * @brief  Configura temporizador B com contagem up e down.
 *
 * @param  none
 *
 * @retval none
 */

void init_motor(){

    TB3CCR0 = 12000;

    TB3CCTL1 = OUTMOD_2;
    TB3CCTL2 = OUTMOD_2;
    TB3CCTL3 = OUTMOD_2;
    TB3CCTL4 = OUTMOD_2;


     /* Configuração da fonte do clock do timer */

    TB3CTL = TBSSEL_2 | MC_3;

    /* Ligação físicas do timer nas portas */

    P6DIR = MOTOR_1 | MOTOR_1N | MOTOR_2 | MOTOR_2N;
    P6OUT  &= ~(MOTOR_1 | MOTOR_1N | MOTOR_2 | MOTOR_2N);
}

/**
 * @brief  Controla o sinal pwm dos motores,
 *         deligando ou ligando as saidas dependendo do direcao pedida
 *
 * @param  Direção
 *
 * @retval none
 */

void motor(dir_t estado, uint16_t PWM){

    PWM_M1  = PWM;
    PWM_M1N = PWM;
    PWM_M2  = PWM;
    PWM_M2N = PWM;

    switch(estado){

    case PARADO:
        P6SEL0 &= ~(MOTOR_1 | MOTOR_1N | MOTOR_2 | MOTOR_2N);
        P6OUT  &= ~(MOTOR_1 | MOTOR_1N | MOTOR_2 | MOTOR_2N);
        break;

    case FRENTE:
        P6SEL0 &= ~(MOTOR_1N | MOTOR_2N);
        P6OUT  &= ~(MOTOR_1N | MOTOR_2N);
        P6SEL0 |= (MOTOR_1 | MOTOR_2);
        break;

    case RE:
        P6SEL0 &= ~(MOTOR_1 | MOTOR_2);
        P6OUT  &= ~(MOTOR_1 | MOTOR_2);
        P6SEL0 |= (MOTOR_1N | MOTOR_2N);
        break;

    case ESQUERDA:
        P6SEL0 &= ~(MOTOR_1 | MOTOR_2N);
        P6OUT  &= ~(MOTOR_1 | MOTOR_2N);
        P6SEL0 |= (MOTOR_1N | MOTOR_2);
        break;

    case DIREITA:
        P6SEL0 &= ~(MOTOR_1N | MOTOR_2);
        P6OUT  &= ~(MOTOR_1N | MOTOR_2);
        P6SEL0 |= (MOTOR_1 | MOTOR_2N);
        break;

    default:
        break;
    }
}

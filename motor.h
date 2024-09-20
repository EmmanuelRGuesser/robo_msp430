/*
 * motor.h
 *
 *  Created on: 27 de out de 2022
 *      Author: EmmanuelRG
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include <stdint.h>

#define MOTOR_1  BIT0
#define MOTOR_1N BIT1
#define MOTOR_2  BIT2
#define MOTOR_2N BIT3

#define PWM_M1  TB3CCR1
#define PWM_M1N TB3CCR2
#define PWM_M2  TB3CCR3
#define PWM_M2N TB3CCR4

typedef enum Direcoes{
    PARADO, FRENTE, RE, DIREITA, ESQUERDA
}dir_t;

/*
 * @brief  Configura temporizador B3 com contagem up e down.
 *
 * @param  none
 *
 * @retval none
 */

void init_motor();


/*
 * @brief  Controla o PWM.
 *
 * @param  Direção, Velocidade.
 *
 * @retval none
 */

void motor(dir_t estado, uint16_t PWM);


#endif /* MOTOR_H_ */

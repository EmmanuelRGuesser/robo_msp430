/*
 * linha.h
 *
 *  Created on: 21 de nov de 2022
 *      Author: EmmanuelRG
 */

#ifndef LINHA_H_
#define LINHA_H_

/* Inicializa os botoes */
void init_S_linha();

/* Retorna o valor do sensor esquerdo*/
uint8_t read_l_ESQ();

/* Retorna o valor do sensor direito*/
uint8_t read_l_DIR();

#endif /* LINHA_H_ */

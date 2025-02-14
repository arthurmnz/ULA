/*S� � necess�rio mexer nesse arquivo se for implementar as fun��es de Ponto Flutuante*/
#ifndef  ULA_H
#define  ULA_H

#include "bit.h"
#include <stdint.h> //biblioteca para definir tipos inteiros

//uint8_t - Inteiro sem sinal de 8 bits
//uint16_t - Inteiro sem sinal de 16 bits

//int8_t - Inteiro com sinal de 8 bits
//int16_t - Inteiro com sinal de 16 bits

void static somadorCompleto (uint8_t A, uint8_t B, uint8_t Cin, uint8_t * co, uint8_t * s);
void static somador8bits( uint8_t A, uint8_t B, uint8_t cin,  uint8_t * co, uint8_t * s);
void static complementador(uint8_t *A);

//Opera��es com n�meros Inteiros de 8 bits com sinal (-128 at� 127)
void ULA_ADD(int8_t *A, int8_t * B, int8_t * overflow);
void ULA_SUB(int8_t *A, int8_t * B, int8_t * overflow);
void ULA_MUL(int8_t *A, int8_t *Q, int8_t * M, int8_t * overflow);
void ULA_DIV(int8_t *A, int8_t *Q, int8_t * M, int8_t * overflow);

//Bonus de 1,0 ponto na AP1 se fizer pelo menos uma opera��o aritm�tica em Ponto Flutuante
//Opera��es em Ponto Flutuante de 32 bits Sinal(1bit); Expoente Polarizado(8bits); Significando(23bits)
//OBS: Considerar que a ULA s� usa registradores de 8 bits. Pontato a ULA vai precisar de 4 registradores de 8 bits
//Para implementar, basta descomentar a linha e codificar no arquivo ULA.c
//void ULA_ADD_PF(float *A, float * B, int8_t * overflow, int8_t * underflow);
//void ULA_SUB_PF(float *A, float * B, int8_t * overflow, int8_t * underflow);
//void ULA_MUL_PF(float *A, float * B, int8_t * overflow, int8_t * underflow);
//void ULA_DIV_PF(float *A, float * B, int8_t * overflow, int8_t * underflow);

#endif

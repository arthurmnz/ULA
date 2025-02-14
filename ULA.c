#include "ULA.h"

//Somador Baseado no livro Willian Stallings 10ed, capitulo 10, pag. 334
static void somadorCompleto (uint8_t A, uint8_t B, uint8_t Cin, uint8_t * co, uint8_t * s){
	*co = (A&B) | (A&Cin) | (B&Cin);
	//*s = A ^ B ^ Cin;
	*s = (~A & ~B & Cin) | (~A & B & ~Cin) | (A & B & Cin) | (A & ~B & ~Cin);	
}

//O somador binario da ULA trata os dois numeros como inteiros sem sinal.
//Entradas: Registrados A, B e cin(CarryIn), Saida: s(soma) e co(CarryOut)
static void somador8bits(uint8_t A, uint8_t B, uint8_t cin, uint8_t * co, uint8_t * s){
	*co = cin;
	uint8_t soma;
	for (int i=0;i<8;i++){
		somadorCompleto(bit_get(A,0),bit_get(B,0), *co, co,&soma);
		A = A>>1;//deslocando os bits para direita a cada interacao
		B = B>>1;
		if(soma==1)bit_set(*s,i);
		else bit_clr(*s,i);
	}
}

//Realiza o complemento de 2 do Registrador A e grava em A
static void complementador(uint8_t *A){
	*A = ~(*A) + 1;
}

//Adicao de A e B e grava resultado em A
void ULA_ADD(int8_t *A, int8_t * B, int8_t * overflow) {
    uint8_t a = (uint8_t)(*A);
    uint8_t b = (uint8_t)(*B);
    uint8_t co;
    uint8_t s;

    somador8bits(a, b, 0, &co, &s);

    int8_t a_sign = (*A) >> 7;
    int8_t b_sign = (*B) >> 7;
    int8_t s_sign = (int8_t)s >> 7;

    *overflow = (a_sign == b_sign) && (s_sign != a_sign) ? 1 : 0;

    *A = (int8_t)s;
}

//Subtracao de A e B e grava resultado em A
void ULA_SUB(int8_t *A, int8_t * B, int8_t * overflow) {
    uint8_t a = (uint8_t)(*A);
    uint8_t b = (uint8_t)(*B);

    complementador(&b); 

    uint8_t co;
    uint8_t s;

    somador8bits(a, b, 0, &co, &s);

    int8_t a_sign = (*A) >> 7;
    int8_t minus_b_sign = (int8_t)b >> 7; 
    int8_t s_sign = (int8_t)s >> 7;

    *overflow = (a_sign == minus_b_sign) && (s_sign != a_sign) ? 1 : 0;

    *A = (int8_t)s;
}

//Multiplicacao de Q(8bits) com M(8bits) gera resultado de 16bits que esta em A(8bits) e Q(8bits)
void ULA_MUL(int8_t *A, int8_t *Q, int8_t *M, int8_t *overflow) {
    int8_t A_reg = 0;        
    int8_t Q_reg = *Q;       
    int8_t M_reg = *M;       
    int8_t Q_menos_1 = 0;    
    int8_t temp_overflow;


    for (int i = 0; i < 8; i++) {
        int8_t Q0 = (int8_t)(Q_reg & 1);

        if (Q0 == 1 && Q_menos_1 == 0) {
            ULA_SUB(&A_reg, &M_reg, &temp_overflow);
        }
        else if (Q0 == 0 && Q_menos_1 == 1) {
            ULA_ADD(&A_reg, &M_reg, &temp_overflow);
        }

        int16_t combo = ((int16_t)A_reg << 8) | (uint8_t)Q_reg;

        combo >>= 1;

        Q_menos_1 = Q0;

        A_reg = (int8_t)(combo >> 8);
        Q_reg = (int8_t)(combo & 0xFF);
    }

    *A = A_reg;
    *Q = Q_reg;
    *overflow = 0; 
}



//Divisao com sinal de Q(Dividendo de 8bits) por M(Divisor de 8bits) com Quociente em Q(8bits) e Resto em A(8bits)
void ULA_DIV(int8_t *A, int8_t *Q, int8_t *M, int8_t *overflow) {
    int8_t divisor = *M;
    if (divisor == 0) {
        *overflow = 1;
        return;
    }

    int8_t dividend = *Q;
    if (dividend == -128 && divisor == -1) {
        *overflow = 1;
        return;
    }

    int sign_dividend = (dividend < 0) ? -1 : 1;
    int sign_divisor = (divisor < 0) ? -1 : 1;

    uint8_t abs_dividend = (dividend == -128) ? 128 : (uint8_t)abs(dividend);
    uint8_t abs_divisor = (uint8_t)abs(divisor);

    uint8_t a = 0;
    uint8_t q = abs_dividend;

    for (int i = 0; i < 8; i++) {
        a = (a << 1) | (q >> 7);
        q <<= 1;

        if (a >= abs_divisor) {
            a -= abs_divisor;
            q |= 1;
        }
    }

    int8_t quotient = q;
    if (sign_dividend != sign_divisor) {
        quotient = -quotient;
    }

    int8_t remainder = a;
    if (sign_dividend < 0) {
        remainder = -remainder;
    }

    *A = remainder;
    *Q = quotient;
    *overflow = 0;
}

//Descomente as fun��es caso deseja implementar as fun��es de Ponto Flutuante
//Baseado no livro Willian Stallings 10ed, cap�tulo 10, pag. 298
//void ULA_ADD_PF(float *A, float * B, int8_t * overflow, int8_t * underflow){}
//void ULA_SUB_PF(float *A, float * B, int8_t * overflow, int8_t * underflow){}
//void ULA_MUL_PF(float *A, float * B, int8_t * overflow, int8_t * underflow){}
//void ULA_DIV_PF(float *A, float * B, int8_t * overflow, int8_t * underflow){}

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

    complementador(&b); // Computa o complemento de dois de B (ou seja, -B)

    uint8_t co;
    uint8_t s;

    somador8bits(a, b, 0, &co, &s);

    int8_t a_sign = (*A) >> 7;
    int8_t minus_b_sign = (int8_t)b >> 7; // O sinal de -B após o complemento
    int8_t s_sign = (int8_t)s >> 7;

    *overflow = (a_sign == minus_b_sign) && (s_sign != a_sign) ? 1 : 0;

    *A = (int8_t)s;
}

//Multiplicacao de Q(8bits) com M(8bits) gera resultado de 16bits que esta em A(8bits) e Q(8bits)
void ULA_MUL(int8_t *A, int8_t *Q, int8_t *M, int8_t *overflow) {
}

//Divisao com sinal de Q(Dividendo de 8bits) por M(Divisor de 8bits) com Quociente em Q(8bits) e Resto em A(8bits)
void ULA_DIV(int8_t *A, int8_t *Q, int8_t * M, int8_t * overflow){
	//Baseado no livro Willian Stallings 10ed, capitulo 10, pag. 296	
}

//Descomente as fun��es caso deseja implementar as fun��es de Ponto Flutuante
//Baseado no livro Willian Stallings 10ed, cap�tulo 10, pag. 298
//void ULA_ADD_PF(float *A, float * B, int8_t * overflow, int8_t * underflow){}
//void ULA_SUB_PF(float *A, float * B, int8_t * overflow, int8_t * underflow){}
//void ULA_MUL_PF(float *A, float * B, int8_t * overflow, int8_t * underflow){}
//void ULA_DIV_PF(float *A, float * B, int8_t * overflow, int8_t * underflow){}

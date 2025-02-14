//Trabalho da Disciplina de RUS0005 - ARQUITETURA DE COMPUTADORES
//UFC - Campus Russas
//Professor Autor: Reuber Regis de Melo
//OBS: Esse arquivo n�o precisa ser editado, somente deve ser editado os arquivos ULA.c e ULA.h
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> //biblioteca para definir tipos inteiros
#include "ULA.h"
#include "ULA.c"

#define MAX_LINHAS 100 // Defina um limite m�ximo de linhas 

void print8Bits( int8_t *A){
	printf("(%d)_10\t= (",*A);
	for(int i=0;i<8;i++){
		printf("%d",bit_get(*A,7-i));
	}
	printf(")_2");	
}

void print16Bits( int16_t *A){
	printf("(%d)_10\t= (",*A);
	for(int i=0;i<16;i++){
		printf("%d",bit_get(*A,15-i));
	}
	printf(")_2\n");
}


int main(int argc, char *argv[]) {
	/*Cabe�alho*/
	printf("\t\t\t\t==========================================\n");
    printf("\t\t\t\t SIMULADOR DE ULA - v0.1  by Prof. Reuber      \n");
    printf("\t\t\t\t==========================================\n");
	
	/*---------------------------------*/
	//Leitura de Arquivo com os Operandos
	FILE *arquivo = fopen("dados.txt", "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }
    int8_t matriz[MAX_LINHAS][2]; // Matriz est�tica
    int linhas = 0;                  // Contador de linhas
    // Lendo os pares de n�meros do arquivo at� EOF
    while (linhas < MAX_LINHAS && fscanf(arquivo, "%d %d", &matriz[linhas][0], &matriz[linhas][1]) == 2) {
        linhas++;
    }
    fclose(arquivo);
    //Fim da Leitura do Arquivo com Operandos
	/*----------------------------*/
	
	/*-----------------------------*/
	//Chama a ULA para realizar as 4 opera��es e imprime os resultados
	for(int i=0;i<linhas;i++){	
		int8_t OpA = matriz[i][0], OpB=matriz[i][1], ovf, regA; //Operandos de 8 bits com sinal (-127 a 128)
		printf("----------------------------------------------\n");
		/*--ADD--*/
		print8Bits(&OpA);
		printf("\t");
		print8Bits(&OpB);	
		ULA_ADD(&OpA,&OpB,&ovf);			
		printf("\tADD: REG A: %d\t\tOverflow: %d\t",OpA,ovf);
		printf("\n");
		/*--SUB--*/
		OpA = matriz[i][0], OpB=matriz[i][1];
		print8Bits(&OpA);
		printf("\t");
		print8Bits(&OpB);	
		ULA_SUB(&OpA,&OpB,&ovf);			
		printf("\tSUB: REG A: %d\t\tOverflow: %d\t",OpA,ovf);
		printf("\n");
		/*--MUL--*/
		OpA = matriz[i][0], OpB=matriz[i][1];
		print8Bits(&OpA);
		printf("\t");
		print8Bits(&OpB);	
		ULA_MUL(&regA,&OpA,&OpB,&ovf);			
		printf("\tMUL: REG A: %d\tREG Q:%d\tAQ: %d\tOverflow: %d\t",regA, OpA,(int16_t) (((regA & 0x00FF) << 8) | (OpA & 0x00FF)),ovf);
		printf("\n");
		/*--DIV--*/
		OpA = matriz[i][0], OpB=matriz[i][1];
		print8Bits(&OpA);
		printf("\t");
		print8Bits(&OpB);
		ULA_DIV(&regA,&OpA,&OpB,&ovf);			
		printf("\tDIV: REG Q: %d\tREG R:%d\tOverflow: %d\t",OpA, regA,ovf);
		printf("\n");
			
	}
	//Fim das Opera��es da ULA e impress�o dos resultados
	/*-----------------------------*/
	system("pause");
	return 0;
}

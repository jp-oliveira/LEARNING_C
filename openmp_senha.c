#include <stdio.h>
#include <omp.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

char char_aleatorio(int);
char verificasenha(char []);

int main(void){
    int iterasenhas = 0;    //iterar o while principal

    printf("\nQuantas senhas voce quer adivinhar?\n");
    int quantidadesenhas;
    scanf("%d",&quantidadesenhas);

    printf("\nQual tamanho cada senha tera?\n");
    int limite;
    scanf("%d",&limite);

    struct timeval comeco_paralelo, fim_paralelo;
	
    printf("Começando a adivinhação cautelosa.\n");
    srand(time(NULL));
    gettimeofday(&comeco_paralelo, NULL);

	int cont = 0;    //para usar no caso de cautelosa, ir iterando em caso de acerto de caracter 
	int validou = 0; //flag para se certificar que a senha tem todos os tipos de caracter.
	char senha[limite];
	char copia[limite];
	
	#pragma omp parallel /*shared(a,b,c)*/ private(cont, validou, senha, copia)
	{
		while(iterasenhas != quantidadesenhas){
			
			// VERIFICA SE A SENHA TEM CARACTER MAIUSCULO, MINUSCULO, NUMERO E SIMBOLO
			while(validou != 1){
				
				for(int i = 0; i < limite; i++){
					senha[i] = char_aleatorio(rand() % 4);
					//printf("%c",senha[i]);
				}
				//printf("\nlimite = %d, tamanho da senha eh %d\n",limite,strlen(senha));
				
				if (verificasenha(senha) == 's'){
					printf("\nA senha gerada foi: %s Essa senha eh valida!\n",senha);
					validou = 1;
				}
				else{
					printf("\nA senha gerada foi: %s \nEssa senha nao eh valida! Estamos gerando outra.\n",senha);
				}
			}
			
			while(cont != limite){
				char chute;
				while(chute != senha[cont]){
					chute = char_aleatorio(rand() % 4);
					//printf("%c",chute); // para ver ele acertando
				}
				copia[cont] = chute;
				cont++;
			}
			printf("\nAcertou a senha!\n");
			cont = 0;
			validou = 0;
			iterasenhas++;
		}
	}
    gettimeofday(&fim_paralelo, NULL);
    
    printf("\nO Tempo gasto na execucao do programa paralelo: %fs\n\n",(double)(fim_paralelo.tv_usec - comeco_paralelo.tv_usec)/1000000 + (double)(fim_paralelo.tv_sec - comeco_paralelo.tv_sec));
	
    return(0);
}

char verificasenha(char senha[]){
    int maiuscula = 0;   //para saber se tem um maiusculo, um minusculo e um caracter especial;
    int numero = 0;
    int simbolo = 0;
    int minuscula = 0;
    char copia[strlen(senha)];
    strcpy(copia,senha);

    for(int i = 0; i < strlen(senha); i++){
        if('A' <= copia[i] && copia[i] <= 'Z'){
            maiuscula = 1;
        }
        else if('0' <= copia[i] && copia[i] <= '9'){
            numero = 1;
        }
        else if('a' <= copia[i] && copia[i] <= 'z'){
            minuscula = 1;
        }
        else{
            simbolo = 1;   
        }
    }
    
    if(maiuscula + minuscula + numero + simbolo == 4) 
        return 's';
    else
        return 'n';
}

char char_aleatorio(int argumento){
	char maiusculo[] = "ABCDEFGHIJKLMNOPQRSTUWVXYZ";
    char minusculo[] = "abcdefghijklmnopqrstuwvxyz";
    char numero[]    = "0123456789";
    char simbolo[]   = "!@#$&*";
    char letra;
    int sorteio;

    if (argumento == 0){  // para maiusculo
        sorteio = rand() % 27;
	    letra = maiusculo[sorteio];
	}
    else if (argumento == 1){  // para maiusculo
        sorteio = rand() % 27;
	    letra = minusculo[sorteio];
	}
    else if (argumento == 2){  // para maiusculo
        sorteio = rand() % 10;
	    letra = numero[sorteio];
	}
    else if (argumento == 3){  // para maiusculo
        sorteio = rand() % 6;
	    letra = simbolo[sorteio];
	}
    return letra;	
}
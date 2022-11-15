#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define row 10 //tamanho maximo da linha
#define mask16 0x800 //mascara para um inteiro de 32 bits.
#define LSIZ 128  // tamanho maximo da linha para o arquivo.
#define MAXPALAVRAS 200  //quantidade maxima de linhas para o arquivo.

//funcao para transformar uma string que contem numeros em um numero decimal.
int extract_nums(char string[]) { 
	
	int chars=0; //variável onde ficam armazenados os dígitos extraídos

	for(int i=0; string[i]!='\0'; i++) {
		
		if(isdigit(string[i])) {
			chars += (int)(string[i])-'0';
			chars *= 10;
		}
	}
	chars /= 10;
	return chars;
}

int main(){
	
	printf("Bem vindo(a) a simulacao de assembly em c! Comece o programa! \n");
	char line[MAXPALAVRAS][LSIZ]; //para ler cada linha do arquivo.
	char fname[255];    		  //para ler o nome do arquivo.
    FILE *fptr = NULL; 			  //ponteiro para o arquivo lido.
	FILE *arquivo = NULL; 		  //ponteiro para escrever um arquivo.
	arquivo = fopen("arquivo_teste_assembly.txt", "a"); //aonde será escrita
    int inc = 0;
	
	printf("\nEscreva o diretorio e nome do seu arquivo: \n");
    scanf("%s", fname);
	fptr = fopen(fname, "r");
	
	if (fptr == NULL){	
		printf("Erro ao abrir arquivo!\n");
        exit(1);
    }
	volta:
	while(fgets(line[inc], LSIZ, fptr)){
		
		fprintf(arquivo, "\n%s", line[inc]);
	
		char copia[row] = ""; //copia CONTERÁ OS CARACTERES DA INSTRUÇÃO QUE SÃO LETRAS.
		char input[row] = ""; //input CONTERÁ OS CARACTERES DA INSTRUÇÃO QUE SÃO NÚMEROS.
		int numero = 0;
		int k = 0; //indice para o vetor copia
		int w = 0; //indice para o vetor input
		
		for(int j = 0; j < strlen(line[inc]); j++ ){
			if (isalpha(line[inc][j])){
				copia[w] = line[inc][j];
				w++;
			}
			else if(isdigit(line[inc][j])){
				input[k] = line[inc][j];
				k++;
			}
		}
		for (int k = 0; k < row; k++)
			copia[k] = toupper(copia[k]); //garante entrada em maiusculo.
		
		numero = extract_nums(input); //input era string. agora numero é inteiro.
		int bin[8]; //vetor para armazenar o numero de decimal para binario.
		
		if (numero < 256){
			int aux;
			for (aux = 7; aux >= 0; aux--) {
				if (numero % 2 == 0)
					bin[aux] = 0;
				else
					bin[aux] = 1;
				numero = numero / 2;
			}
		}
		
		else if (numero >=4096){
				printf("Numero invalido. Entre com um numero menor do que 4096!\n");
				goto volta;
		}

		if (strcmp(copia,"LODD") == 0){
			
			fprintf(arquivo,"\n%s","0000");
			if (numero < 256){
				fprintf(arquivo,"%s","0000");
				for (int i = 0; i < 8; i++)
					fprintf(arquivo,"%d", bin[i]);
			}
			else{
				int aux = mask16;
				for(int i = 11; i >= 0; i--){
					if ((numero & aux) != 0) 
						fprintf(arquivo,"%d",1);
					else 
						fprintf(arquivo,"%d",0);
		    
					aux = aux >> 1;
				}
			}
			fprintf(arquivo,"\n");
		}

		else if (strcmp(copia,"STOD") == 0){
			fprintf(arquivo,"\n%s","0001");
			if (numero < 256){
				fprintf(arquivo,"%s","0000");
				for (int i = 0; i < 8; i++)
					fprintf(arquivo,"%d", bin[i]);
			}
			else{
				int aux = mask16;
				for(int i = 11; i >= 0; i--){
					if ((numero & aux) != 0) 
						fprintf(arquivo,"%d",1);
					else 
						fprintf(arquivo,"%d",0);
		    
					aux = aux >> 1;
				}
			}
			fprintf(arquivo,"\n");
		}
		
		else if (strcmp(copia,"ADDD") == 0){
			fprintf(arquivo,"\n%s","0010");
			if (numero < 256){
				fprintf(arquivo,"%s","0000");
				for (int i = 0; i < 8; i++)
					fprintf(arquivo,"%d", bin[i]);
				fprintf(arquivo,"\n");
			}
			else{
				int aux = mask16;
				for(int i = 11; i >= 0; i--){
					if ((numero & aux) != 0) 
						fprintf(arquivo,"%d",1);
					else 
						fprintf(arquivo,"%d",0);
		    
					aux = aux >> 1;
				}
			}
			fprintf(arquivo,"\n");
		}
		
		else if (strcmp(copia,"SUBD") == 0){
			fprintf(arquivo,"\n%s","0011");
			if (numero < 256){
				fprintf(arquivo,"%s","0000");
				for (int i = 0; i < 8; i++)
					fprintf(arquivo,"%d", bin[i]);
				fprintf(arquivo,"\n");
			}
			else{
				int aux = mask16;
				for(int i = 11; i >= 0; i--){
					if ((numero & aux) != 0) 
						fprintf(arquivo,"%d",1);
					else 
						fprintf(arquivo,"%d",0);
		    
					aux = aux >> 1;
				}
			}
			fprintf(arquivo,"\n");
		}
		
		else if (strcmp(copia,"JPOS") == 0){
			fprintf(arquivo,"\n%s","0100");
			if (numero < 256){
				fprintf(arquivo,"%s","0000");
				for (int i = 0; i < 8; i++)
					fprintf(arquivo,"%d", bin[i]);
				fprintf(arquivo,"\n");
			}
			else{
				int aux = mask16;
				for(int i = 11; i >= 0; i--){
					if ((numero & aux) != 0) 
						fprintf(arquivo,"%d",1);
					else 
						fprintf(arquivo,"%d",0);
		    
					aux = aux >> 1;
				}
			}
			fprintf(arquivo,"\n");
		}
		
		else if (strcmp(copia,"JZER") == 0){
			fprintf(arquivo,"\n%s","0101");
			if (numero < 256){
				fprintf(arquivo,"%s","0000");
				for (int i = 0; i < 8; i++)
					fprintf(arquivo,"%d", bin[i]);
				fprintf(arquivo,"\n");
			}
			else{
				int aux = mask16;
				for(int i = 11; i >= 0; i--){
					if ((numero & aux) != 0) 
						fprintf(arquivo,"%d",1);
					else 
						fprintf(arquivo,"%d",0);
		    
					aux = aux >> 1;
				}
			}
			fprintf(arquivo,"\n");
		}
		
		else if (strcmp(copia,"JUMP") == 0){
			fprintf(arquivo,"\n%s","0110");
			if (numero < 256){
				fprintf(arquivo,"%s","0000");
				for (int i = 0; i < 8; i++)
					fprintf(arquivo,"%d", bin[i]);
			}
			else{
				int aux = mask16;
				for(int i = 11; i >= 0; i--){
					if ((numero & aux) != 0) 
						fprintf(arquivo,"%d",1);
					else 
						fprintf(arquivo,"%d",0);
		    
					aux = aux >> 1;
				}
			}
			fprintf(arquivo,"\n");
		}
		
		else if (strcmp(copia,"LOCO") == 0){
			fprintf(arquivo,"\n%s","0111");
			if (numero < 256){
				fprintf(arquivo,"%s","0000");
				for (int i = 0; i < 8; i++)
					fprintf(arquivo,"%d", bin[i]);
			}
			else{
				int aux = mask16;
				for(int i = 11; i >= 0; i--){
					if ((numero & aux) != 0) 
						fprintf(arquivo,"%d",1);
					else 
						fprintf(arquivo,"%d",0);
		    
					aux = aux >> 1;
				}
			}
			fprintf(arquivo,"\n");
		}
		
		else if (strcmp(copia,"LODL") == 0){
			fprintf(arquivo,"\n%s","1000");
			if (numero < 256){
				fprintf(arquivo,"%s","0000");
				for (int i = 0; i < 8; i++)
					fprintf(arquivo,"%d", bin[i]);
			}
			else{
				int aux = mask16;
				for(int i = 11; i >= 0; i--){
					if ((numero & aux) != 0) 
						fprintf(arquivo,"%d",1);
					else 
						fprintf(arquivo,"%d",0);
		    
					aux = aux >> 1;
				}
			}
			fprintf(arquivo,"\n");
		}
		
		else if (strcmp(copia,"STOL") == 0){
			fprintf(arquivo,"\n%s","1001");
			if (numero < 256){
				fprintf(arquivo,"%s","0000");
				for (int i = 0; i < 8; i++)
					fprintf(arquivo,"%d", bin[i]);
			}
			else{
				int aux = mask16;
				for(int i = 11; i >= 0; i--){
					if ((numero & aux) != 0) 
						fprintf(arquivo,"%d",1);
					else 
						fprintf(arquivo,"%d",0);
		    
					aux = aux >> 1;
				}
			}
			fprintf(arquivo,"\n");
		}
		
		else if (strcmp(copia,"ADDL") == 0){
			fprintf(arquivo,"\n%s","1010");
			if (numero < 256){
				fprintf(arquivo,"%s","0000");
				for (int i = 0; i < 8; i++)
					fprintf(arquivo,"%d", bin[i]);
			}
			else{
				int aux = mask16;
				for(int i = 11; i >= 0; i--){
					if ((numero & aux) != 0) 
						fprintf(arquivo,"%d",1);
					else 
						fprintf(arquivo,"%d",0);
		    
					aux = aux >> 1;
				}
			}
			fprintf(arquivo,"\n");
		}
		
		else if (strcmp(copia,"SUBL") == 0){
			fprintf(arquivo,"\n%s","1011");
			if (numero < 256){
				fprintf(arquivo,"%s","0000");
				for (int i = 0; i < 8; i++)
					fprintf(arquivo,"%d", bin[i]);
			}
			else{
				int aux = mask16;
				for(int i = 11; i >= 0; i--){
					if ((numero & aux) != 0) 
						fprintf(arquivo,"%d",1);
					else 
						fprintf(arquivo,"%d",0);
		    
					aux = aux >> 1;
				}
			}
			fprintf(arquivo,"\n");
		}
		
		else if (strcmp(copia,"JNEG") == 0){
			fprintf(arquivo,"\n%s","1100");
			if (numero < 256){
				fprintf(arquivo,"%s","0000");
				for (int i = 0; i < 8; i++)
					fprintf(arquivo,"%d", bin[i]);
			}
			else{
				int aux = mask16;
				for(int i = 11; i >= 0; i--){
					if ((numero & aux) != 0) 
						fprintf(arquivo,"%d",1);
					else 
						fprintf(arquivo,"%d",0);
		    
					aux = aux >> 1;
				}
			}
			fprintf(arquivo,"\n");
		}
		
		else if (strcmp(copia,"JNZE") == 0){
			fprintf(arquivo,"\n%s","1101");
			if (numero < 256){
				fprintf(arquivo,"%s","0000");
				for (int i = 0; i < 8; i++)
					fprintf(arquivo,"%d", bin[i]);
			}
			else{
				int aux = mask16;
				for(int i = 11; i >= 0; i--){
					if ((numero & aux) != 0) 
						fprintf(arquivo,"%d",1);
					else 
						fprintf(arquivo,"%d",0);
		    
					aux = aux >> 1;
				}
			}
			fprintf(arquivo,"\n");
		}
		
		else if (strcmp(copia,"CALL") == 0){
			fprintf(arquivo,"\n%s","1110");
			if (numero < 256){
				fprintf(arquivo,"%s","0000");
				for (int i = 0; i < 8; i++)
					fprintf(arquivo,"%d", bin[i]);
			}
			else{
				int aux = mask16;
				for(int i = 11; i >= 0; i--){
					if ((numero & aux) != 0) 
						fprintf(arquivo,"%d",1);
					else 
						fprintf(arquivo,"%d",0);
		    
					aux = aux >> 1;
				}
			}
			fprintf(arquivo,"\n");
		}
		
		else if (strcmp(copia,"PSHI") == 0){
			fprintf(arquivo,"\n%s\n","1111000000000000");
		}
		
		else if (strcmp(copia,"POPI") == 0){
			fprintf(arquivo,"\n%s\n","1111001000000000");
		}
		
		else if (strcmp(copia,"PUSH") == 0){
			fprintf(arquivo,"\n%s\n","1111010000000000");
		}
		
		else if (strcmp(copia,"POP") == 0){ //ATENÇÃO
			fprintf(arquivo,"\n%s\n","1111011000000000");
		}
		else if (strcmp(copia,"RETN") == 0){
			fprintf(arquivo,"\n%s\n","1111100000000000");
		}
		
		else if (strcmp(copia,"SWAP") == 0){
			fprintf(arquivo,"\n%s\n","1111101000000000");
		}
		
		else if (strcmp(copia,"INSP") == 0){
			fprintf(arquivo,"%s","11111100");
			for (int i = 0; i < 8; i++)
				fprintf(arquivo,"%d", bin[i]);
			fprintf(arquivo,"\n");
		}
		
		else if (strcmp(copia,"DESP") == 0){
			fprintf(arquivo,"\n%s","11111110");
			for (int i = 0; i < 8; i++)
				fprintf(arquivo,"%d", bin[i]);
			fprintf(arquivo,"\n");
		}
		else
			printf("comando invalido. tente outra vez.\n");
		
		inc++;
		fprintf(arquivo,"\n");
	}
	fclose(arquivo);
	printf("Dados gravados com sucesso!");
	
	return 0;
}
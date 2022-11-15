#include <stdio.h>
//#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct listaEncadeada
{
    char *filhaSelecionada;
    struct listaEncadeada *prox;
};

void gerarFilhas(char entrada [], char filhasGeradas[100][27], int geracao, int porcentMutacao);
char gerarLetra();
char* selecionarFilha(char filhasGeradas[100][27], char fraseDesejada[], int geracao);
void verificaInvolucao(char filhasSelecionadas[50000][27], int mutacoes, char fraseDesejada[]);
int gerarPontuacao(char frase[], char fraseDesejada[]);
void insere(char *selecionada, struct listaEncadeada *filhasSelecionadas);
void printList(struct listaEncadeada *lista);

int main(){
	
	srand(time(NULL));
	
	char fraseDesejada[] = "CELACANTO PROVOCA MAREMOTO";
	char entrada[] = "CELACANTO AAAAAAA MAREMOTO";
	char filhasGeradas[100][27];
	//char filhasSelecionadas[50000][27] = {'\0'};
	int geracao = 2, porcentMutacao = 15, mutacoes = 0;
	char *selecionada;
	
	struct listaEncadeada *filhasSelecionadas = NULL;	
	
	//gerar frase de entrada aleatoriamente
	
	//do{
			
	// filhasSelecionadas = (struct listaEncadeada*) malloc(sizeof(struct listaEncadeada*));
	
	gerarFilhas(entrada, filhasGeradas, geracao, porcentMutacao);
	
	selecionada = selecionarFilha(filhasGeradas, fraseDesejada, geracao);
	
	printf("\n\nFrase Escolhina na mutacao %i: %s\n", mutacoes, selecionada);
	
	insere(selecionada, filhasSelecionadas);
	
	printList(filhasSelecionadas);

	//verificaInvolucao(filhasSelecionadas, mutacoes, fraseDesejada);
	
	mutacoes++;
	printf("%p", filhasSelecionadas);
	printList(filhasSelecionadas);
	
	//} while( (strcmp(selecionada, fraseDesejada)) != 0 );
	
//	for (n=0; filhasSelecionadas[n][i] != '\0'; n++){
//		printf("%s\n", filhasSelecionadas[n]);
//	}		
	return 0;
}

void gerarFilhas(char entrada [], char filhasGeradas[100][27], int geracao, int porcentMutacao)
{
	int porcent, i, n;
		
	for(n=0; n < geracao; n++){
	
		for(i=0; entrada[i] != '\0'; i++){
			
			porcent = rand() % 99;
		
			if (porcent <= porcentMutacao - 1){
				filhasGeradas[n][i] = gerarLetra();
			}else{
				filhasGeradas[n][i] = entrada[i];
			}					
		}		
		filhasGeradas[n][i] = '\0';		
		printf("%s\n", filhasGeradas[n]);
		printf("%i\n", n);
	}
}

char gerarLetra(){
	
	int indiceLetra;
	char Letras[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
	indiceLetra = rand() % 26;
	return Letras[indiceLetra];
}

char* selecionarFilha(char filhasGeradas[100][27], char fraseDesejada[], int geracao){
	
	int i, n, pontuacao[100] = {0}, maxValor, maxIndice;
	char *retorno = NULL;
	
	for(n=0; n < geracao; n++){
		pontuacao[n] = gerarPontuacao(filhasGeradas[n], fraseDesejada);
	}

	i = 0;
	maxValor = pontuacao[0];
	maxIndice = 0;
	
	for(i = 1; i < geracao; i++){
		if(maxValor < pontuacao[i]){
			maxValor = pontuacao[i];
			maxIndice = i;
		}
	}	
	printf("\nFilha Selecionada: %s", filhasGeradas[maxIndice]);
	retorno = strdup(filhasGeradas[maxIndice]);	
	return retorno;
}

void verificaInvolucao(char filhasSelecionadas[50000][27], int mutacoes, char fraseDesejada[]){
	
	int pontuacaoA = 0, pontuacaoB = 0;
	
	if(mutacoes > 0){
		
		pontuacaoA = gerarPontuacao(filhasSelecionadas[mutacoes-1], fraseDesejada);
		pontuacaoB = gerarPontuacao(filhasSelecionadas[mutacoes], fraseDesejada);
		
		if(pontuacaoB < pontuacaoA){
			
			printf("Houve uma involucao.");
		}
	}
}
int gerarPontuacao(char frase[], char fraseDesejada[]){
	
	int i, pontuacao = 0;
	
	for(i=0; frase[i] != '\0'; i++){
			
		if(frase[i] == fraseDesejada[i]){
			pontuacao++;
		}		
	}
	return pontuacao;
}

void insere(char *selecionada, struct listaEncadeada *filhasSelecionadas){
	
   struct listaEncadeada *nova;
   nova = (struct listaEncadeada*) malloc (sizeof (struct listaEncadeada));
   nova->filhaSelecionada = selecionada;
   nova->prox = NULL;
   if (filhasSelecionadas == NULL) {
		filhasSelecionadas = nova;
		printf("%p\n", filhasSelecionadas);
	} else {
		filhasSelecionadas->prox = nova;
	}  
}

void printList(struct listaEncadeada *lista){
	
	printf("OI1\n");
	
	if (lista == NULL){
		return;
	}
	printf("OI2\n");
	printList(lista->prox);
	printf("%s\n", lista->filhaSelecionada);
}
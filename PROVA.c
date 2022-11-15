#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

struct linkedlist
{
    char *daughter;
    struct linkedlist *next;
};

int extract_nums(char []);
char char_aleatorio();
void frase_aleatoria(char [], int, int );
void concatchar(char []);
char selecao(char [], int, int, char []);
void insere(char *choice, struct linkedlist *daughter);
void printList(struct linkedlist *list);

int main(int argc, char **argv) {

    //srand(time(NULL));
    char variavel_p[10] = "";
	char variavel_g[10] = "";
	int arg_g = 0;
	int arg_p = 0;
	char frase[50] = "";

    char *choice;
    struct linkedlist *daughter = NULL;	

    for (int i = 1; i < argc; i++){

		if ( argv[i][0] == '-' && argv[i][1] == 'p' && isdigit(argv[i][2]) )
			strcat(variavel_p,argv[i]); 
	
		else if ( argv[i][0] == '-' && argv[i][1] == 'g' &&  isdigit(argv[i][2]) )
			strcat(variavel_g,argv[i]); 
		
		else{
			strcat(frase, argv[i]);
			strcat(frase, " ");
		}
	}   
    if (strcmp(variavel_g,"") != 0)
		arg_g = extract_nums(variavel_g);
	else
		arg_g = 100; //default

	if (strcmp(variavel_p,"") != 0)
		arg_p = extract_nums(variavel_p);
	else
		arg_p = 5; //default
	
	if ( strcmp(frase,"") == 0 )
		strcat(frase,"CELACANTO PROVOCA MAREMOTO"); //default
        
    for(int i = 0; frase[i]; i++)
        frase[i] = toupper(frase[i]);
    
    printf("\nO numero de filhas a cada iteracao sera %d\n",arg_g);
	printf("\nA chance de mudancas a cada iteracao sera %d %%\n",arg_p);
	printf("\nA frase para a selecao natural foi: %s\n",frase);
    frase_aleatoria(frase, arg_p, arg_g);
    return 0;
}
void frase_aleatoria(char frase[], int chance, int filhas){

    int soma = 0;
        if (frase == "CELACANTO PROVOCA MAREMOTO")
            soma = 2;

	char teste[50] = "";
	for (int i = 0; i < strlen(frase) + soma + 1; i++){ //garante uma frase do mesmo tamanho
		concatchar(teste);
    }
	printf("\nA frase aleatoria gerada foi:       %s\n",teste);
    printf("tamanho de frase: %d \t Tamanho de teste: %d",strlen(frase),strlen(teste));
    selecao(teste, chance, filhas, frase);
}

char selecao(char teste[], int chance, int filhas, char frase[]) {

    char copia[50] = "";  //frase é a frase a ser acertada.
	strcpy(copia, teste); //copia e teste estão iguais. são a frase aleatoria gerada.
    char melhor[50] = "";
	int maior = 0;
    char mae[59] = "";
    strcpy(mae,teste);

    while(strcmp(mae,frase) != 0){
        int pontuacao[filhas + 2];
        
        int involucao = 0;
        for (int j = 0; j != filhas; j++){ //gerando FILHAS frases
            
            pontuacao[j] = 0; // a cada iteração, uma frase filha terá uma pontuação diferente.
            
            for (int k = 0; mae[k] != '\0'; k++){
                
                int sorteio = rand() % 100;
                
                if (sorteio < chance) //existe chance% de uma letra mudar.
                    mae[k] = char_aleatorio();

                if (mae[k] == frase[k])
                    pontuacao[j]+=1;
            }

            if (strcmp(mae,frase) == 0){
                printf("A selecao natural acabou, pois a frase mère %s = frase fille %s",mae,frase);
                exit(0);
                break;
            }            
            if (j ==0){
                maior = pontuacao[j];
                involucao = maior;
                strcpy(melhor,mae);
            }
            if (j >=1)
                if (pontuacao[j] > maior){
                    maior = pontuacao[j];
                    strcpy(melhor,mae);
                }
            printf("\nA frase filha numero %i gerada foi:          %s\n",j + 1,mae);
            printf("\nEssa frase teve %d pontos.\n", pontuacao[j]);
            strcpy(teste,copia);    		
        }
        printf("\nA melhor frase dessa geracao foi a seguinte:     %s\n",melhor);
        printf("\nA pontuacao dessa frase foi a seguinte: %d\n",maior);
        strcpy(mae,melhor);

        if (involucao > maior)
            printf("\nHOUVE INVOLUÇÃO!!\n");       
    }
    return maior;
}

char char_aleatorio(){
	
	//srand(time(NULL)); a frase pode ter caracteres repetidos.
	char vetor[] = "ABCDEFGHIJKLMN OPQRSTUWVXYZ";
	int sorteio = rand() % 28;
	char letra = vetor[sorteio];
	return letra;	
}

void concatchar(char s[]){
    while (*s++) // o ponteiro anda p frente até chegar DEPOIS de '\0' (espaço de memoria alocado p o vetor)
    ;
    s--;
    char t = char_aleatorio();
    *s++ = t;
}

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

void insert(char *choice, struct linkedlist *daughter){
	
   struct linkedlist *new;
   new = (struct linkedlist*) malloc (sizeof (struct linkedlist));
   new->daughter = choice;
   new->next = NULL;
   if (daughter == NULL) {
		daughter = new;
		printf("%p\n", daughter);
	} else {
		daughter->next = new;
	}  
}

void printList(struct linkedlist *list){
	
	printf("Mothers:\n");
	
	if (list == NULL){
		return;
	}
	printf("OI2\n");
	printList(list->next);
	printf("%s\n", list->daughter);
}
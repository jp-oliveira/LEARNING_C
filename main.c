#include <stdio.h>
#include <stdlib.h>
#include <string.h> //necessário para strcat

#define LSIZ 128 // Máximo de carácteres na linha
#define RSIZ 10 // máximo de linhas

#define row 10
// Mascara para um inteiro de 12 bits e outra para inteiro de 8 bits
#define mask12 0x800
#define mask8 0x80

int main(void) {
    char line[RSIZ][LSIZ]; // iniciando a matriz que vai armazenar as linhas lidas
    int aux12, aux8; // variáveis auxiliares que receberão a máscara

    char fname[100];
    FILE *fptr = NULL;
    int i = 0;
    int tot = 0;

    printf("Escreva o diretório e nome do seu arquivo: \n");
    scanf("%s", fname);
//    char* fname = "/home/marcelo/apps/teste.txt";

    fptr = fopen(fname, "r"); // abrindo o arquivo
    if (fptr == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        exit(1);
    }

    while(fgets(line[i], LSIZ, fptr)) // Lendo linha por linha e armazenando a linha lida na matriz linha.
    {
        line[i][strlen(line[i]) - 1] = '\0';
        i++;
    }
    tot = i;

    printf("\n Armazenado no array line : \n");
    for(i = 0; i < tot; ++i)
    {
        printf(" %s\n", line[i]);
    }
    printf("\n");

    char* oname = "saida.txt"; // Jogando o arquivo de saída na pasta do arquivo c

    FILE *f = fopen(oname, "a");

    // para cada uma das linhas:
    for (i = 0; i < tot; i++){
        char *firstHalf = malloc(4 * sizeof(char)); // atribuimos 4 espaços de char para a variável firsthalf
        char *secondHalf = malloc(3 * sizeof(char)); // 3 para secondhalf

        memcpy(firstHalf, line[i], 4 * sizeof(char)); //copiamos o conteudo dos 4 primeiros char da linha para firsthalf
        memcpy(secondHalf, line[i] + 5, 3 * sizeof(char)); // e os 3 ultimos para secondhalf

        // faremos comparações para imprimir os primeiros 4 bits da sequencia.
        if (strcmp(firstHalf, "LODD") == 0){
           fprintf(f,"%s", "0000");
        }

        if (strcmp(firstHalf, "STOD") == 0) {
            fprintf(f,"%s", "0001");
        }

        if (strcmp(firstHalf, "ADDD") == 0) {
            fprintf(f,"%s", "0010");
        }

        if (strcmp(firstHalf, "SUBD") == 0) {
            fprintf(f,"%s", "0011");
        }

        if (strcmp(firstHalf, "JPOS") == 0) {
            fprintf(f,"%s", "0100");
        }

        if (strcmp(firstHalf, "JZER") == 0) {
            fprintf(f,"%s", "0101");
        }

        if (strcmp(firstHalf, "JUMP") == 0) {
            fprintf(f,"%s", "0110");
        }

        if (strcmp(firstHalf, "LOCO") == 0) {
            fprintf(f,"%s", "0111");
        }

        if (strcmp(firstHalf, "LODL") == 0) {
            fprintf(f,"%s", "1000");
        }

        if (strcmp(firstHalf, "STOL") == 0) {
            fprintf(f,"%s", "1001");
        }

        if (strcmp(firstHalf, "ADDL") == 0) {
            fprintf(f,"%s", "1010");
        }

        if (strcmp(firstHalf, "SUBL") == 0) {
            fprintf(f,"%s", "1011");
        }

        if (strcmp(firstHalf, "JNEG") == 0) {
            fprintf(f,"%s", "1100");
        }

        if (strcmp(firstHalf, "JNZE") == 0) {
            fprintf(f,"%s", "1101");
        }

        if (strcmp(firstHalf, "CALL") == 0) {
            fprintf(f,"%s", "1110");
        }

        if (strcmp(firstHalf, "PSHI") == 0) {
            fprintf(f,"%s", "1111000000000000");
            goto last; // estamos usando o goto para pular a parte do código que pega os ultimos digitos e registra em binário.
        }

        if (strcmp(firstHalf, "POPI") == 0) {
            fprintf(f,"%s", "1111001000000000");
            goto last;
        }

        if (strcmp(firstHalf, "PUSH") == 0) {
            fprintf(f,"%s", "1111010000000000");
            goto last;
        }

        if (strcmp(firstHalf, "POP") == 0) {
            fprintf(f,"%s", "1111011000000000");
            goto last;
        }

        if (strcmp(firstHalf, "PSHI") == 0) {
            fprintf(f,"%s", "1111000000000000");
            goto last;
        }

        if (strcmp(firstHalf, "RETN") == 0) {
            fprintf(f,"%s", "1111100000000000");
            goto last;
        }

        if (strcmp(firstHalf, "SWAP") == 0) {
            fprintf(f,"%s", "1111101000000000");
            goto last;
        }

        if (strcmp(firstHalf, "INSP") == 0) {
            fprintf(f,"%s", "11111100");
        }

        if (strcmp(firstHalf, "DESP") == 0) {
            fprintf(f,"%s", "11111110");
        }

        aux12 = mask12;
        aux8 = mask8;
        int n = atoi(secondHalf); // mudando o número que está em str para int.

        // faremos então a gravação do mesmo em binário.
        if ((strcmp(firstHalf, "INSP") == 0) || (strcmp(firstHalf, "DESP")==0)) {
            for (int i=7; i>=0; i--){

                if((n & aux8) != 0)
                    fprintf(f,"%d", 1);
                else
                    fprintf(f,"%d", 0);
                aux8 = aux8 >> 1;
            }
        }
        else {
            for (int i=11; i>=0; i--){

                if((n & aux12) != 0)
                    fprintf(f,"%d", 1);
                else
                    fprintf(f,"%d", 0);
                aux12 = aux12 >> 1;
            }
        }

        // se não houver número para ser lido, pularemos para esta parte do código.
        last:

			fprintf(f, "\n");

    }

    // fechando o arquivo e encerrando
    fclose(f);
    printf("Concluído com Sucesso! \n");
    return 0;
}

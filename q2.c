#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
//#define MAX 18
#define MAX 100
#define ALERT 6

int lelinha(char s[], int lim);
int main()
{

    int i = 0;
    char entrada[MAX];
    int vetorDigitado[6] = {'\0'};
    int vetorAleatorio[6] = {'\0'};

    lelinha(entrada, MAX);

    // ########################
    const char s[2] = " ";
    char *token;

    /* get the first token */
    token = strtok(entrada, s);

    /* walk through other tokens */
    while (token != NULL)
    {
        //printf("Token %s\n", token);
        vetorDigitado[i] = atoi(token);
        // printf(" vetor AUX %d\n", vetorDigitado[i]);
        token = strtok(NULL, s);
        i++;
    }
    //##########################

    srand(time(NULL));

    /*  for (i = 0; i < 6; i++)
    {

        vetorAleatorio[i] = rand() % 60;
        // printf("vetor aleatorio: %d \n ", vetorAleatorio[i]);
    } */

    /*   printf("vetor digitado ");
    for (int i = 0; i < 6; i++)
    {
        printf(" %d ", vetorDigitado[i]);
    }

    printf("\nvetor aleatorio");
    for (int i = 0; i < 6; i++)
    {
        printf(" %d ", vetorAleatorio[i]);
    } */

    printf("\n");

    //   arruma(vetorAleatorio);
    arruma(vetorDigitado);

    /*    printf("\nvetor aleatorio ordenado ");
    for (int i = 0; i < 6; i++)
    {
        printf(" %d ", vetorAleatorio[i]);
    } */
    printf("\nvetor digitado ordenado ");
    for (int i = 0; i < 6; i++)
    {
        printf(" %d ", vetorDigitado[i]);
    }

    int sorteio = 0;
    int sena = 0;
    int semana = 0;
    int meses = 0;
    int anos = 0;
    int hits = 0;

    while (sena == 0)
    { // Loop para gerar números aleatorios até encontrar a Sena

        sorteio += 1;              // Registrando sorteios
        semana += sorteio % 2;     // A cada 2 sorteios temos uma nova semana
        meses = (int)(semana / 4); // 1 mes a cada 4 semanas
        anos = (int)semana / 52;   // um ano a cada 54 semanas1

        gen_numbers(vetorAleatorio);                         // gerador dos números aleatórios
                                                             // arruma(vetorAleatorio);                              // ordenando os numeros aleatorios
        hits = check_numbers(vetorAleatorio, vetorDigitado); // verificando a quantiadde de acertos

        if (hits == 4)
        {

            printf("Quadra encontrada na geracao %d em %d semanas |||||| %d meses |||||| %d anos\n", sorteio, semana, meses, anos);
        }
        if (hits == 5)
        {

            printf("Quina encontrada na geracao %d em %d semanas ####### %d meses ###### %d anos\n", sorteio,
                   semana, meses, anos);
        }

        if (hits == 6)
        {
            sena = 1;
            printf("\nMega-sena encontrada na geracoo %d em %d semanas ////// %d meses ////// %d anos\n", sorteio,
                   semana, meses, anos);
            printf("ate aqui o gasto com os jogos foram de: R$ %f\n", (float)(sorteio * 4.5));
            // Imprimindo o valor gasto com jogos

            printf("numero escolhido: \n");
            for (int i = 0; i < 6; i++)
            {
                printf("%d ", vetorDigitado[i]);
            }

            printf("\nnumero sorteado: ");
            arruma(vetorAleatorio);
            for (int i = 0; i < 6; i++)
            {
                printf("%d ", vetorAleatorio[i]);
            }
            //sena = 1;
        }
    }

    return 0;
}

void gen_numbers(int generated[])
{
    int found;
    int count = 0;

    while (count < 6)
    {
        //int nRandonNumber = rand()%((nMax+1)-nMin) + nMin;
        int randNum = rand() % (60 + 1 - 1) + 1;
        found = 0; //assume the random number hasnt been generated

        //make sure the random number hasnt already been generated
        for (int i = 0; i < 6; i++)
        {
            if (generated[i] == randNum)
            {
                found = 1;
                break; //once we have located the number we dont need to continue checking
            }
        }

        //we have a new random number
        if (found == 0)
        {
            generated[count] = randNum;
            count++;
        }
    }
}

int check_numbers(int numbers[], int generated[])
{
    // verificamos quantos acertos tivemos neste sorteio

    int hits = 0; // começamos assumindo nenhum acerto
    for (int i = 0; i < 6; i++)
    {
        for (int k = 0; k < 6; k++)
        {
            if (numbers[i] == generated[k])
            { // se encontramos números nos dois vetores...

                hits += 1; //... adicionamos um novo acerto
            }
        }
    }
    return hits;
}

void arruma(int vet[])
{

    ///######### ARRUMA O ARRAY ##########///
    ///######### ARRUMA O ARRAY ##########///
    ///######### ARRUMA O ARRAY ##########///
    //Initialize array
    // int arr[] = {5, 2, 8, 7, 1};
    int temp = 0;

    //Calculate length of array arr
    // int length = sizeof(vetorAleatorio) / sizeof(vetorAleatorio[0]);
    int length = 6;
    //Displaying elements of original array
    /*  printf("Elements of original array: \n");
    for (int i = 0; i < length; i++)
    {
        printf("%d ", vet[i]);
    } */

    //Sort the array in ascending order
    for (int i = 0; i < length; i++)
    {
        for (int j = i + 1; j < length; j++)
        {
            if (vet[i] > vet[j])
            {
                temp = vet[i];
                vet[i] = vet[j];
                vet[j] = temp;
            }
        }
    }

    printf("\n");

    //Displaying elements of array after sorting
    /*     printf("Elements of array sorted in ascending order: \n");
    for (int i = 0; i < 6; i++)
    {
        printf("%i ", vet[i]);
    } */
    ///######### ARRUMA O ARRAY ##########///
    ///######### ARRUMA O ARRAY ##########///
    ///######### ARRUMA O ARRAY ##########///
    ///######### ARRUMA O ARRAY ##########///
}

int lelinha(char s[], int lim)
{
    int tamanhoVetor = 0;
    int c, i, error = 0;
    for (i = 0; i < lim - 1 && (c = getchar()) != '\n'; ++i)
    {
        //s[i] = 'z';
        if (c >= '0' && c <= '9') //se for um digito
        {
            s[i] = c;
        }
        else if (c = ' ')
        {
            s[i] = c;
        }

        else
        {
            printf("erro apenas numeros são aceitos");
            break;
        }
    }

    if (error > 1)
    {
        printf("#Error: A linha possui mais de 100 caracteres!");
    }

    s[i] = '\0';

    return i;
}

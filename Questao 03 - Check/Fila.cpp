#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

#define TAM 1000
//Declaracao de elementos privados
typedef struct
{
    char nomeArquivo[100];
    char nome[50];
    char corDoCabelo[50];
    char corDaPele[50];
    char corDosOlhos[50];
    char anoNascimento[50];
    char genero[50];
    char homeworld[50];
    int altura;
    double peso;
} Personagens;

typedef struct Celula
{
    Personagens elemento; // Elemento inserido na celula.
    struct Celula *prox;  // Aponta a celula prox.
} Celula;

#define MAXTAM 6
Celula *inicio;
Celula *ultimo;
int primeiro = 0;
int fim = 0;

Personagens personagem;
Personagens array[TAM];
int n = 0;

/*void mostrar()
{
    int i;

    for (i = 0; i < n; i++)
    {
        printf("[%d] ", i);
        PrintarObjeto(array[i]);
    }
} */

void PrintarObjeto(Personagens personagem)
{
    printf(" ## %s ## ", personagem.nome);
    printf("%d ## ", personagem.altura);
    printf("%g ## ", personagem.peso);
    printf("%s ## ", personagem.corDoCabelo);
    printf("%s ## ", personagem.corDaPele);
    printf("%s ## ", personagem.corDosOlhos);
    printf("%s ## ", personagem.anoNascimento);
    printf("%s ## ", personagem.genero);
    printf("%s ## \n", personagem.homeworld);
}

void lerPersonagem()
{
    FILE *arq;
    arq = fopen(personagem.nomeArquivo, "rb");

    char *line = NULL;

    size_t bufsize = 1000;
    getline(&line, &bufsize, arq);

    line = strndup(line, indexOf("films", line) + 10);

    char *aux = (char *)malloc(1000 * sizeof(char));
    char *aux2 = (char *)malloc(TAM * sizeof(char));
    char *aux3 = (char *)malloc(TAM * sizeof(char));

    strcpy(personagem.nome, strndup(&line[10], indexOf("'height':", line) - 13));

    strcpy(aux, strndup(&line[indexOf("'height':", line) + 11], indexOf("'mass':", &line[indexOf("'height':", line) + 11]) - 3));
    if (aux[0] == 'u')
        personagem.altura = 0;
    else
        sscanf(aux, "%d", &personagem.altura);

    strcpy(aux, strndup(&line[indexOf("'mass':", line) + 9], indexOf("'hair_color':", &line[indexOf("'mass':", line) + 9]) - 3));

    int tam = strlen(aux);

    for (int i = 0; i < tam; i++)
    {
        if (aux[i] == ',')
        {
            aux2 = strndup(aux, i);
            strcpy(aux3, &aux[i + 1]);
            strcat(aux2, aux3);
            strcpy(aux, aux2);
        }
    }

    if (aux[0] == 'u')
        personagem.peso = 0;
    else
        sscanf(aux, "%lf", &personagem.peso);
    aux = NULL;
    free(aux);
    aux2 = NULL;
    free(aux2);
    aux3 = NULL;
    free(aux3);

    strcpy(personagem.corDoCabelo, lerCorDoCabelo(line));

    strcpy(personagem.corDaPele, lerCorDaPele(line));

    strcpy(personagem.corDosOlhos, lerCorDosOlhos(line));

    strcpy(personagem.anoNascimento, lerAnoNascimento(line));

    strcpy(personagem.genero, lerGenero(line));

    strcpy(personagem.homeworld, lerHomeworld(line));
}

void printPersonagem(Personagens x)
{
    personagem = x;
    lerPersonagem();

    printf(" ## %s ## ", personagem.nome);
    printf("%d ## ", personagem.altura);
    printf("%g ## ", personagem.peso);
    printf("%s ## ", personagem.corDoCabelo);
    printf("%s ## ", personagem.corDaPele);
    printf("%s ## ", personagem.corDosOlhos);
    printf("%s ## ", personagem.anoNascimento);
    printf("%s ## ", personagem.genero);
    printf("%s ## \n", personagem.homeworld);
}

char *lerCorDoCabelo(char *line)
{ //Separar cor do cabelo
    char *aux = (char *)malloc(1000 * sizeof(char));

    strcpy(aux, strndup(&line[indexOf("'hair_color':", line) + 15], indexOf("'skin_color':", &line[indexOf("'hair_color':", line) + 15]) - 3));

    return aux;
}

char *lerCorDaPele(char *line)
{ //Separar cor da pele
    char *aux = (char *)malloc(1000 * sizeof(char));

    strcpy(aux, strndup(&line[indexOf("'skin_color':", line) + 15], indexOf("'eye_color':", &line[indexOf("'skin_color':", line) + 15]) - 3));

    return aux;
}

char *lerCorDosOlhos(char *line)
{ //Separar cor dos olhos
    char *aux = (char *)malloc(1000 * sizeof(char));

    strcpy(aux, strndup(&line[indexOf("'eye_color':", line) + 14], indexOf("'birth_year':", &line[indexOf("'eye_color':", line) + 14]) - 3));

    return aux;
}

char *lerAnoNascimento(char *line)
{ //Separar ano nascimento
    char *aux = (char *)malloc(1000 * sizeof(char));

    strcpy(aux, strndup(&line[indexOf("'birth_year':", line) + 15], indexOf("'gender':", &line[indexOf("'birth_year':", line) + 15]) - 3));

    return aux;
}

char *lerGenero(char *line)
{ //Separar genero
    char *aux = (char *)malloc(1000 * sizeof(char));

    strcpy(aux, strndup(&line[indexOf("'gender':", line) + 11], indexOf("'homeworld':", &line[indexOf("'gender':", line) + 11]) - 3));

    return aux;
}

char *lerHomeworld(char *line)
{ //Separar planeta natal
    char *aux = (char *)malloc(1000 * sizeof(char));

    strcpy(aux, strndup(&line[indexOf("'homeworld':", line) + 14], indexOf("'films':", &line[indexOf("'homeworld':", line) + 14]) - 3));

    return aux;
}

char *substring(char *padrao, char *entrada)
{ //Criacao de substring
    char *pointer = strstr(entrada, padrao);

    return strdup(pointer);
}

long int indexOf(char *padrao, char *entrada)
{ //uso indexOf
    char *pointer = strstr(entrada, padrao);

    return pointer - entrada;
}

bool isFim(char *s)
{ //Identificar FIM
    return (strlen(s) >= 3 && s[0] == 'F' && s[1] == 'I' && s[2] == 'M');
}

Celula *novaCelula(Personagens elemento)
{
    Celula *nova = (Celula *)malloc(sizeof(Celula));
    nova->elemento = elemento;
    nova->prox = NULL;
    return nova;
}

Celula *celulaPos(int x)
{
    Celula *aux;
    int i = 0;
    for (aux = inicio; i < x; aux = aux->prox)
        i++;
    return aux;
}

Personagens remover()
{
    Personagens resp = celulaPos(primeiro)->elemento;
    primeiro = (primeiro + 1) % 6;
    return resp;
}

void inserir(Personagens x)
{
    if (((fim + 1) % 6) == primeiro)
    {
        remover();
    }

    celulaPos(fim)->elemento = x;
    fim = (fim + 1) % 6;

    double altura = 0;
    int num = 0;
    for (int i = primeiro; i != fim; i = ((i + 1) % 6))
    {
        altura += celulaPos(i)->elemento.altura;
        num++;
    }
    altura /= num;
    printf("%.f\n", altura);
}

void construir(Personagens x)
{
    Celula *aux = novaCelula(x);
    inicio = aux;

    for (int i = 0; i < 5; i++)
    {
        aux->prox = novaCelula(x);
        aux = aux->prox;
    }
    ultimo = aux;
    ultimo->prox = inicio;
}

void mostrar()
{
    Celula *i;
    for (int i = primeiro; i != fim; i = ((i + 1) % 6))
    {
        PrintarObjeto(celulaPos(i)->elemento);
    }
}

int main()
{
    char palavra[TAM][TAM];

    int i = 0;

    //Preencher array
    do
    {
        fgets(palavra[i], TAM, stdin);
    } while (isFim(palavra[i++]) == false);
    //Testar palavra FIM
    i--;

    //Inserir personagens na lista
    for (int contador = 0; contador < i; contador++)
    {
        strcpy(personagem.nomeArquivo, strndup(palavra[contador], strlen(palavra[contador]) - 1));
        lerPersonagem();
        construir(personagem);
        inserir(personagem);
    }
    char comandos[TAM][TAM];
    fgets(comandos[0], TAM, stdin);
    int tamanho = atoi(comandos[0]);

    for (int x = 0; x < tamanho; x++)
    {
        fgets(comandos[x], TAM, stdin);
        if (comandos[x][0] == 'I')
        {
            strcpy(personagem.nomeArquivo, strndup(&comandos[x][2], strlen(&comandos[x][2]) - 1));
            lerPersonagem();
            inserir(personagem);
        }
        else if (comandos[x][0] == 'R')
        {
            printf("(R) %s\n", remover().nome);
        }
        mostrar();
    }
}
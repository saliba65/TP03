#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TAM 1000

typedef struct
{
    char nomeArquivo[100];
    char nome[100];
    char corDoCabelo[100];
    char corDaPele[100];
    char corDosOlhos[100];
    char anoNascimento[100];
    char genero[100];
    char homeworld[100];
    int altura;
    double peso;
} Personagens;

typedef struct CelulaDupla
{
    Personagens elemento;
    struct CelulaDupla *prox;
    struct CelulaDupla *ant;
} CelulaDupla;

CelulaDupla *primeiro;
CelulaDupla *ultimo;

bool isFim(char *s);
char *substring(char *padrao, char *entrada);
long int indexOf(char *padrao, char *entrada);
char *lerCorDoCabelo(char *line);
char *lerCorDaPele(char *line);
char *lerCorDosOlhos(char *line);
char *lerAnoNascimento(char *line);
char *lerGenero(char *line);
char *lerHomeworld(char *line);
void lerPersonagem();
void printPersonagem(Personagens x);
//void inserirInicio(Personagens x);
void inserirFim(Personagens x);
//void inserirPos(Personagens x, int pos);
//Personagens removerInicio();
//Personagens removerFim();
//Personagens removerPos(int pos);
Personagens personagem;
//Personagens array[TAM];
int compareTo(char *a, char *b, char *c, char *d);
void swap(int a, int b);
void quicksort();
void quicksortRec(int esq, int dir);

int n = 0;

int main()
{
    char palavra[TAM][TAM];

    int i = 0;

    do //preencher a matriz
    {
        fgets(palavra[i], TAM, stdin);
    } while (isFim(palavra[i++]) == false); //testar se eh FIM
    i--;

    for (int contador = 0; contador < i; contador++) //ler os primeiros personagens e inserir na lista
    {
        strcpy(personagem.nomeArquivo, strndup(palavra[contador], strlen(palavra[contador]) - 1));
        lerPersonagem();
        inserirFim(personagem);
    }

    quicksort();

    CelulaDupla *a = primeiro;

    for (; a != ultimo; a = a->prox)
    {
        strcpy(personagem.nomeArquivo, a->elemento.nomeArquivo); //printar os personagem
        printPersonagem(personagem);
    }
    strcpy(personagem.nomeArquivo, a->elemento.nomeArquivo);
    printPersonagem(personagem);
}

CelulaDupla *novaCelulaDupla(Personagens elemento)
{
    CelulaDupla *nova = (CelulaDupla *)malloc(sizeof(CelulaDupla));
    nova->elemento = elemento;
    nova->ant = nova->prox = NULL;
    return nova;
}

CelulaDupla *celulaPos(int x)
{
    CelulaDupla *aux;
    int i = 0;
    for (aux = primeiro; i < x; aux = aux->prox)
    {
        i++;
    }
    return aux;
}

int compareTo(char *a, char *b, char *c, char *d)
{
    int resp = 0;

    int tam = strlen(a);
    if (strlen(b) < tam)
        tam = strlen(b);

    for (int i = 0; i < tam; i++)
    {
        if (a[i] > b[i])
        {
            resp = 1;
            i = tam;
        }

        else if (a[i] < b[i])
        {
            resp = -1;
            i = tam;
        }
    }

    if (resp == 0 && strlen(a) != strlen(b))
    {
        if (strlen(b) > strlen(a))
            resp = -1;
        else
            resp = 1;
    }
    else if (resp == 0)
    {
        int tam = strlen(c);
        if (strlen(d) < tam)
            tam = strlen(d);

        for (int i = 0; i < tam; i++)
        {
            if (c[i] > d[i])
            {
                resp = 1;
                i = tam;
            }

            else if (c[i] < d[i])
            {
                resp = -1;
                i = tam;
            }
        }

        if (resp == 0 && strlen(c) != strlen(d))
        {
            if (strlen(d) > strlen(c))
                resp = -1;
            else
                resp = 1;
        }
    }

    return resp;
}

void swap(int b, int c)
{
    Personagens tmp = celulaPos(b)->elemento;
    celulaPos(b)->elemento = celulaPos(c)->elemento;
    celulaPos(c)->elemento = tmp;
}

void quicksortRec(int esq, int dir)
{
    int i = esq, j = dir;
    Personagens pivo = celulaPos((dir + esq) / 2)->elemento;

    while (i <= j)
    {
        CelulaDupla *aux = celulaPos(i);
        while (compareTo(aux->elemento.corDoCabelo, pivo.corDoCabelo, aux->elemento.nome, pivo.nome) < 0)
        {
            aux = aux->prox;
            i++;
        }

        aux = celulaPos(j);
        while (compareTo(aux->elemento.corDoCabelo, pivo.corDoCabelo, aux->elemento.nome, pivo.nome) > 0)
        {
            aux = aux->ant;
            j--;
        }

        if (i <= j)
        {
            swap(i, j);
            i++;
            j--;
        }
    }

    if (esq < j)
        quicksortRec(esq, j);
    if (i < dir)
        quicksortRec(i, dir);
}

void quicksort()
{
    quicksortRec(0, n - 1);
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

    /*printf(" ## %s ## ",personagem.nome);
    printf("%d ## ",personagem.altura);
    printf("%g ## ",personagem.peso);
    printf("%s ## ",personagem.corDoCabelo);
    printf("%s ## ",personagem.corDaPele);
    printf("%s ## ",personagem.corDosOlhos);
    printf("%s ## ",personagem.anoNascimento);
    printf("%s ## ",personagem.genero);
    printf("%s ## \n",personagem.homeworld);*/
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
{
    char *aux = (char *)malloc(1000 * sizeof(char));

    strcpy(aux, strndup(&line[indexOf("'hair_color':", line) + 15], indexOf("'skin_color':", &line[indexOf("'hair_color':", line) + 15]) - 3));

    return aux;
}

char *lerCorDaPele(char *line)
{
    char *aux = (char *)malloc(1000 * sizeof(char));

    strcpy(aux, strndup(&line[indexOf("'skin_color':", line) + 15], indexOf("'eye_color':", &line[indexOf("'skin_color':", line) + 15]) - 3));

    return aux;
}

char *lerCorDosOlhos(char *line)
{
    char *aux = (char *)malloc(1000 * sizeof(char));

    strcpy(aux, strndup(&line[indexOf("'eye_color':", line) + 14], indexOf("'birth_year':", &line[indexOf("'eye_color':", line) + 14]) - 3));

    return aux;
}

char *lerAnoNascimento(char *line)
{
    char *aux = (char *)malloc(1000 * sizeof(char));

    strcpy(aux, strndup(&line[indexOf("'birth_year':", line) + 15], indexOf("'gender':", &line[indexOf("'birth_year':", line) + 15]) - 3));

    return aux;
}

char *lerGenero(char *line)
{
    char *aux = (char *)malloc(1000 * sizeof(char));

    strcpy(aux, strndup(&line[indexOf("'gender':", line) + 11], indexOf("'homeworld':", &line[indexOf("'gender':", line) + 11]) - 3));

    return aux;
}

char *lerHomeworld(char *line)
{
    char *aux = (char *)malloc(1000 * sizeof(char));

    strcpy(aux, strndup(&line[indexOf("'homeworld':", line) + 14], indexOf("'films':", &line[indexOf("'homeworld':", line) + 14]) - 3));

    return aux;
}

char *substring(char *padrao, char *entrada)
{
    char *pointer = strstr(entrada, padrao);

    return strdup(pointer);
}

long int indexOf(char *padrao, char *entrada)
{
    char *pointer = strstr(entrada, padrao);

    return pointer - entrada;
}

bool isFim(char *s)
{
    return (strlen(s) >= 3 && s[0] == 'F' && s[1] == 'I' && s[2] == 'M'); //retornar true ou false para se eh o FIM
}

void inserirFim(Personagens x)
{
    if (n == 0)
    {
        primeiro = novaCelulaDupla(x);
        ultimo = primeiro;
    }

    else
    {
        ultimo->prox = novaCelulaDupla(x);
        ultimo->prox->ant = ultimo;
        ultimo = ultimo->prox;
    }
    n++;
}

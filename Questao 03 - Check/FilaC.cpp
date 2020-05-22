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

Personagens personagem[100];

bool isFim(char *s);
char *substring(char *padrao, char *entrada);
long int indexOf(char *padrao, char *entrada);
char *lerNome(char *line);
int lerAltura(char *line);
double lerPeso(char *line);
char *lerCorDoCabelo(char *line);
char *lerCorDaPele(char *line);
char *lerCorDosOlhos(char *line);
char *lerAnoNascimento(char *line);
char *lerGenero(char *line);
char *lerHomeworld(char *line);
void lerPersonagem(int cont);
void Printar(int cont);
void PrintarObjeto(Personagens personagem);

typedef struct Celula
{
    Personagens elemento;
    // Elemento inserido na celula.
    struct Celula *prox;
    // Aponta a celula prox.
} Celula;

#define MAXTAM 6
Celula *inicio;
Celula *ultimo;
int primeiro = 0;
int fim = 0;

Celula *novaCelula(Personagens elemento);
Celula *celulaPos(int pos);
Personagens remover();
void inserir(Personagens jedi);
void construir(Personagens jedi);
void mostrar();

int main()
{
    char palavra[TAM][TAM];

    int i = 0;

    //preencher a matriz
    do
    {
        fgets(palavra[i], TAM, stdin);
    } while (isFim(palavra[i++]) == false);
    //testar se eh FIM
    i--;

    int contador = 0;

    strcpy(personagem[contador].nomeArquivo, strndup(palavra[contador], strlen(palavra[contador]) - 1));
    lerPersonagem(contador);
    construir(personagem[contador]);
    inserir(personagem[contador++]);

    for (; contador < i; contador++)
    {
        strcpy(personagem[contador].nomeArquivo, strndup(palavra[contador], strlen(palavra[contador]) - 1));
        lerPersonagem(contador);
        inserir(personagem[contador]);
    }

    char comandos[TAM][TAM];
    fgets(comandos[0], TAM, stdin);
    int tamanho = atoi(comandos[0]);

    for (int x = tamanho; x > 0; x--, contador++)
    {
        fgets(comandos[x], TAM, stdin);
        if (comandos[x][0] == 'I')
        {
            strcpy(personagem[contador].nomeArquivo, strndup(&comandos[x][2], strlen(&comandos[x][2]) - 1));
            lerPersonagem(contador);
            inserir(personagem[contador]);
        }
        else if (comandos[x][0] == 'R')
        {
            printf("(R) %s\n", remover().nome);
        }
    }
    mostrar();
}

bool isFim(char *s)
{
    return (strlen(s) >= 3 && s[0] == 'F' && s[1] == 'I' && s[2] == 'M'); //retornar true ou false para se eh o FIM
}

char *substring(char *padrao, char *entrada)
{
    return strdup(strstr(entrada, padrao));
}

long int indexOf(char *padrao, char *entrada)
{
    return strstr(entrada, padrao) - entrada;
}

char *lerNome(char *line)
{
    return strndup(&line[10], indexOf("'height':", line) - 13);
}

int lerAltura(char *line)
{
    char *aux = (char *)malloc(1000 * sizeof(char));
    int alt = 0;
    strcpy(aux, strndup(&line[indexOf("'height':", line) + 11], indexOf("'mass':", &line[indexOf("'height':", line) + 11]) - 3));
    if (aux[0] != 'u')
        sscanf(aux, "%d", &alt);
    return alt;
}

double lerPeso(char *line)
{
    char *aux = (char *)malloc(1000 * sizeof(char));
    char *aux2 = (char *)malloc(TAM * sizeof(char));
    char *aux3 = (char *)malloc(TAM * sizeof(char));
    double peso = 0;

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
        peso = 0;
    else
        sscanf(aux, "%lf", &peso);
    aux = NULL;
    free(aux);
    aux2 = NULL;
    free(aux2);
    aux3 = NULL;
    free(aux3);

    return peso;
}

char *lerCorDoCabelo(char *line)
{
    return strndup(&line[indexOf("'hair_color':", line) + 15], indexOf("'skin_color':", &line[indexOf("'hair_color':", line) + 15]) - 3);
}

char *lerCorDaPele(char *line)
{
    return strndup(&line[indexOf("'skin_color':", line) + 15], indexOf("'eye_color':", &line[indexOf("'skin_color':", line) + 15]) - 3);
}

char *lerCorDosOlhos(char *line)
{
    return strndup(&line[indexOf("'eye_color':", line) + 14], indexOf("'birth_year':", &line[indexOf("'eye_color':", line) + 14]) - 3);
}

char *lerAnoNascimento(char *line)
{
    return strndup(&line[indexOf("'birth_year':", line) + 15], indexOf("'gender':", &line[indexOf("'birth_year':", line) + 15]) - 3);
}

char *lerGenero(char *line)
{
    return strndup(&line[indexOf("'gender':", line) + 11], indexOf("'homeworld':", &line[indexOf("'gender':", line) + 11]) - 3);
}

char *lerHomeworld(char *line)
{
    return strndup(&line[indexOf("'homeworld':", line) + 14], indexOf("'films':", &line[indexOf("'homeworld':", line) + 14]) - 3);
}

void lerPersonagem(int w)
{
    FILE *arq;
    arq = fopen(personagem[w].nomeArquivo, "rb");

    char *line = NULL;

    size_t bufsize = 1000;
    getline(&line, &bufsize, arq);

    line = strndup(line, indexOf("films", line) + 10);

    strcpy(personagem[w].nome, lerNome(line));

    personagem[w].altura = lerAltura(line);

    personagem[w].peso = lerPeso(line);
    strcpy(personagem[w].corDoCabelo, lerCorDoCabelo(line));

    strcpy(personagem[w].corDaPele, lerCorDaPele(line));

    strcpy(personagem[w].corDosOlhos, lerCorDosOlhos(line));

    strcpy(personagem[w].anoNascimento, lerAnoNascimento(line));

    strcpy(personagem[w].genero, lerGenero(line));

    strcpy(personagem[w].homeworld, lerHomeworld(line));
}

void Printar(int w)
{
    printf(" ## %s ## ", personagem[w].nome);
    printf("%d ## ", personagem[w].altura);
    printf("%g ## ", personagem[w].peso);
    printf("%s ## ", personagem[w].corDoCabelo);
    printf("%s ## ", personagem[w].corDaPele);
    printf("%s ## ", personagem[w].corDosOlhos);
    printf("%s ## ", personagem[w].anoNascimento);
    printf("%s ## ", personagem[w].genero);
    printf("%s ## \n", personagem[w].homeworld);
}

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

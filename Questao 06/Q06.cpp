#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Time {
	char nome[1000];
	char apelido[1000];
	char estadio[1000];
	char tecnico[1000];
	char liga[1000];
	char nomeArquivo[1000];
	char linhaCapacidadeEstadio[1000];
	int capacidadeEstadio;
	char linhaDataFundacao[1000];
	int diaFundacao;
	int mesFundacao;
	int anoFundacao;
	long tamanhoArquivo;
} Time;

void lerAtributos(Time *time);
char * lerArquivo(Time *time);
char * removerTags(char *linha);
bool ehTagAtributo(char *linha, int i);
char * removerLixo(char *linha);
char * meuReplaceChar(char *linha, const char meuChar);
char * meuReplaceString(char *linha, const char *minhaString);
void lerDataFundacao(Time *time);
const char * lerMesFundacao(char * mesFundacao);
void escreverAtributos(Time *time);

//Construtor, sem parâmetros, do registro
Time * criarTime() {
	Time *novoTime = (Time *) malloc(sizeof(Time));

	strcpy(novoTime->nome, "0");
	strcpy(novoTime->apelido, "0");
	strcpy(novoTime->estadio, "0");
	strcpy(novoTime->tecnico, "0");
	strcpy(novoTime->liga, "0");
	strcpy(novoTime->nomeArquivo, "0");

	novoTime->capacidadeEstadio = novoTime->diaFundacao = novoTime->mesFundacao = novoTime->anoFundacao = 0;
	novoTime->tamanhoArquivo = 0;

	return novoTime;
}

//Construtor do registro
Time * criarTime(char nomeArquivo[]) {
	Time *novoTime = (Time *) malloc(sizeof(Time));

	strcpy(novoTime->nomeArquivo, nomeArquivo);
	lerAtributos(novoTime);
	lerDataFundacao(novoTime);

	return novoTime;
}

//Ler os atributos do time recebido por parâmetro
//A partir de uma linha contendo todos os atributos, utiliza-se a função strtok() para separar essa em várias linhas
//Verifica-se cada linha contendo os atributo, avaliando se esta possui o atributo em questão, para assim inicializar as variáveis do registro
void lerAtributos(Time *time) {
	char *linhaAtributos = lerArquivo(time);
	bool achouNome, achouApelido, achouEstadio, achouTecnico, achouLiga, achouCapacidadeEstadio, achouDataFundacao;

	linhaAtributos = strtok(linhaAtributos, "<");
	achouNome = achouApelido = achouEstadio = achouTecnico = achouLiga = achouCapacidadeEstadio = achouDataFundacao = false;

	while (linhaAtributos != NULL) {
		if (!achouNome && strstr(linhaAtributos, "Full") != NULL) {
			if (strstr(linhaAtributos, "Name") != NULL) {
				achouNome = true;
				strcpy(time->nome, meuReplaceString(strdup(linhaAtributos), "Full Name"));
			} else if (strstr(linhaAtributos, "name") != NULL) {
				achouNome = true;
				strcpy(time->nome, meuReplaceString(strdup(linhaAtributos), "Full name"));
			}
		} else if (!achouApelido && strstr(linhaAtributos, "Nickname") != NULL) {
			if (strstr(linhaAtributos, "(s)") != NULL) {
				achouApelido = true;
				strcpy(time->apelido, meuReplaceString(strdup(linhaAtributos), "Nickname(s)"));
				strcpy(time->apelido, meuReplaceChar(time->apelido, '"'));
			} else if (strstr(linhaAtributos, "(es)") != NULL) {
				achouApelido = true;
				strcpy(time->apelido, meuReplaceString(strdup(linhaAtributos), "Nickname(es)"));
			}
		} else if (!achouEstadio && strstr(linhaAtributos, "Ground") != NULL) {
			achouEstadio = true;
			strcpy(time->estadio, meuReplaceString(strdup(linhaAtributos), "Ground"));
		} else if (!achouTecnico && strstr(linhaAtributos, "Head") != NULL || strstr(linhaAtributos, "Coach") != NULL || strstr(linhaAtributos, "General") || strstr(linhaAtributos, "Manager")) {
			if (strstr(linhaAtributos, "Head Coach") != NULL) {
				achouTecnico = true;
				strcpy(time->tecnico, meuReplaceString(strdup(linhaAtributos), "Head Coach"));
			} else if (strstr(linhaAtributos, "Head coach") != NULL) {
				achouTecnico = true;
				strcpy(time->tecnico, meuReplaceString(strdup(linhaAtributos), "Head coach"));
			} else if (strstr(linhaAtributos, "Coach") != NULL) {
				achouTecnico = true;
				strcpy(time->tecnico, meuReplaceString(strdup(linhaAtributos), "Coach"));
			} else if (strstr(linhaAtributos, "General") != NULL) {
				if (strstr(linhaAtributos, "Manager") != NULL) {
					achouTecnico = true;
					strcpy(time->tecnico, meuReplaceString(strdup(linhaAtributos), "General Manager"));
				} else if (strstr(linhaAtributos, "manager") != NULL) {
					achouTecnico = true;
					strcpy(time->tecnico, meuReplaceString(strdup(linhaAtributos), "General manager"));
				}
			} else if (strstr(linhaAtributos, "Manager") != NULL) {
				achouTecnico = true;
				strcpy(time->tecnico, meuReplaceString(strdup(linhaAtributos), "Manager"));
			}
		} else if (!achouLiga && strstr(linhaAtributos, "League") != NULL) {
			achouLiga = true;
			strcpy(time->liga, meuReplaceString(strdup(linhaAtributos), "League"));
		} else if (!achouCapacidadeEstadio && strstr(linhaAtributos, "Capacity") != NULL) {
			strcpy(time->linhaCapacidadeEstadio, meuReplaceString(strdup(linhaAtributos), "Capacity"));
			strcpy(time->linhaCapacidadeEstadio, meuReplaceChar(time->linhaCapacidadeEstadio, ','));

			time->capacidadeEstadio = atoi(time->linhaCapacidadeEstadio);
		} else if (!achouDataFundacao && strstr(linhaAtributos, "Founded") != NULL) {
			achouDataFundacao = true;
			strcpy(time->linhaDataFundacao, meuReplaceString(strdup(linhaAtributos), "Founded"));
			strcpy(time->linhaDataFundacao, meuReplaceChar(time->linhaDataFundacao, ','));
		}

		linhaAtributos = strtok(NULL, "<");
	}
}

//Ler o arquivo do time recebido por parâmetro e determinar o tamanho desse
char * lerArquivo(Time *time) {
	FILE *arquivo = fopen(time->nomeArquivo, "rb");

	fseek(arquivo, 0L, SEEK_END);
	
	time->tamanhoArquivo = ftell(arquivo);

	fclose(arquivo);

	arquivo = fopen(time->nomeArquivo, "rb");

	if (arquivo == NULL) {
		printf("Erro: Arquivo Inexistente");
		exit(1);
	}

	char *linha = NULL;
	size_t tamanho = 0;

	getline(&linha, &tamanho, arquivo);

	while (!feof(arquivo) && !strstr(linha, "vcard")) {
		getline(&linha, &tamanho, arquivo);
	}

	linha = removerTags(strdup(linha));
	linha[strlen(linha) - 1] = '\0';

	return linha;
}

//Remover as tags da linha obtida a partir do arquivo do time em questão, exceto as tags separadoras de atributos: </td>
char * removerTags(char *linha) {
	char *novaLinha = (char *) malloc(sizeof(char) * 1000);
	int contador = 0;

	for (int i = 0; i < strlen(linha); i++) {
		if (linha[i] == '<') {
			if (ehTagAtributo(linha, i + 1)) {
				novaLinha[contador] = linha[i];
				contador++;
				i += 4;
			} else {
				i++;

				while (linha[i] != '>') {
					i++;
				}
			}
		} else {
			novaLinha[contador] = linha[i];
			contador++;
		}
	}

	novaLinha = removerLixo(strdup(novaLinha));

	return novaLinha;
}

//Verificar se um trecho da linha obtida a partir do arquivo do time em questão é uma tag separadora de atributos: </td>
bool ehTagAtributo(char *linha, int i) {
	return (linha[i] == '/' && linha[i + 1] == 't' && linha[i + 2] == 'd' && linha[i + 3] == '>');
}

//Remover os lixos da linha obtida a partir do arquivo do time em questão
char * removerLixo(char *linha) {
	char *novaLinha = (char *) malloc(sizeof(char) * 1000);
	int contador = 0;

	for (int i = 0; i < strlen(linha); i++) {
		if (linha[i] == '&') {
			i++;

			while (linha[i] != ';') {
				i++;
			}

			if (linha[i + 1] == 'n') {
				i++;

				while (linha[i] != ';') {
					i++;
				}
			} else if (linha[i + 2] == '&') {
				i++;

				while (linha[i] != ';') {
					i++;
				}
			}

			novaLinha[contador] = ' ';
			contador++;
		} else {
			novaLinha[contador] = linha[i];
			contador++;
		}
	}

	return novaLinha;
}

//Remover o caractere recebido por parâmetro da linha recebida por parâmetro
char * meuReplaceChar(char *linha, const char meuChar) {
	char *novaString = (char *) malloc(sizeof(char) * 1000);
	int contador = 0;
	bool achouMeuChar = false;
	int contadorMeuChar = 0;

	for (int i = 0; i < strlen(linha); i++) {
		if (linha[i] == meuChar) {
			achouMeuChar = true;
			contadorMeuChar++;
		} else {
			novaString[contador] = linha[i];
			contador++;
		}
	}

	if (achouMeuChar) {
		novaString[strlen(linha) - contadorMeuChar] = '\0';
	}

	return novaString;
}

//Remover o trecho recebido por parâmetro da linha recebida por parâmetro
char * meuReplaceString(char *linha, const char *minhaString) {
	char *novaString = (char *) malloc(sizeof(char) * 1000);
	int contador = 0;

	for (int i = strlen(minhaString); i < strlen(linha); i++, contador++) {
		novaString[contador] = linha[i];
	}

	return novaString;
}

//Ler a data de fundação do time recebido por parâmetro
//A partir de uma linha contendo a data de fundação, utiliza-se a função strtok() para separar aquela em várias linhas
//Verifica-se o modo como a data de fundação está escrita, para assim inicializar as variáveis do registro
void lerDataFundacao(Time *time) {
	char linhaDataFundacao[1000];
	char *dataFundacao = (char *) malloc(sizeof(char) * 1000);
	int tamanhoDataFundacao = 0;
	int posAnoFundacao;

	strcpy(linhaDataFundacao, time->linhaDataFundacao);
	
	dataFundacao = strtok(linhaDataFundacao, " ");

	while (dataFundacao != NULL) {
		tamanhoDataFundacao++;

		if (strstr(dataFundacao, "years") != NULL) {
			posAnoFundacao = tamanhoDataFundacao - 2;
		}

		dataFundacao = strtok(NULL, " ");
	}

	strcpy(linhaDataFundacao, time->linhaDataFundacao);

	dataFundacao = strtok(linhaDataFundacao, " ");

	if (tamanhoDataFundacao == 1 || posAnoFundacao == 1) {
		time->diaFundacao = 0;
		time->mesFundacao = 0;
		time->anoFundacao = atoi(dataFundacao);
	} else {
		if (dataFundacao[0] >= '0' && dataFundacao[0] <= '9') {
			time->diaFundacao = atoi(dataFundacao);
			dataFundacao = strtok(NULL, " ");
			time->mesFundacao = atoi(lerMesFundacao(dataFundacao));
			dataFundacao = strtok(NULL, " ");
			time->anoFundacao = atoi(dataFundacao);
		} else {
			time->mesFundacao = atoi(lerMesFundacao(dataFundacao));
			dataFundacao = strtok(NULL, " ");
			time->diaFundacao = atoi(dataFundacao);
			dataFundacao = strtok(NULL, " ");
			time->anoFundacao = atoi(dataFundacao);
		}
	}
}

//Converter o mês de fundação recebido por parâmetro em um número
const char * lerMesFundacao(char *mesFundacao) {
	const char *novoMesFundacao = (char *) malloc(sizeof(char) * 1000);

	if (strstr(mesFundacao, "January") != NULL) {
		novoMesFundacao = "01";
	} else if (strstr(mesFundacao, "February") != NULL) {
		novoMesFundacao = "02";
	} else if (strstr(mesFundacao, "March") != NULL) {
		novoMesFundacao = "03";
	} else if (strstr(mesFundacao, "April") != NULL) {
		novoMesFundacao = "04";
	} else if (strstr(mesFundacao, "May") != NULL) {
		novoMesFundacao = "05";
	} else if (strstr(mesFundacao, "June") != NULL) {
		novoMesFundacao = "06";
	} else if (strstr(mesFundacao, "July") != NULL) {
		novoMesFundacao = "07";
	} else if (strstr(mesFundacao, "August") != NULL) {
		novoMesFundacao = "08";
	} else if (strstr(mesFundacao, "September") != NULL) {
		novoMesFundacao = "09";
	} else if (strstr(mesFundacao, "October") != NULL) {
		novoMesFundacao = "10";
	} else if (strstr(mesFundacao, "November") != NULL) {
		novoMesFundacao = "11";
	} else {
		novoMesFundacao = "12";
	}

	return novoMesFundacao;
}

//Escrever todos os atributos do time recebido por parâmetro
void escreverAtributos(Time *time) {
	printf("%s ## ", time->nome);
	printf("%s ## ", time->apelido);
	printf("%02d/%02d/%04d ## ", time->diaFundacao, time->mesFundacao, time->anoFundacao);
	printf("%s ## ", time->estadio);
	printf("%d ## ", time->capacidadeEstadio);
	printf("%s ## ", time->tecnico);
	printf("%s ## ", time->liga);
	printf("%s ## ", time->nomeArquivo);
	printf("%ld ## \n", time->tamanhoArquivo);
}

typedef struct CelulaTime {
	Time *time;
	struct CelulaTime *prox;
} CelulaTime;

//Construtor do registro
CelulaTime * criarCelulaTime(char nomeArquivo[]) {
	CelulaTime *novaCelulaTime = (CelulaTime *) malloc(sizeof(CelulaTime));

	novaCelulaTime->time = criarTime(nomeArquivo);
	novaCelulaTime->prox = NULL;

	return novaCelulaTime;
}

CelulaTime *topo;

void escreverInseridos(CelulaTime *i, int cont);
int getTamanho();

//Construtor da pilha flexível
void criarPilhaFlexivel() {
	topo = NULL;
}

//Inserir um time no topo da pilha flexível a partir do nome de arquivo recebido por parâmetro
void inserir(char nomeArquivo[]) {
	CelulaTime *temp = criarCelulaTime(nomeArquivo);

	temp->prox = topo;
	topo = temp;
	temp = NULL;
}

//Remover o time que ocupa o topo da pilha flexível
char * remover() {
	if (topo == NULL) {
		printf("Erro: Pilha Vazia");
		exit(1);
	}

	char *nomeRemovido = topo->time->nome;
	CelulaTime *temp = topo;

	topo = topo->prox;
	temp->prox = NULL;

	free(temp);
	temp = NULL;

	return nomeRemovido;
}

//Inicializar a função recursiva
void escreverInseridos() {
	escreverInseridos(topo, getTamanho() - 1);
}

//Escrever, na ordem de inserção, todos os atributos dos times inseridos na pilha flexível
void escreverInseridos(CelulaTime *i, int cont) {
	if (i->prox != NULL) {
		escreverInseridos(i->prox, cont - 1);
	}

	printf("[%d] ", cont);
	escreverAtributos(i->time);
}

//Calcular o tamanho da pilha flexível
int getTamanho() {
	int tam = 0;

	for (CelulaTime *i = topo; i != NULL; i = i->prox, tam++);

	return tam;
}

void lerComando();

int main() {
	char nomeArquivos[1000][1000];
	int totalTimes = 0;
	int totalComandos;

	criarPilhaFlexivel();

	do {
		fgets(nomeArquivos[totalTimes], 1000, stdin);
	} while (strstr(nomeArquivos[totalTimes++], "FIM") == NULL);

	totalTimes--;

	for (int i = 0; i < totalTimes; i++) {
		nomeArquivos[i][strlen(nomeArquivos[i]) - 1] = '\0';
		
		inserir(nomeArquivos[i]);
	}

	scanf("%d ", &totalComandos);

	for (int i = 0; i < totalComandos; i++) {
		lerComando();
	}

	escreverInseridos();

    return 0;
}

//Ler um comando de inserção ou remoção da pilha flexível
void lerComando() {
	char linhaComando[1000];
	char *comando = (char *) malloc(sizeof(char));
	int tamanhoComando = 0;
	char aux[1000];

	fgets(linhaComando, 1000, stdin);
	strcpy(aux, linhaComando);
	
	comando = strtok(linhaComando, " ");
	
	while (comando != NULL) {
		tamanhoComando++;
		comando = strtok(NULL, " ");
	}

	strcpy(linhaComando, aux);

	comando = strtok(linhaComando, " ");

	if (tamanhoComando == 1) {
		printf("(R) %s\n", remover());
	} else {
		comando = strtok(NULL, " ");
		comando[strlen(comando) - 1] = '\0';

		inserir(comando);
	}
}
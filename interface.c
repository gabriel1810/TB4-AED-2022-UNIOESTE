#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "PATRICIA.h"

int menu()
{
	int index;
	printf("|  --Menu-- \n");
	printf("|  1 -> Carregar arquivo de palavras\n");
	printf("|  2 -> Carregar arquivo stopwords\n");
	printf("|  3 -> Consultar Palavra\n");
	printf("|  4 -> Imprimir Dicionario\n");
	printf("|  5 -> Consulta por nivel\n");
	printf("|  6 -> Excluir todo o dicionario\n");
	printf("|  0 -> Sair\n");
	printf("|  Selecione uma opcao: ");

	scanf("%d%*c", &index);
	return index;
}

void transformarString(char* str) {
    int i, j;
    int len = strlen(str);

    // Converter caracteres uppercase para lowercase
    for (i = 0; i < len; i++) {
        str[i] = tolower(str[i]);
    }

    // Remover caracteres especiais
    j = 0;
    for (i = 0; i < len; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[j++] = str[i];
        }
    }
    str[j] = '\0'; // Adicionar o caractere nulo para indicar o fim da nova string
}

PTRC ler_txt(PTRC p, FILE *f, int func){
	char str[100];
	    while (fgets(str, sizeof(str), f) != NULL) {
        // Remover o caractere de nova linha no final da palavra (se existir)
        str[strcspn(str, "\n")] = '\0';
		transformarString(str);
		if(func)
        	p = inserir(p, str);
		else
			p = remover(p, str);
    }
	return p;
}

PTRC menu_ler_arquivo(PTRC p, int func)
{
	char nome_arq[100];
	printf("Digite o nome do arquivo: ");
	scanf("%[^\n]%*c", nome_arq);
	if (strstr(nome_arq, ".txt") == NULL)
	{
		strcat(nome_arq, ".txt");
	}
	FILE *f;
	if ((f = fopen(nome_arq, "r")) == NULL)
	{
		printf("Erro ao abrir o arquivo.\n");
		return p;
	}
	while (!feof(f))
	{

		p = ler_txt(p, f, func);
	}
	printPorNivel(p);
	fclose(f);
	printf("Arquivo carregado.\n");
	return p;
}

void menu_consultar(PTRC p){
	char str[100];
	printf("Digite o prefixo que deseja consultar: ");
	scanf("%[^\n]%*c", str);
	transformarString(str);
	consultaPalavra(p, str);
	printf("\n");
}

void menu_imprimir_tudo(PTRC p){
	printf("Todas as palavra no dicionario: \n");
	imprime_tudo(p, "");
    printf("\n");
}

void menu_imprimir_sub(PTRC p){
	char str[100];
	printf("Digite o prefixo que deseja consultar: ");
	scanf("%[^\n]%*c", str);
	transformarString(str);
	imprimir_sub(p, str);
	printf("\n");
}

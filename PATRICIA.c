#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "PATRICIA.h"

PTRC cria_no(string str)
{
	PTRC p = (PTRC)malloc(sizeof(struct no));
	p->str = (string)malloc(sizeof(char) * strlen(str));
	strcpy(p->str, str);
	p->filhos = 0;
	p->final = 1;
	for (int i = 0; i < MAX; i++)
		p->filho[i] = NULL;
	return p;
}

// verifica em que caracter a str2 difere de str1
int compareStrings(string str1, string str2)
{
	int i;

	for (i = 0; str1[i] != '\0' || str2[i] != '\0'; i++)
	{
		if (str1[i] != str2[i])
		{
			return i;
		}
	}

	if (str1[i] == '\0' && str2[i] == '\0')
	{
		return -1; // As strings são idênticas
	}

	return i; // Uma string é um prefixo da outra
}

// dado duas strings, retorna a palavra em comum entre elas
string getPrefixo(string str1, string str2)
{
	int i, len1, len2;
	len1 = strlen(str1);
	len2 = strlen(str2);

	int minLen = (len1 < len2) ? len1 : len2;
	string prefix = (string)malloc((minLen + 1) * sizeof(char));

	for (i = 0; i < minLen; i++)
	{
		if (str1[i] != str2[i])
		{
			break;
		}
		prefix[i] = str1[i];
	}
	prefix[i] = '\0';

	return prefix;
}

// dado uma string e um valor n, remove os primeiros N caracteres da palavra
string getSufixo(string str, int n)
{

	int len = strlen(str) - n;

	string suffix = (string)malloc((n + 1) * sizeof(char));
	int i;
	for (i = 0; i < len; i++)
	{
		suffix[i] = str[n + i];
	}
	suffix[i] = '\0';

	return suffix;
}
PTRC inserir(PTRC p, string str)
{

	if (p == NULL)
	{
		return cria_no(str);
	}

	// posição em que as stringsd se divergem
	int pos = compareStrings(str, p->str);

	// prefixo em comum entre as duas strings
	string prefix = getPrefixo(str, p->str);

	// sufixo da palavra que chegou
	string strsufix = getSufixo(str, pos);

	// sufixo da palavra no nó
	string psufix = getSufixo(p->str, pos);

	// as palavras não são iguais
	if (pos != -1)
	{
		// se não gera um sufixo para o nó atual é porque a palavra que chegou é uma continuação do nó atual
		if (strlen(psufix) == 0)
		{
			// Se for folha, apenas adiciona o sufixo da palavra que chegou em um filho
			if (p->filhos == 0)
			{
				PTRC aux = cria_no(strsufix);
				int index = strsufix[0] - 'a';
				p->filho[index] = aux;
				p->filhos++;
				return p;
			} // se não for folha, insere no filho correspondente
			else
			{
				// pega o index do filho com a primeira letra do sufixo da palavra que chegou
				int index = strsufix[0] - 'a';
				if (p->filho[index] == NULL)
				{
					p->filho[index] = inserir(p->filho[index], strsufix);
					p->filhos++;
					return p;
				}
				else
				{
					p->filho[index] = inserir(p->filho[index], strsufix);
					return p;
				}
			}
		} // se gerar um sufixo é porque há uma divergencia de palavras nesse nó, precisa fazer split
		else
		{

			PTRC aux = cria_no(prefix);

			strcpy(p->str, psufix);
			int p_index = psufix[0] - 'a';
			aux->filho[p_index] = p;
			aux->filhos++;

			PTRC filho = cria_no(strsufix);
			int filho_index = strsufix[0] - 'a';
			aux->filho[filho_index] = filho;
			aux->filhos++;

			aux->final = 0;
			return aux;
		}
	}
	else
	{
		if (p->final)
		{
			printf("Palavra ja esta inserida");
		}
		else
		{
			p->final = 1;
		}
		return p;
	}
}

char *strconcat(char *str1, const char *str2)
{
	// printf("Concatenando: \"%s\" e \"%s\"\n", str1, str2);
	char *str3 = (char *)malloc(strlen(str1) + strlen(str2) + 1);
	strcpy(str3, str1);
	strcat(str3, str2);
	return str3;
}

void consultaPalavraRec(PTRC p, string str, string current, int *count)
{
	if (p != NULL)
	{
		current = strconcat(current, p->str);
		int pos = compareStrings(str, p->str);
		string strsufix = getSufixo(str, pos);
		string psufix = getSufixo(p->str, pos);


		if (pos == -1)
		{
					if (p->final)
			if ((*count) < 10)
			{
				printf("%s, ", current);
				(*count)++;
			}

			for (int i = 0; i < MAX; i++)
			{
				consultaPalavraRec(p->filho[i], (p->filho[i] != NULL) ? p->filho[i]->str : NULL, current, count);
			}
		}
		else
		{

			if (strlen(strsufix) > 0)
			{
				int index = strsufix[0] - 'a';
				if (p->filho[index] != NULL)
				{
					consultaPalavraRec(p->filho[index], strsufix, current, count);
				}
				else
				{
					printf("Nao ha palavras com esse prefixo\n");
				}
			}
			else
			{
						if (p->final)
			if ((*count) < 10)
			{
				printf("%s, ", current);
				(*count)++;
			}
				for (int i = 0; i < MAX; i++)
				{
					consultaPalavraRec(p->filho[i], (p->filho[i] != NULL) ? p->filho[i]->str : NULL, current, count);
				}
			}
		}
	}
}

void imprime_tudo(PTRC p, string current)
{
	if (p != NULL)
	{
		current = strconcat(current, p->str);
		if (p->final)
		{
			printf("%s, ", current);
		}

		if (p->filhos > 0)
			for (int i = 0; i < MAX; i++)
			{
				imprime_tudo(p->filho[i], current);
			}
	}
}
void consultaPalavra(PTRC p, string str)
{
	printf("Consulta da palavra: %s\n", str);
	int count = 0;
	consultaPalavraRec(p, str, "", &count);
}

int altura(PTRC root)
{
	if (root == NULL)
	{
		return 0;
	}

	int maxHeight = 0;

	for (int i = 0; i < MAX; i++)
	{
		int childHeight = altura(root->filho[i]);
		if (childHeight > maxHeight)
		{
			maxHeight = childHeight;
		}
	}

	return 1 + maxHeight;
}

void printNivel(PTRC p, int i, int nivel)
{
	if (p != NULL)
	{
		// current = strconcat(current, raiz->str);
		if (i == nivel)
		{
			printf("(");
			printf("%s : %d", p->str, p->filhos);
			printf(") ");
		}
		for (int j = 0; j < MAX; j++)
		{
			printNivel(p->filho[j], i + 1, nivel);
		}
	}
}

void printPorNivel(PTRC p)
{
	int i, alturaArvore;
	alturaArvore = altura(p);
	printf("Print por Nivel:\n");
	for (i = 0; i <= alturaArvore-1; i++)
	{
		printf("Nivel %d:  ", i);
		printNivel(p, 0, i);
		printf("\n");
	}
}

int diferenca(string str, string str2)
{

	// Se for string vazia a diferença vai ser na primeira posicao
	if (strlen(str) == 0 || strlen(str2) == 0)
		return 0;

	// Se forem iguais
	if (strcmp(str, str2) == 0)
		return -1;

	int pos;
	for (pos = 0; pos < strlen(str) && pos < strlen(str2); pos++)
	{
		if (str[pos] != str2[pos])
			return pos;
	}

	return pos;
}

PTRC remover(PTRC p, string str)
{
	if (p == NULL || strlen(str) == 0)
		return p;

	// Se for exatamente a palavra que estou procurando
	if (strcmp(p->str, str) == 0)
	{
		// Se tiver apenas um filho só concatena
		if (p->filhos == 1)
		{
			int posFilho;
			for (posFilho = 0; posFilho < MAX && (p->filho[posFilho] == NULL); posFilho++)
				;
			PTRC filho = p->filho[posFilho];
			string novaStr = strcat(p->str, filho->str);
			p = filho;
			p->str = novaStr;
			p->final = filho->final;
		}

		// Se tiver dois ou mais não pode remover, só marca que não é fim de palavra
		else if (p->filhos > 1)
		{
			p->final = 0;
		}

		// Se não possui filhos só libera a memoria e retorna NULL
		else
		{
			free(p);
			return NULL;
		}
	}

	// Senão tem que andar na arvore
	else
	{
		int posDiferenca = diferenca(p->str, str);
		int index = str[posDiferenca] - 'a';
		if (index < MAX && index >= 0)
		{
			string old = "";
			if(p->filho[index] != NULL)
			old = strconcat("",p->filho[index]->str);

			p->filho[index] = remover(p->filho[index], getSufixo(str, posDiferenca));
			string new = "";
			if(p->filho[index] != NULL) {
				new = strconcat("",p->filho[index]->str);
			}

			if (strcmp(old,new) != 0 && p->filho[index] == NULL)
			{
				p->filhos--;
			}

			// Só ficou com 1 filho e nao é final de palavra, concatena
			if (p->filhos == 1 && p->final == 0)
			{
				int posFilho;
				for (posFilho = 0; posFilho < MAX && (p->filho[posFilho] == NULL); posFilho++)
					;
				PTRC filho = p->filho[posFilho];
				string novaStr = strcat(p->str, filho->str);
				p = filho;
				p->str = novaStr;
				p->final = 1;
			}
		}
	}

	return p;
}

void imprime_sub_rec(PTRC p, string str, int i, int nivel)
{
	if (p != NULL)
	{
		// current = strconcat(current, raiz->str);
		if (i == nivel)
		{
			printf("(");
			printf("%s : %d", (strlen(p->str) == 0) ? "-" : p->str, p->filhos);
			printf(") ");
		}

		int pos = compareStrings(str, p->str);
		string strsufix = getSufixo(str, pos);
		string psufix = getSufixo(p->str, pos);

		if (strlen(psufix) > 0)
		{ // Se gera um sufixo para P é porque STR é menor logo as subarvores são prefixos de STR
			for (int j = 0; j < MAX; j++)
			{
				imprime_sub_rec(p->filho[j], strsufix, i + 1, nivel);
			}
		}
		else
		{ // se não gera um sufixo para P é porque ou str é maior(precisa descer na arvore) ou igual(achou o prefixo, imprime todas as subarvores)
			if (pos == -1)
			{ // str é igual a P, imprime todas as subarvores
				for (int j = 0; j < MAX; j++)
			{
				imprime_sub_rec(p->filho[j], strsufix, i + 1, nivel);
			}
			}
			else
			{ // não são iguais, desce para o sufixo de str
				int index = strsufix[0] - 'a';
				imprime_sub_rec(p->filho[index], strsufix, i + 1, nivel);
			}
		}
	}
}

void imprimir_sub(PTRC p, string str)
{
	printf("Sub-arvore da palavra: %s\n", str);
	int i, alturaArvore;
	alturaArvore = altura(p);
	printf("Print por Nivel:\n");
	for (i = 0; i <= alturaArvore-1; i++)
	{
		printf("Nivel %d:  ", i);
		imprime_sub_rec(p, str, 0, i);
		printf("\n");
	}
}

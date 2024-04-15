#ifndef PATRICIA_H
#define PATRICIA_H

// Tamanho do alfabeto
#define MAX 26

typedef char *string;

struct no
{
	string str;					// Palavra armazenada no No
	int filhos;					// Quantidade de filhos do No
	int final;					// Flag final de palavra
	struct no *filho[MAX];		// Vetor de ponteiros para os Nos filhos
};

typedef struct no *PTRC;

/*
 * @brief Cria um novo no folha da arvore PATRICIA, alocando espaco em memoria e atribuindo as variaveis
 * @returns Novo No da arvore PATRICIA
 * @pre nenhuma
 * @post Novo No e retornado
 * @param str String a ser gravada no No
 */
PTRC cria_no(string str);

/*
 * @brief Compara duas strings, verificando em que posicao diferem
 * @returns Posicao em que diferem
 * @pre nenhuma
 * @post Retorna em qual posicao ocorre a primeira diferenca
 * @param str1 String a ser testada
 * @param str2 String a ser testada
 */
int compareStrings(string str1, string str2);

/*
 * @brief Dada duas Strings, retorna o prefixo em comum entre elas
 * @returns String com prefixo em comum
 * @pre nenhuma
 * @post Compara as strings e retorna o prefixo em comum
 * @param str1 String a ser testada
 * @param str2 String a ser testada
 */
string getPrefixo(string str1, string str2);

/*
 * @brief Retorna o sufixo de str, dada a posicao n
 * @returns String sufixo de str
 * @pre nenhuma
 * @post Recorta a string, retornando seu sufixo
 * @param str String a ser recortada
 * @param n Posicao inicial do recorte
 */
string getSufixo(string str, int n);

/*
 * @brief Insere um novo No, com o conteudo de str na arvore p
 * @returns Arvore modificada com a nova palavra inserida
 * @pre Arvore deve ser inicializada antes
 * @post A palavra str e inserida na arvore p
 * @param p Raiz da arvore PATRICIA
 * @param str Palavra a ser inserida na arvore
 */
PTRC inserir(PTRC p, string str);

/*
 * @brief Concatena str2 em str1
 * @returns String com conteúdo str1+str2
 * @pre nenhuma
 * @post As palavras sao concatenadas e str3 e retornada
 * @param str1 Palavra base
 * @param str2 Palavra a ser concatenada em str1
 */
char *strconcat(char *str1, const char *str2);

/*
 * @brief Auxiliar de consultaPalavra()
 * @returns nada
 * @pre A arvore p deve estar inicializada na memoria
 * @post As 10 primeiras palavras com prefixo str sao mostradas na tela
 * @param p Raiz da arvore PATRICIA
 * @param str prefixo desejado das palavras
 */
void consultaPalavraRec(PTRC p, string str, string current, int *count);

/*
 * @brief Imprime todas as palavras do dicionario
 * @returns nada
 * @pre A arvore p deve estar inicializada na memoria
 * @post Todas as palavras presentes na arvore sao impressas na tela
 * @param p Raiz da arvore PATRICIA
 */
void imprime_tudo(PTRC p, char *current);

/*
 * @brief Consulta as 10 primeiras palavras com o prefixo str presentes na arvore
 * @returns nada
 * @pre A arvore p deve estar inicializada na memoria
 * @post As 10 primeiras palavras com prefixo str sao mostradas na tela
 * @param p Raiz da arvore PATRICIA
 * @param str prefixo desejado das palavras
 */
void consultaPalavra(PTRC p, string str);

/*
 * @brief Calcula a altura da arvore
 * @returns Altura da arvore
 * @pre A arvore root deve estar inicializada na memoria
 * @post Calcula e retorna a altura da arvore
 * @param root raiz da arvore PATRICIA
 */
int altura(PTRC root);

/*
 * @brief Imprime o nivel da arvore
 * @returns nada
 * @pre A arvore p deve estar inicializada
 * @post Imprime na tela o nivel
 * @param p Raiz da arvore PATRICIA
 * @param i iterador
 * @param nivel nivel a ser impresso
 */
void printNivel(PTRC p, int i, int nivel);

/*
 * @brief Imprime a arvore por niveis
 * @returns nada
 * @pre A arvore p deve estar inicializada
 * @post Imprime a arvore por niveis
 * @param p Raiz da arvore PATRICIA
 */
void printPorNivel(PTRC p);

/*
 * @brief Remove a palavra str da arvore
 * @returns arvore com str removido
 * @pre A arvore p deve estar inicializada
 * @post A palavra str e removida e a arvore retornada
 * @param p Raiz da arvore PATRICIA
 * @param str Palavra a ser removida
 */
PTRC remover(PTRC p, string str);

/*
 * @brief Imprime por nivel, os Nos que tem como prefixo str
 * @returns nada
 * @pre A arvore p deve estar inicializada
 * @post Os Nos que contem str como prefixo sao impressos
 * @param p Raiz da arvore PATRICIA
 * @param str Prefixo desejado
 */
void imprimir_sub(PTRC p, string str);

/*
 * @brief Auxiliar de imprimir_sub(), imprime o nivel
 * @returns nada
 * @pre A arvore p deve estar inicializada
 * @post Imprime Nos do nivel que contem str como prefixo
 * @param p Raiz da arvore PATRICIA
 * @param str Prefixo desejado
 * @param i iterador
 * @param nivel nivel atual
 */
void imprime_sub_rec(PTRC p, string str, int i, int nivel);

/*
 * @brief Auxiliar de remover(), retorna a posicao que str e str2 diferem
 * @returns posicao que str e str2 sao diferentes
 * @pre nada
 * @post Retorna a posicao da primeira diferenca de str e str2
 * @param str String a ser testada
 * @param str2 String a ser testada
 */
int diferenca(string str,string str2);

#endif

#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>
#include "PATRICIA.h"

/*
 * @brief Imprime o menu principal e retorna a opcao selecionada
 * @returns Opcao do menu selecionada
 * @pre nenhuma
 * @post O programa e desviado para a opcao selecionada
 */
int menu();

/*
 * @brief Le o arquivo de texto com as palavras, tanto para insercao quanto para remocao
 * @returns nova arvore criada a partir das palavras lidas
 * @pre a arvore deve estar inicializada na memoria
 * @post le o arquivo e retorna a arvore
 * @param p Raiz da arvore PATRICIA
 * @param func flag de operacao, 1 -> Insercao || 2 -> Remocao
 */
PTRC menu_ler_arquivo(PTRC p, int func);

/*
 * @brief Trata a string recebida, removendo caracteres especiais e convertendo caracteres maiusculos
 * @returns nada
 * @pre nehuma
 * @post str e modificada
 * @param str String a ser tratada
 */
void transformarString(char* str);

/*
 * @brief Auxiliar de menu_ler_arquivo(), faz a leitura da linha, trata a linha e faz a insercao/remocao
 * @returns Novo No da arvore PATRICIA
 * @pre a arvore deve estar inicializada na memoria
 * @post Novo No e retornado
 * @param p Raiz da arvore PATRICIA
 * @param f arquivo a ser lido
 * @param func flag de operacao, 1 -> Insercao || 2 -> Remocao
 */
PTRC ler_txt(PTRC p, FILE *f, int func);

/*
 * @brief Exibe o menu de consultar palavra, le o prefixo desejado e desvia o programa para a funcao de consultar
 * @returns nada
 * @pre A arvore deve estar inicializada na memoria
 * @post O programa e desviado para a funcao de consultar com a string lida
 * @param p Raiz da arvore PATRICIA
 */
void menu_consultar(PTRC p);

/*
 * @brief Exibe o menu de imprimir subniveis dado um prefixo, le o prefixo e desvia o programa
 * @returnsnada
 * @pre A arvore deve estar inicializada na memoria
 * @post O programa e desviado para a funcao de imprimir subarvore com o prefixo em comum
 * @param p Raiz da arvore PATRICIA
 */
void menu_imprimir_sub(PTRC p);

/*
 * @brief Exibe o menu da funcao que imprime toda a arvore
 * @returns nada
 * @pre A arvore deve estar inicializada na memoria
 * @post Imprime todas as palavras do dicionario
 * @param p Raiz da arvore PATRICIA
 */
void menu_imprimir_tudo(PTRC p);


#endif
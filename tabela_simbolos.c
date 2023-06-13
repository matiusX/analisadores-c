#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// constante repesenta o tamanho da tabela
#define tam_total 100

// variável que guarda a posição do ID no arquivo de entrada
int posicao = 0;

// estrutura Identificador com posição, nome do ID e tipo
typedef struct{
    int id_posicao;
    char id_nome[50];
    char id_tipo[20];
}Identificador;

// tabela hash do tipo Identificador
Identificador tabelaHash[tam_total];

// inicializa a tabela
void inicializarTabela(){
    int i;

    for(i = 0; i < tam_total; i++)
       strcpy(tabelaHash[i].id_nome, "");
}

// função de espalhamento (resto da divisão da chave por tam_total)
int funcaoHash(int chave){
    return chave % tam_total;
}

// Função hash a partir de texto
int funcaoHashString(char str[]){
    int i, tamS = strlen(str);
    unsigned int hash = 0;

    for(i = 0; i < tamS; i++)
        hash += str[i] * (i + 1); // somatório do código ASCII vezes a posição
    return hash % tam_total;
}

// inserir uma Identificador na tabela
void inserirHash(char id_nome[], char id_tipo[]){
    Identificador p;
    p.id_posicao = posicao;
    strcpy(p.id_nome, id_nome);
    strcpy(p.id_tipo, id_tipo);
    posicao += 1;
    int indice = funcaoHashString(p.id_nome);
    while(strlen(tabelaHash[indice].id_nome) > 0)
        indice = funcaoHash(indice + 1);
    tabelaHash[indice] = p;
}

// busca um ID na tabela pelo nome
Identificador* buscarHash(char chave[]){
    int indice = funcaoHashString(chave);
    while(strlen(tabelaHash[indice].id_nome) > 0){
        if(strcmp(tabelaHash[indice].id_nome, chave) == 0)
            return &tabelaHash[indice];
        else
            indice = funcaoHash(indice + 1);
    }
    return NULL;
}

// imprime a tabela de símbolos(tabela hash) no arquivo de saída
void imprimirHash(FILE* arquivo_hash){
    int i;
    fprintf(arquivo_hash, "\n------------------------TABELA DE SÍMBOLOS---------------------------\n");
    fprintf(arquivo_hash, "\nPOSIÇÃO  |  IDENTIFICADOR  |  TIPO\n\n");

    /*
        POSICAO -> posição que o ID aparece no código de entrada   
        IDENTIFICADOR -> nome do ID 
        TIPO -> tipo do ID
    */

    for(i = 0; i < tam_total; i++){
        if(strlen(tabelaHash[i].id_nome) > 0)

            // se o ID não tem tipo definido (Erro de declaração)
            if(strcmp(tabelaHash[i].id_tipo, "") == 0)
                fprintf(arquivo_hash, "%d  |  %s  |   %s\n", tabelaHash[i].id_posicao, tabelaHash[i].id_nome, "ERRO: ID NÃO DEFINIDO");
            
            // se o ID tem tipo definido 
            else
                fprintf(arquivo_hash, "%d  |  %s  |  %s\n", tabelaHash[i].id_posicao, tabelaHash[i].id_nome, tabelaHash[i].id_tipo);
    }
    fprintf(arquivo_hash, "----------------------------------------------------------\n");
}
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// arquivo onde foi feito o código da tabela de símbolos
#include "tabela_simbolos.c"

// arquivo onde foi feito o código da análise léxica
#include "analise_lexica.c"

// arquivo onde foi feito o código da análise sintática
#include "analise_sintatica.c"


// ====================================== MAIN ======================================

void main(int argc, char *argv[]){

  arquivo = fopen(argv[1], "rb");

  FILE* f_out_hash = fopen("tabela_de_simbolos.txt", "wb"); // arquivo de saída da tabela de símbolos

  inicializarTabela();  // inicializa a tabela

  grava_token(arquivo); // faz a varredura do código de entrada e imprime os tokens e lexemas no arquivo de saída

  printf("\nAnalise Lexica executada com sucesso!\n");

  imprimirHash(f_out_hash); // imprime a tabela de símbolos no arquivo de saída tabela_de_simbolos.txt

  printf("\nTabela de simbolos gerada com sucesso!\n");

  FILE* f_out = fopen("saida.txt", "rb");

  syn_analysis(f_out);

  fclose(f_out);

  printf("\nSaida gerada com sucesso!\n");
  fclose(arquivo); 
}
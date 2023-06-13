#include <stdio.h>
#include "lex.yy.h" // inclui o cabeçalho gerado pelo lex
#include "y.tab.h" // inclui o cabeçalho gerado pelo yacc
extern FILE* yyin; // declara a entrada de dados (pode ser um arquivo ou a entrada padrão)

int main(int argc, char **argv) {
    FILE* arquivo = fopen("resultado.txt", "wb");
    if(argc < 2) {
        printf("Uso: %s arquivo_de_entrada\n", argv[0]);
        return 1;
    }
    FILE *f = fopen(argv[1], "r");
    if(!f) {
        printf("Não foi possível abrir o arquivo %s\n", argv[1]);
        return 1;
    }
    yyout = arquivo;
    yyin = f;
    //yylex();
    //while(yylex() != 0);
    yyparse();
    fclose(f);
    fclose(arquivo);
    return 0;
}

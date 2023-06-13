%{
#include <stdio.h>
#include <string.h>
#include "y.tab.h"
%}

%option yylineno

%%

"/*"        {
                int comment_depth = 1;
                while(comment_depth > 0) {
                    int c = input();
                    if(c == EOF) {
                        fprintf(yyout, "Erro: Comentário não fechado\n");
                        return 1;
                    }
                    if(c == '/' && input() == '*') {
                        comment_depth++;
                    }
                    if(c == '*' && input() == '/') {
                        comment_depth--;
                    }
                }
            }

"//"        {
                while(input() != '\n') {
                    if (input() == EOF) {
                        return 0;
                    }
                }
            }

"+"         { fprintf(yyout, "OPERADOR DE SOMA\n"); return '+';}
"-"         { fprintf(yyout, "OPERADOR DE SUBTRAÇÃO\n"); return '-';}
"*"         { fprintf(yyout, "OPERADOR DE MULTIPLICAÇÃO\n"); return '*';}
"/"         { fprintf(yyout, "OPERADOR DE DIVISÃO\n"); return '/';}
"%"         { fprintf(yyout, "OPERADOR MÓDULO\n"); return '%';}
"?"         { fprintf(yyout, "SINAL DE INTERROGAÇÃO\n"); return '?';}
":"         { fprintf(yyout, "SINAL DE DOIS PONTOS\n"); return ':';}
"!"         { fprintf(yyout, "OPERADOR LÓGICO DE NEGAÇÃO\n"); return '!';}
"&"         { fprintf(yyout, "OPERADOR LÓGICO AND\n"); return '&';}
"->"        { fprintf(yyout, "OPERADOR DE ACESSO DE MEMBRO\n"); return TOK_SETA;}
"<"         { fprintf(yyout, "OPERADOR MENOR QUE\n"); return '<';}
">"         { fprintf(yyout, "OPERADOR MAIOR QUE\n"); return '>';}
"=="        { fprintf(yyout, "OPERADOR DE IGUALDADE\n"); return TOK_IGUAL;}
"="         { fprintf(yyout, "OPERADOR DE ATRIBUIÇÃO\n"); return '=';}
"!="        { fprintf(yyout, "OPERADOR DE DIFERENTE DE\n"); return TOK_DIFERENTE; }
"<="        { fprintf(yyout, "OPERADOR MENOR OU IGUAL QUE\n"); return TOK_MENOR_IGUAL; }
">="        { fprintf(yyout, "OPERADOR MAIOR OU IGUAL QUE\n"); return TOK_MAIOR_IGUAL; }
"+="        { fprintf(yyout, "OPERADOR DE ATRIBUIÇÃO SOMA\n"); return TOK_ATRIB_SOMA; }
"-="        { fprintf(yyout, "OPERADOR DE ATRIBUIÇÃO SUBTRAÇÃO\n"); return TOK_ATRIB_SUB; }
"*="        { fprintf(yyout, "OPERADOR DE ATRIBUIÇÃO MULTIPLICAÇÃO\n"); return TOK_ATRIB_MULT; }
"/="        { fprintf(yyout, "OPERADOR DE ATRIBUIÇÃO DIVISÃO\n"); return TOK_ATRIB_DIV; }
"%="        { fprintf(yyout, "OPERADOR DE ATRIBUIÇÃO MÓDULO\n"); return TOK_ATRIB_MOD; }
"++"        { fprintf(yyout, "OPERADOR DE INCREMENTO\n"); return TOK_INC; }
"--"        { fprintf(yyout, "OPERADOR DE DECREMENTO\n"); return TOK_DEC; }
"&&"        { fprintf(yyout, "OPERADOR LÓGICO AND\n"); return TOK_AND; }
"||"        { fprintf(yyout, "OPERADOR LÓGICO OR\n"); return TOK_OR; }
","         { fprintf(yyout, "VÍRGULA\n"); return ','; }
";"         { fprintf(yyout, "PONTO E VÍRGULA\n"); return ';'; }
"."         { fprintf(yyout, "PONTO\n"); return '.'; }
"("         { fprintf(yyout, "PARENTESE ABERTO\n"); return '('; }
")"         { fprintf(yyout, "PARENTESE FECHADO\n"); return ')'; }
"{"         { fprintf(yyout, "CHAVE ABERTA\n"); return '{'; }
"}"         { fprintf(yyout, "CHAVE FECHADA\n"); return '}'; }
"["         { fprintf(yyout, "COLCHETE ABERTO\n"); return '['; }
"]"         { fprintf(yyout, "COLCHETE FECHADO\n"); return ']';}

"void"      { fprintf(yyout, "PALAVRA RESERVADA: void\n"); return TOK_VOID;}
"int"       { fprintf(yyout, "PALAVRA RESERVADA: int\n"); return TOK_INT;}
"float"     { fprintf(yyout, "PALAVRA RESERVADA: float\n"); return TOK_FLOAT;}
"char"      { fprintf(yyout, "PALAVRA RESERVADA: char\n"); return TOK_CHAR;}
"bool"      { fprintf(yyout, "PALAVRA RESERVADA: bool\n"); return TOK_BOOL;}
"if"        { fprintf(yyout, "PALAVRA RESERVADA: if\n"); return TOK_IF;}
"else"      { fprintf(yyout, "PALAVRA RESERVADA: else\n"); return TOK_ELSE;}
"for"       { fprintf(yyout, "PALAVRA RESERVADA: for\n"); return TOK_FOR;}
"while"     { fprintf(yyout, "PALAVRA RESERVADA: while\n"); return TOK_WHILE;}
"do"        { fprintf(yyout, "PALAVRA RESERVADA: do\n"); return TOK_DO;}
"return"    { fprintf(yyout, "PALAVRA RESERVADA: return\n"); return TOK_RETURN;}
"break"     { fprintf(yyout, "PALAVRA RESERVADA: break\n"); return TOK_BREAK;}
"continue"  { fprintf(yyout, "PALAVRA RESERVADA: continue\n"); return TOK_CONTINUE;}
"goto"      { fprintf(yyout, "PALAVRA RESERVADA: goto\n"); return TOK_GOTO;}
"true"      { fprintf(yyout, "PALAVRA RESERVADA: true\n"); return TOK_TRUE;}
"false"     { fprintf(yyout, "PALAVRA RESERVADA: false\n"); return TOK_FALSE;}
"double"    { fprintf(yyout, "PALAVRA RESERVADA: double\n"); return TOK_DOUBLE;}

[a-zA-Z_][a-zA-Z0-9_]* {
    int TAM_MAX_ID = 50;
    if(strlen(yytext) > TAM_MAX_ID) {
        fprintf(stderr, "Erro na linha %d: identificador %s é muito longo\n", yylineno, yytext);
        exit(1);
    }
    fprintf(yyout, "IDENTIFICADOR: %s\n", yytext);
    return TOK_IDENTIFICADOR;
}

[0-9]+ {
    int valor = atoi(yytext);
    if(valor > 32767) {
        fprintf(stderr, "Erro na linha %d: valor inteiro %d é muito grande\n", yylineno, valor);
        exit(1);
    }
    fprintf(yyout, "LITERAL INTEIRO: %d\n", valor);
    return TOK_NUMERO;
}

[0-9]+(\.[0-9]+)? {
    float valor = atof(yytext);
    if(valor > 32767) {
        fprintf(stderr, "Erro na linha %d: valor decimal %f é muito grande\n", yylineno, valor);
        exit(1);
    }
    fprintf(yyout, "LITERAL DECIMAL: %f\n", valor);
    return TOK_NUMERO_DECIMAL;
}

\'[^\']\' {
    fprintf(yyout, "LITERAL CARACTERE: %s\n", yytext);
    return TOK_CARACTERE;
}

\"[^\"\n]*\" {
    int TAM_MAX_STR = 100;
    if(strlen(yytext) > TAM_MAX_STR) {
        fprintf(stderr, "Erro na linha %d: string %s é muito longa\n", yylineno, yytext);
        exit(1);
    }
    fprintf(yyout, "LITERAL STRING: %s\n", yytext);
    return TOK_STRING;
}



[ \t\n] { /* ignorar espaços em branco e quebras de linha */ }
. { fprintf(yyout, "Caractere inválido: %s\n", yytext); exit(1); }

%%

int yywrap() {
        return 1;
}

%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lex.yy.h"

int yylex();
void yyerror(const char* s);
extern int yylineno;
extern char* yytext;
%}

%token TOK_SETA
%token TOK_IGUAL
%token TOK_DIFERENTE
%token TOK_MENOR_IGUAL
%token TOK_MAIOR_IGUAL
%token TOK_ATRIB_SOMA
%token TOK_ATRIB_SUB
%token TOK_ATRIB_MULT
%token TOK_ATRIB_DIV
%token TOK_ATRIB_MOD
%token TOK_INC
%token TOK_DEC
%token TOK_AND
%token TOK_OR
%token TOK_VOID
%token TOK_INT
%token TOK_FLOAT
%token TOK_CHAR
%token TOK_BOOL
%token TOK_IF
%token TOK_ELSE
%token TOK_FOR
%token TOK_WHILE
%token TOK_DO
%token TOK_RETURN
%token TOK_BREAK
%token TOK_CONTINUE
%token TOK_GOTO
%token TOK_TRUE
%token TOK_FALSE
%token TOK_DOUBLE
%token TOK_IDENTIFICADOR
%token TOK_NUMERO
%token TOK_CARACTERE
%token TOK_STRING
%token TOK_NUMERO_DECIMAL

%start programa

%%

programa: lista_decl
        ;

lista_decl: lista_decl decl
          | decl
          ;

decl: decl_var
    | decl_func
    ;

decl_var: espec_tipo var ';'
        ;

espec_tipo: TOK_INT
          | TOK_VOID
          | TOK_FLOAT
          ;

decl_func: espec_tipo TOK_IDENTIFICADOR '(' params ')' com_comp
         ;

params: lista_param
      | TOK_VOID
      | /* vazio */
      ;

lista_param: lista_param ',' param
           | param
           ;

param: espec_tipo var
     ;

decl_locais: decl_locais decl_var
           | /* vazio */
           ;

lista_com: comando lista_com 
         | /* vazio */
         ;

comando: com_expr
        | com_atrib
        | com_comp
        | com_selecao
        | com_repeticao
        | com_retorno
        ;

com_expr: exp ';'
        | ';'
        ;

com_atrib: var '=' exp ';'
         ;

com_comp: '{' decl_locais lista_com '}'
        ;

com_selecao: TOK_IF '(' exp ')' comando
            | TOK_IF '(' exp ')' com_comp TOK_ELSE comando
            ;

com_repeticao: TOK_WHILE '(' exp ')' comando
             | TOK_DO comando TOK_WHILE '(' exp ')' ';'
             ;

com_retorno: TOK_RETURN ';'
           | TOK_RETURN exp ';'
           ;

exp: exp_soma op_relac exp_soma
   | exp_soma 
   ;

op_relac: TOK_MENOR_IGUAL
        | '<'
        | '>'
        | TOK_MAIOR_IGUAL
        | TOK_IGUAL
        | TOK_DIFERENTE
        ;

exp_soma: exp_soma op_soma exp_mult
        | exp_mult
        ;

op_soma: '+'
       | '-'
       ;

exp_mult: exp_mult op_mult exp_simples
        | exp_simples
        ;

op_mult: '*'
       | '/'
       | '%'
       ;

exp_simples: '(' exp ')'
           | var
           | cham_func
           | literais
           ;

literais: TOK_NUMERO
        | TOK_NUMERO '.' TOK_NUMERO
        ;

cham_func: TOK_IDENTIFICADOR '(' args ')'
        ;

var: TOK_IDENTIFICADOR
    | TOK_IDENTIFICADOR '[' TOK_NUMERO ']'
    ;

args: lista_arg
    | /* vazio */
    ;

lista_arg: lista_arg ',' exp
        | exp
        ;

%%

void yyerror(const char* s) {
    fprintf(yyout, "Erro na linha %d: %s próximo ao token '%s'\n", yylineno, s, yytext);
}

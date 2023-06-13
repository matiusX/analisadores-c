# Análise Léxica

### Objetivo:

O objetivo deste trabalho é construir um analisador léxico para uma linguagem de programação de alto nível. 

### ARQUIVO DE ENTRADA
    *formato = .txt
    *deve conter palavras que fazem parte do Alfabeto definido
    *caso nao contenha, deve dar erro e apontar a linha onde deu erro
    *foram enviados arquivos de entrada para exemplificar os casos de teste 

### ARQUIVO DE SAIDA DA ANÁLISE LÉXICA
    *formato = saida.txt
    *contem o token e o lexema de cada elemento do arquivo de entrada
    *estao no formado: TOKEN   LEXEMA\n

### ARQUIVO DE SAIDA DA TABELA DE SÍMBOLOS
    *formato = tabela_de_simbolos.txt
    *contém a tabela de símbolos do compilador
    *está no formato: POSICAO   IDENTIFICADOR   TIPO
        *POSICAO -> posição do ID no código de entrada
        *IDENTIFICADOR -> nome do ID
        *TIPO -> tipo do ID (ex: bool, int, char, etc.)

### COMO EXECUTAR
    *o codigo principal se chama codigo_fonte.c
    *foi compilado utilizando o gcc nas versoes 18.04 e ____ do ubuntu
    *tambem foi enviado o programa compilado: "codigo_fonte.out"
    *para compilar o programa (no linux), faca no terminal: gcc codigo_fonte.c -o codigo_fonte.out
    *para rodar o programa, faca no terminal: ./codigo_fonte.out entrada.txt
        ->"entrada.txt" deve ser o arquivo contendo os lexemas para teste

### ARQUIVOS DE TESTE
    *foram enviados dois arquivos para teste
    *palavras nao-reservadas devem ser tratadas como id (a validacao se eh um id valido ou nao so ocorre na analise sintatica)
    *palavras como boolean, boleano, inteiro devem ser tratadas como id (a avaliacao se sao palavras reservadas deve ocorrer apenas no sintatico)    
    *entrada.txt
        -> deve rodar corretamente
        -> abrange grande parte dos tokens e lexemas
        -> testa se os comentarios (em bloco e linha) aparecem no arquivo de saida (nao aparecem)
        -> faz verificacoes em strings
    *entrada_com_erro.txt
        ->herda alguns lexemas de "entrada.txt"
        ->deve dar erro no meio do codigo
        ->testa se o codigo realmente para de rodar quando aparece um erro

# Analise Sintatica

### Objetivo:

O objetivo deste trabalho é construir um analisador sintático para uma linguagem de programação de alto nível. 
Para isso, utilizamos o Yacc e o Lex.

### Lex

Lex é uma ferramenta que gera um analisador léxico, também conhecido como scanner, que é responsável por analisar a entrada de um programa em busca de padrões de caracteres que representam tokens, tais como palavras-chave, operadores, identificadores, números, símbolos de pontuação, etc. O analisador léxico produz uma sequência de tokens que é passada para o analisador sintático.

### Yacc

Yacc é uma ferramenta que gera um analisador sintático, também conhecido como parser, que é responsável por analisar a estrutura gramatical do programa em busca de padrões de tokens que correspondem a regras gramaticais definidas para a linguagem. O analisador sintático produz uma árvore de análise sintática que é usada pelo compilador ou interpretador para gerar o código executável.

### ARQUIVO DE ENTRADA
    *formato = entrada.txt
    *deve conter palavras que fazem parte do Alfabeto definido
    *caso nao contenha, deve dar erro e apontar a linha onde deu erro
    *foram enviados arquivos de entrada para exemplificar os casos de teste 

### ARQUIVO DE SAIDA
    *formato = resultado.txt
    *contem o token e o lexema de cada elemento do arquivo de entrada
    *estao no formado: TOKEN   LEXEMA\n
    *contém o erro da análise sintática, caso exista algum
    *o erro está no formato: "Erro na linha X: syntax error próximo ao token Y

### COMO EXECUTAR
    *utilizamos o flex e o yacc para a realização deste trabalho.
    *execute os seguintes passos, no terminal:

        -> instalação do lex e yacc:
            $ sudo apt-get update
            $ sudo apt-get install flex
            $ sudo apt-get install bison

        -> compilação e execução:
            $ flex -o lex.yy.c --header-file=lex.yy.h lexico.l
            $ yacc -d parser.y
            $ gcc lex.yy.c -lfl -o lexico
            $ gcc lex.yy.c y.tab.c main.c -o meu_programa
            $ ./meu_programa entrada.txt
            
    *onde "entrada.txt" deve ser o arquivo contendo os lexemas para teste
    *foi compilado utilizando o gcc nas versoes 18.04 e 22.04 do ubuntu

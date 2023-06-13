#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

FILE *arquivo;
const int tamanho_token_string = 100; // tamanho do buffer que guarda strings
int line = 1;               // guarda as linhas do arquivo de entrada
int	putBack;                // guarda o caractere que será colocado de volta para ser lido novamente 
char numFloat[50];          // guarda um número float
bool flagFloat = false;     // flag que indica o tipo do número lido (False -> Inteiro , True -> Float)
char varID[50];             // guarda o nome do ID
char guarda_pal_reserv[20]; // guarda uma palavra reservada (usada na tabela de símbolos para guardar o tipo de um ID)

/*
definindo os tokens e lexemas usados. 
Todos estão listados de forma mais organizada no arquivo "tokens_definidos.txt".
*/

char *tokens[] = { "OP_SOMA","OP_SUB","OP_MULT","OP_DIV","NUM_INT","RESTO","QUEST",
                  "COLON","NEG","ADDR","ARROW","LESS","GREATER","EQUAL","ATR",
                  "DIF","LESS_EQ","GREATER_EQ","PLUS_EQ","MINUS_EQ","MULT_EQ",
                  "DIV_EQ","RESTO_EQ","INCR","DECRE","AND","OR","COMMA","SEMICOLON",
                  "PARENT_OP","PARENT_CL","CHAVE_OP","CHAVE_CL","COLCH_OP","COLCH_CL",
                  "CARACTERE","STRING","VOID","INT","FLOAT","CHAR","BOOL","IF",
                  "ELSE","FOR","WHILE","DO","RETURN","BREAK","CONTINUE","GOTO","TRUE",
                  "FALSE","DOUBLE","NUM_FLOAT","ID"};

char *lexemas[] = { "+","-","*","/","integ","%","?",
                    ":","!","&","->","<",">","==","=",
                    "!=","<=",">=","+=","-=","*=",
                    "/=","%=","++","--","&&","||",",",";",
                    "(",")","{","}","[","]",
                    "chr","str","void","int","float","char","bool","if",
                    "else","for","while","do","return","break","continue","goto","true",
                    "false","double","floater","id"};


//ABAIXO ESTAO AS FUNCOES AUXILIARES QUE USAMOS NO TRABALHO

// Estrutura de um token
struct token {
  char lexemaStr[100];  // guarda lexemas que são strings
  int token;  
  int lexema;
};

// Enum para mapear todos os tokens
enum {
  T_SOMA, T_SUB, T_MULT, T_DIV, T_NUMINT, T_RESTO, T_QUEST, // 7
  T_COLON, T_NEG, T_ADDR, T_ARROW, T_LESS, T_GREATER, T_EQ, T_ATR, // 15
  T_DIF, T_LESS_EQ, T_GREATER_EQ, T_PLUS_EQ, T_MINUS_EQ, T_MULT_EQ, // 21
  T_DIV_EQ, T_RESTO_EQ, T_INCR, T_DECRE, T_AND, T_OR, T_COMMA, T_SEMICOLON, // 29
  T_PARENT_OP, T_PARENT_CL, T_CHAVE_OP, T_CHAVE_CL, T_COLCH_OP, T_COLCH_CL, // 35
  T_CARACTERE, T_STRING, T_VOID, T_INT, T_FLOAT, T_CHAR, T_BOOL, T_IF,    // 43
  T_ELSE, T_FOR, T_WHILE, T_DO, T_RETURN, T_BREAK, T_CONTINUE, T_GOTO, T_TRUE, // 52
  T_FALSE, T_DOUBLE, T_NUMFLOAT, T_ID
};



// ====================================== FUNÇÕES UTILIZADAS ======================================



// Coloca de volta um caractere que foi retirado e deve voltar para leitura
static void colocaDeVolta(int c) {
  putBack = c;
}

// Pega o próximo caractere, caso haja algum.
static int prox_char() {
  int c;
  
  if (putBack) {                // caso tenha algum caractere para ser colocado de volta
    c = putBack;                
    putBack = 0;
    return c;
  }

  c = fgetc(arquivo);           // Lendo o caractere da vez 

  if ('\n' == c) {
    line++;                     // Incrementa a linha
  }

  return c;
}

// Retorna o próximo caracter válido 
int pulaProProximo(void) {
  int c;
  c = prox_char();

  while (' ' == c || '\t' == c || '\n' == c || '\r' == c || '\f' == c) {
    c = prox_char();
  }

  return (c);
}

// Ignora comentários do arquivo de entrada
int ignoraComentario(FILE* arq) {
  int c;

  if(c == '/') {
    c = prox_char();
    if(c == '/') {
        c = prox_char();
        while (c != '\n') {
            if(feof(arq) == true) { break; }
            c = prox_char();
        }
        c = pulaProProximo();
    } else if(c == '*') {
        c = prox_char();
        while (true) {
            if(feof(arq) == true) { break; }

            if(c == '*') {
                c = prox_char();
                if(c == '/') {
                    c = pulaProProximo();
                    break;
                }
            } else {
                c = prox_char();
            }
        }
    } else {
        colocaDeVolta(c);
        colocaDeVolta('/');
        c = prox_char();
    }
  } 
  else {
    return (c);
  }

  return (c);
}

// Retorna a posição do caractere c na string s,
// ou -1 se c não for encontrado
int posCaracter(char *s, int c) {
  char *p;

  p = strchr(s, c);
  return (p ? p - s : -1);
}

// Lê um float.
// Guarda o valor como string somente para 
// fins de printar no arquivo de saída.
int scanFloat(int c, int* pontC, char res[]) {
  int k, val = 0;
  c = prox_char();
  char resposta2[50];

  // Converte cada caractere em um valor inteiro
  while ((k = posCaracter("0123456789", c)) >= 0) {
    val = val * 10 + k;
    sprintf(resposta2, "%d", val);
    c = prox_char();
  }

  // concatena a segunda parte do número (depois do .)
  // com a primeira parte do número (antes do .)
  strcat(numFloat, resposta2);

  *pontC = c;

  // Atingimos um caractere não inteiro, colocamos de volta.
  colocaDeVolta(c);
  return val;
}

// Escaneia e retorna um inteiro do arquivo de entrada.
// Guarda o valor como uma string.
int scanInt(int c) {
  int k, val = 0;

  // Converte cada caractere em um valor inteiro
  while ((k = posCaracter("0123456789", c)) >= 0) {
    val = val * 10 + k;
    c = prox_char();
  }

  // se achar um . é porque é float
  if(c == '.') {
    flagFloat = true;
    sprintf(numFloat, "%d", val); // guarda a primeira parte lida (número antes do .)
    strcat(numFloat, ".");
    scanFloat(c, &c, numFloat);   // chama a função scanFloat para ler a próxima parte do número (depois do .)
  }

  // Atingimos um caractere não inteiro, colocamos de volta.
  colocaDeVolta(c);
  return val;
}

// Retorna o próximo caractere
// de um char ou string literal
static int scanChar(void) {
  int c;
  c = prox_char();  // lê o caractere 

  return c;   
}

// Pega uma string do arquivo de entrada e
// guarda no buff[]. Retorna o tamanho da string.
static int scanStr(char buf[]) {
  int i, c;
  // Loop enquanto tem espaço no buffer
  for (i=0; i<tamanho_token_string-1; i++) {
    c = scanChar();
    if (c == '"') {
      buf[i] = 0;
      return(i);
    }else if (c == '\\'){
      c = prox_char();
    }
    buf[i] = c;
  }
  printf("ERROR: String muito longa");
  return(0);
}

// Verifica o PRIMEIRO caractere de um ID
// e retorna se é válido ou não
bool verificaPrimLetraId(int c) {
  // se for letras minúsculas, letras maiúsculas, cifrão ou underline
  if((c >= 97 && c <= 122) || (c >= 65 && c <= 90) || c == 36 || c == 95) {
    return true;
  }
  return false;
}

// Verifica os caracteres de um ID
// e retorna se é válido ou não
bool verificaId(int c) {

  // se for letras minúsculas, letras maiúsculas, números, cifrão ou underline
  if((c >= 97 && c <= 122) || (c >= 65 && c <= 90) || (c >= 48 && c <= 57) || c == 36 || c == 95) {
    return true;
  }
  return false;
}

// Verifica se a string é um ID
void scanId(int c) {
  char aux[2];

  // Converte cada caractere em um valor inteiro
  while (verificaId(c) == true) {
    sprintf(aux, "%c", c);
    strcat(varID, aux);
    c = prox_char();
  }


  // Atingimos um caractere inválido, colocamos de volta.
  colocaDeVolta(c);
}



// Escaneia e retorna o próximo token encontrado na entrada.
// Retorna 1 se o token for válido, 0 se não houver mais tokens.
int scan(struct token *t, FILE* arq) {
  int c;

  // pula o espaço e os comentários
  c = pulaProProximo();
  c = ignoraComentario(arq);
 
  // Determina o token com base no caractere de entrada
  switch (c) {
  case EOF:     // EOF - fim do arquivo
    return (0);
  case '+':     // ------- COMEÇO DO SCAN DOS LEXEMAS -------
    c = prox_char();
    if (c == '=') {
      t->token = T_PLUS_EQ;
    } else if (c == '+') {
      t->token = T_INCR;
    } else {
      colocaDeVolta(c);
      t->token = T_SOMA; }
    break;
  case '-':
    c = prox_char();
    if (c == '>') {
      t->token = T_ARROW;
    } else if (c == '=') {
      t->token = T_MINUS_EQ;
    } else if (c == '-') {
      t->token = T_DECRE;
    } else {
      colocaDeVolta(c);
      t->token = T_SUB; }
    break;
  case '*':
    c = prox_char();
    if (c == '=') {
      t->token = T_MULT_EQ;
    } else {
      colocaDeVolta(c);
      t->token = T_MULT; }
    break;
  case '/':
    c = prox_char();
    if (c == '=') {
      t->token = T_DIV_EQ;
    } else {
      colocaDeVolta(c);
      t->token = T_DIV; }
    break;
  case '%':
    c = prox_char();
    if (c == '=') {
      t->token = T_RESTO_EQ;
    } else {
      colocaDeVolta(c);
      t->token = T_RESTO; }
    break;
  case '!':
    c = prox_char();
    if (c == '=') {
      t->token = T_DIF;
    } else {
      colocaDeVolta(c);
      t->token = T_NEG; }
    break;
  case '&':
    c = prox_char();
    if (c == '&') {
      t->token = T_AND;
    } else {
      colocaDeVolta(c);
      t->token = T_ADDR; }
    break;
  case '|':
    c = prox_char();
    if (c == '|') {
      t->token = T_OR;
    } else {
      printf("Caractere: %c não reconhecido na linha %d\n", c, line); }
    break;
  case '<':
    c = prox_char();
    if (c == '=') {
      t->token = T_LESS_EQ;
    } else {
      colocaDeVolta(c);
      t->token = T_LESS; }
    break;
  case '>':
    c = prox_char();
    if (c == '=') {
      t->token = T_GREATER_EQ;
    } else {
      colocaDeVolta(c);
      t->token = T_GREATER; }
    break;
  case '=':
    c = prox_char();
    if (c == '=') {
      t->token = T_EQ;
    } else {
      colocaDeVolta(c);
      t->token = T_ATR; }
    break;
  case '\'':
    t->lexema = scanChar();
    t->token = T_CARACTERE;
    if (prox_char() != '\'')
      printf("Esperado um '\'' no final de um char literal");
    break;
  case '\"': //comeca a ler uma string
    scanStr(t->lexemaStr);
    t->token= T_STRING;
    break;
  case '?': t->token = T_QUEST;
    break;
  case ':': t->token = T_COLON;
    break;
  case ',': t->token = T_COMMA;
    break;
  case ';': t->token = T_SEMICOLON;
    break;
  case '(': t->token = T_PARENT_OP;
    break;
  case ')': t->token = T_PARENT_CL;
    break;
  case '{': t->token = T_CHAVE_OP;
    break;
  case '}': t->token = T_CHAVE_CL;
    break;
  case '[': t->token = T_COLCH_OP;
    break;
  case ']': t->token = T_COLCH_CL;
    break;
  default:
    // Se o caractere lido for um número
    if (isdigit(c)) {
      int numInt = scanInt(c);
      // Se o número lido for um INTEIRO
      if(flagFloat == false) {
        t->lexema = numInt;
        t->token = T_NUMINT;
      // Se o número lido for um DECIMAL
      } else {
        t->token = T_NUMFLOAT;
      }
      flagFloat = false;
      break;
    }
    // Se pode ser um ID
    else if (verificaPrimLetraId(c) == true) {
      scanId(c);

      for(int i=37; i<=53; i++){

        // Se for uma PALAVRA RESERVADA
        if(strcmp(varID, lexemas[i]) == 0){
          t->token = i;
          strcpy(guarda_pal_reserv, lexemas[i]);
          return(1);
        }
      }

      // Caso realmente seja um ID
      t->token = T_ID;
      break;

    }

    printf("Caractere: %c não reconhecido na linha %d\n", c, line);
    exit(1);
  }

  // Encontramos um token
  return (1);
}

// Varredura de loop de todos os tokens no arquivo de entrada.
// Grava os tokens e os lexemas no arquivo de saída.
static void grava_token(FILE* arq) {
  struct token T;
  FILE* f_out = fopen("saida.txt", "wb");

  fprintf(f_out, "TOKENS | LEXEMAS\n-----------------\n");

  while (scan(&T, arq)) {

    // Para o programa caso ache um erro
    if(T.token == -1){
      break;
    }

    // Printa o TOKEN para o lexema lido
    fprintf(f_out, "%s",tokens[T.token]);

    // Printa o lexema de um NÚM. INTEIRO 
    if (T.token == T_NUMINT){
      fprintf(f_out, "   %d", T.lexema);
    }
    // Printa o lexema de um CARACTERE
    else if (T.token == T_CARACTERE) {
      fprintf(f_out, "   %c", T.lexema);
    }
    // Printa o lexema de uma STRING
    else if (T.token == T_STRING) {
      fprintf(f_out, "   \"%s\"", T.lexemaStr);
    }
    // Printa o lexema de um NÚM. FLOAT
    else if (T.token == T_NUMFLOAT) {
      fprintf(f_out, "   %s", numFloat);
    }
    // Printa o lexema de um ID
    else if (T.token == T_ID) {
      fprintf(f_out, " %s", varID);

      // Verifica se o ID já está na tabela de símbolos.
      // Se não estiver, insere ele.
      if(buscarHash(varID) == NULL) {
        inserirHash(varID, guarda_pal_reserv);
        sprintf(guarda_pal_reserv, "%s", ""); // ressetando o guarda_pal_reserv
      }

      sprintf(varID, "%s", ""); // ressetando o varID
    }    
    // Printa qualquer outro lexema
    else {
      fprintf(f_out, "   %s", lexemas[T.token]);
    }
    sprintf(varID, "%s", ""); //limpa o conteudo do ID
    fprintf(f_out, "\n");

    //limpa o lexema
    T.lexema = 0;
    sprintf(T.lexemaStr, "%s", "");
    T.token = -1;

  }

  fclose(f_out);
}
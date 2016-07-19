#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>


//------------------LISTA--------------------------
typedef struct lista Lista;
struct lista{
    int token;
    int tipo;
    char lexema[200];
    Lista* proximo;
};

Lista* lista_criar(){
	Lista* l = (Lista*)malloc(sizeof(Lista));
	l->proximo = NULL;
	return l;
}

void lista_insere_inicio(Lista* l, int token, int tipo, char lexema[]){
	Lista *n = (Lista*)malloc(sizeof(Lista));
	n->token = token;
    n->tipo = tipo;
    strcpy(n->lexema,lexema);

    Lista *old = l->proximo;
    l->proximo = n;
    n->proximo = old;
}


Lista* lista_buscar_token(Lista* l, char lexema[]){
	Lista* local;
	int i;
	int n=0;
	for (local =l; local != NULL; local = local->proximo){
            if(strcmp(local->lexema,lexema)==0){
                n=1;
                return local;
            }

	}

	return NULL;
}

void lista_imprime(Lista* l)
{
    Lista* lst;

    for(lst = l; lst != NULL; lst = lst->proximo)
        printf("%s", lst->lexema);
}

void libera(Lista *l)
{
 if(l->proximo != NULL){
  Lista *prox, *atual;

  atual=l->proximo;
  while(atual != NULL){
   prox = atual->proximo;
   free(atual);
   atual = prox;
  }
 }
}
//------------------PILHA--------------------------

char pilha [100];
int t;

void criapilha (void)
{
   t = 0;
   pilha[t] = 0;
}

void empilha (int y)
{
   t = t++;
   pilha[t] = y;
}

void desempilha(int x)
{

    int z =0;
   while (z < x)
   {
        t= t--;
        z = z++;

   }


}

int pilhavazia()
{
   return t <= 0;
}

//------------------DEFINE LEXICO--------------------------
 #define TOKEN int
 #define TOKEN_NUM 1
 #define TOKEN_LITERAL 2
 #define TOKEN_ID 3
 #define TOKEN_COMENTARIO 4
 #define TOKEN_ESPACO_BARRA_N 5
 #define TOKEN_FIM_ARQUIVO 6
 #define TOKEN_OPERADORES_RELACIONAIS 7
 #define TOKEN_ATRIBUICAO 8
 #define TOKEN_OPERADORES_ARITIMETICOS 9
 #define TOKEN_PARENTESES_A 10
 #define TOKEN_PARENTESES_F 11
 #define TOKEN_PONRTO_VIRGULA 12
 #define TOKEN_ERRO 0

 #define TOKEN_INICIO 13
 #define TOKEN_VARINICIO 14
 #define TOKEN_VARFIM 15
 #define TOKEN_ESCREVA 16
 #define TOKEN_LEIA 17
 #define TOKEN_SE 18
 #define TOKEN_ENTAO 19
 #define TOKEN_FIMSE 20
 #define TOKEN_FIM 21
 #define TOKEN_INTEIRO 22
 #define TOKEN_REAL 23
 #define TOKEN_LITERAL_PC 24

 #define COLUNA int

 #define ESPACO 0
 #define BARRA_N 1
 #define D 2
 #define PONTO 3
 #define L 4
 #define ELEVADO 5
 #define UNDERLINE 6
 #define ASPAS 7
 #define MAIS 8
 #define MENOS 9
 #define CHAVES_A 10
 #define CHAVES_F 11
 #define MAIOR 12
 #define MENOR 13
 #define IGUAL 14
 #define VEZES 15
 #define DIVISAO 16
 #define PARENTESES_A 17
 #define PARENTESES_F 18
 #define PONTO_VIRGULA 19
 #define FIM_ARQUIVO 20
 #define QQ 21

//------------------DEFINES SINTÀTICO--------------------------

#define PRODUCAO_1 1 //P' -> P
#define PRODUCAO_2 2 // P -> inicio V A
#define PRODUCAO_3 3 // V -> varinicio LV
#define PRODUCAO_4 4 // LV -> D LV
#define PRODUCAO_5 5 // LV ->varfim;
#define PRODUCAO_6 6 //D -> id TIPO;
#define PRODUCAO_7 7 //TIPO -> int
#define PRODUCAO_8 8 //TIPO -> real
#define PRODUCAO_9 9 //TIPO -> lit
#define PRODUCAO_10 10 // A -> ES A
#define PRODUCAO_11 11 // ES ->leia id;
#define PRODUCAO_12 12 //ES -> escreva ARG;
#define PRODUCAO_13 13 //ARG -> literal
#define PRODUCAO_14 14 // ARG -> num
#define PRODUCAO_15 15 // ARG -> id
#define PRODUCAO_16 16 //A -> CMD A
#define PRODUCAO_17 17 //CMD ->id reb LD;
#define PRODUCAO_18 18 //LD -> OPRD opm OPRD
#define PRODUCAO_19 19 // LD -> OPRD
#define PRODUCAO_20 20 //OPRD -> id
#define PRODUCAO_21 21 //OPRD -> num
#define PRODUCAO_22 22 // A -> COND A
#define PRODUCAO_23 23 // COND -> CABEÇALHO CORPO
#define PRODUCAO_24 24 // CABEÇALHO -> se (EXP_R) então
#define PRODUCAO_25 25 // EXP_R -> OPRD opr OPRD
#define PRODUCAO_26 26 // CORPO -> ES CORPO
#define PRODUCAO_27 27 // CORPO -> CMD CORPO
#define PRODUCAO_28 28 // CORPO -> COND CORPO
#define PRODUCAO_29 29 // CORPO -> fimse
#define PRODUCAO_30 30 // A -> fim

// Parte A da produção A -> B
#define P0 25
#define P 26
#define V 27
#define A 28
#define LV 29
#define D1 30
#define TIPO 31
#define ES 32
#define ARG 33
#define CMD 34
#define LD 35
#define OPRD 36
#define COND 37
#define CABECALHO 38
#define EXP_R 39
#define CORPO 40

//------------------------Semântico ------------------------------

typedef struct tokenatr tokenAtr;
struct tokenatr{
    int token;
    int tipo;
    char lexema[200];

};

//Variáveis de controle léxico

 char lexema[200];
 int contador;
 int linha = 1;
 int coluna= 1;
 int estado;

//Variaveis de controle sintático

int desemNum;

tokenAtr inicio;
tokenAtr varinicio;
tokenAtr varfim;
tokenAtr pvirg;
tokenAtr id[100];
tokenAtr inte;
tokenAtr real;
tokenAtr lit;
tokenAtr leia;
tokenAtr escreva;
tokenAtr literal;
tokenAtr num;
tokenAtr reb;
tokenAtr opm;
tokenAtr se;
tokenAtr abre_parentese;
tokenAtr fecha_parentese;
tokenAtr entao;
tokenAtr opr;
tokenAtr fimse;
tokenAtr fim;
tokenAtr eof;
tokenAtr semP;
tokenAtr semV;
tokenAtr semA;
tokenAtr semLV;
tokenAtr semD;
tokenAtr semTIPO;
tokenAtr semES;
tokenAtr semARG;
tokenAtr semCMD;
tokenAtr semLD;
tokenAtr semOPRD[10];
tokenAtr semCOND;
tokenAtr semCABECALHO;
tokenAtr semEXP_R;
tokenAtr semCORPO;
int tx = 0;
FILE *programa;
int d =0;
int x = 0;
bool oprdnum = false;
 //Tabela Léxica
 int tab_transicao [31][22] =
 {    // 0      1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20    21
      // espaço	\n	D	.	L	E	_	“	+	-  {	}	<	>	=	*	/  (	)	;	EOF  QQ
  // 0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20   21
     0,	 0,	 1,	-1,	11,	11,	-1,	 8,	24,	25,	13,	-1,	19,	17,	23,	26,	27,	28,	29,	30,	16, -1, //estado 0
    -1,	-1,	 1,	 2,	-1,	 4,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1, //estado 1
    -1,	-1,	 3,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1, //estado 2
    -1,	-1,	 3,	-1,	-1,	 4,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1, //estado 3
    -1,	-1,	 6,	-1,	-1,	-1,	-1,	-1,	 5,	 5,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1, //estado 4
    -1,	-1,	 7,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1, //estado 5
    -1,	-1,	 6,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1, //estado 6
    -1,	-1,	 7,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1, //estado 7
     9,	 9,	 9,	 9,	 9,	 9,	 9,	 9,	 9,	 9,	 9,	 9,	 9,	 9,	 9,	 9,	 9,	 9,	 9,	 9,	 9, 9,  //estado 8
     9,	 9, 9,	 9,	 9,	 9,	 9,	10,  9,	 9,	 9,	 9,	 9,	 9,	 9,	 9,	 9,	 9,	 9,	 9,	 -1, 9,  //estado 9
    -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1, //estado 10
    -1,	-1,	12,	-1,	12,	12,	12,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1, //estado 11
    -1,	-1,	12,	-1,	12,	12,	12,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1, //estado 12
    14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14, 14, //estado 13
    14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	14,	15,	14,	14,	14,	14,	14,	14,	14,	14,	-1, 14, //estado 14
    -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1, //estado 15
    -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1, //estado 16
    -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	18,	-1,	-1,	-1,	-1,	-1,	-1, -1, //estado 17
    -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1, //estado 18
    -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	22,	-1,	-1,	-1,	21,	20,	-1,	-1,	-1,	-1,	-1,	-1, -1, //estado 19
    -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1, //estado 20
    -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1, //estado 21
    -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1, //estado 22
    -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1, //estado 23
    -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1, //estado 24
    -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1, //estado 25
    -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1, //estado 26
    -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1, //estado 27
    -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1, //estado 28
    -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1, //estado 29
    -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1  //estado 30

 };

//Tabela Sintática
int tabela_sintatica [60][37] =
{
   202, -1, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1,	-1,	 1, -1, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1,200, -1, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,
    -1,204,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1,	-1, -1,  3,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,
	-1,	-1,	-1,	-1,212,	-1,	-1,	-1,210,211,	-1,	-1,	-1,	-1,214, -1, -1,	-1,	-1,	-1,209,	-1,	-1,	-1,	 5, -1,	-1,	-1,	 6, -1,	 7, -1,	-1,	 8,	13, -1,	-1,
	-1,	-1,217,	-1,218,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1, -1, -1,	-1,	-1, -1,	-1,	15,	16, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1, -1, -1,102, -1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,	-1, -1, -1, -1,
	-1,	-1,	-1,	-1,212,	-1,	-1,	-1,210,211,	-1,	-1,	-1,	-1,214,	-1,	-1, -1,	-1, -1,209,	-1, -1, -1,	25,	-1, -1, -1,	 6,	-1,	 7,	-1, -1,	 8,	13, -1, -1,
	-1,	-1,	-1,	-1,212,	-1,	-1,	-1,210,211,	-1,	-1,	-1,	-1,214,	-1,	-1, -1,	-1, -1,209,	-1, -1, -1,	26,	-1, -1, -1,	 6,	-1,	 7,	-1, -1,  8,	13, -1, -1,
	-1,	-1,	-1,	-1,212,	-1,	-1,	-1,210,211,	-1,	-1,	-1,	-1,214,	-1,	-1, -1,	-1, -1,209, -1, -1, -1, 27, -1, -1, -1,  6, -1,	 7, -1, -1,	 8,	13, -1, -1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,130, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,
	-1,	-1,	-1,	-1,228,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,	-1, -1, -1, -1,
	-1,	-1,	-1,	-1,232,	-1,	-1,	-1,	-1,	-1,230,231,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	29, -1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,233,	-1,	-1,	-1,	-1, -1,	-1, -1, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,	-1, -1,
	-1,	-1,	-1,	-1,212, -1,	-1,	-1,210,211,	-1,	-1,	-1,	-1,214,	-1,	-1, -1,	-1, -1,238,-1,	-1,	-1,	-1,	-1,	-1,	-1,	35, -1,	36, -1, -1,	37,	13, -1,	34,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,239, -1,	-1, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,	-1, -1, -1,
	-1,	-1,	-1,	-1,103,	-1,	-1,	-1,103,103,	-1,	-1,	-1,	-1,103,	-1,	-1, -1, -1,	-1,103, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,	-1,
	-1,	-1,217, -1,218,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	19,	16, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,
	-1,	-1,	-1,220,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,	-1, -1, -1, -1,
	-1,	-1,	-1,	-1,	-1,222,223,224,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	21, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,
	-1,	-1,	-1,	-1,104,	-1,	-1,	-1,104,104,	-1,	-1,	-1,	-1,104,	-1,	-1, -1,	-1, -1,104,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,	-1,
	-1,	-1,	-1,	-1,105,	-1,	-1,	-1,105,105,	-1,	-1,	-1,	-1,105,	-1,	-1, -1,	-1, -1,105, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,	-1,
	-1,	-1,-1, 259, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,	-1, -1, -1, -1,
	-1,	-1,	-1,107,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,	-1, -1, -1, -1,
	-1,	-1,	-1,108,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,	-1, -1, -1, -1,
	-1,	-1,	-1,109,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,	-1, -1, -1, -1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1, -1, -1,110,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1, -1, -1,116,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1, -1, -1,122, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,
	-1,	-1,	-1,240,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,	-1, -1, -1, -1,
	-1,	-1,	-1,241,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,	-1, -1, -1, -1,
	-1,	-1,	-1,113,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,	-1, -1, -1, -1,
	-1,	-1,	-1,114,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,	-1, -1, -1, -1,
	-1,	-1,	-1,115,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,	-1, -1, -1, -1,
	-1,	-1,	-1,	-1,244,	-1,	-1,	-1,	-1,	-1,	-1,245, -1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	42,	43, -1, -1, -1, -1,
	-1,	-1,	-1,	-1,123,	-1,	-1,	-1,123,123, -1,	-1,	-1,	-1,123,	-1,	-1, -1,	-1,123,123, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,	-1,
	-1,	-1,	-1,	-1,212,	-1,	-1,	-1,210,211,	-1,	-1,	-1,	-1,214,	-1,	-1, -1,	-1, 238,-1, -1,	-1,	-1,	-1,	-1,	-1,	-1,	35, -1,	36, -1, -1,	37,	13, -1,	47,
	-1,	-1,	-1,	-1,212,	-1,	-1,	-1,210,211,	-1,	-1,	-1,	-1,214,	-1,	-1, -1,	-1, 238,-1, -1,	-1,	-1,	-1,	-1,	-1,	-1,	35, -1,	36, -1, -1,	37,	13,	-1,	48,
	-1,	-1,	-1,	-1,212,	-1,	-1,	-1,210,211,	-1,	-1,	-1,	-1,214,	-1,	-1, -1,	-1, 238,-1, -1,	-1,	-1,	-1,	-1,	-1,	-1,	35,	-1,	36, -1, -1,	37,	13,	-1,	49,
	-1,	-1,	-1,	-1,129,	-1,	-1,	-1,129,129,	-1,	-1,	-1,	-1,129,	-1,	-1, -1,	-1,	129,129, -1,-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,	-1, -1, -1,
	-1,	-1,	-1,	-1,244,	-1,	-1,	-1,	-1,	-1,	-1,245, -1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1,	51,	-1, -1, 50, -1,
	-1,	-1,	-1,	-1,111,	-1,	-1,	-1,111,111,	-1,	-1,	-1,	-1,111,	-1,	-1, -1,	-1,111,111, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,	-1,
	-1,	-1,	-1,	-1,112,	-1,	-1,	-1,112,112,	-1,	-1,	-1,	-1,112,	-1,	-1, -1,	-1,112,112, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,	-1,
	-1,	-1,	-1,252,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,	-1, -1, -1, -1,
	-1,	-1,	-1,119,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,253, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,	-1, -1, -1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,120,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,120, -1, -1,120, -1,120, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,	-1, -1, -1,
	-1,	-1,	-1,121,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,121, -1, -1,121, -1,121, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,	-1, -1, -1,
    -1,	-1,	-1,121,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,121, -1, -1,121, -1,121, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,	-1, -1, -1,
	-1,	-1,	-1,	-1,126,	-1,	-1,	-1,126,126,	-1,	-1,	-1,	-1,126,	-1, -1,	-1, -1,126,126, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,	-1,
	-1,	-1,	-1,	-1,127,	-1,	-1,	-1,127,127,	-1,	-1,	-1,	-1,127,	-1, -1,	-1, -1,127,127, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,	-1,
	-1,	-1,	-1,	-1,128,	-1,	-1,	-1,128,128,	-1,	-1,	-1,	-1,128,	-1, -1,	-1, -1,128,128, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,254,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,	-1, -1,-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1, -1,255, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,	-1, -1,	-1,
	-1,	-1,	-1,	-1,117,	-1,	-1,	-1,117,117,	-1,	-1,	-1,	-1,117,	-1, -1,	-1, -1,117,117, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,	-1,
	-1,	-1,	-1,	-1,244,	-1,	-1,	-1,	-1,	-1,	-1,245, -1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,	56, -1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,257, -1,	-1, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,	-1,
	-1,	-1,	-1,	-1,244,	-1,	-1,	-1,	-1,	-1,	-1,245, -1,	-1,	-1,	-1, -1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	58, -1,	-1,	-1,	-1,
	-1,	-1,	-1,118,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,	-1, -1,
	-1,	-1,	-1,	-1,124,	-1,	-1,	-1,124,124,	-1,	-1,	-1,	-1,124,	-1, -1,	-1,	-1,124,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,	-1, -1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,125,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,	-1, -1,
	-1,	-1,106,	-1,106,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1, -1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1, -1,	-1,	-1,	-1,	-1,	-1, -1,	-1, -1
};
 //Mapeamento caracter/coluna

// ---------------------- FUNÇÔES LÉXICO-------------------
Lista* inicializaTabela()
{

Lista* l = lista_criar();
	char inicio[]= "inicio";
	char varinicio[]= "varinicio";
	char varfim[]= "varfim";
	char escreva[]= "escreva";
	char leia[]= "leia";
	char se[]= "se";
	char entao[]= "entao";
	char fimse[]= "fimse";
	char fim[]= "fim";
	char inteiro[]= "inteiro";
	char real[]= "real";
	char literal[]= "literal";

    lista_insere_inicio(l, TOKEN_INICIO, 0, inicio);
	lista_insere_inicio(l, TOKEN_VARINICIO, 0, varinicio);
	lista_insere_inicio(l, TOKEN_VARFIM, 0, varfim);
	lista_insere_inicio(l, TOKEN_ESCREVA, 0, escreva);
	lista_insere_inicio(l, TOKEN_LEIA, 0, leia);
	lista_insere_inicio(l, TOKEN_SE, 0, se);
	lista_insere_inicio(l, TOKEN_ENTAO, 0, entao);
	lista_insere_inicio(l, TOKEN_FIMSE, 0, fimse);
	lista_insere_inicio(l, TOKEN_FIM, 0, fim);
	lista_insere_inicio(l, TOKEN_INTEIRO, 0, inteiro);
	lista_insere_inicio(l, TOKEN_REAL, 0, real);
	lista_insere_inicio(l, TOKEN_LITERAL_PC, 0, literal);

	return l;

}

 void guardaLexema(char caracter, int contador)
 {
     //lexema = (char*) malloc ((contador+1) * sizeof(char));
     if(caracter != '\n' && caracter !=' ')
            lexema[contador] = caracter;


}




 COLUNA mapa_caracter_coluna(char c)
 {
        if (c=='\n')    return BARRA_N;
        if (c==' ')     return ESPACO;
        if (isdigit(c)) return D;
        if (c=='E')     return ELEVADO;
        if (c=='.')     return PONTO;
        if (isalpha(c)) return L;
        if (c=='_')     return UNDERLINE;
        if (c=='"')     return ASPAS;
        if (c=='+')     return MAIS;
        if (c=='-')     return MENOS;
        if (c=='{')     return CHAVES_A;
        if (c=='}')     return CHAVES_F;
        if (c=='<')     return MAIOR;
        if (c=='>')     return MENOR;
        if (c=='=')     return IGUAL;
        if (c=='*')     return VEZES;
        if (c=='/')     return DIVISAO;
        if (c=='(')     return PARENTESES_A;
        if (c==')')     return PARENTESES_F;
        if (c==';')     return PONTO_VIRGULA;
        if (c==EOF)     return FIM_ARQUIVO;
        return QQ;
 }

 TOKEN mapa_estado_token(int estado)
 {
       if((estado == 1) || (estado == 6) || (estado == 7))
       {
        strcpy(num.lexema,lexema);
        num.tipo = inte.tipo;
        num.token = TOKEN_NUM;

        return TOKEN_NUM;
       }

       if(estado == 3)
       {
            strcpy(num.lexema,lexema);
            num.tipo = real.tipo;
            num.token = TOKEN_NUM;
           return TOKEN_NUM;
       }
       if(estado == 10)
       {
        strcpy(literal.lexema, lexema);
        return TOKEN_LITERAL;
       }
       if((estado == 11) || (estado == 12))
       {
            d++;
            id[d].token = TOKEN_ID;;
            id[d].tipo = 0;
            strcpy(id[d].lexema,lexema);
            //printf(id[d].lexema);
            for(int x =0; x <= d; x++)
            {
               if(strcmp(id[x].lexema, lexema) == 0)
               {
                   id[d].token = id[x].token;
                    id[d].tipo = id[x].tipo;
                    strcpy(id[d].lexema,id[x].lexema);
               }
            }

            printf("%d --- ", d);
            printf(id[d].lexema);
            printf("\n");







            return TOKEN_ID;
       }
       if(estado == 15) return TOKEN_COMENTARIO;
       if(estado == 0) return TOKEN_ESPACO_BARRA_N;
       if(estado == 16) return TOKEN_FIM_ARQUIVO;
       if((estado == 19) || (estado == 18) || (estado == 17) || (estado == 20) || (estado == 21) || (estado == 23))
       {

        strcpy(opr.lexema, lexema);
        return TOKEN_OPERADORES_RELACIONAIS;

       }
       if(estado == 22) return TOKEN_ATRIBUICAO;
       if((estado == 24) || (estado == 25) || (estado == 26) || (estado == 27))
       {

        strcpy(opm.lexema, lexema);
        return TOKEN_OPERADORES_ARITIMETICOS;

       }
       if(estado == 28) return TOKEN_PARENTESES_A;
       if(estado == 29) return TOKEN_PARENTESES_F;
       if(estado == 30) return TOKEN_PONRTO_VIRGULA;
       return TOKEN_ERRO;
 }

 TOKEN lexico(FILE *texto_fonte)
 {

       estado = 0;
       char caracter;
       caracter = fgetc(texto_fonte);

       contador = 0;


       do
       {
            guardaLexema(caracter, contador);

            if(caracter != '\n' && caracter !=' ')
                contador++;
             estado = tab_transicao[estado][mapa_caracter_coluna(caracter)];
             if(estado == -1)
             {
                 guardaLexema('\0', contador);
                 return TOKEN_ERRO;
             }
             caracter = fgetc(texto_fonte);


             if(caracter == '\n')
             {
                        coluna = 1;
                        linha++;

             }
                else
                    coluna++;

          // printf("%d : %d\n",estado,mapa_caracter_coluna(caracter));
       }while (tab_transicao[estado][mapa_caracter_coluna(caracter)] != -1 );

       ungetc(caracter,texto_fonte);  //devolve caracter ao arquivo

       guardaLexema('\0', contador);

       return mapa_estado_token(estado);
 }

 //---------------------FUNÇOES SINTÀTICO-------------------------------------

 int desempilhaNum(int producao)
 {
     // Retorna 2 * o nº de caracteres no lado direito da produação
     switch(producao)
     {
         case PRODUCAO_1: return 2;
         case PRODUCAO_2: return 6;
         case PRODUCAO_3: return 4;
         case PRODUCAO_4: return 4;
         case PRODUCAO_5: return 4;
         case PRODUCAO_6: return 6;
         case PRODUCAO_7: return 2;
         case PRODUCAO_8: return 2;
         case PRODUCAO_9: return 2;
         case PRODUCAO_10: return 4;
         case PRODUCAO_11: return 6;
         case PRODUCAO_12: return 6;
         case PRODUCAO_13: return 2;
         case PRODUCAO_14: return 2;
         case PRODUCAO_15: return 2;
         case PRODUCAO_16: return 4;
         case PRODUCAO_17: return 8;
         case PRODUCAO_18: return 6;
         case PRODUCAO_19: return 2;
         case PRODUCAO_20: return 2;
         case PRODUCAO_21: return 2;
         case PRODUCAO_22: return 4;
         case PRODUCAO_23: return 4;
         case PRODUCAO_24: return 10;
         case PRODUCAO_25: return 6;
         case PRODUCAO_26: return 4;
         case PRODUCAO_27: return 4;
         case PRODUCAO_28: return 4;
         case PRODUCAO_29: return 2;
         case PRODUCAO_30: return 2;




     }

 }

 void imprimeProducao(int producao)
 {
     if(producao == PRODUCAO_1) printf("P'-> P\n");
     if(producao == PRODUCAO_2) printf("P->inicio V A\n");
     if(producao == PRODUCAO_3) printf("V->varinicio LV\n");
     if(producao == PRODUCAO_4) printf("LV->D LV\n");
     if(producao == PRODUCAO_5) printf("LV->varfim;\n");
     if(producao == PRODUCAO_6) printf("D->id TIPO;\n");
     if(producao == PRODUCAO_7) printf("TIPO->int\n");
     if(producao == PRODUCAO_8) printf("TIPO->real\n");
     if(producao == PRODUCAO_9) printf("TIPO->lit\n");
     if(producao == PRODUCAO_10) printf("A -> ES A\n");
     if(producao == PRODUCAO_11) printf("ES ->leia id;\n");
     if(producao == PRODUCAO_12) printf("ES->escreva ARG;\n");
     if(producao == PRODUCAO_13) printf("ARG->literal\n");
     if(producao == PRODUCAO_14) printf("ARG->num\n");
     if(producao == PRODUCAO_15) printf("ARG->id\n");
     if(producao == PRODUCAO_16) printf("A->CMD A\n");
     if(producao == PRODUCAO_17) printf("CMD->id reb LD;\n");
     if(producao == PRODUCAO_18) printf("LD->OPRD opm OPRD\n");
     if(producao == PRODUCAO_19) printf("LD->OPRD\n");
     if(producao == PRODUCAO_20) printf("OPRD->id\n");
     if(producao == PRODUCAO_21) printf("OPRD->num\n");
     if(producao == PRODUCAO_22) printf("A-> COND A\n");
     if(producao == PRODUCAO_23) printf("COND->CABEÇALHO CORPO\n");
     if(producao == PRODUCAO_24) printf("CABEÇALHO ->se (EXP_R) entao\n");
     if(producao == PRODUCAO_25) printf("EXP_R->OPRD opr OPRD\n");
     if(producao == PRODUCAO_26) printf("CORPO-> ES CORPO\n");
     if(producao == PRODUCAO_27) printf("CORPO-> CMD CORPO\n");
     if(producao == PRODUCAO_28) printf("CORPO-> COND CORPO\n");
     if(producao == PRODUCAO_29) printf("CORPO->fimse\n");
     if(producao == PRODUCAO_30) printf("A->fim\n");


 }
int colunaSintatico (int token)
{
    if(token == TOKEN_INICIO) return 0;
    if(token == TOKEN_VARINICIO) return 1;
    if(token == TOKEN_VARFIM) return 2;
    if(token == TOKEN_PONRTO_VIRGULA) return 3;
    if(token == TOKEN_ID) return 4;
    if(token == TOKEN_INTEIRO) return 5;
    if(token == TOKEN_REAL) return 6;
    if(token == TOKEN_LITERAL_PC) return 7;
    if(token == TOKEN_LEIA) return 8;
    if(token == TOKEN_ESCREVA) return 9;
    if(token == TOKEN_LITERAL) return 10;
    if(token == TOKEN_NUM) return 11;
    if(token == TOKEN_ATRIBUICAO) return 12;
    if(token == TOKEN_OPERADORES_ARITIMETICOS) return 13;
    if(token == TOKEN_SE) return 14;
    if(token == TOKEN_PARENTESES_A) return 15;
    if(token == TOKEN_PARENTESES_F) return 16;
    if(token == TOKEN_ENTAO) return 17;
    if(token == TOKEN_OPERADORES_RELACIONAIS) return 18;
    if(token == TOKEN_FIMSE) return 19;
    if(token == TOKEN_FIM) return 20;
    if(token == TOKEN_FIM_ARQUIVO) return 21;
    if(token == P) return 22;
    if(token == V) return 23;
    if(token == A) return 24;
    if(token == LV) return 25;
    if(token == D1) return 26;
    if(token == TIPO) return 27;
    if(token == ES) return 28;
    if(token == ARG) return 29;
    if(token == CMD) return 30;
    if(token == LD) return 31;
    if(token == OPRD) return 32;
    if(token == COND) return 33;
    if(token == CABECALHO) return 34;
    if(token == EXP_R) return 35;
    if(token == CORPO) return 36;
}

int colunaA(int x)
{
    if(x == 1) return P0;
    if(x == 2) return P;
    if(x == 3) return V;
    if(x == 4) return LV;
    if(x == 5) return LV;
    if(x == 6) return D1;
    if(x == 7) return TIPO;
    if(x == 8) return TIPO;
    if(x == 9) return TIPO;
    if(x == 10) return A;
    if(x == 11) return ES;
    if(x == 12) return ES;
    if(x == 13) return ARG;
    if(x == 14) return ARG;
    if(x == 15) return ARG;
    if(x == 16) return A;
    if(x == 17) return CMD;
    if(x == 18) return LD;
    if(x == 19) return LD;
    if(x == 20) return OPRD;
    if(x == 21) return OPRD;
    if(x == 22) return A;
    if(x == 23) return COND;
    if(x == 24) return CABECALHO;
    if(x == 25) return EXP_R;
    if(x == 26) return CORPO;
    if(x == 27) return CORPO;
    if(x == 28) return CORPO;
    if(x == 29) return CORPO;
    if(x == 30) return A;
}

void erroSintatico()
{
    printf("Erro sintático na linha %d ", linha-1);

}
// ---------------------- FUNÇÔES SEMÂNTICO-------------------

void inicializaSemantico()
{
    //inte
    strcpy(inte.lexema,"int");
    inte.tipo = 1;

    real.tipo = 2;

    lit.tipo = 3;

    literal.token = TOKEN_LITERAL;
    strcpy( literal.lexema,"");
    num.token = TOKEN_NUM;


}
char variavelTX()
{
    tx++;
    char c = (char)tx;
    return c;
}

void analisadorSemantico(int reducao)
{



    char res[200];


    switch(reducao)
    {

        case 5:
            fprintf(programa, "\n\n\n");
            break;

        case 6:

            id[d-2].tipo = semTIPO.tipo;
            strcpy(res, "");
            switch(semTIPO.tipo)
            {
                case 1:
                    strcat(res, "int ");
                    strcat(res, id[d-2].lexema);
                    strcat(res, ";\n");
                    fprintf(programa, res);
                    break;

                case 2:
                    strcat(res, "double ");
                    strcat(res, id[d-2].lexema);
                    strcat(res, ";\n");
                    fprintf(programa, res);
                    break;

                case 3:
                    strcat(res, "literal ");
                    strcat(res, id[d-2].lexema);
                    strcat(res, ";\n");
                    fprintf(programa, res);
                    break;

            }
            break;



        case 7:
            semTIPO.tipo = inte.tipo;
            break;

        case 8:
            semTIPO.tipo = real.tipo;
            break;

        case 9:
            semTIPO.tipo = lit.tipo;
            break;

        case 11:
            if(id[d-1].tipo == 0)
                printf("Erro: Variável não declarada case \n");
            else
                if(id[d-1].tipo == 1)
                {
                    strcpy(res, "");
                    strcat(res, "scanf(\"%%d\",&");
                    strcat(res, id[d-1].lexema);
                    strcat(res, ");");
                    strcat(res, "\n");
                    fprintf(programa, res);
                }
                if(id[d-1].tipo == 2)
                {
                    strcpy(res, "");
                    strcat(res, "scanf(\"%%lf\",&");
                    strcat(res, id[d-1].lexema);
                    strcat(res, ");");
                    strcat(res, "\n");
                    fprintf(programa, res);
                }
                if(id[d-1].tipo == 3)
                {
                    strcpy(res, "");
                    strcat(res, "scanf(\"%%s\",");
                    strcat(res, id[d-1].lexema);
                    strcat(res, ");");
                    strcat(res, "\n");
                    fprintf(programa, res);
                }
                break;

        case 12:

                strcpy(res, "");
                strcat(res,  "printf(");
                strcat(res, semARG.lexema);
                strcat(res, ");");
                strcat(res, "\n");
                fprintf(programa, res);
                break;



        case 13:
            strcpy(semARG.lexema,literal.lexema);
            semARG.tipo = literal.tipo;
            semARG.token = literal.token;
            break;

        case 14:
            strcpy(semARG.lexema,id[d-1].lexema);
            semARG.tipo = id[d-1].tipo;
            semARG.token = id[d-1].token;
            break;
        case 15:
            printf(id[d].lexema);
            if(id[d].tipo == 0)
               printf("Erro: Variável não declarada\n");
            else
            {
                strcpy(semARG.lexema,id[d].lexema);
                semARG.tipo = id[d].tipo;
                semARG.token = id[d].token;
            }
            break;
        case 17:
            if(oprdnum)
            {
                printf(id[d-1].lexema);
                if(id[d-1].tipo == 0)
                printf("Erro: Variável não declarada");
                else
                {
                    if(id[d-1].tipo == semLD.tipo)
                    {
                        strcpy(res, "");
                        strcat(res, id[d-1].lexema);
                        strcat(res, "=");
                        strcat(res,semLD.lexema);
                        strcat(res, ";\n");
                        fprintf(programa, res);
                        oprdnum = false;
                    }

                    else
                        printf("Erro: TIpos diferentes para atribuicao\n");
                }
            }
            else
            {
                if(id[d-2].tipo == 0)
                printf("Erro: Variável não declarada");
                else
                {
                    if(id[d-2].tipo == semLD.tipo)
                    {
                        strcpy(res, "");
                        strcat(res, id[d-2].lexema);
                        strcat(res, "=");
                        strcat(res,semLD.lexema);
                        strcat(res, ";\n");
                        fprintf(programa, res);
                    }

                    else
                        printf("Erro: TIpos diferentes para atribuicao\n");
                }

            }

            break;
        case 18:
            if((semOPRD[1].tipo == semOPRD[2].tipo) && semOPRD[1].tipo != 3)
            {
                char resTX[2] = "t";
                strcpy(res, "");

                resTX[1] = (char)(tx + 48);
                resTX[2] = '\0';

                strcpy(semLD.lexema,resTX);
                strcat(res, inte.lexema);
                strcat(res, " ");
                strcat(res, resTX);
                strcat(res, ";\n");
                fprintf(programa, res);
                semLD.tipo = inte.tipo;

                strcpy(res, "");
                strcat(res, resTX);
                strcat(res, " = ");
                strcat(res, semOPRD[1].lexema);
                strcat(res, opm.lexema);
                strcat(res,semOPRD[2].lexema);

                strcat(res, ";\n");
                fprintf(programa, res);
                tx++;
                x = 0;

            }
            else
            {
                printf("Erro: Operandos com tipos incompativeis\n");
            }
            break;

        case 19:
                strcpy(semLD.lexema,semOPRD[x].lexema);
                semLD.tipo = semOPRD[x].tipo;
                semLD.token = semOPRD[x].token;

                break;
        case 20:
            printf(id[d].lexema);
            if(id[d].tipo == 0)
               printf("Erro: Variável não declarada\n");
            else
            {
                x++;
                strcpy(semOPRD[x].lexema, id[d].lexema);
                semOPRD[x].tipo = id[d].tipo;
                semOPRD[x].token = id[d].token;


            }
            break;
        case 21:
            x++;
            strcpy(semOPRD[x].lexema, num.lexema);
            semOPRD[x].tipo = num.tipo;
            semOPRD[x].token = num.token;
            oprdnum = true;

            break;
        case 23:
            fprintf(programa, "}\n");
            break;
        case 24:
            strcpy(res, "");
            strcat(res,"if(" );
            strcat(res, semEXP_R.lexema);
            strcat(res, "){\n");
            fprintf(programa, res);
            break;

        case 25:
            printf("%d", semOPRD[1].tipo);
            printf("%d", semOPRD[2].tipo);
            printf("%d", x);
            if((semOPRD[1].tipo == semOPRD[2].tipo))
            {
                char resTX[2] = "t";
                strcpy(res, "");

                resTX[1] = (char)(tx + 48);
                resTX[2] = '\0';
                printf("%s", resTX);

                strcpy(semEXP_R.lexema,resTX);
                tx++;
                strcat(res, inte.lexema);
                strcat(res, " ");
                strcat(res, resTX);
                strcat(res, ";\n");
                fprintf(programa, res);
                strcpy(res, "");
                strcat(res, resTX);
                strcat(res, " = ");
                strcat(res, semOPRD[1].lexema);
                strcat(res, opr.lexema);
                strcat(res, semOPRD[2].lexema);
                strcat(res, ";\n");
                fprintf(programa, res);
                x = 0;

            }
            else
            {
                printf("Erro: Operandos com tipos incompativeis");
            }
            break;


    }



}



int analisadorSintatico(FILE *texto_fonte)
 {
     Lista* l;
     Lista* ltoken;

     criapilha();
     l = inicializaTabela();
     int ip;

     ip = lexico(texto_fonte);
      if(ip == TOKEN_ID)
      {

          ltoken =lista_buscar_token(l,lexema);
          if(ltoken == NULL)
          {


            lista_insere_inicio(l,TOKEN_ID,0,lexema);

          //printf("\n[ID][%s]", lexema);

          }
          if(ltoken != NULL && ltoken->token != 3)
          {
              //printf("\n[%s][%s]", lexema, lexema);

              ip = ltoken->token;
          }


      }

     if(ip == TOKEN_ERRO)
     {
         if(estado == 2 || estado == 4 || estado == 5)
            printf("\nErro na linha %d coluna %d : Digito esperado",linha-1, coluna-1);

         if(estado ==8 || estado== 9)
            printf("\nErro na linha %d coluna %d : Fecha aspas esperado",linha, coluna-1);

         if(estado== 13 || estado == 14)
            printf("\nErro na linha %d coluna %d : Fecha chaves esperado",linha, coluna-1);

         else
            printf("\nErro na linha %d coluna %d : Caracter desconhecido %s",linha, coluna-1,lexema);

     }


     while(1)
        {
         int s = pilha[t];

         int a = colunaSintatico(ip);

        // printf(" Coluna s %d\n",s);
        // printf("Coluna a %d\n",a);
        // printf("Resulta tabela %d\n",tabela_sintatica[s][a]);
          if (tabela_sintatica[s][a] != -1)
            {
              int acao = tabela_sintatica[s][a] - 200;

              if(acao > 0)
              {

                  empilha(ip);
                 //printf("%d", ip);
                  //printf("%d", pilha[t]);
                  empilha(acao);
                  ip = lexico(texto_fonte);
                  //printf("%d",t);
                  if(ip == TOKEN_ID)
                      {

                          ltoken =lista_buscar_token(l,lexema);
                          if(ltoken == NULL)
                          {


                            lista_insere_inicio(l,TOKEN_ID,0,lexema);

                          //printf("\n[ID][%s]", lexema);

                          }
                          if(ltoken != NULL && ltoken->token != 3)
                          {
                              //printf("\n[%s][%s]", lexema, lexema);
                              ip = ltoken->token;



                          }




                        }
                   // printf("%d",ip);

                  if(ip == TOKEN_ERRO)
                         {
                             if(estado == 2 || estado == 4 || estado == 5)
                                printf("\nErro na linha %d coluna %d : Digito esperado",linha-1, coluna-1);

                             if(estado ==8 || estado== 9)
                                printf("\nErro na linha %d coluna %d : Fecha aspas esperado",linha, coluna-1);

                             if(estado== 13 || estado == 14)
                                printf("\nErro na linha %d coluna %d : Fecha chaves esperado",linha, coluna-1);

                             else
                                printf("\nErro na linha %d coluna %d : Caracter desconhecido %s",linha, coluna-1,lexema);

                         }
                }

              if(acao < 0)
              {

                  int reducao = tabela_sintatica[s][a] - 100;
                //  printf("Reducao %d\n", reducao);


                  desempilha(desempilhaNum(reducao));
                 // printf("%d",desempilhaNum(reducao));
                  s = pilha[t];
                //  printf("Coluna s apos reduzir %d\n",pilha[t]);
                  int colA = colunaA(reducao);
                  empilha(colA);

                  empilha(tabela_sintatica[s][colunaSintatico(colA)]);
                // printf("Coluna Sintatico %d\n",colunaSintatico(colA));
                //  printf("Desvio %d\n",tabela_sintatica[s][colunaSintatico(colA)]);

                  imprimeProducao(reducao);

                  analisadorSemantico(reducao);




              }
              if(acao == 0)
              {
                   libera(l);
                   printf("ACEITA!");
                   return 0;
              }

            }
           else
           {
                erroSintatico();
                return 0;
           }





        }

 }


//------------------MAIN--------------------------
 int main(int argc, char *argv[])
 {

     FILE *texto_fonte;
     TOKEN token;


     programa = fopen(argv[2], "w");


     texto_fonte = fopen(argv[1],"r");

     if(! texto_fonte) // texto_fonte == NULL
     {
          printf("\nproblema na abertura do arquivo %s\n",argv[1]);
          exit(0);
     }

    inicializaSemantico();
    analisadorSintatico(texto_fonte);



 /*   while(
            ((token = lexico(texto_fonte)) != TOKEN_ERRO) &&
            (token != TOKEN_FIM_ARQUIVO)
          )

     {
          if(token == TOKEN_NUM)                       printf("\n[Numerico][%s][ ]", lexema);
          if(token == TOKEN_LITERAL)                   printf("\n[Literal][%s][ ]", lexema);
          if(token == TOKEN_ID)
          {

              ltoken =lista_buscar_token(l,lexema);
              if(ltoken == NULL)
              {

              lista_insere_inicio(l,TOKEN_ID,0,lexema);
              printf("\n[ID][%s]", lexema);

              }
              if(ltoken != NULL && ltoken->token != 3)
              {
                  printf("\n[%s][%s]", lexema, lexema);

              }
              if(ltoken != NULL && ltoken->token == 3)
                    printf("\n[ID][%s]", lexema);


          }


          if(token == TOKEN_COMENTARIO)                printf("\n[Comentario][%s]",lexema);
          if(token == TOKEN_OPERADORES_RELACIONAIS)    printf("\n[Operador relacional][%s]",lexema);
          if(token == TOKEN_ATRIBUICAO)                printf("\n[atribuicao][%s]",&lexema);
          if(token == TOKEN_OPERADORES_ARITIMETICOS)   printf("\n[operador aritimetico][%s]",lexema);
          if(token == TOKEN_PARENTESES_A)              printf("\n[(][%s]",lexema);
          if(token == TOKEN_PARENTESES_F)              printf("\n[)][%s]",lexema);
          if(token == TOKEN_PONRTO_VIRGULA)            printf("\n[;][%s]",lexema);


     }

*/

     //lista_imprime(l);

     getchar();

     return 0;
 }

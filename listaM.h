#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 100 // S2

typedef struct termo Termo; 
typedef struct polinomios Polinomios;
typedef struct ListaPrincipal ListaP;

ListaP *criarl();
Polinomios *criarp();
Termo *criart(int coef, int exp);
int inserirPolinomio(ListaP *l);
int entradaRuim(ListaP *l, int id);
int inserirTermo(ListaP *l,int id, int coef, int exp);
int cleanTerm(ListaP *l, int id,int exp );
int reinicializacao(ListaP *l, int id);
void mostraTudo(ListaP *l);
int inserirTermosSemProblemas(Polinomios *caim, int coef, int exp);
int sumPolinomios(ListaP *l, int id1, int id2);
long substituiX(ListaP *l,int pos, int id, long valorDeX);
long pegaExtremos(long vecSoma[], int quantPlus, long *min, long *max);
int eliminaPolinomio(ListaP *l, int idzin);
long leEvalida();
int mostrar(ListaP *l, int id);
int polinomioVazio(ListaP *l, int id);
int casoExpIgual(ListaP *l, Polinomios *p,Termo *t_atual, int coef, int exp);
void desaloca(ListaP* lista);
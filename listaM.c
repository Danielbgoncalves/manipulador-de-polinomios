// Inclusão de bibliotecas necessárias para o desenvolvimento do programa
#include "listaM.h"   
#include <stdlib.h>
#include  <stdio.h>
#include   <math.h>
   
/*Aqui, o Termo funciona como o "No" da lista de polinômios,
recebendo os dados de cada X e apontando para o proximo termo*/
typedef struct termo { 
    int coeficiente; 
    int expoente;  
    struct termo* prox;
}Termo;

//Os polinomios são os "NO's" da Lista Principal, cada um contendo uma lista de termos
typedef struct polinomios {
    int id;
    Termo* iniciot;//Descritor que aponta para o inicio dos termos
    struct polinomios* proximo;
} Polinomios;

typedef struct ListaPrincipal {
    Polinomios* iniciop;//Descritor que aponta para  o inicio dos polinomios
} ListaP;

//Criação da lista principal
ListaP *criarl(){
    ListaP *l = (ListaP*)malloc(sizeof(ListaP));
    l->iniciop = NULL;
    return l;
}

//Criação do polinômio 
Polinomios *criarp(){
    Polinomios *p = (Polinomios*)malloc(sizeof(Polinomios));
    p->iniciot= criart(0,0);
    p->proximo = NULL;
    p->id = 0;
    return p;
}

//Criação do termo
Termo *criart(int coef, int exp){
    Termo *t = (Termo*)malloc(sizeof(Termo));
    t->prox = NULL;
    t->coeficiente = coef;
    t->expoente = exp;
    return t;
}

/* Insere na lista Principal de "Polinomios" um polinomio com
o id(indentificador) subsequente ao ultimo polinomio já inserido, 
caso exista, se não adiciona o polinomio de id 1 */
int inserirPolinomio(ListaP *l){ // Vulgo inicializar o polinômio
    if(l == NULL) return -2;
    Polinomios *P = criarp();
    if(P == NULL) return -3;
    if(l->iniciop == NULL) {
        l->iniciop = P;
        P->id = 1;
    } else {
        Polinomios *n = l->iniciop;
        int cont = 2;
        while(n->proximo != NULL){
            n = n->proximo;
            cont++;
        }
        n->proximo = P;
        P->id = cont;
    }
    return P->id;
}

/* Mostra as opções do usuário para o caso de uma tentativa de 
inserção com expoente igual a um já existente no polinomio
e trata cada uma das possíveis escolhas */
int casoExpIgual(ListaP *l, Polinomios *p,Termo *t_atual, int coef, int exp){
    printf("\n--------------------------------------------------\n");
    printf("Ja existe um termo com esse expoente, voce deseja:\n");
    printf("1- inserir o termo na posicao correspondente\n");
    printf("2- substituir termo existente\n");
    printf("3- adicionar o valor inserido ao valor ja existente\n");
    int a, coefAnt = coef, coef2;   
    int primeiraVez = 0;  
    Termo *t = p->iniciot; // Cria um ponteiro para termo para ser iterado sobre o polinômio
    printf("=>");
    scanf("%d",&a);
    switch (a){
    case 1: /*Substitui o coeficiente do termo que contém o expoente igual e
            passa os coeficientes para os termos seguintes incrementando-os*/  
        while(t != NULL){ 
            if(t->expoente <= exp){
                if(!primeiraVez){
                    coefAnt = t->coeficiente;
                    t->coeficiente = coef;
                    primeiraVez++;
                } else {
                    if (t != NULL) {
                        coef2 = t->coeficiente;
                        t->coeficiente = coefAnt;
                        coefAnt = coef2;
                    } else {
                        coefAnt = 0;
                    }  
                } 
            }
            t = t->prox;
        }
        
        break;
    case 2: // Substitui o termo existente pelo novo
        t_atual->coeficiente = coef;
        break;
    case 3: // soma o coeficiente da entrada com o do termo de igual expoente
        t_atual->coeficiente += coef;
        break;
    default:                
        printf("Opcao invalida!\n\n");
        break;
    }
    return 0;
}

/*Verifica se a entrada feita pelo usuário é válida, ou seja, 
se existe um termo com aquele especificador ou um polinomio com aquele id*/
int entradaRuim(ListaP *l, int id){
    if(id != (int)id) return 0;
    Polinomios *n = l->iniciop;
    int cont = 0;
    while( n != NULL){
        cont ++;
        n = n->proximo;
    }
    if(cont < id || id < 1) {//Verifica se o id passado é maior que a quantidade de polinomios da lista
        printf("A entrada nao eh valida!\n"); 
        return 0;
    }
    return 1;
}

// Insere um termo em um determinado polinômio
int inserirTermo(ListaP *l, int id, int coef, int exp){
    if (l == NULL) return -1;
    
    Polinomios *n = l->iniciop;
    while(n != NULL ){
        if(n->id == id){ 
            Termo *termo = n->iniciot;
            while(termo != NULL){
                //Se o termo a ser inserido tem o expoente igual a algum que já existe no polinomio
                if(termo->expoente == exp){
                    return casoExpIgual(l,n,termo,coef,exp);
                }
                termo = termo->prox;
            }
            //Se o termo tem um expoente diferente:
            Termo *ant = NULL;
            Termo *atual = n->iniciot;
            //Encontra onde o termo deve ser inserido para manter a ordem
            while(atual != NULL && exp < atual->expoente){
                ant = atual;
                atual = atual->prox;
            }
            
            if(ant == NULL){ // Se o expoente passado for maior que todos os outros       
                Termo *t = criart(coef, exp);
                t->prox = atual;
                n->iniciot = t;
            } else {
                Termo *t = criart(coef, exp);
                t->prox = ant->prox;
                ant->prox = t;
            }
        }

        n = n->proximo;
    }


    
    return 0;
}

// Elimina o termo associado à k-ésima potência indicada pelo usuário
int cleanTerm(ListaP *l, int id, int exp){
    if (l == NULL) return -1;

    Polinomios *n = l->iniciop;
    while(n != NULL){ 
        if(n->id == id){
            Termo *t = n->iniciot;
            Termo *prev = NULL;
            while(t != NULL && t->expoente != exp){ /*Laço que para exatamente quando chegamos no termo 
                                                    com o expoente que desejamos manipular*/
                prev = t;
                t = t->prox;
            }
            if(t == NULL) { /* Verifica se a causa da saída do laço anterior foi a 
                            ausência do termo com o expoente entrada pelo usuário*/
                printf("Nao tem o expoente.\n");
                return 1; 
            } else {  /* Apaga, efetivamente, o termo atual, passando o ponteiro que aponta
                      para ele para o seu próximo, "pulando-o"*/
                if(prev == NULL) { // Havia apenas um termo, o de expoente escolhido
                    n->iniciot = t->prox;
                } else {
                    prev->prox = t->prox;
                }
                free(t); // desaloca a memória alocada pelo termo do expoente apagado
                return 0;
            } //  0x^0 -> NULL
        }
    n = n->proximo;
    }

}
 // Morre, e, das cinzas, surge um novo polinômio
 // Reinicializa o polinômio para a forma 0x^0
int reinicializacao(ListaP *l, int id){
    Polinomios *n = l->iniciop;
    while(n != NULL){
        if(n->id == id){
            Termo *t = n->iniciot;
            while(t->prox != NULL){
                cleanTerm(l,id,t->expoente); // Limpa termo por termo
                t = t->prox;
            } 
            //Reinicializa o coeficiente e o expoente que sobrou para 0
            t->coeficiente = 0;
            t->expoente = 0;
        }
        n = n->proximo;
    } 
    return 0;
}

//Exibe todos os polinômios
void mostraTudo(ListaP *l){
    Polinomios *n = l->iniciop;
    while(n != NULL){
        mostrar(l, n->id);// Mostra polinomio por polinomio
        n = n->proximo;
    }
}

/* Função que insere os termos com expoentes iguais além dos que já existem, 
sem chamar a função casoExpIgual */
int inserirTermosSemProblemas(Polinomios *c, int coef, int exp){
    Termo *t = criart(coef, exp);
    if(t == NULL) return -1;

    Termo *ant = NULL;
    Termo *atual = c->iniciot;
    while(atual != NULL && exp < atual->expoente){
        //Encontra a posição em que o termo deve ser inserido para manter a ordem
        ant = atual;
        atual = atual->prox;
    }
    if(ant == NULL){   // Se for inserir o primeiro termo   
        t->prox = atual;
        c->iniciot = t;
    } else {
        t->prox = ant->prox;
        ant->prox = t;
    }
}

// Soma dois polinômios escolhidos pelo usuário 
int sumPolinomios(ListaP *l, int id1, int id2){
    Polinomios *a = l->iniciop;
    Polinomios *e = l->iniciop;
  
    int idNovo = inserirPolinomio(l);// Insere um polinomio que receberá a soma 
    Polinomios *c = l->iniciop;
    
    // whiles para chegar nos polinômios de ids necessários
    while(a->id != id1) a = a->proximo;
    while(e->id != id2) e = e->proximo;
    while(c->id != idNovo) c = c->proximo;
    
    Termo *ta = a->iniciot;
    Termo *te = e->iniciot; 

    while(ta != NULL){//Insere todos os termos do polinomio "a" no polinômio de idNovo
        inserirTermosSemProblemas(c, ta->coeficiente,ta->expoente);
        ta = ta->prox;
    }
    while(te != NULL){//Insere todos os termos do polinômio "e" no polinômio de idNovo
        inserirTermosSemProblemas(c, te->coeficiente,te->expoente);
        te = te->prox;
    }
    Termo *t1 = c->iniciot;
    while(t1 != NULL){
        Termo *t2 = t1->prox;
        Termo *aux = t1;
        while(t2 != NULL){
            //Verifica se existem termos com o mesmo expoente para somar seus respectivos coeficientes            
            if(t1->expoente == t2->expoente){
                t1->coeficiente += t2->coeficiente;
                aux->prox = t2->prox; 
                free(t2);//Desaloca o segundo termo dos que foram somados
                t2 = aux->prox;
            } else{
                aux = t2;
                t2 = t2->prox;
            } 
        }
        t1 = t1->prox;
    }
    return c->id;
}

// Substitui o valor de X nos polinômios e retorna o valor final
long substituiX(ListaP *l,int pos, int id, long valorDeX){
    if(l == NULL) return -1;
    
    Polinomios *p = l->iniciop;
    while(p->id != id) p = p->proximo;// Encontra o polinomio com o id requerido
    long soma = 0;
    Termo *termo = p->iniciot;
    while(termo != NULL){
        soma += termo->coeficiente * pow(valorDeX, termo->expoente); 
        /* Substitui o valor de x passado em todos os termos e 
        realiza o cálculo com o expoente e coeficiente de cada um*/
       termo = termo->prox;
    } 
    return soma;
}

// Determina o menor e o maior valor resultados da função substituiX
long pegaExtremos(long vecSoma[], int quantPlus, long *min, long *max){
    *max = vecSoma[0];
    *min = vecSoma[0];
    int i = 0;
    for(i = 0; i < quantPlus; i++ ){ 
        if( *max < vecSoma[i]) *max = vecSoma[i];
        if( *min > vecSoma[i]) *min = vecSoma[i];
    }
    if(i == 0){
        *max = 0;
        *min = 0;
    }
    return 0;
}

// Caso o usuario não queira salvar o polinomio essa funçao elimina o polinomio de id passado
int eliminaPolinomio(ListaP *l, int idzin){
    if(l == NULL) return -1;
    Polinomios *p = l->iniciop;
    Polinomios *aux = l->iniciop;
    while(p->id != idzin ){
        aux = p;
        p = p->proximo;
    }

    Termo *t = p->iniciot;
    while(t != NULL){
        cleanTerm(l,idzin,t->expoente);//Limpa todos os termos do polinomio, um a um
        t = t->prox;
    }
    aux->proximo = NULL;
    free(p);
}

// confere se o polinômio passado por id é vazio
int polinomioVazio(ListaP *l, int id){
    Polinomios *n = l->iniciop;

    while(n->id != id) n = n->proximo;

    if(n->iniciot == NULL) return 1;
    else return 0;
}

// Mostra na tela o conteúdo do polinômio por intermédio do id 
int mostrar(ListaP *l, int id){
    Polinomios *n = l->iniciop;
    printf("P%d(x) = ", id);
    while(n != NULL){ 
        if(n->id == id){
            if(polinomioVazio(l,id) == 1){
                printf("Vazio\n");
                return 1;
            }
            Termo *t = n->iniciot;
            while(t->prox != NULL){
                printf(" %dx^%d +", t->coeficiente, t->expoente);
                t = t->prox;
            }
            printf(" %dx^%d ", t->coeficiente, t->expoente);
            printf("\n");
            return 0;
        }  
        n = n->proximo;
    }
    return 1;   
}

// Verifica se a entrada é do tipo int ou long int
long leEvalida() {
    char bEntrada[64];
    char* pontoParada;

    while (1) {
        setbuf(stdin, NULL);
        fgets(bEntrada, 64, stdin);
        setbuf(stdin, NULL);

        long numeroLido = strtol(bEntrada, &pontoParada, 0); /*Essa função recebe uma string, um ponteiro 
        para char que acompanha a string e a base para a conversão da string para número. Essa função tenta 
        converter a string até encontrar um caracter que não possa ser convertido para o tipo numérico */

        if ((numeroLido == 0 && pontoParada == bEntrada) || *pontoParada != '\n') {
            printf("Entrada invalida. Digite novamente => ");//E volta para o inicio do while
        } else {
            return numeroLido;
        }
    }
}


void desaloca(ListaP* lista){
    Polinomios* pAtual;
    Polinomios* pProx;
    Termo* tAtual;
    Termo* tProx;

    pAtual = lista->iniciop;
    while (pAtual != NULL) {
        tAtual = pAtual->iniciot;
        while (tAtual != NULL) {
            tProx = tAtual->prox;
            free(tAtual);
            tAtual = tProx;
        }
        pProx = pAtual->proximo;
        free(pAtual);
        pAtual = pProx;
    }
    free(lista);
}

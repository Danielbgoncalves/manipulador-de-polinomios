#include "listaM.h"

int main(){
    ListaP *l = criarl();
    //Todas as variáveis que serão utilizadas no programa:
    long op, coef, exp;
    int idzin, idA, idE; 
    char escolha;
    long valorDeX, quant;
    int pos, quantPlus;
    long *vecSoma = (long *) malloc(sizeof(long ));
    long min, max, valor;
    int deuErro = 0; 

    do{
        printf("======================== Manipulador de Polinomios ========================");
        printf( "\n1- Inicializar um polinomio\n2- Inserir um novo termo a um polinomio.\n3- Exibir um polinomio.\n"
                "4- Eliminar um termo.\n5- Reinicializar um polinomio.\n6- Somar dois polinomios."
                "\n7- Calcular P(x) para o x solicitado\n8- Mostrar todos os polinomios salvos \n9- Sair.\n=> ");
        op = leEvalida();

        switch (op){
            case 1:
                idzin = inserirPolinomio(l);
                printf("O polinomio de id %d foi criado\n", idzin);
                break;
            case 2: 
                printf("Informe o id do polinomio no qual deseja inserir um novo termo =>");
                idzin = leEvalida();
                if(entradaRuim(l,idzin) == 0) break;
                printf("Insira o coeficiente =>");
                setbuf(stdin,NULL);
                coef = leEvalida();
                printf ("Insira o expoente =>");
                setbuf(stdin, NULL);
                exp = leEvalida();
                setbuf(stdin, NULL);
                inserirTermo(l,idzin, coef,exp);
                break;
            case 3:
                printf("Informe o id do polinomio que deseja exibir: ");
                setbuf(stdin, NULL);
                idzin = leEvalida();
                if(entradaRuim(l,idzin) == 0) break;
                mostrar(l,idzin);
                break;
            case 4: 
                printf("Informe o id do polinomio do qual o termo sera retirado: ");
                setbuf(stdin, NULL);
                idzin = leEvalida();
                //scanf("%d", &idzin);
                if(entradaRuim(l,idzin) == 0) break;              
                printf("Informe a expoente do termo a ser retirado: ");
                setbuf(stdin,NULL);
                exp = leEvalida();

                cleanTerm(l, idzin, exp);
        
                break;
            case 5:
                printf("Informe o id do polinomio que sera reinicializado: ");
                setbuf(stdin, NULL);
                idzin = leEvalida();
                //scanf("%d", &idzin);
                if(entradaRuim(l,idzin) == 0) break;
                reinicializacao(l,idzin);
            
                break;
            case 6:
                printf("Informe o primeiro id a ser somado: ");
                idA = leEvalida();
                printf("Informe o segundo id a ser somado: ");
                idE = leEvalida();
                //setbuf(stdin, NULL);
                //scanf("%d %d", &idA, &idE);
                if(entradaRuim(l,idA) == 0) break;
                if(entradaRuim(l,idE) == 0) break;
                idzin = sumPolinomios(l,idA, idE);
                mostrar(l,idzin);
                printf("Deseja salvar esse polinomio (s/n)?\n => ");
                setbuf(stdin, NULL);
                scanf("%c", &escolha);
                if( escolha == 'n') eliminaPolinomio(l, idzin);
            
                break;
            case 7:
                printf("Informe o x a ser substituido no polinomio: ");
                setbuf(stdin, NULL);
                valorDeX = leEvalida();
                printf("Informe quantos polinomios serao calculados para x = %ld: ", valorDeX);
                setbuf(stdin, NULL);
                quant = leEvalida();
                if(entradaRuim(l,quant) == 0) break;
                vecSoma = (long *)realloc(vecSoma, quant * sizeof(long));

                pos = 0;
                quantPlus = quant;
                while(quant > 0 ){
                    printf("Informe o id: ");
                    setbuf(stdin,NULL);
                    idzin = leEvalida();
                    if(entradaRuim(l,idzin) == 0){
                        deuErro++;
                        break;
                    } 
                    vecSoma[pos] = substituiX(l,pos,idzin, valorDeX);
                    printf("P%d(%ld) = %ld\n",idzin, valorDeX, vecSoma[pos]);
                    pos++;
                    quant--;
                }
               
               if(!deuErro){
                printf("\n-------------------\n");
                pegaExtremos(vecSoma,quantPlus, &min, &max);
                printf("O valor minimo eh: %d\n", min);
                printf("O valor maximo eh: %d\n", max);
               }
                
                
                break;
            case 8:
                printf("------ Polinomios Salvos ------\n");
                mostraTudo(l);
                break;
            case 9:
                printf("------ Fim ------\n");
                desaloca(l);
                //mostraTudo(l);
                break;    
            default:
                printf("Opcao invalida!\n\n");
                break;
        }
    setbuf(stdin, NULL);
    }while(op != 9);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Trabalho 2 de Estrutura de Dados
//Alunos: Joao Victor de Morais Freitas e Ricardo Menezes Bandeira

typedef struct arvore{
    int info;
    struct arvore *esq;
    struct arvore *dir;
}arvore;

arvore* LerArvore(FILE *arq,arvore *a){//codigo do Dalessandro pra criar a arvore a partir da notação ensinada em aula
    char c;
    int num;

    fscanf(arq,"%c",&c);    //Ler '('
    fscanf(arq,"%d",&num);  //Ler a raiz

    if(num == -1){
        fscanf(arq,"%c",&c);
        return NULL;
    }
    else{
        arvore *a = (arvore*)malloc(sizeof(arvore));
        a->info = num;
        a->esq = LerArvore(arq,a->esq);
        a->dir = LerArvore(arq,a->dir);
        fscanf(arq,"%c",&c);    //Ler ')'
        return a;
    }
}

arvore* destroi(arvore *a){

    if(a->esq != NULL){//se tem caminho pela esquerda
        a->esq = destroi(a->esq);
    }
    if(a->dir != NULL){//se tem caminho pela direita
        a->dir = destroi(a->dir);
    }
    if(a->esq == NULL && a->dir == NULL){//se é uma folha destroi e retorna
        free(a);
        return NULL;
    }
}

void ImprimirPre(arvore *a){//pré-ordem
    if(a != NULL){
        printf("%d ",a->info);
        ImprimirPre(a->esq);
        ImprimirPre(a->dir);
    }
}

void ImprimirEmOrdem(arvore *a){//em-ordem
    if(a != NULL){
        ImprimirEmOrdem(a->esq);
        printf("%d ",a->info);
        ImprimirEmOrdem(a->dir);
    }
}

void ImprimirPos(arvore *a){//pós-ordem
    if(a != NULL){
        ImprimirPos(a->esq);
        ImprimirPos(a->dir);
        printf("%d ",a->info);
    }
}

void imprimirFolhas(arvore *a){
    if(a!=NULL){
        if(a->esq == NULL && a->dir == NULL){
           printf("%d ",a->info);
        }else{
            imprimirFolhas(a->esq);
            imprimirFolhas(a->dir);
        }
    }
}

arvore* VerificaX(arvore *a, int x){//verifica se um elemento X está na arvore
    if(a != NULL){
        if(a->info == x){// se entrar nesse if encontrou o elemento
            return a;
        }
        else if(a->info < x){
            return (VerificaX(a->dir,x));//retorna para a raiz a resposta da chamada dos nós
        }
        else{
            return (VerificaX(a->esq,x));//retorna para a raiz a resposta da chamada dos nós
        }
    }
    else{
        return NULL;
    }
}

int contarElementos(arvore *a){
    if(a==NULL){
        return 0;// igual a null retorna zero como condição de parada
    }else{
        return 1 +contarElementos(a->dir)+contarElementos(a->esq);//se diferente de null retorna 1+ chamadas da esq + chamadas da direita
    }
}

int altura(arvore *a){

    if(a == NULL){
        return 0;
    }
    else{
        int he,hd;
        he = altura(a->esq);
        hd = altura(a->dir);
        if(he>hd){
            return he+1;
        }
        else{
            return hd+1;
        }
    }
}

void ImprimirLargura(arvore *a,int cont, int nivel){
    if(a != NULL){
        if(cont == nivel){
            printf("%d ",a->info);
        }
        else{
            ImprimirLargura(a->esq,cont+1,nivel);
            ImprimirLargura(a->dir,cont+1,nivel);
        }
    }
}

void CamadaDoItem(arvore *a, int x, int camada){//camada deve ser iniciada com 1
    if(a !=NULL) {
        if(a->info == x){
            printf("%d",camada);
        }
        if(a->info < x){
            CamadaDoItem(a->dir,x,camada+1);//se x maior vai pra direita
        }
        else{
            CamadaDoItem(a->esq,x,camada+1);//se x menor vai pra esquerdar
        }
    }
}

int Balanceada(arvore *a){
    if(a == NULL){
        return 1;//se for NULL está balanceada
    }
    else{//se nao for NULL, compara as alturas
        int he,hd;
        he = altura(a->esq);
        hd = altura(a->dir);

        if((he - hd < -1) || (he - hd > 1)){
            return 0; // nao está balanceada pois a altura difere em mais de um nivel
        }
        else{
            return 1 && (Balanceada(a->esq)&&Balanceada(a->dir));// retorna 1 (balanceada) se a sub-arvore à esquerda e a sub-arvore à direita tambem estiverem balanceadas
        }
    }
}

int Cheia(arvore* a){
    int h = altura(a) ;
    int total = contarElementos(a);
    if (pow(2, h) - 1 == total){
        return 1;
    }else{
        return 0;
    }
}

void menu(arvore *raiz){//o ponteiro raiz é criado na main e é usado como argumento por todas as funções do menu
//antes não funcionava pq a declaração do ponteiro era feita no proprio menu e sempre que ele era chamado recursivamente o valor era alterado pra NULL
    int opcao,x,h;//opcao é a váriavel de escolha do menu e X é o elemento a ser procurado na arvore por uma das funções
    char nomeArq[20];
    FILE *arq = NULL;
    printf("1- Ler uma árvore de um arquivo fornecido\n");
    printf("2- Imprimir a árvore\n");
    printf("3- Verificar se um elemento x existe na árvore\n");
    printf("4- Contar o número de elementos na árvore\n");
    printf("5- Imprimir os nós folhas da árvore\n");
    printf("6- Verificar se a árvore é balanceada\n");
    printf("7- Verificar se a árvore é cheia\n");
    printf("8- Imprimir o nível de um nó X\n");
    printf("9- Sair\n\n");
    scanf("%d",&opcao);
    switch(opcao){
        case 1:
            if(raiz!=NULL){
                destroi(raiz);
            }
            printf("\nDigite o nome do arquivo: ");
            scanf("%s",nomeArq);
            arq = fopen(nomeArq,"rt");
            if(arq == NULL){
                printf("\nO arquivo não existe. Tente novamente!\n\n");
                break;
            }
            raiz = LerArvore(arq,raiz);
            fclose(arq);
            printf("\n");
            break;
        case 2:
            printf("\n1- Pre-Ordem\n");
            printf("2- Em-Ordem\n");
            printf("3- Pos-Ordem\n");
            printf("4- Em Largura\n");
            printf("9- Voltar ao menu principal\n\n");
            scanf("%d",&opcao);
            switch(opcao){
                case 1:
                    printf("\n");
                    ImprimirPre(raiz);
                    printf("\n");
                    break;
                case 2:
                    printf("\n");
                    ImprimirEmOrdem(raiz);
                    printf("\n");
                    break;
                case 3:
                    printf("\n");
                    ImprimirPos(raiz);
                    printf("\n");
                    break;
                case 4:
                    h = altura(raiz);
                    printf("\n");
                    for(int i=0;i<h;i++){
                        ImprimirLargura(raiz,0,i);
                        printf("\n");
                    }
                    break;
                case 9:
                    break;//volta ao menu principal
            }
            printf("\n");
            break;
        case 3:
            printf("\nDigite o elemento a ser procurado na árvore: ");
            scanf("%d",&x);
            printf("\n%d\n",VerificaX(raiz,x));
            printf("\n");
            break;
        case 4:
            printf("\n%d\n",contarElementos(raiz));
            break;
        case 5:
            printf("\n");
            imprimirFolhas(raiz);
            printf("\n");
            break;
        case 6:
            if(raiz == NULL){
                printf("Toda árvore vazia é balanceada.\n");
            }
            printf("\n%d\n\n",Balanceada(raiz));
            break;
        case 7:
            if(raiz == NULL){
                printf("Toda árvore vazia é completa\n");
            }
            printf("\n%d\n\n",Cheia(raiz));
            break;
        case 8:
            printf("Digite o elemento: ");
            scanf("%d",&x);
            printf("\n");
            if(VerificaX(raiz,x) == NULL){
                printf("\nO elemento não se encontra na árvore.\n\n");
                break;
            }
            CamadaDoItem(raiz,x,0);
            printf("\n\n");
            break;
        case 9:
            if(raiz != NULL){
                destroi(raiz);
            }
            return;//encerramento do programa caso o usuario digite 9
    }
    menu(raiz);
}

int main(){

    arvore *raiz = NULL;//criacao do primeiro nó da arvore que será passado por todas as funções
    menu(raiz);//chamada da função menu implementada de forma recursiva

    return 0;
}

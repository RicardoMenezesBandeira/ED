#include <stdio.h>
#include <stdlib.h>

typedef struct arvore{
    int info;
    struct arovre *esq;
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

int VerificaX(arvore *a, int x){//verifica se um elemento X está na arvore
    if(a == NULL){// se entrar nesse if já passou por todos os ramos
        return 0;
    }
    else if(a->info == x){// se entrar nesse if encontrou o elemento
        return 1;
    }
    else{
        return (VerificaX(a->esq,x) || VerificaX(a->dir,x));//retorna para a raiz a resposta da chamada dos nós
    }
}

arvore *destroi(arvore *a){

    if(a->esq !=NULL){//se tem caminho pela esquerda
        a = destroi(a->esq);
    }
    if(a->esq !=NULL){//se tem caminho pela direita
        a = destroi(a->dir);
    }
    if(a->esq ==NULL && a->dir ==NULL){//se é uma folha destroi e retorna
        free(a);
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



void menu(arvore *raiz){//o ponteiro raiz é criado na main e é usado como argumento por todas as funções do menu
//antes não funcionava pq a declaração do ponteiro era feita no proprio menu e sempre que ele era chamado recursivamente o valor era alterado pra NULL
    int opcao,x;//opcao é a váriavel de escolha do menu e X é o elemento a ser procurado na arvore por uma das funções
    char nomeArq[20];
    FILE *arq = NULL;
    printf("1- Ler uma árvore de um arquivo fornecido\n");
    printf("2- Imprimir a árvore\n");
    printf("3- Verificar se um elemento x existe na árvore\n");
    printf("4- Contar o número de elementos na árvore\n");
    printf("5- Imprimir os nós folhas da árvore\n");
    printf("9- Sair\n");
    scanf("%d",&opcao);
    switch(opcao){
        case 1:
            if(raiz!=NULL){
                destroi(raiz);
            }
            printf("Digite o nome do arquivo: ");
            scanf("%s",nomeArq);
            arq = fopen(nomeArq,"rt");
            raiz = LerArvore(arq,raiz);
            fclose(arq);
            break;
        case 2:
            printf("1- Pre-Ordem\n");
            printf("2- Em-Ordem\n");
            printf("3- Pos-Ordem\n");
            printf("9- Voltar ao menu principal\n");
            scanf("%d",&opcao);
            switch(opcao){
                case 1:
                    ImprimirPre(raiz);
                    printf("\n");
                    break;
                case 2:
                    ImprimirEmOrdem(raiz);
                    printf("\n");
                    break;
                case 3:
                    ImprimirPos(raiz);
                    printf("\n");
                    break;
                case 9:
                    break;//volta ao menu principal
            }
            break;
        case 3:
            printf("Digite o elemento a ser procurado na árvore: ");
            scanf("%d",&x);
            printf("%d\n",VerificaX(raiz,x));
            break;
        case 4:
            printf("\n %d\n",contarElementos(raiz));
            break;
        case 5:
            printf("\n");
            imprimirFolhas(raiz);
            printf("\n");
            break;
        case 9:
            destroi(raiz);
            return;//encerramento do programa caso o usuario digite 9
    }
    menu(raiz);
}
int main(){
    arvore *raiz = NULL;//criacao do primeiro nó da arvore que será passado por todas as funções
    menu(raiz);//chamada da função menu implementada de forma recursiva

    return 0;
}

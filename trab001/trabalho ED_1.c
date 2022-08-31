#include <stdio.h>
typedef struct arvore{
    int info;
    struct arovre *esq;
    struct arvore *dir;
}arvore;
int menu(){
    int opcao;
    char nomeArq[20];
    arvore *a = NULL;
    FILE *arq = NULL;
    printf("1- Ler uma árvore de um arquivo fornecido\n");
    printf("2- Imprimir a árvore\n");
    printf("3- Verificar se um elemento x existe na árvore\n");
    printf("4- Contar o número de elemenetos na árvore\n");
    printf("5- Imprimir os nós folhas da árvore\n");
    printf("6- Sair\n");
    scanf("%d",&opcao);

    switch(opcao){
        case 1:
            printf("Digite o nome do arquivo: ");
            scanf("%s",nomeArq);
            arq = fopen(nomeArq,"rt");
            a = LerArvore(&arq);
            fclose(arq);
            break;
        case 2:
            ImprimirArvore(a);
            break;
        case 3:

            break;
        case 4:

            break;
        case 5:

            break;
        case 6:
            return;
    }

    menu();
}
arvore *ler(FILE *arq){
    char c;
    int num;
    arvore *a;

    fscanf(arq, "%c",&c);//ler (
    fscanf(arq, "%s",&num);//ler algarismo
    if(num==-1){//-1 vale como null
        return NULL;
    }else{
        a = (arvore*)malloc(sizeof(arvore));//separa espaço da memoria para um elemento da arvore e quarda o ponteiro em 'a'
        a->info = num;
        a->esq= ler(arq);//cria ramo para a esquerda ate encontrar null
        a->dir= ler(arq);//cria ramo para a direita ate encontrar null
        fscanf(arq, "%c",&c);//ler )
        return a;//retorna a arvore
    }
}

void imprimirPre(arvore *a){//pré-ordem 
    if(a != NULL){

        ImprimirArvore(a->esq);
        printf("%d ",a->info);
        ImprimirArvore(a->dir);
    }

}
void imprimirEm(arvore *a){}
void imprimirPos(arvore *a){}
void encontra(arvore *a,int x){}
void contarElementos(arvore *a){}
void imprimirFolhas(arvore *a){}
arvore *destroi(arvore *a){//revisar
    
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
int main(){
//    FILE *arq = NULL;
//    char nomeArq[200];
//    scanf("%s",nomeArq);
//    arq = fopen(nomeArq,"rt");
//    arvore *a = NULL;
//    a = LerArvore(arq);
//    ImprimirArvore(a);
//    fclose(arq);
    menu();
return 0;
}

#include <stdio.h>
typedef struct arvore{
    int info;
    struct arovre *esq;
    struct arvore *dir;
}arvore;
int menu(){
    int op;// variavel que recebe as opções
    printf("menu com opções");//mudar para testo correto depois
    fscanf("%d",&op);//op recebe opção digitada
    if(op<1 || op>6) {//opções numeradas de 1 a 6. fora desse intervalo é invalido
        printf("opção invalida");
        return 0;
    }
    else{
        //IF com opções
    }    
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

void imprimirPre(arvore *a){}
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

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

struct pilha{
  struct pilha* prox;
  int valor;
};
typedef struct pilha* Pilha;

int pilha_vazia(Pilha p) {
  if(p->prox == NULL){
    return 1;
  }
  return 0;
}

struct piramide {
  int tam_max, tam_atual;
};
typedef struct piramide* Piramide;

Piramide cria_piramide() {
  Piramide p = (Piramide) malloc(sizeof(struct piramide));
  p->tam_atual = 0;
  p->tam_max = 0;
  return p;
}

Pilha cria_pilha() {
  Pilha p = (Pilha) malloc(sizeof(struct pilha));
  p->prox =NULL;
  return p;
}

void empilha(Pilha pilha, int valor) {
  Pilha p = cria_pilha();
  p->valor = valor;
  p->prox = pilha->prox;
  pilha->prox = p;
}

int desempilha(Pilha pilha){
  int valor = pilha->prox->valor;
  Pilha aux = cria_pilha();
  aux = pilha->prox->prox;
  free(pilha->prox);
  pilha->prox = aux;
  return valor;
}

void esvazia_pilha(Pilha pilha) {
  while(!pilha_vazia(pilha)) {
    desempilha(pilha);
  }
}

void transfere_pilha(Pilha pilha, Pilha pilha2) {
  while(!pilha_vazia(pilha)) {
    empilha(pilha2, desempilha(pilha));
  }
}



int verifica_piramide(int valor, Pilha pilha,Piramide piramide) {
  if(pilha_vazia(pilha)){
    empilha(pilha, valor);
    printf("**[1]**\n");
  }
  else {
    int v = desempilha(pilha);
    if(valor > v){
      printf("**[2]**\n");
      empilha(pilha, v);
      empilha(pilha, valor);
    }
    else {
      if(valor == v){
        if(piramide->tam_atual == 0) {
          printf("**[3]**\n");
          esvazia_pilha(pilha);
          piramide->tam_atual = 0;
          empilha(pilha, v);
        }
        else {
          if(piramide->tam_atual > 0) {
            printf("**[4]**\n");
            piramide->tam_atual = piramide->tam_atual + 1;
            if(piramide->tam_atual > piramide->tam_max) {
              printf("**[5]**\n");
              piramide->tam_max = piramide->tam_atual;
            }
          }
        }
      }
      else {

        printf("**[6]**\n");
        if(pilha_vazia(pilha)) {
          printf("**[7]**\n");
          empilha(pilha, valor);
          empilha(pilha, v);
        }
        else {
          printf("**[8]**\n");
          int v2 = desempilha(pilha);
          if(v2 == valor) {
            printf("**[9]**\n");
            piramide->tam_atual = 1;
            if(piramide->tam_max < piramide->tam_atual) {
              printf("**[10]**\n");
              piramide->tam_max = 1;
            }
          }
        }
      }
    }
  }
}

struct item_lista {
  struct  item_lista *prox;
  int valor ;
  int qtd_lida;
};
typedef struct item_lista* Item;
 
struct  cabeca_lista {
  struct item_lista *inicio, *fim;
  int qtd_total, size;
};
typedef struct cabeca_lista* Cabeca;
/**
* funçao
*/
void adiciona_Item(int valor, Cabeca lista) {
  Item i = (Item) malloc(sizeof(struct item_lista));
  i->valor = valor;
  i->qtd_lida = 1;
  i->prox = NULL;
  if(lista->inicio == NULL){
    lista->inicio = i;
  }else{
    lista->fim->prox = i;
  }
  lista->fim = i;
  lista->size = lista->size + 1;
}

Cabeca cria_Cabeca(){
  Cabeca c = (Cabeca) malloc(sizeof(struct cabeca_lista));
  c->size = -1;
  c->inicio = NULL;
  c->qtd_total = 0;
  adiciona_Item(0,c);
  return c;
}

void ler_e_incrementa_Item(int valor, Cabeca lista){
  lista->qtd_total = lista->qtd_total +1;
  Item aux = lista->inicio;
  while(aux->prox !=NULL){
    if(aux->prox->valor == valor){
      aux->prox->qtd_lida = aux->prox->qtd_lida + 1;
      return;
    }
    aux = aux->prox;
  }
  adiciona_Item(valor,lista);
}


void remove_Item(Cabeca lista, Item itemlista) {
  Item aux = lista->inicio;
  Item aux2;
  while(aux->prox != NULL){
    if(aux->prox->valor == itemlista->valor){
      aux2 = aux->prox->prox;
      free(aux->prox);
      aux->prox = aux2;
      break;
    }
    aux = aux->prox;
  }
}

void imprimeLista(Cabeca lista){
  Item aux = lista->inicio;
  float real;
  while(aux->prox != NULL) {
    real = (float) aux->prox->qtd_lida / (float) lista->qtd_total;
    printf("%i   %i    %.3f\n",aux->prox->valor, aux->prox->qtd_lida, real);
    aux = aux->prox;
  }

}

void ler_numero(int valor, Cabeca lista,Pilha pilha, Piramide piramide){
  ler_e_incrementa_Item(valor, lista);
  verifica_piramide(valor , pilha, piramide);
}

void  ler(Cabeca cabeca,Pilha pilha, Piramide piramide){
  FILE* arq;
  arq = fopen("seq.in", "r");
  int inteiro;
  if(arq == NULL)
    exit(-1);
  while(!feof(arq)){
    fscanf(arq, "%i",&inteiro);
    printf("lendo (%i)\n",inteiro);
    ler_numero(inteiro,cabeca,pilha,piramide);
    if(!feof(arq)){
      fscanf(arq, ",");
    }
    if(!feof(arq)){
      fscanf(arq, " ");
    }
    imprimeLista(cabeca);
    printf("\nMAIOR PIRAMEDE:%d\n\n\n\n",piramide->tam_max);
  }
}

int main(void) {
  Cabeca cabeca =  cria_Cabeca();
  Pilha pilha = cria_pilha();
  Piramide piramide = cria_piramide();
  ler(cabeca, pilha, piramide);
  imprimeLista(cabeca);
  printf("\n\n%d",piramide->tam_max);
  return 0;
}

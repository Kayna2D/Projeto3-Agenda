#include "agenda.h"
#include <stdio.h>
#include <string.h>

Erro criar(Contato agenda[], int *pos) {
  if (*pos >= TOTAL)
    return MAX_CONTATOS;

  printf("Entre com o nome: ");
  
  printf("Entre com o sobrenome: ");
  
  printf("Entre com o e-mail: ");
  
  printf("Entre com o telefone (apenas numeros): ");
  

  return OK;
}

Erro listar(Contato agenda[], int pos) {
  printf("Listar\n");

  return OK;
}

Erro deletar(Contato agenda[], int *pos) {
  printf("Deletar\n");

  return OK;
}

void clearBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}
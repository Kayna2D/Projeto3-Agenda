#include "agenda.h"
#include <stdio.h>
#include <string.h>

Erro criar(Contato agenda[], int *pos) {
  if (*pos >= TOTAL)
    return MAX_CONTATOS;

  printf("Entre com o nome: ");
  scanf("%[^\n]", agenda[*pos].nome);
  clearBuffer();
  
  printf("Entre com o sobrenome: ");
  scanf("%[^\n]", agenda[*pos].sobrenome);
  clearBuffer();
  
  printf("Entre com o e-mail: ");
  scanf("%[^\n]", agenda[*pos].email);
  clearBuffer();
  
  printf("Entre com o telefone (apenas numeros): ");
  scanf("%[^\n]", agenda[*pos].telefone);
  clearBuffer();
  
  *pos = *pos + 1;
  
  return OK;
}

Erro listar(Contato agenda[], int *pos) {
  if(*pos == 0)
    return SEM_CONTATOS;

  // for(int i = 0; i < *pos; i++) {
  //   printf("Nome: %s\n", agenda[i].nome);
  //   printf("Sobrenome: %s\n", agenda[i].sobrenome);
  //   printf("E-mail: %s\n", agenda[i].email);
  //   printf("Telefone: %s\n", agenda[i].telefone);
  // }

  

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
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
  
  printf("Entre com o telefone de 11 digitos (apenas numeros): ");
  scanf("%[^\n]", agenda[*pos].telefone);
  clearBuffer();
  if (strlen(agenda[*pos].telefone) != 11)
    return TEL_INVALIDO;
  
  *pos = *pos + 1;
  
  return OK;
}

Erro listar(Contato agenda[], int *pos) {
  if(*pos == 0)
    return SEM_CONTATOS;

  for(int i = 0; i < *pos; i++) {
    printf("Nome: %s\t", agenda[i].nome);
    printf("Sobrenome: %s\t", agenda[i].sobrenome);
    printf("E-mail: %s\t", agenda[i].email);
    printf("Telefone: %c%c %c.%c%c%c%c-%c%c%c%c\n", agenda[i].telefone[0], agenda[i].telefone[1], agenda[i].telefone[2], agenda[i].telefone[3], agenda[i].telefone[4], agenda[i].telefone[5], agenda[i].telefone[6], agenda[i].telefone[7], agenda[i].telefone[8], agenda[i].telefone[9], agenda[i].telefone[10]);
  }

  

  return OK;
}

Erro deletar(Contato agenda[], int *pos) {
  if (*pos == 0)
    return SEM_CONTATOS;

  char telefone[11];
  int check = 0;

  printf("Entre com o telefone de 11 digitos (apenas numeros): ");
  scanf("%[^\n]", telefone);
  clearBuffer();
  if (strlen(telefone) != 11)
    return TEL_INVALIDO;

  for(int i = 0; i < *pos; i++) {
    if (strcmp(agenda[i].telefone, telefone) == 0) {
      *pos = *pos - 1;
      check = 1;
      for(int j = i; j < *pos; j++) {
        strcpy(agenda[j].nome, agenda[j + 1].nome);
        strcpy(agenda[j].sobrenome, agenda[j + 1].sobrenome);
        strcpy(agenda[j].email, agenda[j + 1].email);
        strcpy(agenda[j].telefone, agenda[j + 1].telefone);
      }
      break;
    }
  }
  if (check == 0)
    return NAO_ENCONTRADO;

  
  return OK;
}

Erro salvar(Contato agenda[], int *pos) {
  FILE *f = fopen("agenda.bin", "wb");
  if (f == NULL)
    return ABRIR;

  int qtd = fwrite(agenda, TOTAL, sizeof(Contato), f);
  if (qtd == 0)
    return ESCREVER;

  qtd = fwrite(pos, 1, sizeof(int), f);
  if (qtd == 0)
    return ESCREVER;
  
  if (fclose(f))
    return FECHAR;
  
  return OK;
}

Erro carregar(Contato agenda[], int *pos) {
  FILE *f = fopen("agenda.bin", "rb");
  if (f == NULL)
    return ABRIR;

  int qtd = fread(agenda, TOTAL, sizeof(Contato), f);
  if (qtd == 0)
    return LER;

  qtd = fread(pos, 1, sizeof(int), f);
  if (qtd == 0)
    return LER;

  if (fclose(f))
    return FECHAR;

  return OK;
}

void clearBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}
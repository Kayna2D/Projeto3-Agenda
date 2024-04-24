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

  for(int i = 0; i < *pos; i++) {
    printf("Pos: %d\t", i + 1);
    printf("Nome: %s\t", agenda[i].nome);
    printf("Sobrenome: %s\t", agenda[i].sobrenome);
    printf("E-mail: %s\t", agenda[i].email);
    printf("Telefone: %s\n", agenda[i].telefone);
  }

  

  return OK;
}

Erro deletar(Contato agenda[], int *pos) {
  if (*pos == 0)
    return SEM_CONTATOS;

  int pos_deletar;
  printf("Entre com a posicao do contato a ser deletado: ");
  scanf("%d", &pos_deletar);
  pos_deletar--; // garantir posicao certa no array
  if (pos_deletar >= *pos || pos_deletar < 0)
    return NAO_ENCONTRADO;

  for (int i = pos_deletar; i < *pos; i++)
    {
      strcpy(agenda[i].nome, agenda[i + 1].nome);
      strcpy(agenda[i].sobrenome, agenda[i + 1].sobrenome);
      strcpy(agenda[i].email, agenda[i + 1].email);
      strcpy(agenda[i].telefone, agenda[i + 1].telefone);
    }

    *pos = *pos - 1;

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
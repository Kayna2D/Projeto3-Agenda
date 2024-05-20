#include "agenda.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int validar_char(char c) {
  return (isalnum(c) || c == '.' || c == '-' || c == '_');
}

int validar_email(const char *email) {
  const char *arroba = strchr(email, '@');
  if (!arroba)
    return 0;

  const char *dom = arroba + 1;
  if (strchr(dom, '@'))
    return 0;

  const char *ponto = strrchr(dom, '.');
  if (!ponto)
    return 0;

  if (ponto == dom || ponto == dom + strlen(dom) - 1)
    return 0;

  for (const char *p = email; p < arroba; ++p) {
    if (!validar_char(*p))
      return 0;
  }

  for (const char *p = dom; p < ponto; ++p) {
    if (!validar_char(*p))
      return 0;
  }

  for (const char *p = ponto + 1; *p; ++p) {
    if (!isalpha(*p))
      return 0;
  }

  return 1;
}

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
  if (!validar_email(agenda[*pos].email))
    return EMAIL_INVALIDO;
  printf("Entre com o telefone de 11 digitos (apenas numeros): ");
  scanf("%[^\n]", agenda[*pos].telefone);
  clearBuffer();
  if (strlen(agenda[*pos].telefone) != 11)
    return TEL_INVALIDO;

  *pos = *pos + 1;

  return OK;
}

Erro listar(Contato agenda[], int *pos) {
  if (*pos == 0)
    return SEM_CONTATOS;

  for (int i = 0; i < *pos; i++) {
    printf("Nome: %s\t", agenda[i].nome);
    printf("Sobrenome: %s\t", agenda[i].sobrenome);
    printf("E-mail: %s\t", agenda[i].email);
    printf("Telefone: %c%c %c.%c%c%c%c-%c%c%c%c\n", agenda[i].telefone[0],
           agenda[i].telefone[1], agenda[i].telefone[2], agenda[i].telefone[3],
           agenda[i].telefone[4], agenda[i].telefone[5], agenda[i].telefone[6],
           agenda[i].telefone[7], agenda[i].telefone[8], agenda[i].telefone[9],
           agenda[i].telefone[10]);
  }

  return OK;
}

Erro deletar(Contato agenda[], int *pos) {
  if (*pos == 0)
    return SEM_CONTATOS;

  int pos_deletar = -1;
  char telefone[12];

  printf("Entre com o telefone de 11 digitos (apenas numeros): ");
  scanf("%[^\n]", telefone);
  clearBuffer();
  if (strlen(telefone) != 11)
    return TEL_INVALIDO;

  for (int i = 0; i < *pos; i++) {
    if (strcmp(agenda[i].telefone, telefone) == 0) {
      pos_deletar = i;
      break;
    }
  }

  if (pos_deletar >= *pos || pos_deletar < 0)
    return NAO_ENCONTRADO;

  for (int i = pos_deletar; i < *pos; i++) {
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
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

int verificar_telefone_unico(Contato agenda[], int *pos, char *telefone) {
  for (int i = 0; i < *pos; i++) {
    if (strcmp(agenda[i].telefone, telefone) == 0)
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
  else if (!verificar_telefone_unico(agenda, pos, agenda[*pos].telefone))
    return TEL_EXISTENTE;

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

Erro alterar(Contato agenda[], int *pos) {
  if (*pos == 0)
    return SEM_CONTATOS;

  char telefone[12];
  int pos_alterar = -1;

  printf("Entre com o telefone de 11 digitos (apenas numeros): ");
  scanf("%[^\n]", telefone);
  clearBuffer();
  if (strlen(telefone) != 11)
    return TEL_INVALIDO;

  for (int i = 0; i < *pos; i++) {
    if (strcmp(agenda[i].telefone, telefone) == 0) {
      pos_alterar = i;
      break;
    }
  }

  if (pos_alterar >= *pos || pos_alterar < 0)
    return NAO_ENCONTRADO;
  else {
    int opcao;
    do {
      printf("Qual campo deseja alterar?\n");
      printf("1 - Nome\t");
      printf("2 - Sobrenome\t");
      printf("3 - E-mail\t");
      printf("4 - Telefone\t");
      printf("0 - Pronto!\n");
      printf("Entre com uma opcao: ");
      scanf("%d", &opcao);
      clearBuffer();
      opcao--;
      if (opcao > 3)
        printf("Opcao invalida\n");
      else if (opcao == 0){
        printf("Entre com o novo nome: ");
        scanf("%[^\n]", agenda[pos_alterar].nome);
        clearBuffer();
        printf("\n");
        }
      else if (opcao == 1){
        printf("Entre com o novo sobrenome: ");
        scanf("%[^\n]", agenda[pos_alterar].sobrenome);
        clearBuffer();
        printf("\n");
}
      else if (opcao == 2){
        char email[300];
        printf("Entre com o novo e-mail: ");
        scanf("%[^\n]", email);
        clearBuffer();
        if (!validar_email(email)){
          printf("Email invalido. Por favor, tente novamente\n");
          printf("\n");
          }
        else
          strcpy(agenda[pos_alterar].email, email);
} 
      else if (opcao == 3){
        char telefone[12];
        printf("Entre com o novo telefone de 11 digitos (apenas numeros): ");
        scanf("%[^\n]", telefone);
        clearBuffer();
        if (strlen(telefone) != 11)
          printf("Telefone invalido. Por favor, tente novamente\n");
        
        if (!verificar_telefone_unico(agenda, pos, telefone)){
          printf("Telefone ja registrado. Por favor, tente novamente\n");
          }
        else
          strcpy(agenda[pos_alterar].telefone, telefone);
        printf("\n");
}
// (!verificar_telefone_unico(agenda, pos, agenda[*pos].telefone)
    } while (opcao >= 0);
    
    }
  
  return OK;

}

Erro salvar(Contato agenda_pessoal[], int *pos_pessoal, Contato agenda_profissional[], int *pos_profissional) {
  FILE *f = fopen("agenda_pessoal.bin", "wb");
  if (f == NULL)
    return ABRIR;

  if (fwrite(pos_pessoal, sizeof(int), 1, f) != 1){
    fclose(f);
    return ESCREVER;
}

  if (fwrite(agenda_pessoal, sizeof(Contato), *pos_pessoal, f) != *pos_pessoal){
    fclose(f);
    return ESCREVER;
}

  if (fclose(f))
    return FECHAR;

  f = fopen("agenda_profissional.bin", "wb");
  if (f == NULL)
    return ABRIR;

  if (fwrite(pos_profissional, sizeof(int), 1, f) != 1){
    fclose(f);
    return ESCREVER;
}

  if (fwrite(agenda_profissional, sizeof(Contato), *pos_profissional, f) != *pos_profissional){
    fclose(f);
    return ESCREVER;
}

  if (fclose(f))
    return FECHAR;

  return OK;
}

Erro carregar(Contato agenda_pessoal[], int *pos_pessoal, Contato agenda_profissional[], int *pos_profissional) {
  FILE *f = fopen("agenda_pessoal.bin", "rb");
  if (f == NULL)
    return ABRIR;

  if (fread(pos_pessoal, sizeof(int), 1, f) != 1){
    fclose(f);
    return LER;
}
  
  if (fread(agenda_pessoal, sizeof(Contato), *pos_pessoal, f) != *pos_pessoal){
    fclose(f);    
    return LER;
}

  if (fclose(f))
    return FECHAR;

  f = fopen("agenda_profissional.bin", "rb");
  if (f == NULL)
    return ABRIR;

  if (fread(pos_profissional, sizeof(int), 1, f) != 1){
    fclose(f);
    return LER;
}

  if (fread(agenda_profissional, sizeof(Contato), *pos_profissional, f) != *pos_profissional){
    fclose(f);
    return LER;
  }

  if (fclose(f))
    return FECHAR;

  return OK;
}

void clearBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}


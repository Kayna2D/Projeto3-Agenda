#define TOTAL 255

typedef struct Contato {
  char nome[100];
  char sobrnome[300];
  char email[300];
  char telefone[11];
} Contato;

typedef enum Erros {
  OK,
  MAX_CONTATOS,
  SEM_TAREFAS
} Erro;

Erro criar(Contato agenda[], int *pos);
Erro listar(Contato agenda[], int pos);
Erro deletar(Contato agenda[], int *pos);

void clearBuffer();
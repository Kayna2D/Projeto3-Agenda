#define TOTAL 255

typedef struct Contato {
  char nome[100];
  char sobrnome[300];
  char email[300];
  char telefone[11];
} Contato;

void criar(Contato agenda[], int *pos);
void listar(Contato agenda[], int pos);
void deletar(Contato agenda[], int *pos);
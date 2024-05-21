#define TOTAL 255

typedef struct Contato {
  char nome[100];
  char sobrenome[300];
  char email[300];
  char telefone[12];
} Contato;

typedef enum Erros {
  OK,
  MAX_CONTATOS,
  SEM_CONTATOS,
  NAO_ENCONTRADO, 
  ABRIR,
  ESCREVER, 
  LER,
  FECHAR,
  TEL_INVALIDO,
  EMAIL_INVALIDO,
  TEL_EXISTENTE
} Erro;

typedef Erro (*funcao)(Contato[], int*);

Erro criar(Contato agenda[], int *pos);
Erro listar(Contato agenda[], int *pos);
Erro deletar(Contato agenda[], int *pos);
Erro salvar(Contato agenda[], int *pos);
Erro carregar(Contato agenda[], int *pos);

void clearBuffer();
int validar_email(const char *telefone);
int validar_char(char c);
int verificar_telefone_unico(Contato agenda[], int *pos, char *telefone);
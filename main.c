#include <stdio.h>
#include "agenda.h"

int main() {
  int pos;
  int opcao;
  Contato agenda[TOTAL];
  do {
    printf("\nMenu principal\n");
    printf("1 - Criar contato\n");
    printf("2 - Listar contatos\n");
    printf("3 - Deletar contatos\n");
    printf("0 - Sair\n");
    printf("Entre com uma opção: ");
    int i = scanf("%d", &opcao);
    printf("Opção escolhida: %d\n", opcao);

    if (opcao == 1)
      criar(agenda, &pos);
    else if (opcao == 2)
      listar(agenda, pos);
    else if (opcao == 3)
      deletar(agenda, &pos);
  } while (opcao != 0);    
}
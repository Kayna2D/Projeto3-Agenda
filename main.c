#include <stdio.h>

int main() {
  int opcao = 1;
  do {
    printf("\nMenu principal\n");
    printf("1 - Criar tarefa\n");
    printf("2 - Deletar tarefa\n");
    printf("3 - Listar tarefas\n");
    printf("0 - Sair\n");
    printf("Entre com uma opção: ");
  } while (opcao != 0);    
}
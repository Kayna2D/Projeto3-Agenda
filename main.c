#include "agenda.h"
#include <stdio.h>

int main() {
  funcao fs[] = {criar, listar, deletar};

  int pos;
  Erro erro;
  int opcao;
  Contato agenda[TOTAL];
  do {
    printf("\nMenu principal\n");
    printf("1 - Criar contato\n");
    printf("2 - Listar contatos\n");
    printf("3 - Deletar contatos\n");
    printf("0 - Sair\n");
    printf("Entre com uma opção: ");
    
    scanf("%d", &opcao);
    clearBuffer();
    opcao--;
    
    if (opcao > 2)
      printf("Opção inválida\n");
    else if (opcao >= 0) {
      erro = fs[opcao](agenda, &pos);
      if (opcao == 0){
        if (erro == MAX_CONTATOS)
          printf("Numero maximo de contatos atingido\n");
        else
          printf("Contato criado com sucesso\n");
      }
        
      else if (opcao == 1){
        if (erro == SEM_CONTATOS)
          printf("Não há contatos para listar\n");
   }
      else if (opcao == 2){
        if (erro == SEM_CONTATOS)
          printf("Não há contatos para deletar\n");
        else if (erro == NAO_ENCONTRADO)
          printf("Contato não encontrado\n");
          }
    } 
  } while (opcao >= 0);
    }
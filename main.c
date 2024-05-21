#include "agenda.h"
#include <stdio.h>

int main() {
  funcao fs[] = {criar, listar, deletar, salvar, carregar};

  int pos;
  Contato agenda[TOTAL];
  Erro erro = fs[4](agenda, &pos);
  if(erro == ABRIR){
    printf("Erro de leitura ou arquivo inexistente");
    pos = 0;
  } else if (erro == FECHAR)
    printf("Erro ao fechar arquivo");
  int opcao;
  
  do {
    printf("\nMenu principal\n");
    printf("1 - Criar contato\n");
    printf("2 - Listar contatos\n");
    printf("3 - Deletar contato\n");
    printf("0 - Sair\n");
    printf("Entre com uma opcao: ");
    
    scanf("%d", &opcao);
    clearBuffer();
    opcao--;
    
    if (opcao > 2)
      printf("Opcao invalida\n");
    else if (opcao >= 0) {
      erro = fs[opcao](agenda, &pos);
      if (opcao == 0){
        if (erro == MAX_CONTATOS)
          printf("Numero maximo de contatos atingido\n");
        else if (erro == TEL_INVALIDO)
          printf("Numero de telefone invalido. Por favor, tente novamente\n");
        else if (erro == TEL_EXISTENTE)
          printf("Telefone já registrado. Por favor, tente novamente\n");
        else if (erro == EMAIL_INVALIDO)
          printf("Email invalido. Por favor, tente novamente\n");
        else
          printf("Contato criado com sucesso\n");
      }
        
      else if (opcao == 1){
        if (erro == SEM_CONTATOS)
          printf("Nao ha contatos para listar\n");
   }
      else if (opcao == 2){
        if (erro == SEM_CONTATOS)
          printf("Nao ha contatos para deletar\n");
        else if (erro == NAO_ENCONTRADO)
          printf("Contato nao encontrado\n");
        else if (erro == TEL_INVALIDO)
          printf("Numero de telefone invalido\n");
        else
          printf("Contato deletado com sucesso\n");
          }
    } else
      printf("Saindo...\n");
  } while (opcao >= 0);

  fs[3](agenda, &pos);
  Erro erro_salvar = fs[3](agenda, &pos);
  if (erro_salvar == ABRIR)
    printf("Erro ao abrir arquivo\n");
  else if (erro_salvar == ESCREVER)
    printf("Erro ao salvar no arquivo\n");
  else if (erro_salvar == FECHAR)
    printf("Erro ao fechar arquivo\n");
  else
    printf("Arquivo salvo com sucesso!\n");
    }
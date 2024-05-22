#include "agenda.h"
#include <stdio.h>

int main() {
  funcao fs[] = {criar, listar, deletar, alterar};

  int pos_pessoal = 0;
  int pos_profissional = 0;
  Contato agenda_pessoal[TOTAL];
  Contato agenda_profissional[TOTAL];

  Erro erro = carregar(agenda_pessoal, &pos_pessoal, agenda_profissional, &pos_profissional);
  if(erro == ABRIR){
    printf("Erro de leitura ou arquivo inexistente");
  } else if (erro == FECHAR)
    printf("Erro ao fechar arquivo");
  else
    printf("Arquivo carregado com sucesso");

  int opcao;
  Tipo_Contato tipo;

  do {
    printf("\nMenu principal\n");
    printf("1 - Criar contato\n");
    printf("2 - Listar contatos\n");
    printf("3 - Deletar contato\n");
    printf("4 - Alterar contato\n");
    printf("0 - Sair\n");
    printf("Entre com uma opcao: ");
    
    scanf("%d", &opcao);
    clearBuffer();

    if (opcao != 0) {
      printf("Escolha o tipo de contato: \n");
      printf("1 - Pessoal\n");
      printf("2 - Profissional\n");
      printf("Entre com uma opcao: ");
      scanf("%d", &tipo);
      clearBuffer();
    }

    opcao--;
    tipo--;
    if (opcao >= 0 && opcao <= 3) {
      if (tipo == PESSOAL) 
        erro = fs[opcao](agenda_pessoal, &pos_pessoal);
      else if (tipo == PROFISSIONAL) 
        erro = fs[opcao](agenda_profissional, &pos_profissional);
      else if (tipo > 1) {
        printf("Opcao invalida\n");
        continue;
      }

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

    else if (opcao == 3){
      if (erro == SEM_CONTATOS)
        printf("Nao ha contatos para alterar\n");
      else if (erro == NAO_ENCONTRADO)
        printf("Contato nao encontrado\n");
      else if (erro == TEL_INVALIDO)
        printf("Numero de telefone invalido\n");
      else if (erro == TEL_EXISTENTE)
        printf("Telefone ja registrado. Por favor, tente novamente\n");
      else if (erro == EMAIL_INVALIDO)
        printf("Email invalido. Por favor, tente novamente\n");
      else
        printf("Voltando para o menu\n");
  } 
  }else if (opcao < 0)
    printf("Saindo...\n");
  else
    printf("Opcao invalida\n");
} while (opcao >= 0);


Erro erro_salvar = salvar(agenda_pessoal, &pos_pessoal, agenda_profissional, &pos_profissional);
if (erro_salvar == ABRIR)
  printf("Erro ao abrir arquivo\n");
else if (erro_salvar == ESCREVER)
  printf("Erro ao salvar no arquivo\n");
else if (erro_salvar == FECHAR)
  printf("Erro ao fechar arquivo\n");
else
  printf("Arquivo salvo com sucesso!\n");

  return 0;
  }


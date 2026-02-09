#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

#define MENU_CLIENTE 1
#define MENU_CONTAS 2
#define MENU_MOVIMENTO 3
#define SAIR_DA_APLICACAO 4

#define NOVA_CONTA 1
#define EDITAR_CONTA 2
#define ENCERAR_CONTA 3
#define LISTAR_CONTA 4
#define PESQUISAR_CONTA 5
#define VOLTAR_CONTA 6


#define NOVO_CLIENTE 1
#define EDITAR_CLIENTE 2
#define ELIMINAR_CLIENTE 3
#define LISTAR_CLIENTES 4
#define PESQUISAR_CLIENTE 5
#define VOLTAR_CLIENTE 6

#define NOVO_DEPOSITO 1
#define NOVO_LEVANTAMENTO 2
#define LISTAR_MOVIMENTOS 3
#define VOLTAR_MOVIMENTO 4	

void apresentacao()
{
	char opcao;
	
	printf("\t------------------------------------------------\n");
	printf("\tUNIVERSIDADE CATOLICA DE ANGOLA\n");
	printf("\tFACULDADE DE ENGENHARIA\n");
	printf("\tPROJECTO DE FUNDAMENTOS DE PROG. I ANO 25-26\n");
	printf("\tAUTOR: SABALO ZUA, N. 36697\n");
	printf("\t------------------------------------------------\n");
	printf("\tTEMA: GESTAO DE CONTAS BANCARIAS\n");
	printf("\tDOCENTE: ENG. OSVALDO RAMOS\n");
	printf("\tOBS: USO EXCLUSIVO DENTRO DA UCAN\n");
	printf("\t------------------------------------------------\n");
	printf("\tSE CONCORDA COM OS TERMOS DE USO DIGITE S, N CASO CONTRARIO\n");
	
	scanf(" %c", &opcao);	
	
	if (opcao == 'S' || opcao == 's')
		menuPrincipal();
	else
	{
		printf("ate a proxima!\n");
		return;
	}
}


void menuPrincipal()
{
	int opcao;
		
	do
	{
	
		system("cls");	
		printf("\n\t\tMENU PRINCIPAL\n");
		printf("\t\t1 - MENU CLIENTE\n");
		printf("\t\t2 - MENU CONTA\n");
		printf("\t\t3 - MENU MOVIMENTOS\n");
		printf("\t\t4 - SAIR DA APLICACAO\n");
		
		printf("Escolha uma Opcao\n");
		scanf("%d", &opcao);
		
		switch(opcao)
		{
			case MENU_CLIENTE:
				menuCliente();
			break;
			
			case MENU_CONTAS:
				menuConta();
			break;
			
			case  MENU_MOVIMENTO:
				menuMovimento();
			break;
			
			case SAIR_DA_APLICACAO:
				return;
			break;
			
			default:
				printf("Opcao Invalida!\n");
		}
	}while (opcao != SAIR_DA_APLICACAO);
}

void menuCliente()
{
	int opcao;
	
	system("cls");
	
	do
	{		
							
		printf("***MENU CLIENTE***\n");
		printf("***1 - NOVO CLIENTE***\n");
		printf("***2 - EDITAR CLIENTE***\n");
		printf("***3 - ELIMINAR CLIENTE***\n");
		printf("***4 - LISTAR CLIENTES***\n");
		printf("***5 - PESQUISAR CLIENTE***\n");
		printf("***6 - VOLTAR***\n");
		printf("Escolha uma opcao\n");
		scanf("%d", &opcao);
		
		switch (opcao)
		{
			case NOVO_CLIENTE:
				salvarDadosCliente();	
				
				system("pause");		
			break;
			
			case EDITAR_CLIENTE:
				alterarDadosCliente();
				
				system("pause");
			break;
			
			case ELIMINAR_CLIENTE:
				printf("Eliminar Cadaver\n");
			break;
		
			case LISTAR_CLIENTES:
				listarDadosCliente();
				
				system("pause");
			break;
			
			case PESQUISAR_CLIENTE:
				pesquisarClientePorNome();
			break;
				
			case VOLTAR_CLIENTE:
				return;
			break;
			
			default:
				printf("Opcao Invalida\n");
		}
	}while(opcao != VOLTAR_CLIENTE);
}


void menuConta()
{
	int opcao;
	
	system("cls");
	
	do
	{		
							
		printf("***MENU CONTA***\n");
		printf("***1 - NOVA CONTA***\n");
		printf("***2 - ENCERRAR CONTA***\n");
		printf("***3 - LISTAR CONTAS***\n");
		printf("***4 - LISTAR CLIENTE***\n");
		printf("***5 - PESQUISAR CONTA***\n");
		printf("***6 - VOLTAR***\n");
		printf("Escolha uma opcao\n");
		scanf("%d", &opcao);
		
		switch (opcao)
		{
			case NOVA_CONTA:
				salvarDadosConta();	
				
				system("pause");		
			break;
			
			case EDITAR_CONTA:
				alterarDadosConta();
				
				system("pause");
			break;
			
			case ENCERAR_CONTA:
				printf("Eliminar Cadaver\n");
			break;
		
			case LISTAR_CONTA:
				listarDadosConta();
				
				system("pause");
			break;
			
			case PESQUISAR_CONTA:
				pesquisarContaPorNumero();
			break;
				
			case VOLTAR_CONTA:
				return;
			break;
			
			default:
				printf("Opcao Invalida\n");
		}
	}while(opcao != VOLTAR_CONTA);
}

void menuMovimento()

{
	int opcao;
	
	system("cls");
	
	do
	{		
							
		printf("***MENU CONTA***\n");
		printf("***1 - NOVO DEPOSITO***\n");
		printf("***2 - NOVO LEVANTAMENTO***\n");
		printf("***3 - LISTAR MOVIMENTOS***\n");
		printf("***4 - VOLTAR***\n");
		printf("Escolha uma opcao\n");
		scanf("%d", &opcao);
		
		switch (opcao)
		{
			case NOVO_DEPOSITO:
				salvarDadosConta();	
				
				system("pause");		
			break;
			
			case NOVO_LEVANTAMENTO:
			    realizarLevantamento();
				
				system("pause");
			break;
			
			case LISTAR_MOVIMENTOS:
				printf("Eliminar Cadaver\n");
			break;
		
			case VOLTAR_MOVIMENTO:
				return;
			break;
			
			default:
				printf("Opcao Invalida\n");
		}
	}while(opcao != VOLTAR_MOVIMENTO);
}
	
	
	
	
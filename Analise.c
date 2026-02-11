/******************************
FileName: Analise.c
Objectivo: Analise do Projecto
Tema: Gestão de Contas Bancárias
Nome: Sabalo Zua
N.º 36697
Data do Ficheiro: 25.01.2026

1. Descrição do Projecto:
criação de um sistema para gestão
de contas bancárias,que permita operações de abertura,
depósitos, levantamentos, e consultas.

2. Menus do Projecto
MENU PRINCIPAL
1 - MENU CLIENTE
2 - MENU CONTA
3 - MENU MOVIMENTOS
4 - SAIR
3. MENU CLIENTE
1 - NOVO CLIENTE
2 - EDITAR CLIENTE (Submenu: 1-Morada, 2-Telefone, 3-Email)
3 - ELIMINAR CLIENTE
4 - LISTAR CLIENTES
5 - PESQUISAR CLIENTE
6 - VOLTAR

4. MENU CONTA
1 - NOVA CONTA
2 - ENCERRAR CONTA
3 - LISTAR CONTA
4 - PESQUISAR CONTA
5 - VOLTAR

5. MENU MOVIMENTOS
1 - NOVO DEPÓSITO
2 - NOVO LEVANTAMENTO
3 - LISTAR MOVIMENTOS
4 - VOLTAR

6. Entidades
CLIENTE
int id;
char nome[50], bi[20] ,genero[14], morada[50], telefone[12];
DATE dataNascimento;


7. CONTA
int id, idCliente, numeroConta;
char iban[26], tipo[50];
float saldo;
DATE dataAbertura;

8.MOVIMENTO
int id, numeroConta ;
char tipo[50];
float valor;
DATE dataMovimento;

9. Ficheiros de Dados
CLIENTES.DAT
CONTAS.DAT
MOVIMENTOS.DAT
10. Implementação

Linguagem C
Editor de Código: Dev C++ 
*/

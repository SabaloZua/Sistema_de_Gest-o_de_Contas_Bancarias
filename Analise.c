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
2 - ELIMINAR CLIENTE
3 - LISTAR CLIENTES
4 - PESQUISAR CLIENTE
5 - VOLTAR
4. MENU CONTA
1 - NOVA CONTA
2 - ENCERRAR CONTA
3 - LISTAR CONTAS
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
char nome, bi,genero,  morada, telefone, email;
DATE dataNascimento;


7. CONTA
int id, idCliente,numeroConta,iban;
char tipo; float saldo;
DATE dataAbertura;

8.MOVIMENTO
int id, contaId ;
char tipo;
float valor;
DATE dataMovimento;

9. Ficheiros de Dados
CLIENTES.DAT
CONTAS.DAT
MOVIMENTOS.DAT
10. Implementação

Linguagem C
*/

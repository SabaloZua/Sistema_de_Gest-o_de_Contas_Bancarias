
/* Estrutura para representar uma data (dia, mes e ano) */
typedef struct data
{
	int dia, mes, ano;
}DATE;

/* Estrutura para representar um cliente do banco */
typedef struct cliente
{
	int id;                    // Identificador unico do cliente
	char nome[50], bi[20] ,genero[14], morada[50], telefone[12];
	DATE dataNascimento;       // Data de nascimento do cliente
}CLIENTE;

/* Estrutura para representar uma conta bancaria */
typedef struct conta
{
  	int id, idCliente;         // ID da conta e ID do cliente titular
	int numeroConta;           // Numero da conta
	char iban[26];             // AO06 + 21 digitos + '\0'
	char tipo[50];             // Tipo de conta (Poupanca/Corrente)
	float saldo;               // Saldo actual da conta em Kz
	DATE dataAbertura;         // Data de abertura da conta
}CONTA;

/* Estrutura para representar um movimento bancario (deposito ou levantamento) */
typedef struct movimento
{
	 int id, numeroConta ;         // ID do movimento e ID da conta associada
	 char tipo[50];            // Tipo de movimento (Deposito/Levantamento)
	 float valor;              // Valor do movimento em Kz
DATE dataMovimento;            // Data em que o movimento foi realizado
}MOVIMENTO;

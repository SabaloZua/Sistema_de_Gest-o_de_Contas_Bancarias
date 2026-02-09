
typedef struct data
{
	int dia, mes, ano;
}DATE;

typedef struct cliente
{
	int id;
	char nome[50], bi[20] ,genero[14], morada[50], telefone[12], email[50];
	DATE dataNascimento;
}CLIENTE;

typedef struct conta
{
  	int id, idCliente;
	char numeroConta[17];  // 16 digitos + '\0'
	char iban[26];         // AO06 + 21 digitos + '\0'
	char tipo[50];
	float saldo;
	DATE dataAbertura;
}CONTA;

typedef struct movimento
{
	 int id, contaId ;
	 char tipo[50];
	 float valor;
DATE dataMovimento;
}MOVIMENTO;

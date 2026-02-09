#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "Estrutras.h"

void pedirDadosCliente(CLIENTE *cliente, int alterar, int oldId) {
    if (alterar == 0) {
        printf("Id = %d\n", getNextClienteAutoID());
        cliente->id = getNextClienteAutoID();
        fflush(stdin);
    } else {
        printf("Id = %d\n", oldId);
        cliente->id = oldId;
        fflush(stdin);
    }

    printf("Nome?\n");
    gets(cliente->nome);

    fflush(stdin);

    printf("BI?\n");
    gets(cliente->bi);

    fflush(stdin);

    printf("Genero?\n");
    gets(cliente->genero);

    fflush(stdin);

    printf("Morada?\n");
    gets(cliente->morada);

    fflush(stdin);
    
     printf("Telefone?\n");
    gets(cliente->telefone);
    
      printf("email?\n");
    gets(cliente->email);


    fflush(stdin);

    printf("Data de Nascimento[DD-MM-AAAA]?\n");
    scanf("%d%d%d", &cliente->dataNascimento.dia,
          &cliente->dataNascimento.mes, &cliente->dataNascimento.ano);

    fflush(stdin);

 
}

void mostrarDadosCliente(CLIENTE cliente) {
	
	printf("\n ------------------------Dados Pessoasis----------------------------- \n");
    printf("Id: %d\n", cliente.id);

    printf("Nome: %s\n", cliente.nome);

    printf("BI: %s\n", cliente.bi);

    printf("Genero: %s\n", cliente.genero);

    printf("Morada %s\n", cliente.morada);
    
     printf("Data de Nascimento: [%d-%d-%d]\n",
           cliente.dataNascimento.dia,
           cliente.dataNascimento.mes,
           cliente.dataNascimento.ano);


 
           
    printf("\n ------------------------Dados Conctato----------------------------- \n");
    
    printf("Telefone %s\n", cliente.telefone);
    
    printf("email %s\n", cliente.email);

   
}

void salvarDadosCliente() {
    FILE *fp;
    CLIENTE cliente;
    memset(&cliente, 0, sizeof(CLIENTE));

    //abrir ou criar o ficheiro
    if ( (fp = fopen("CLIENTE.DAT", "ab")) == NULL) {
        puts("Erro ao tentar abrir o ficheiro!");
        return;
    }

    //movimentar o File Pointer
    fseek(fp, 0L, SEEK_END);	//SEEK_SET, SEEK_CUR, SEEK_END

    //pedir dados ao utilizador
    pedirDadosCliente(&cliente, 0, 0);

    //escrever os dados da estrutura para o ficheiro
    if( fwrite(&cliente, sizeof(CLIENTE), 1, fp) == 1) {
        system("cls");
        puts("Registo adicionado com sucesso no Ficheiro");
    }

    // fechar o ficheiro
    fclose( fp );
}

void listarDadosCliente() {
    FILE *fp;
    CLIENTE cliente;

    //abrir ou criar o ficheiro
    fp = fopen("CLIENTE.DAT", "rb");

    //movimentar o File Pointer
    fseek(fp, 0L, SEEK_SET);

    system("cls");

    puts("Listagem de Dados");

    //escrever os dados da estrutura para o ficheiro
    while( fread(&cliente, sizeof(CLIENTE), 1, fp) == 1) {
        puts("---------------------------------------");
        mostrarDadosCliente(cliente);
    }

    fclose( fp );

    system("pause");
    system("cls");
}

void pesquisarClientePorNome() {
    FILE *fp;
    CLIENTE cliente;
    char nomeProcurado[50];

    //abrir ou criar o ficheiro
    fp = fopen("CLIENTE.DAT", "rb");

    //colocar o File Pointer no principio do ficheiro
    rewind(fp);

    puts("Digite o Nome Procurado");
    getchar();
    gets(nomeProcurado);

    //escrever os dados da estrutura para o ficheiro
    while( fread(&cliente, sizeof(CLIENTE), 1, fp) == 1) {
        if ( strcmp(cliente.nome, nomeProcurado) == 0) {
            system("cls");

            puts("Registo Localizado do Ficheiro\n");
            printf("-------------------------------------------\n");
            mostrarDadosCliente(cliente);
            printf("-------------------------------------------\n");

            fclose(fp);

            system("pause");
            system("cls");

            return;
        }
    }

    printf("%s nao Encontrado!...\n", nomeProcurado);

    fclose( fp );
}

int getNextClienteAutoID() {
    FILE *fp;
    CLIENTE cliente;
    int nextID = 1;

    fp = fopen("CLIENTES.DAT", "rb");

    rewind(fp);

    while( fread(&cliente, sizeof(CLIENTE), 1, fp) == 1) {
        nextID++;
    }

    fclose( fp );

    return nextID;
}

void alterarDadosCliente() {
    FILE *fp;
    CLIENTE cliente;
    memset(&cliente, 0, sizeof(CLIENTE));
    int idProcurado, posicao = 0;
    char opcao;

    //abrir ou criar o ficheiro
    if ( (fp = fopen("CLIENTE.DAT", "a+b")) == NULL) {
        puts("Erro ao tentar abrir o ficheiro!");
        return;
    }

    rewind(fp);

    puts("Digite o Id que deseja alterar");
    scanf("%d", &idProcurado);

    //escrever os dados da estrutura para o ficheiro
    while( fread(&cliente, sizeof(CLIENTE), 1, fp) == 1) {
        posicao++;

        if ( cliente.id == idProcurado ) {
            system("cls");

            puts("Registo Localizado");
            mostrarDadosCliente(cliente);


            printf("\nTem certeza q deseja alterar este registo [S/N]?\n");
            scanf(" %c", &opcao);

            system("cls");

            if (opcao == 'S' || opcao == 's') {
                pedirDadosCliente(&cliente, 1, cliente.id);

                //rever apartir daqui
                rewind(fp);

                //colocar o curso no registo procurado
                fseek(fp, (posicao-1)*sizeof(CLIENTE), SEEK_SET);

                //escrever os dados da estrutura para o ficheiro
                if( fwrite(&cliente, sizeof(CLIENTE), 1, fp) == 1) {
                    system("cls");
                    puts("Registo Alterado com sucesso no Ficheiro");
                } else {
                    system("cls");
                    puts("Erro ao tentar alterar os dados do ficheiro");
                }

            }

            fclose(fp);
            return;
        }
    }

    printf("%d nao Encontrado!...\n", idProcurado);
    fclose(fp);

}

// ======================= FUNCOES CONTA BANCARIA =======================

// Gera numero de conta (16 digitos) e IBAN baseado nele
void gerarContaEIban(char *numeroConta, char *iban) {
    static int inicializado = 0;
    if (!inicializado) {
        srand((unsigned int)time(NULL));
        inicializado = 1;
    }

    // Gerar 16 digitos para numero de conta
    for (int i = 0; i < 16; i++) {
        numeroConta[i] = '0' + (rand() % 10);
    }
    numeroConta[16] = '\0';

    // IBAN: AO06 + 0040 (banco) + 0000 (balcao) + 11 primeiros digitos da conta + 2 digitos controlo
    char digitosControlo[3];
    digitosControlo[0] = '0' + (rand() % 10);
    digitosControlo[1] = '0' + (rand() % 10);
    digitosControlo[2] = '\0';

    sprintf(iban, "AO0600400000%.11s%s", numeroConta, digitosControlo);
}

int getNextContaAutoID() {
    FILE *fp;
    CONTA conta;
    int nextID = 1;

    fp = fopen("CONTA.DAT", "rb");
    if (fp == NULL) {
        return nextID;
    }

    rewind(fp);

    while (fread(&conta, sizeof(CONTA), 1, fp) == 1) {
        nextID++;
    }

    fclose(fp);

    return nextID;
}

void pedirDadosConta(CONTA *conta , int alterar, int oldId) {
    if (alterar == 0) {
        conta->id = getNextContaAutoID();
    } else {
        conta->id = oldId;
    }

    printf("Id do Cliente?\n");
    scanf("%d", &conta->idCliente);
    fflush(stdin);

    // Gerar numero de conta e IBAN automaticamente
    gerarContaEIban(conta->numeroConta, conta->iban);
    printf("Numero da Conta: %s\n", conta->numeroConta);
    printf("IBAN: %s\n", conta->iban);

    printf("Tipo de Conta (Poupanca/Corrente)?\n");
    gets(conta->tipo);
    fflush(stdin);

    printf("Saldo Inicial?\n");
    scanf("%f", &conta->saldo);
    fflush(stdin);

    printf("Data de Abertura [DD-MM-AAAA]?\n");
    scanf("%d%d%d", &conta->dataAbertura.dia,
          &conta->dataAbertura.mes, &conta->dataAbertura.ano);
    fflush(stdin);
}

void mostrarDadosConta(CONTA conta) {
    printf("\n ------------------------Dados da Conta----------------------------- \n");
    printf("Id: %d\n", conta.id);
    printf("Id Cliente: %d\n", conta.idCliente);
    printf("Numero da Conta: %s\n", conta.numeroConta);
    printf("IBAN: %s\n", conta.iban);
    printf("Tipo: %s\n", conta.tipo);
    printf("Saldo: %.2f Kz\n", conta.saldo);
    printf("Data de Abertura: [%d-%d-%d]\n",
           conta.dataAbertura.dia,
           conta.dataAbertura.mes,
           conta.dataAbertura.ano);
}

void salvarDadosConta() {
    FILE *fp;
    CONTA conta;
    memset(&conta, 0, sizeof(CONTA));

    if ((fp = fopen("CONTA.DAT", "ab")) == NULL) {
        puts("Erro ao tentar abrir o ficheiro!");
        return;
    }

    fseek(fp, 0L, SEEK_END);

    pedirDadosConta(&conta, 0, 0);

    if (fwrite(&conta, sizeof(CONTA), 1, fp) == 1) {
        system("cls");
        puts("Conta adicionada com sucesso no Ficheiro");
    }

    fclose(fp);
}

void listarDadosConta() {
    FILE *fp;
    CONTA conta;

    fp = fopen("CONTA.DAT", "rb");
    if (fp == NULL) {
        puts("Nenhuma conta encontrada!");
        system("pause");
        return;
    }

    fseek(fp, 0L, SEEK_SET);

    system("cls");

    puts("Listagem de Contas");

    while (fread(&conta, sizeof(CONTA), 1, fp) == 1) {
        puts("---------------------------------------");
        mostrarDadosConta(conta);
    }

    fclose(fp);

    system("pause");
    system("cls");
}

void pesquisarContaPorNumero() {
    FILE *fp;
    CONTA conta;
    char numeroProcurado[17];

    fp = fopen("CONTA.DAT", "rb");
    if (fp == NULL) {
        puts("Nenhuma conta encontrada!");
        system("pause");
        return;
    }

    rewind(fp);

    puts("Digite o Numero da Conta Procurada (16 digitos)");
    scanf("%16s", numeroProcurado);

    while (fread(&conta, sizeof(CONTA), 1, fp) == 1) {
        if (strcmp(conta.numeroConta, numeroProcurado) == 0) {
            system("cls");

            puts("Conta Localizada no Ficheiro\n");
            printf("-------------------------------------------\n");
            mostrarDadosConta(conta);
            printf("-------------------------------------------\n");

            fclose(fp);

            system("pause");
            system("cls");

            return;
        }
    }

    printf("Conta %d nao Encontrada!...\n", numeroProcurado);

    fclose(fp);
    system("pause");
}

void alterarDadosConta() {
    FILE *fp;
    CONTA conta;
    memset(&conta, 0, sizeof(CONTA));
    int idProcurado, posicao = 0;
    char opcao;

    if ((fp = fopen("CONTA.DAT", "a+b")) == NULL) {
        puts("Erro ao tentar abrir o ficheiro!");
        return;
    }

    rewind(fp);

    puts("Digite o Id da Conta que deseja alterar");
    scanf("%d", &idProcurado);

    while (fread(&conta, sizeof(CONTA), 1, fp) == 1) {
        posicao++;

        if (conta.id == idProcurado) {
            system("cls");

            puts("Conta Localizada");
            mostrarDadosConta(conta);

            printf("\nTem certeza que deseja alterar esta conta [S/N]?\n");
            scanf(" %c", &opcao);

            system("cls");

            if (opcao == 'S' || opcao == 's') {
                pedirDadosConta(&conta, 1, conta.id);

                rewind(fp);

                fseek(fp, (posicao - 1) * sizeof(CONTA), SEEK_SET);

                if (fwrite(&conta, sizeof(CONTA), 1, fp) == 1) {
                    system("cls");
                    puts("Conta Alterada com sucesso no Ficheiro");
                } else {
                    system("cls");
                    puts("Erro ao tentar alterar os dados do ficheiro");
                }
            }

            fclose(fp);
            return;
        }
    }

    printf("Conta com Id %d nao Encontrada!...\n", idProcurado);
    fclose(fp);
}


// ======================= FUNCOES MOVIMENTOS =======================

int getNextMovimentoAutoID() {
    FILE *fp;
    MOVIMENTO mov;
    int nextID = 1;

    fp = fopen("MOVIMENTO.DAT", "rb");
    if (fp == NULL) {
        return nextID;
    }

    rewind(fp);

    while (fread(&mov, sizeof(MOVIMENTO), 1, fp) == 1) {
        nextID++;
    }

    fclose(fp);

    return nextID;
}

// Procura uma conta pelo id e retorna 1 se encontrada, 0 caso contrario
int buscarContaPorId(int idConta, CONTA *contaEncontrada) {
    FILE *fp;
    CONTA conta;

    fp = fopen("CONTA.DAT", "rb");
    if (fp == NULL) {
        return 0;
    }

    rewind(fp);

    while (fread(&conta, sizeof(CONTA), 1, fp) == 1) {
        if (conta.id == idConta) {
            *contaEncontrada = conta;
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

// Actualiza o saldo de uma conta no ficheiro
int actualizarSaldoConta(int idConta, float novoSaldo) {
    FILE *fp;
    CONTA conta;
    int posicao = 0;

    if ((fp = fopen("CONTA.DAT", "r+b")) == NULL) {
        return 0;
    }

    rewind(fp);

    while (fread(&conta, sizeof(CONTA), 1, fp) == 1) {
        posicao++;
        if (conta.id == idConta) {
            conta.saldo = novoSaldo;
            fseek(fp, (posicao - 1) * sizeof(CONTA), SEEK_SET);
            fwrite(&conta, sizeof(CONTA), 1, fp);
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

// Salvar movimento no ficheiro
void salvarMovimento(MOVIMENTO mov) {
    FILE *fp;

    if ((fp = fopen("MOVIMENTO.DAT", "ab")) == NULL) {
        puts("Erro ao tentar abrir o ficheiro de movimentos!");
        return;
    }

    fseek(fp, 0L, SEEK_END);

    if (fwrite(&mov, sizeof(MOVIMENTO), 1, fp) == 1) {
        puts("Movimento registado com sucesso!");
    }

    fclose(fp);
}

void realizarLevantamento() {
    CONTA conta;
    MOVIMENTO mov;
    int idConta;
    float valor;
    char opcao;

    memset(&mov, 0, sizeof(MOVIMENTO));

    system("cls");
    puts("========== LEVANTAMENTO ==========");

    printf("Id da Conta?\n");
    scanf("%d", &idConta);
    fflush(stdin);

    // Verificar se a conta existe
    if (!buscarContaPorId(idConta, &conta)) {
        printf("Conta com Id %d nao encontrada!\n", idConta);
        system("pause");
        system("cls");
        return;
    }

    // Mostrar dados da conta
    mostrarDadosConta(conta);

    printf("\nValor a levantar?\n");
    scanf("%f", &valor);
    fflush(stdin);

    // Validar valor
    if (valor <= 0) {
        puts("Valor invalido! O valor deve ser maior que zero.");
        system("pause");
        system("cls");
        return;
    }

    // Verificar saldo suficiente
    if (valor > conta.saldo) {
        printf("Saldo insuficiente! Saldo disponivel: %.2f Kz\n", conta.saldo);
        system("pause");
        system("cls");
        return;
    }

    printf("\nConfirmar levantamento de %.2f Kz da conta %s? [S/N]\n", valor, conta.numeroConta);
    scanf(" %c", &opcao);

    if (opcao == 'S' || opcao == 's') {
        // Actualizar saldo
        float novoSaldo = conta.saldo - valor;

        if (actualizarSaldoConta(idConta, novoSaldo)) {
            // Registar movimento
            mov.id = getNextMovimentoAutoID();
            mov.contaId = idConta;
            mov.valor = valor;
            strcpy(mov.tipo, "Levantamento");

            printf("Data do Movimento [DD-MM-AAAA]?\n");
            scanf("%d%d%d", &mov.dataMovimento.dia,
                  &mov.dataMovimento.mes, &mov.dataMovimento.ano);
            fflush(stdin);

            salvarMovimento(mov);

            system("cls");
            puts("Levantamento realizado com sucesso!");
            printf("Valor levantado: %.2f Kz\n", valor);
            printf("Novo saldo: %.2f Kz\n", novoSaldo);
        } else {
            puts("Erro ao actualizar o saldo da conta!");
        }
    } else {
        puts("Levantamento cancelado.");
    }

    system("pause");
    system("cls");
}

void realizarDeposito() {
    CONTA conta;
    MOVIMENTO mov;
    int idConta;
    float valor;
    char opcao;

    memset(&mov, 0, sizeof(MOVIMENTO));

    system("cls");
    puts("========== DEPOSITO ==========");

    printf("Id da Conta?\n");
    scanf("%d", &idConta);
    fflush(stdin);

    // Verificar se a conta existe
    if (!buscarContaPorId(idConta, &conta)) {
        printf("Conta com Id %d nao encontrada!\n", idConta);
        system("pause");
        system("cls");
        return;
    }

    // Mostrar dados da conta
    mostrarDadosConta(conta);

    printf("\nValor a depositar?\n");
    scanf("%f", &valor);
    fflush(stdin);

    // Validar valor
    if (valor <= 0) {
        puts("Valor invalido! O valor deve ser maior que zero.");
        system("pause");
        system("cls");
        return;
    }

    printf("\nConfirmar deposito de %.2f Kz na conta %s? [S/N]\n", valor, conta.numeroConta);
    scanf(" %c", &opcao);

    if (opcao == 'S' || opcao == 's') {
        // Actualizar saldo
        float novoSaldo = conta.saldo + valor;

        if (actualizarSaldoConta(idConta, novoSaldo)) {
            // Registar movimento
            mov.id = getNextMovimentoAutoID();
            mov.contaId = idConta;
            mov.valor = valor;
            strcpy(mov.tipo, "Deposito");

            printf("Data do Movimento [DD-MM-AAAA]?\n");
            scanf("%d%d%d", &mov.dataMovimento.dia,
                  &mov.dataMovimento.mes, &mov.dataMovimento.ano);
            fflush(stdin);

            salvarMovimento(mov);

            system("cls");
            puts("Deposito realizado com sucesso!");
            printf("Valor depositado: %.2f Kz\n", valor);
            printf("Novo saldo: %.2f Kz\n", novoSaldo);
        } else {
            puts("Erro ao actualizar o saldo da conta!");
        }
    } else {
        puts("Deposito cancelado.");
    }

    system("pause");
    system("cls");
}
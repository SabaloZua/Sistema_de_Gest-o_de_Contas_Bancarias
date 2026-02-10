#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "Estrutras.h"

/*
 * Solicita e preenche os dados de um cliente via teclado.
 * Se alterar == 0, gera um novo ID automatico; caso contrario, mantem o ID antigo.
 * @param cliente  - Ponteiro para a estrutura CLIENTE a preencher
 * @param alterar  - Flag que indica se e uma alteracao (1) ou novo registo (0)
 * @param oldId    - ID antigo do cliente (usado apenas quando alterar == 1)
 */

  
void ActualizarDadosCliente(CLIENTE *cliente, int oldId)
{
 
        printf("Id = %d\n", oldId);
        cliente->id = oldId;
        fflush(stdin);
    



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
    scanf("%d-%d-%d", &cliente->dataNascimento.dia,
          &cliente->dataNascimento.mes, &cliente->dataNascimento.ano);

    fflush(stdin);
}


void pedirDadosCliente(CLIENTE *cliente, int oldId){ 

    
        printf("Id = %d\n", oldId);
        cliente->id = oldId;
        fflush(stdin);
    

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
    scanf("%d-%d-%d", &cliente->dataNascimento.dia,
          &cliente->dataNascimento.mes, &cliente->dataNascimento.ano);

    fflush(stdin);
}

/*
 * Exibe no ecra os dados pessoais e de contacto de um cliente.
 * @param cliente - Estrutura CLIENTE com os dados a exibir
 */
void mostrarDadosCliente(CLIENTE cliente)
{

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

/*
 * Cria um novo registo de cliente e grava-o no ficheiro CLIENTE.DAT.
 * Solicita os dados ao utilizador atraves de pedirDadosCliente().
 */
void salvarDadosCliente()
{
    FILE *fp;
    CLIENTE cliente;
    // memset: preenche um bloco de memoria com um valor; aqui preenche toda a estrutura com 0 (zeros)
    // Parametros: ponteiro destino, valor a preencher, numero de bytes
    memset(&cliente, 0, sizeof(CLIENTE));

    // fopen: abre um ficheiro; "ab" = append + binario (adiciona no final, cria se nao existir)
    // Retorna NULL se nao conseguir abrir
    if ((fp = fopen("CLIENTE.DAT", "ab")) == NULL)
    {
        // puts: escreve uma string no ecra seguida de uma nova linha (\n automatico)
        puts("Erro ao tentar abrir o ficheiro!");
        return;
    }

    // fseek: move o cursor de leitura/escrita dentro do ficheiro
    // Parametros: ponteiro do ficheiro, deslocamento em bytes, posicao de referencia
    // SEEK_SET = inicio, SEEK_CUR = posicao actual, SEEK_END = final do ficheiro
    fseek(fp, 0L, SEEK_END);

    // pedir dados ao utilizador
    pedirDadosCliente(&cliente, 0);

    if (!verificarMaiorIdade(cliente))
    {
        system("cls");
        puts("Conta NAO criada! O cliente e menor de idade (menos de 18 anos).");
        printf("Cliente: %s | Data de Nascimento: %d-%d-%d\n",
               cliente.nome,
               cliente.dataNascimento.dia,
               cliente.dataNascimento.mes,
               cliente.dataNascimento.ano);
        fclose(fp);
        system("pause");
        return;
    }
    // fwrite: escreve dados binarios num ficheiro
    // Parametros: ponteiro dos dados, tamanho de cada elemento, quantidade de elementos, ponteiro do ficheiro
    // Retorna o numero de elementos escritos com sucesso
    if (fwrite(&cliente, sizeof(CLIENTE), 1, fp) == 1)
    {
        system("cls");
        puts("Registo adicionado com sucesso no Ficheiro");
    }

    // fclose: fecha o ficheiro e liberta os recursos associados
    fclose(fp);
}

/*
 * Le e exibe todos os registos de clientes armazenados no ficheiro CLIENTE.DAT.
 */
void listarDadosCliente()
{
    FILE *fp;
    CLIENTE cliente;

    // abrir ou criar o ficheiro
    fp = fopen("CLIENTE.DAT", "rb");

    // movimentar o File Pointer
    fseek(fp, 0L, SEEK_SET);

    system("cls");

    puts("Listagem de Dados");

    // fread: le dados binarios de um ficheiro
    // Parametros: ponteiro destino, tamanho de cada elemento, quantidade de elementos, ponteiro do ficheiro
    // Retorna o numero de elementos lidos com sucesso
    while (fread(&cliente, sizeof(CLIENTE), 1, fp) == 1)
    {
        puts("---------------------------------------");
        mostrarDadosCliente(cliente);
    }

    fclose(fp);

    system("pause");
    system("cls");
}

/*
 * Pesquisa um cliente pelo nome no ficheiro CLIENTE.DAT.
 * Solicita o nome ao utilizador e exibe os dados se encontrado.
 */
void pesquisarClientePorNome()
{
    FILE *fp;
    CLIENTE cliente;
    char nomeProcurado[50];

    // abrir ou criar o ficheiro
    fp = fopen("CLIENTE.DAT", "rb");

    // rewind: reposiciona o cursor de leitura/escrita no inicio do ficheiro (equivalente a fseek(fp, 0, SEEK_SET))
    rewind(fp);

    puts("Digite o Nome Procurado");
    getchar();
    gets(nomeProcurado);

    while (fread(&cliente, sizeof(CLIENTE), 1, fp) == 1)
    {
        // strcmp: compara duas strings caractere a caractere
        // Retorna 0 se forem iguais, valor negativo se a 1a for menor, positivo se for maior
        if (strcmp(cliente.nome, nomeProcurado) == 0)
        {
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

    fclose(fp);
}

/*
 * Calcula o proximo ID automatico para clientes.
 * Conta o numero de registos no ficheiro CLIENTE.DAT e retorna o proximo valor.
 * @return Proximo ID disponivel (comeca em 1)
 */
int getNextClienteAutoID()
{
    FILE *fp;
    CLIENTE cliente;
    int nextID = 1;

    fp = fopen("CLIENTE.DAT", "rb");
    if (fp == NULL)
    {
        return nextID;
    }

    rewind(fp);

    while (fread(&cliente, sizeof(CLIENTE), 1, fp) == 1)
    {
        nextID++;
    }

    fclose(fp);

    return nextID;
}

/*
 * Permite alterar os dados de um cliente existente no ficheiro CLIENTE.DAT.
 * Solicita o ID do cliente, exibe os dados actuais e pede confirmacao antes de alterar.
 */
void alterarDadosCliente()
{
    FILE *fp;
    CLIENTE cliente;
    memset(&cliente, 0, sizeof(CLIENTE));
    int idProcurado, posicao = 0;
    char opcao;

    // abrir ou criar o ficheiro
    if ((fp = fopen("CLIENTE.DAT", "a+b")) == NULL)
    {
        puts("Erro ao tentar abrir o ficheiro!");
        return;
    }

    rewind(fp);

    puts("Digite o Id que deseja alterar");
    scanf("%d", &idProcurado);

    // escrever os dados da estrutura para o ficheiro
    while (fread(&cliente, sizeof(CLIENTE), 1, fp) == 1)
    {
        posicao++;

        if (cliente.id == idProcurado)
        {
            system("cls");

            puts("Registo Localizado");
            mostrarDadosCliente(cliente);

            printf("\nTem certeza q deseja alterar este registo [S/N]?\n");
            scanf(" %c", &opcao);

            system("cls");

            if (opcao == 'S' || opcao == 's')
            {
                ActualizarDadosCliente(&cliente,cliente.id);

                // rever apartir daqui
                rewind(fp);

                // colocar o curso no registo procurado
                fseek(fp, (posicao - 1) * sizeof(CLIENTE), SEEK_SET);

                if (!verificarMaiorIdade(cliente))
                {
                    system("cls");
                    puts("Conta NAO criada! O cliente e menor de idade (menos de 18 anos).");
                    printf("Cliente: %s | Data de Nascimento: %d-%d-%d\n",
                           cliente.nome,
                           cliente.dataNascimento.dia,
                           cliente.dataNascimento.mes,
                           cliente.dataNascimento.ano);
                    fclose(fp);
                    system("pause");
                    return;
                }
                // escrever os dados da estrutura para o ficheiro
                if (fwrite(&cliente, sizeof(CLIENTE), 1, fp) == 1)
                {
                    system("cls");
                    puts("Registo Alterado com sucesso no Ficheiro");
                }
                else
                {
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

/*
 * Procura um cliente pelo seu ID no ficheiro CLIENTE.DAT.
 * @param idCliente         - ID do cliente a procurar
 * @param clienteEncontrado - Ponteiro para a estrutura CLIENTE onde os dados serao copiados
 * @return 1 se o cliente foi encontrado, 0 caso contrario
 */
int buscarClientePorId(int idCliente, CLIENTE *clienteEncontrado)
{
    FILE *fp;
    CLIENTE cliente;

    fp = fopen("CLIENTE.DAT", "rb");
    if (fp == NULL)
    {
        return 0;
    }

    rewind(fp);

    while (fread(&cliente, sizeof(CLIENTE), 1, fp) == 1)
    {
        if (cliente.id == idCliente)
        {
            *clienteEncontrado = cliente;
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

/*
 * Verifica se um cliente e maior de idade (18 anos ou mais).
 * Compara a data de nascimento do cliente com a data actual do sistema.
 * @param cliente - Estrutura CLIENTE com a data de nascimento a verificar
 * @return 1 se o cliente tem 18 anos ou mais, 0 caso contrario
 */
int verificarMaiorIdade(CLIENTE cliente)
{
    // Obter o ano actual do sistema
    time_t agora = time(NULL);
    struct tm *hoje = localtime(&agora);
    int anoActual = hoje->tm_year + 1900;

    // Calcular a idade e verificar se tem 18 ou mais
    return (anoActual - cliente.dataNascimento.ano) >= 18;
}

/*
 * Gera um numero de conta aleatorio de 16 digitos e o respectivo IBAN angolano.
 * O IBAN segue o formato: AO06 + codigo banco (0040) + balcao (0000) + 11 digitos da conta + 2 digitos controlo.
 * @param numeroConta - Buffer para armazenar o numero de conta gerado (minimo 17 caracteres)
 * @param iban        - Buffer para armazenar o IBAN gerado (minimo 26 caracteres)
 */
void gerarContaEIban(char *numeroConta, char *iban)
{
    static int inicializado = 0;
    if (!inicializado)
    {
        // srand: inicializa o gerador de numeros aleatorios com uma semente
        // time(NULL) retorna o tempo actual em segundos, garantindo uma semente diferente a cada execucao
        srand((unsigned int)time(NULL));
        inicializado = 1;
    }

    // Gerar 16 digitos para numero de conta
    for (int i = 0; i < 16; i++)
    {
        // rand: gera um numero inteiro pseudo-aleatorio; % 10 limita o resultado entre 0 e 9
        numeroConta[i] = '0' + (rand() % 10);
    }
    numeroConta[16] = '\0';

    // IBAN: AO06 + 0040 (banco) + 0000 (balcao) + 11 primeiros digitos da conta + 2 digitos controlo
    char digitosControlo[3];
    digitosControlo[0] = '0' + (rand() % 10);
    digitosControlo[1] = '0' + (rand() % 10);
    digitosControlo[2] = '\0';

    // sprintf: escreve uma string formatada num buffer (similar ao printf, mas guarda numa variavel)
    // Parametros: buffer destino, formato, valores a formatar
    sprintf(iban, "AO0600400000%.11s%s", numeroConta, digitosControlo);
}

/*
 * Calcula o proximo ID automatico para contas bancarias.
 * Conta o numero de registos no ficheiro CONTA.DAT e retorna o proximo valor.
 * @return Proximo ID disponivel (comeca em 1)
 */
int getNextContaAutoID()
{
    FILE *fp;
    CONTA conta;
    int nextID = 1;

    fp = fopen("CONTA.DAT", "rb");
    if (fp == NULL)
    {
        return nextID;
    }

    rewind(fp);

    while (fread(&conta, sizeof(CONTA), 1, fp) == 1)
    {
        nextID++;
    }

    fclose(fp);

    return nextID;
}

/*
 * Solicita e preenche os dados de uma conta bancaria via teclado.
 * Gera automaticamente o numero de conta e IBAN.
 * Se alterar == 0, gera um novo ID automatico; caso contrario, mantem o ID antigo.
 * @param conta   - Ponteiro para a estrutura CONTA a preencher
 * @param alterar - Flag que indica se e uma alteracao (1) ou novo registo (0)
 * @param oldId   - ID antigo da conta (usado apenas quando alterar == 1)
 */
void pedirDadosConta(CONTA *conta, int alterar, int oldId)
{
    if (alterar == 0)
    {
        conta->id = getNextContaAutoID();
    }
    else
    {
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

    printf("Data de Abertura [DD-MM-AAAA]?\n");
    scanf("%d-%d-%d", &conta->dataAbertura.dia,
          &conta->dataAbertura.mes, &conta->dataAbertura.ano);
    fflush(stdin);
}

/*
 * Exibe no ecra os dados de uma conta bancaria (ID, cliente, numero, IBAN, tipo, saldo e data).
 * @param conta - Estrutura CONTA com os dados a exibir
 */
void mostrarDadosConta(CONTA conta)
{
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

/*
 * Cria uma nova conta bancaria e grava-a no ficheiro CONTA.DAT.
 * Solicita os dados ao utilizador atraves de pedirDadosConta().
 */
void salvarDadosConta()
{
    FILE *fp;
    CONTA conta;
    CLIENTE cliente;
    memset(&conta, 0, sizeof(CONTA));

    if ((fp = fopen("CONTA.DAT", "ab")) == NULL)
    {
        puts("Erro ao tentar abrir o ficheiro!");
        return;
    }

    fseek(fp, 0L, SEEK_END);

    pedirDadosConta(&conta, 0, 0);

    // Verificar se o cliente existe e se e maior de idade
    if (!buscarClientePorId(conta.idCliente, &cliente))
    {
        printf("Cliente com Id %d nao encontrado!\n", conta.idCliente);
        fclose(fp);
        system("pause");
        return;
    }

    if (fwrite(&conta, sizeof(CONTA), 1, fp) == 1)
    {
        system("cls");
        puts("Conta adicionada com sucesso no Ficheiro");
    }

    fclose(fp);
}

/*
 * Le e exibe todas as contas bancarias armazenadas no ficheiro CONTA.DAT.
 */
void listarDadosConta()
{
    FILE *fp;
    CONTA conta;

    fp = fopen("CONTA.DAT", "rb");
    if (fp == NULL)
    {
        puts("Nenhuma conta encontrada!");
        system("pause");
        return;
    }

    fseek(fp, 0L, SEEK_SET);

    system("cls");

    puts("Listagem de Contas");

    while (fread(&conta, sizeof(CONTA), 1, fp) == 1)
    {
        puts("---------------------------------------");
        mostrarDadosConta(conta);
    }

    fclose(fp);

    system("pause");
    system("cls");
}

/*
 * Pesquisa uma conta bancaria pelo numero de conta (16 digitos) no ficheiro CONTA.DAT.
 * Solicita o numero ao utilizador e exibe os dados se encontrada.
 */
void pesquisarContaPorNumero()
{
    FILE *fp;
    CONTA conta;
    char numeroProcurado[17];

    fp = fopen("CONTA.DAT", "rb");
    if (fp == NULL)
    {
        puts("Nenhuma conta encontrada!");
        system("pause");
        return;
    }

    rewind(fp);

    puts("Digite o Numero da Conta Procurada (16 digitos)");
    scanf("%16s", numeroProcurado);

    while (fread(&conta, sizeof(CONTA), 1, fp) == 1)
    {
        if (strcmp(conta.numeroConta, numeroProcurado) == 0)
        {
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

/*
 * Permite alterar os dados de uma conta existente no ficheiro CONTA.DAT.
 * Solicita o ID da conta, exibe os dados actuais e pede confirmacao antes de alterar.
 */
void alterarDadosConta()
{
    FILE *fp;
    CONTA conta;
    memset(&conta, 0, sizeof(CONTA));
    int idProcurado, posicao = 0;
    char opcao;

    if ((fp = fopen("CONTA.DAT", "a+b")) == NULL)
    {
        puts("Erro ao tentar abrir o ficheiro!");
        return;
    }

    rewind(fp);

    puts("Digite o Id da Conta que deseja alterar");
    scanf("%d", &idProcurado);

    while (fread(&conta, sizeof(CONTA), 1, fp) == 1)
    {
        posicao++;

        if (conta.id == idProcurado)
        {
            system("cls");

            puts("Conta Localizada");
            mostrarDadosConta(conta);

            printf("\nTem certeza que deseja alterar esta conta [S/N]?\n");
            scanf(" %c", &opcao);

            system("cls");

            if (opcao == 'S' || opcao == 's')
            {
                pedirDadosConta(&conta, 1, conta.id);

                rewind(fp);

                fseek(fp, (posicao - 1) * sizeof(CONTA), SEEK_SET);

                if (fwrite(&conta, sizeof(CONTA), 1, fp) == 1)
                {
                    system("cls");
                    puts("Conta Alterada com sucesso no Ficheiro");
                }
                else
                {
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

/*
 * Calcula o proximo ID automatico para movimentos.
 * Conta o numero de registos no ficheiro MOVIMENTO.DAT e retorna o proximo valor.
 * @return Proximo ID disponivel (comeca em 1)
 */
int getNextMovimentoAutoID()
{
    FILE *fp;
    MOVIMENTO mov;
    int nextID = 1;

    fp = fopen("MOVIMENTO.DAT", "rb");
    if (fp == NULL)
    {
        return nextID;
    }

    rewind(fp);

    while (fread(&mov, sizeof(MOVIMENTO), 1, fp) == 1)
    {
        nextID++;
    }

    fclose(fp);

    return nextID;
}

/*
 * Procura uma conta bancaria pelo seu ID no ficheiro CONTA.DAT.
 * @param idConta          - ID da conta a procurar
 * @param contaEncontrada  - Ponteiro para a estrutura CONTA onde os dados serao copiados
 * @return 1 se a conta foi encontrada, 0 caso contrario
 */
int buscarContaPorNumero(int numeroConta, CONTA *contaEncontrada)
{
    FILE *fp;
    CONTA conta;

    fp = fopen("CONTA.DAT", "rb");
    if (fp == NULL)
    {
        return 0;
    }

    rewind(fp);

    while (fread(&conta, sizeof(CONTA), 1, fp) == 1)
    {
        if (conta.numeroConta == numeroConta)
        {
            *contaEncontrada = conta;
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

/*
 * Actualiza o saldo de uma conta bancaria no ficheiro CONTA.DAT.
 * Procura a conta pelo ID e substitui o valor do saldo.
 * @param numeroConta   - ID da conta a actualizar
 * @param novoSaldo - Novo valor do saldo a gravar
 * @return 1 se actualizado com sucesso, 0 caso contrario
 */
int actualizarSaldoConta(int numeroConta, float novoSaldo)
{
    FILE *fp;
    CONTA conta;
    int posicao = 0;

    if ((fp = fopen("CONTA.DAT", "r+b")) == NULL)
    {
        return 0;
    }

    rewind(fp);

    while (fread(&conta, sizeof(CONTA), 1, fp) == 1)
    {
        posicao++;
        if (conta.numeroConta == numeroConta)
        {
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

/*
 * Grava um registo de movimento no ficheiro MOVIMENTO.DAT.
 * @param mov - Estrutura MOVIMENTO com os dados do movimento a gravar
 */
void salvarMovimento(MOVIMENTO mov)
{
    FILE *fp;

    if ((fp = fopen("MOVIMENTO.DAT", "ab")) == NULL)
    {
        puts("Erro ao tentar abrir o ficheiro de movimentos!");
        return;
    }

    fseek(fp, 0L, SEEK_END);

    if (fwrite(&mov, sizeof(MOVIMENTO), 1, fp) == 1)
    {
        puts("Movimento registado com sucesso!");
    }

    fclose(fp);
}

/*
 * Realiza um levantamento (retirada de dinheiro) de uma conta bancaria.
 * Solicita o ID da conta e o valor, valida o saldo disponivel,
 * actualiza o saldo e regista o movimento no ficheiro MOVIMENTO.DAT.
 */
void realizarLevantamento()
{
    CONTA conta;
    MOVIMENTO mov;
    int numeroConta;
    float valor;
    char opcao;

    memset(&mov, 0, sizeof(MOVIMENTO));

    system("cls");
    puts("========== LEVANTAMENTO ==========");

    printf("Numero da Conta?\n");
    scanf("%d", &numeroConta);
    fflush(stdin);

    // Verificar se a conta existe
    if (!buscarContaPorNumero(numeroConta, &conta))
    {
        printf("Conta com numero %d nao encontrada!\n", numeroConta);
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
    if (valor <= 0)
    {
        puts("Valor invalido! O valor deve ser maior que zero.");
        system("pause");
        system("cls");
        return;
    }

    // Verificar saldo suficiente
    if (valor > conta.saldo)
    {
        printf("Saldo insuficiente! Saldo disponivel: %.2f Kz\n", conta.saldo);
        system("pause");
        system("cls");
        return;
    }

    printf("\nConfirmar levantamento de %.2f Kz da conta %s? [S/N]\n", valor, conta.numeroConta);
    scanf(" %c", &opcao);

    if (opcao == 'S' || opcao == 's')
    {
        // Actualizar saldo
        float novoSaldo = conta.saldo - valor;

        if (actualizarSaldoConta(numeroConta, novoSaldo))
        {
            // Registar movimento
            mov.id = getNextMovimentoAutoID();
            mov.numeroConta = numeroConta;
            mov.valor = valor;
            // strcpy: copia uma string de origem para o destino, incluindo o '\0' final
            // Parametros: ponteiro destino, ponteiro origem
            strcpy(mov.tipo, "Levantamento");

            printf("Data do Movimento [DD-MM-AAAA]?\n");
            scanf("%d-%d-%d", &mov.dataMovimento.dia,
                  &mov.dataMovimento.mes, &mov.dataMovimento.ano);
            fflush(stdin);

            salvarMovimento(mov);

            system("cls");
            puts("Levantamento realizado com sucesso!");
            printf("Valor levantado: %.2f Kz\n", valor);
            printf("Novo saldo: %.2f Kz\n", novoSaldo);
        }
        else
        {
            puts("Erro ao actualizar o saldo da conta!");
        }
    }
    else
    {
        puts("Levantamento cancelado.");
    }

    system("pause");
    system("cls");
}

/*
 * Realiza um deposito (adicao de dinheiro) numa conta bancaria.
 * Solicita o ID da conta e o valor, actualiza o saldo
 * e regista o movimento no ficheiro MOVIMENTO.DAT.
 */
void realizarDeposito()
{
    MOVIMENTO mov;
    int numeroConta;
    float valor;
    char opcao;
    CONTA conta;

    memset(&mov, 0, sizeof(MOVIMENTO));

    system("cls");
    puts("========== DEPOSITO ==========");

    printf("Numero da Conta?\n");
    scanf("%d", &numeroConta);
    fflush(stdin);

    // Verificar se a conta existe
    if (!buscarContaPorNumero(numeroConta, &conta))
    {
        printf("Conta com Id %d nao encontrada!\n", numeroConta);
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
    if (valor <= 0)
    {
        puts("Valor invalido! O valor deve ser maior que zero.");
        system("pause");
        system("cls");
        return;
    }

    printf("\nConfirmar deposito de %.2f Kz na conta %s? [S/N]\n", valor, conta.numeroConta);
    scanf(" %c", &opcao);

    if (opcao == 'S' || opcao == 's')
    {
        // Actualizar saldo
        float novoSaldo = conta.saldo + valor;

        if (actualizarSaldoConta(numeroConta, novoSaldo))
        {
            // Registar movimento
            mov.id = getNextMovimentoAutoID();
            mov.numeroConta = numeroConta;
            mov.valor = valor;
            strcpy(mov.tipo, "Deposito");

            printf("Data do Movimento [DD-MM-AAAA]?\n");
            scanf("%d-%d-%d", &mov.dataMovimento.dia,
                  &mov.dataMovimento.mes, &mov.dataMovimento.ano);
            fflush(stdin);

            salvarMovimento(mov);

            system("cls");
            puts("Deposito realizado com sucesso!");
            printf("Valor depositado: %.2f Kz\n", valor);
            printf("Novo saldo: %.2f Kz\n", novoSaldo);
        }
        else
        {
            puts("Erro ao actualizar o saldo da conta!");
        }
    }
    else
    {
        puts("Deposito cancelado.");
    }

    system("pause");
    system("cls");
}

/*
 * Le e exibe todos os movimentos armazenados no ficheiro MOVIMENTO.DAT.
 */
void listarDadosMovimentos()
{
    FILE *fp;
    CONTA conta;

    MOVIMENTO movimento;

    fp = fopen("MOVIMENTO.DAT", "rb");
    if (fp == NULL)
    {
        puts("Nenhuma movimento encontrado!");
        system("pause");
        return;
    }

    fseek(fp, 0L, SEEK_SET);

    system("cls");

    puts("Listagem de Movimentos");

    while (fread(&movimento, sizeof(MOVIMENTO), 1, fp) == 1)
    {
        puts("---------------------------------------");
        mostrarDadosMovimento(movimento);
    }

    fclose(fp);

    system("pause");
    system("cls");
}

/*
 * Elimina uma conta bancaria do ficheiro CONTA.DAT.
 * Solicita o ID da conta, exibe os dados e pede confirmacao antes de eliminar.
 * Copia todos os registos excepto o eliminado para um ficheiro temporario.
 */
void eliminarConta()
{
    FILE *fp, *fpTemp;
    CONTA conta;
    int idProcurado;
    char opcao;
    int encontrado = 0;

    if ((fp = fopen("CONTA.DAT", "rb")) == NULL)
    {
        puts("Nenhuma conta encontrada!");
        system("pause");
        return;
    }

    system("cls");
    puts("========== ELIMINAR CONTA ==========");

    printf("Digite o Id da Conta que deseja eliminar:\n");
    scanf("%d", &idProcurado);
    fflush(stdin);

    // Procurar a conta para mostrar ao utilizador
    rewind(fp);
    while (fread(&conta, sizeof(CONTA), 1, fp) == 1)
    {
        if (conta.id == idProcurado)
        {
            encontrado = 1;
            system("cls");
            puts("Conta Localizada:");
            mostrarDadosConta(conta);
            break;
        }
    }

    if (!encontrado)
    {
        printf("Conta com Id %d nao encontrada!\n", idProcurado);
        fclose(fp);
        system("pause");
        return;
    }

    printf("\nTem certeza que deseja ELIMINAR esta conta? [S/N]\n");
    scanf(" %c", &opcao);

    if (opcao != 'S' && opcao != 's')
    {
        puts("Operacao cancelada.");
        fclose(fp);
        system("pause");
        system("cls");
        return;
    }

    // Abrir ficheiro temporario para copiar os registos que nao serao eliminados
    if ((fpTemp = fopen("CONTA_TEMP.DAT", "wb")) == NULL)
    {
        puts("Erro ao criar ficheiro temporario!");
        fclose(fp);
        system("pause");
        return;
    }

    // Copiar todos os registos excepto o eliminado
    rewind(fp);
    while (fread(&conta, sizeof(CONTA), 1, fp) == 1)
    {
        if (conta.id != idProcurado)
        {
            fwrite(&conta, sizeof(CONTA), 1, fpTemp);
        }
    }

    fclose(fp);
    fclose(fpTemp);

    // Substituir o ficheiro original pelo temporario
    remove("CONTA.DAT");
    rename("CONTA_TEMP.DAT", "CONTA.DAT");

    system("cls");
    puts("Conta eliminada com sucesso!");
    system("pause");
    system("cls");
}

/*
 * Elimina um cliente do ficheiro CLIENTE.DAT.
 * Solicita o ID do cliente, exibe os dados e pede confirmacao antes de eliminar.
 * Verifica se o cliente tem contas associadas antes de permitir a eliminacao.
 * Copia todos os registos excepto o eliminado para um ficheiro temporario.
 */
void eliminarCliente()
{
    FILE *fp, *fpTemp;
    CLIENTE cliente;
    CONTA conta;
    int idProcurado;
    char opcao;
    int encontrado = 0;

    if ((fp = fopen("CLIENTE.DAT", "rb")) == NULL)
    {
        puts("Nenhum cliente encontrado!");
        system("pause");
        return;
    }

    system("cls");
    puts("========== ELIMINAR CLIENTE ==========");

    printf("Digite o Id do Cliente que deseja eliminar:\n");
    scanf("%d", &idProcurado);
    fflush(stdin);

    // Procurar o cliente para mostrar ao utilizador
    rewind(fp);
    while (fread(&cliente, sizeof(CLIENTE), 1, fp) == 1)
    {
        if (cliente.id == idProcurado)
        {
            encontrado = 1;
            system("cls");
            puts("Cliente Localizado:");
            mostrarDadosCliente(cliente);
            break;
        }
    }

    if (!encontrado)
    {
        printf("Cliente com Id %d nao encontrado!\n", idProcurado);
        fclose(fp);
        system("pause");
        return;
    }

    // Verificar se o cliente tem contas associadas
    FILE *fpConta = fopen("CONTA.DAT", "rb");
    if (fpConta != NULL)
    {
        while (fread(&conta, sizeof(CONTA), 1, fpConta) == 1)
        {
            if (conta.idCliente == idProcurado)
            {
                puts("\nNao e possivel eliminar este cliente!");
                puts("O cliente possui contas bancarias associadas.");
                puts("Elimine as contas primeiro.");
                fclose(fpConta);
                fclose(fp);
                system("pause");
                system("cls");
                return;
            }
        }
        fclose(fpConta);
    }

    printf("\nTem certeza que deseja ELIMINAR este cliente? [S/N]\n");
    scanf(" %c", &opcao);

    if (opcao != 'S' && opcao != 's')
    {
        puts("Operacao cancelada.");
        fclose(fp);
        system("pause");
        system("cls");
        return;
    }

    // Abrir ficheiro temporario para copiar os registos que nao serao eliminados
    if ((fpTemp = fopen("CLIENTE_TEMP.DAT", "wb")) == NULL)
    {
        puts("Erro ao criar ficheiro temporario!");
        fclose(fp);
        system("pause");
        return;
    }

    // Copiar todos os registos excepto o eliminado
    rewind(fp);
    while (fread(&cliente, sizeof(CLIENTE), 1, fp) == 1)
    {
        if (cliente.id != idProcurado)
        {
            fwrite(&cliente, sizeof(CLIENTE), 1, fpTemp);
        }
    }

    fclose(fp);
    fclose(fpTemp);

    // Substituir o ficheiro original pelo temporario
    remove("CLIENTE.DAT");
    rename("CLIENTE_TEMP.DAT", "CLIENTE.DAT");

    system("cls");
    puts("Cliente eliminado com sucesso!");
    system("pause");
    system("cls");
}

/*
 * Exibe no ecra os dados de um movimento (ID, conta, tipo, data e valor).
 * @param movimento - Estrutura MOVIMENTO com os dados a exibir
 */
void mostrarDadosMovimento(MOVIMENTO movimento)
{
    printf("\n ------------------------Dados da Movimento----------------------------- \n");
    printf("Id: %d\n", movimento.id);
    printf("Numero Conta: %d\n", movimento.numeroConta);
    printf("Numero da Conta: %s\n", movimento.tipo);
    printf("Data de Movimento: [%d-%d-%d]\n",
           movimento.dataMovimento.dia,
           movimento.dataMovimento.mes,
           movimento.dataMovimento.ano);
    printf("Valor: %f\n", movimento.valor);
}

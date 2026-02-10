#include "estruturas.h"


// ======================= FUNCOES ClIENTE =======================
void pedirDadosCliente(CLIENTE *cliente);       // Solicita e preenche os dados de um cliente
void salvarDadosCliente();                      // Cria um novo cliente e grava no ficheiro CLIENTE.DAT
void mostrarDadosCliente(CLIENTE cliente);       // Exibe os dados pessoais e de contacto de um cliente
void listarDadosCliente();                       // Le e exibe todos os clientes do ficheiro CLIENTE.DAT
void pesquisarClientePorNome();                  // Pesquisa um cliente pelo nome no ficheiro
int getNextClienteAutoID();                      // Calcula o proximo ID automatico para clientes
void alterarDadosCliente();                      // Permite alterar os dados de um cliente existente
int buscarClientePorId(int idCliente, CLIENTE *clienteEncontrado); // Procura um cliente pelo ID no ficheiro
int verificarMaiorIdade(CLIENTE cliente);         // Verifica se o cliente tem 18 anos ou mais
void eliminarCliente();                          // Elimina um cliente do ficheiro CLIENTE.DAT



// ======================= FUNCOES CONTA =======================
int getNextContaAutoID();                        // Calcula o proximo ID automatico para contas
void pedirDadosConta(CLIENTE *cliente);           // Solicita e preenche os dados de uma conta bancaria
void mostrarDadosConta(CLIENTE cliente);           // Exibe os dados de uma conta bancaria
void salvarDadosConta();                          // Cria uma nova conta e grava no ficheiro CONTA.DAT
void listarDadosConta();                          // Le e exibe todas as contas do ficheiro CONTA.DAT
void pesquisarContaPorNumero();                   // Pesquisa uma conta pelo numero no ficheiro
void alterarDadosConta ();                        // Permite alterar os dados de uma conta existente
void eliminarConta();                            // Elimina uma conta do ficheiro CONTA.DAT


// ======================= FUNCOES MOVIMENTOS =======================
int getNextMovimentoAutoID();                     // Calcula o proximo ID automatico para movimentos
int  pesquisarContaPorNumero(int numeroConta, CONTA *contaEncontrada); // Procura uma conta pelo ID no ficheiro
int actualizarSaldoConta(int numeroConta, float novoSaldo);     // Actualiza o saldo de uma conta no ficheiro
void salvarMovimento(MOVIMENTO mov);              // Grava um movimento no ficheiro MOVIMENTO.DAT
void realizarLevantamento();                      // Executa um levantamento (retirada de dinheiro)
void  mostrarDadosMovimento(MOVIMENTO movimento); // Exibe os dados de um movimento
void listarDadosMovimentos();                     // Le e exibe todos os movimentos do ficheiro

// ======================= FUNCOES Deposito =======================
void realizarDeposito();                          // Executa um deposito (adicao de dinheiro)

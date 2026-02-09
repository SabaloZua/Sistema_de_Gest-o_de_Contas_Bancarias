#include "estruturas.h"


// ======================= FUNCOES ClIENTE =======================
void pedirDadosCliente(CLIENTE *cliente);
void salvarDadosCliente();
void mostrarDadosCliente(CLIENTE cliente);
void listarDadosCliente();
void pesquisarClientePorNome();
int getNextClienteAutoID();
void alterarDadosCliente();



// ======================= FUNCOES CONTA =======================
int getNextContaAutoID();
void pedirDadosConta(CLIENTE *cliente);
void mostrarDadosConta(CLIENTE cliente);
void salvarDadosConta();
void listarDadosConta();
void pesquisarContaPorNumero();
void alterarDadosConta ();


// ======================= FUNCOES MOVIMENTOS =======================
int getNextMovimentoAutoID();
int  buscarContaPorId(int idConta, CONTA *contaEncontrada);
int actualizarSaldoConta(int idConta, float novoSaldo);
void salvarMovimento(MOVIMENTO mov);
void realizarLevantamento();


// ======================= FUNCOES Deposito =======================
void 
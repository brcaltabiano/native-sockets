#include "server_socket.h"

/**
 * O construtor da classe responsável pelo
 * socket lado servidor realiza o passo a passo
 * necessário para construir um servidor de sockets e 
 * torná-lo disponível para eventuais trocas de mensagens
 * junto a clientes.
 * Todos os métodos de construção fazem checagem de erro,
 * informando no console uma mensagem sobre o ocorrido
 * e abortando a construção caso algo haja alguma
 * falha.
 **/
ServerSocket::ServerSocket() {
  this->server_fd = doAttach();
  this->address.sin_family = AF_INET;
  this->address.sin_port = htons(DEFAULT_PORT);
  this->address.sin_addr.s_addr = INADDR_ANY;
  doBind();
  doListen();
}

/** Primeiro passo: construção do socket
 * */
int ServerSocket::doAttach() {
  int result = socket(AF_INET, SOCK_STREAM, 0);
  if (result == 0) {
    cout << "socket attachment failed" << endl;
    exit(EXIT_FAILURE);
  }
  return result;
}

/** Segundo passo: associação do socket construído
 * a um endereço e uma porta.
 * */
int ServerSocket::doBind() {
  int result = bind(this->server_fd, (struct sockaddr *) &this->address, sizeof(struct sockaddr));
  if (result < 0) {
    cout << "socket bind failed" << endl;
    exit(EXIT_FAILURE);
  }
}

/** Terceiro passo: colocar o socket em modo
 * escuta para que clientes possam atingi-lo.
 **/
int ServerSocket::doListen() {
  int result = listen(this->server_fd, 3);
  if (result < 0) {
    cout << "socket listen failed" << endl;
    exit(EXIT_FAILURE);
  }
}

/**
 * Método responsável por aguardar a conexão
 * com um socket cliente, adicionando-o à lista
 * de clientes do servidor em caso de sucesso, 
 * ou informando uma mensagem de erro caso contrário. */
int ServerSocket::doAccept() {
  cout << "[Server] accepting socket..." << endl;
  int addrlen = sizeof(this->address);
  int result = accept(this->server_fd, (struct sockaddr *) &this->address, (socklen_t*) &addrlen);
  if (result < 0) {
    cout << "socket accept failed" << endl;
  } else {
    /* Adicionando o resultado do socket
    à lista de clientes conectados no servidor
    para realizar futuras referências. */
    this->clients.push_front(result);
    cout << "[Server] accepted socket!" << endl; 
  }
  return result;
}


/**
 * Método público responsável por enviar uma
 * dada mensagem ao(s) socket(s) cliente(s)
 * cuja conexão já foi estabelecida previamente. */
void ServerSocket::sendMessage(string message) {
  char const *m = message.c_str();
  list<int> :: iterator it;
  for (it = this->clients.begin(); it != this->clients.end(); it++) {
    send(*it, m, strlen(m), 0);
  }
  cout << "Broadcast message: " << message << endl;
}
#include "client_socket.h"

/**
 * O construtor da classe responsável pelo
 * socket lado client realiza o passo a passo
 * necessário para construir um socket client e 
 * tornar possível a sua conexão com o servidor,
 * que já deve estar inicializado.
 * Todos os métodos de construção fazem checagem de erro,
 * informando no console uma mensagem sobre o ocorrido
 * e abortando a construção caso algo haja alguma
 * falha.
 **/
ClientSocket::ClientSocket(int id) {
  this->id = id;
  this->server_fd = doAttach();
  this->serv_addr.sin_family = AF_INET;
	this->serv_addr.sin_port = htons(PORT);
  doConnect();
}

/** Método responsável por anexar o socket client
 * ao servidor já inicializado e em execução. */
int ClientSocket::doAttach() {
  int result = socket(AF_INET, SOCK_STREAM, 0);
  if (result < 0) {
    cout << "Socket creation error" << endl;
		return -1;
  }
  return result;
}

/* Com a anexação ao servidor concluída, este método
tenta realizar uma conexão para futuras comunicações. */
int ClientSocket::doConnect() {
  int result = connect(this->server_fd, (struct sockaddr *) &this->serv_addr, sizeof(this->serv_addr));
  if (result < 0) {
    cout << "\nConnection Failed" << endl;
  }
  return result;
}

/** Método responsável por fazer a leitura do tópico
 * (mesagem) sendo publicada pelo servidor de maneira
 * cíclica (via broadcast). */
void ClientSocket::readMessage() {
  char buffer[1024] = {0};
  read(this->server_fd, buffer, 1024);
  cout << "Client " << this->id << " read: " << buffer << endl;
}
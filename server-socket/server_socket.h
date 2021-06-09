#ifndef SERVER_SOCKET_H_
#define SERVER_SOCKET_H_

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>
#include <iostream>
#include <arpa/inet.h>
#include <netdb.h>
#include <list>
#include <iterator>

using namespace std;

#define DEFAULT_PORT 8080

class ServerSocket {
  /**
   * Como privados, encontram-se atributos e métodos
   * inerentes à arquitetura, construção e manutenção
   * de Sockets lado servidor.
   **/
  private:
    // Atributos de definição do server socket
    int server_fd;
    struct sockaddr_in address;

    /* Lista de clientes conectados - a cada conexão
    bem sucedida através do método "doAccept", o valor
    inteiro de referência do cliente é guardado aqui
    para que o servidor possa fazer broadcast para todos
    eles posteriormente. */
    list<int> clients;

    // Métodos de construção do server
    int doAttach();
    int doBind();
    int doListen();

  /**
   * Deixamos aqui acessíveis à aplicações que queiram
   * se utilizar da nossa construção de sockets
   * os métodos necessários para se estabelecer
   * um servidor que possa receber conexões de clientes,
   * ouvindo e/ou recebendo mensagens.
   **/
  public:
    ServerSocket();
    int doAccept();
    void sendMessage(string);
};

#endif
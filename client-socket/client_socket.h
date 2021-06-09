#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

using namespace std;

#define PORT 8080

class ClientSocket {
  /** Métodos e atributos inerentes à construção/
   * manutenção de client sockets. Apenas a própria
   * implementação da classe deve utilizá-los.
   **/
  private:
    int id;
    int server_fd;
    struct sockaddr_in serv_addr;
    int doAttach();
    int doConnect();
  
  /** Métodos públicos para que aplicações possam
   * utilizar nossa construção de client socket
   * e realizar comunicações conforme necessidade. */
  public:
    ClientSocket(int id);
    void readMessage();
};

#endif
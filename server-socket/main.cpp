#include "server_socket.h"
#include <chrono>
#include <thread>

/**
 * As "tasks" cíclicas (descritas a seguir) serão
 * executadas em threads e precisam
 * fazer referência ao único server socket criado. Assim,
 * criamos uma struct para realizar a passagem de parâmetros
 * para as threads. */
struct threadArgs {
    ServerSocket *socket;
};

/**
 * Função cíclica que mantém aberto
 * um "socket accept" para que um eventual
 * cliente possa chegar e se conectar com o
 * servidor. Quando uma conexão é bem sucedida,
 * o cliente é contabilizado pelo servidor,
 * e o ciclo se inicia novamente para receber
 * clientes futuros.
 **/
void *clientListener(void * voidArgs) {
    threadArgs *args = (threadArgs *) voidArgs;
    int socket;
    while (1) {
        args->socket->doAccept();
    }
}

/**
 * Função cíclica que simula um mecanismo de publicação
 * de mensagens em um tópico a ser lido por clientes.
 * O servidor faz, dado um intervalo de tempo, um broadcast 
 * de uma certa mensagem para todos os clientes conectados até então.
 **/
void *broadcaster(void * voidArgs) {
    threadArgs *args = (threadArgs *) voidArgs;
    int counter = 0;
    while (1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        args->socket->sendMessage("Message #" + to_string(counter));
        counter++;
    }
}

int main(int argc, char const **argv) {
    ServerSocket *serverSocket = new ServerSocket();

    /**
     * Para a realização de duas "tasks" cíclicas simultâneas
     * (recebimento de novos clientes e broadcast de mensagens),
     * utilizamos o mecanismo nativo de threads do C/C++. Uma thread
     * toma conta do rastreamento de clientes, e outra thread mantém
     * a execução do broadcast. */
    pthread_mutex_t mutexsum = PTHREAD_MUTEX_INITIALIZER;  
    pthread_t threads[2];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    threadArgs args;
    args.socket = serverSocket;
    pthread_create(&threads[0], &attr, clientListener, &args);
    pthread_create(&threads[1], &attr, broadcaster, &args);
    while (1) {}
    return 0;
}
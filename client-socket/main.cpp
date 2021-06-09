#include "client_socket.h"
#include <chrono>
#include <thread>

int main(int argc, char const *argv[]) {
	ClientSocket *s1 = new ClientSocket(1);
    ClientSocket *s2 = new ClientSocket(2);
    ClientSocket *s3 = new ClientSocket(3);
	while (1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        s1->readMessage();
        s2->readMessage();
        s3->readMessage();
        cout << endl;
    }
	return 0;
}

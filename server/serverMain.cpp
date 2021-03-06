#include <thread>
#include "cli/CLI.h"
#include "TcpServerSocket.h"
#include "SocketIO.h"

void handle(TcpSocket clientSock) {
    SocketIO io(&clientSock);
    try {
        CLI cli(&io);
        cli.start();
    } catch (...) {

    }
    clientSock.close();
}

int main() {
    // store the client threads to wait for them after timout
    std::vector<std::thread*> threads;

    // reminder -> reference paths start with "../"
    TcpServerSocket server(5487, "127.0.0.1");
    while (true) {
        try {
            // socket object to receive incoming clients
            // DEFAULT TIMEOUT ---> 30000ms with 1000ms delay by default
            TcpSocket client = server.accept();
            // displaying that new client has connected
            std::cout << "new client connected" << std::endl;
            //creating a new thread object
            auto *clientThread = new std::thread(handle, client);
            threads.push_back(clientThread);
        } catch (std::exception& e) {
            // waiting for all client threads to finish
            for (std::thread* t : threads) {
                if (t->joinable()) {
                    t->join();
                }
                delete t;
            }
            break;
        }
    }
    server.close();
}

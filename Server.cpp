
#include "Server.h"
#include <unistd.h>
#include<signal.h>

int gSignalStatus = 1;

Server::Server(int port) throw(const char *) {
    this->moreClients = true;
    this->t = nullptr;
    this->my_addr.sin_family = AF_INET;
    this->my_addr.sin_port = htons(port);
    this->my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    this->sock = socket(AF_INET, SOCK_STREAM, 0);
    if (this->sock < 0) {
        throw "failed creating";
    }
    if (bind(this->sock, (struct sockaddr *) &this->my_addr, sizeof(this->my_addr)) < 0) {
        throw "failed binding";
    }
    listen(this->sock, 5);
};

void sig_handler(int signal) {
    gSignalStatus = signal;
}

void Server::start(ClientHandler &ch) throw(const char *) {
    this->t = new thread([&ch, this]() {
        signal(SIGALRM, sig_handler);
        struct sockaddr_in cli_addr;
        cli_addr.sin_family = AF_INET;
        socklen_t clilen = sizeof(cli_addr);
        while (this->moreClients) {
            alarm(2);
            if(this->moreClients){
                int newsockfd = accept(this->sock, (struct sockaddr *) &cli_addr, &clilen);
                if (newsockfd < 0) {
                    throw "failed accepting";
                }
                ch.handle(newsockfd);
                close(newsockfd);
            }
        }
        alarm(0);
    });
}

void Server::stop() {
    this->moreClients = false;
    close(this->sock);
    this->t->join(); // do not delete this!
}

Server::~Server() {
    delete this->t;
}


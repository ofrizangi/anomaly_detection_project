

#ifndef SERVER_H_
#define SERVER_H_

#include <thread>
#include "commands.h"
#include "CLI.h"
#include <sys/socket.h>
#include <hash_map>

using namespace std;

// edit your ClientHandler interface here:
class ClientHandler{
public:
    virtual void handle(int clientID)=0;
};




// you can add helper classes here and implement on the cpp file
class SocketIO: public DefaultIO{
    //struct sockaddr_in my_addr;
    int sock;
public:
    SocketIO(int socknum){
        this->sock = socknum;
    }

    virtual string read(){
        string myStr = "";
        char c;
        while (c != '\n'){
            recv(this->sock, &c , sizeof c,0);
            if (c!= '\n'){
                myStr = myStr + c;
            }
        }
        return myStr;
    }

    virtual void write(string text){
        const char * t = text.c_str();
        send(this->sock, t, strlen(t), 0);
    }
    virtual void write(float f){
        send(this->sock, &f, sizeof (f), 0);
    }

    virtual void read(float *f){
        float * buffer;
        recv(this->sock, buffer, 1024,0);
        f = buffer;
    }
//    void bindSock(){
//        bind(this->sock, (struct sockaddr*)&my_addr , sizeof (my_addr));
//        listen(this->sock,5);
//    }
//    void acceptClient(struct sockaddr_in cli_addr){
//        socklen_t clilen = sizeof (cli_addr);
//        accept(this->sock, (struct sockaddr *) &cli_addr, &clilen);
//    }
//    void connectServer(struct sockaddr_in serv_addr){
//        connect(this->sock ,(struct sockaddr *) &serv_addr, sizeof (serv_addr));
//    }
//    struct sockaddr_in get_sockaddr_in(){
//        return this->my_addr;
//    }
//
//    int getSock(){
//        return this->sock;
//    }


};


class AnomalyDetectionHandler:public ClientHandler{
public:
    virtual void handle(int clientID){
        SocketIO socketIo(clientID);
        CLI cli(&socketIo);
        cli.start();
    }
};




// implement on Server.cpp
class Server {
    int sock;
    struct sockaddr_in my_addr;
    thread* t; // the thread to run the start() method in

public:
    Server(int port) throw(const char *);
    virtual ~Server();
    void start(ClientHandler &ch)throw(const char*);
    void stop();
};

#endif /* SERVER_H_ */
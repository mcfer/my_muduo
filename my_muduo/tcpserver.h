#ifndef TCPSERVER
#define TCPSERVER
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<iostream>
#include <sys/epoll.h>
#include<fcntl.h>
#include<iostream>
#include<string.h>
#include<channel.h>
#include<map>
#include<tcpconnection.h>
#include<acceptor.h>
#include<define.h>

using namespace std;

class TcpServer:public IAcceptCallBack
{
    private:
        void update(Channel *_pChannel,int op);
        int _epollfd;
        epoll_event _events[MAX_EVENTS];
        map<int,TcpConnection*>_connections;
        Acceptor *_pAcceptor;
public:
        TcpServer();
        ~TcpServer();
        void start();
        virtual void newConnection(int sockfd);

};

#endif // TCPSERVER


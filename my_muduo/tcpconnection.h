#ifndef TCPCONNECTION
#define TCPCONNECTION
#include<ichannelcallback.h>
#include<channel.h>
class TcpConnection:public IChannelCallBack
{
public:
    TcpConnection(int epollfd,int sockfd);
    ~TcpConnection();
    void virtual OnIn(int sockfd);

private:
    int _epollfd;
    int _sockfd;
    Channel* _pchannel;
};

#endif // TCPCONNECTION


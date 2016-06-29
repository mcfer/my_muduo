#ifndef ACCEPTOR
#define ACCEPTOR
#include<ichannelcallback.h>
#include<channel.h>
#include<iacceptorcallback.h>
class Acceptor:public IChannelCallBack
{
private:
    int createAndListen();
    int _epollfd;
    int _listenfd;
    Channel* _pAcceptChannel;

    IAcceptCallBack *_pCallback;
public:
    Acceptor(int epollfd);
    ~Acceptor();
    void virtual OnIn(int sockfd);
    void setCallBack(IAcceptCallBack *pCallBack);
    void start();
};

#endif // ACCEPTOR


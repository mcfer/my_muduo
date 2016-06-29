#include<acceptor.h>
#include<head.h>
#include<define.h>
Acceptor::Acceptor(int epollfd):_epollfd(epollfd),_listenfd(-1),_pCallback(NULL),_pAcceptChannel(NULL)
{

};
Acceptor::~Acceptor()
{}
void Acceptor::setCallBack(IAcceptCallBack *pCallBack)
{
    _pCallback=pCallBack;
}
void Acceptor::start()
{
    _listenfd=createAndListen();
    _pAcceptChannel=new Channel(_epollfd,_listenfd);
    _pAcceptChannel->setCallBack(this);
    _pAcceptChannel->enableReading();
}
int Acceptor::createAndListen()
{
    sockaddr_in serveraddr;
    int listenfd;

    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(8888);
    serveraddr.sin_addr.s_addr=(INADDR_ANY);//需要转网络自序

    listenfd=socket(AF_INET,SOCK_STREAM,0);
    fcntl(listenfd,F_SETFL,O_NONBLOCK);

    if(bind(listenfd,(sockaddr*)&serveraddr,sizeof(serveraddr))<0)
    {
        cout<<"bind failed ..."<<endl;
        exit(-1);
    }
    if(listen(listenfd,MAX_LISTENFD)<0)
    {
        cout<<"listen failed ..."<<endl;
        exit(-1);
    }
    return listenfd;
}
void Acceptor::OnIn(int sockfd)//处理新链接到来的函数
{
    int connfd;
    cout<<"OnIn"<<sockfd<<endl;
    sockaddr_in clientaddr;
    socklen_t len;

    connfd=accept(_listenfd,(sockaddr*)&clientaddr,&len);
    if(connfd<0)
        cout<<"accept failed from Acceptor"<<endl;
    else
    {
        cout<<"a new link from "<<inet_ntoa(clientaddr.sin_addr)<<":"<<ntohs(clientaddr.sin_port)<<endl;
        fcntl(connfd,F_SETFL,O_NONBLOCK);
        _pCallback->newConnection(connfd);
    }
}

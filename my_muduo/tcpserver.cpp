#include<tcpserver.h>
#include<define.h>
#include<vector>


using namespace std;
TcpServer::TcpServer():_epollfd(-1),_pAcceptor(NULL)
{}
TcpServer::~TcpServer()
{}
void TcpServer::newConnection(int sockfd)
{
    TcpConnection *tcp=new TcpConnection(_epollfd,sockfd);
    _connections[sockfd]=tcp;
}
void TcpServer::start()
{
    _epollfd=epoll_create(1);
    if(_epollfd<0)
        cout<<"epoll_create failed"<<endl;
    _pAcceptor=new Acceptor(_epollfd);
    _pAcceptor->setCallBack(this);
    _pAcceptor->start();
    for(;;)
    {
        vector<Channel*>channels;
    int fds=epoll_wait(_epollfd,_events,MAX_EVENTS,-1);
    if(fds==-1)
    {
        cout<<"epoll_wait error "<<errno<<endl;
        break;
    }
    for(int i=0;i<fds;i++)
    {
        //int tempfd=_events[i].data.fd;
        Channel *pchannel=static_cast<Channel*>(_events[i].data.ptr);
        pchannel->setRevents(_events[i].events);
        channels.push_back(pchannel);
    }
    for(vector<Channel*>::iterator iter=channels.begin();iter!=channels.end();iter++)
    {
        (*iter)->handleEvent();
    }
    }
}



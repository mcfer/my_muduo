#include<tcpconnection.h>
#include<channel.h>
#include<head.h>
#include<define.h>
TcpConnection::TcpConnection(int epollfd, int sockfd):_epollfd(epollfd),_sockfd(sockfd)
{
    _pchannel=new Channel(epollfd,sockfd);
    _pchannel->setCallBack(this);
    _pchannel->enableReading();

}
TcpConnection::~TcpConnection()
{}
void TcpConnection::OnIn(int sockfd)
{
    char buffer[MAX_LINE];
    memset(buffer,0,MAX_LINE);
    int read_count;
    if((read_count=read(sockfd,buffer,sizeof(buffer)))<0)
    {
        cout<<"read <0, failed"<<endl;
        close(sockfd);

    }
    else if(read_count==0)
    {
        cout<<"read 0 byte "<<endl;
        close(sockfd);
    }
    else
    {
        if(write(sockfd,buffer,read_count)<read_count)
            cout<<"not write one time"<<endl;
    }


}


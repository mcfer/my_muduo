#include<channel.h>
#include<head.h>
Channel::Channel(int epollfd,int sockfd):_epollfd(epollfd),_sockfd(sockfd),_revents(0),_events(0),_callback(NULL)
  {}
void Channel::setCallBack(IChannelCallBack *callback)
{
    _callback=callback;
}
void Channel::setRevents(int revent)
{
    _revents=revent;
}
void Channel::handleEvent()
{
    if(_revents&EPOLLIN )
    {
        _callback->OnIn(_sockfd);
    }
}
void Channel::enableReading()
{
    _events |=EPOLLIN;
    update();
}
int Channel::getSockfd()
{
    return _sockfd;
}
void Channel::update()
{
    epoll_event ev;
    //ev.data.fd=sockfd;
    ev.events=_events;
    ev.data.ptr=this;
    epoll_ctl(_epollfd,EPOLL_CTL_ADD,_sockfd,&ev);
}

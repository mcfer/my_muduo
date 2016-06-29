#ifndef CHANNEL
#define CHANNEL

#include<head.h>
#include<ichannelcallback.h>
class Channel
{
    public:
        Channel(int epollfd,int sockfd);
        ~Channel();
        void setCallBack(IChannelCallBack *callback);
        void handleEvent();
        void setRevents(int revent);
        int getSockfd();
        void enableReading();
private:
       void update();
       int _epollfd;
       int _sockfd;
       int _events;
       int _revents;
       IChannelCallBack *_callback;
};

#endif // CHANNEL


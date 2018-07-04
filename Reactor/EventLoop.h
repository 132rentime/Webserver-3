#pragma once

#include "Epoll.h"
#include "TimerManager.h"
#include <queue>
#include <pthread.h>

class Channel;
class Epoll;
class TimerManager;
typedef std::shared_ptr<Channel> SP_Channel;
typedef std::shared_ptr<Epoll> SP_Epoll;
typedef std::shared_ptr<TimerManager> SP_TimerManager;

class EventLoop{
private:
	typedef std::function<void()> Functor;
	std::queue<Functor> pendingfunctorq; 
	SP_Epoll poller;
	bool looping;
	bool quit;
	SP_TimerManager timermanager;
	pthread_mutex_t mutex;	

public:
	EventLoop();
	void addPoller(SP_Channel channel);
	void updatePoller(SP_Channel channel);
	void removePoller(SP_Channel channel);
	void loop();
	void addTimer(SP_Channel channel,int timeout);
	void queueInLoop(Functor &&cb);
	void doPendingFunctors();
};

typedef std::shared_ptr<EventLoop> SP_EventLoop;
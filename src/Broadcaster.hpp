#pragma once
#include <Poco/Net/DatagramSocket.h>
#include <Poco/Net/SocketReactor.h>
#include <Poco/Net/SocketNotification.h>
#include <Poco/Thread.h>
class Broadcaster
{
public:
	Broadcaster();
	void Broadcast();
	void OnReadable(const Poco::AutoPtr<Poco::Net::ReadableNotification>&);
private:
	Poco::Net::DatagramSocket socket;
	Poco::Net::SocketReactor reactor;
	Poco::Thread thread;
};
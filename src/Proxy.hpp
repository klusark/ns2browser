#pragma once
#include <Poco/Net/DatagramSocket.h>
#include <Poco/Net/SocketReactor.h>
#include <Poco/Net/SocketNotification.h>
#include <Poco/Thread.h>
class Proxy
{
public:
	Proxy(unsigned short listenPort, Poco::Net::SocketAddress &address);
	void OnReadable(const Poco::AutoPtr<Poco::Net::ReadableNotification>&);
private:
	Poco::Net::DatagramSocket socket;
	Poco::Net::SocketReactor reactor;
	Poco::Thread thread;
	Poco::Net::SocketAddress address;
	Poco::Net::SocketAddress localAddress;
	bool hasLocal;
	char *buffer;
};
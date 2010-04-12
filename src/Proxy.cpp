#include "Proxy.hpp"
#include <Poco/NObserver.h>
#include <Poco/Net/NetException.h>

Proxy::Proxy(unsigned short listenPort, Poco::Net::SocketAddress &address)
{
	socket.bind(Poco::Net::SocketAddress("0.0.0.0", listenPort));
	reactor.addEventHandler(socket, Poco::NObserver<Proxy, Poco::Net::ReadableNotification	>(*this, &Proxy::OnReadable	));
	hasLocal = false;
	buffer = new char[4096];
	this->address = address;
	thread.start(reactor);
	
	
	
}

void Proxy::OnReadable(const Poco::AutoPtr<Poco::Net::ReadableNotification>&)
{
	Poco::Net::SocketAddress socketAddress;
	//Put the packet into the buffer
	try{
		int length = socket.receiveFrom(buffer, 4096, socketAddress);
		printf("Proxy packet from %s %i\n", socketAddress.toString().c_str(), length);
		if (strcmp(buffer, "\xff\xff\xff\xffTSource Engine Query\0") == 0)
			return;
		if (socketAddress.host() == address.host() && hasLocal){
			socket.sendTo(buffer, length, localAddress);
		}else{
			localAddress = socketAddress;
			hasLocal = true;
			socket.sendTo(buffer, length, address);
		}
	}catch(Poco::Net::NetException &e){
		printf("error");
	}
}
#include "Broadcaster.hpp"
#include <Poco/NObserver.h>
Broadcaster::Broadcaster()
{
	reactor.addEventHandler(socket, Poco::NObserver<Broadcaster, Poco::Net::ReadableNotification	>(*this, &Broadcaster::OnReadable	));
	socket.setBroadcast(true);
	thread.start(reactor);
	
}

void Broadcaster::Broadcast()
{
	char *buffer = "\xff\xff\xff\xffTSource Engine Query\0";
	int length = strlen(buffer)+1;
	socket.sendTo(buffer, length, Poco::Net::SocketAddress("5.255.255.255", 27015));
	socket.sendTo(buffer, length, Poco::Net::SocketAddress("5.255.255.255", 27016));
	socket.sendTo(buffer, length, Poco::Net::SocketAddress("5.255.255.255", 27017));
	socket.sendTo(buffer, length, Poco::Net::SocketAddress("5.255.255.255", 27018));
	socket.sendTo(buffer, length, Poco::Net::SocketAddress("5.255.255.255", 27019));
	socket.sendTo(buffer, length, Poco::Net::SocketAddress("5.255.255.255", 26901));
	socket.sendTo(buffer, length, Poco::Net::SocketAddress("5.255.255.255", 26902));
	socket.sendTo(buffer, length, Poco::Net::SocketAddress("5.255.255.255", 27020));
	socket.sendTo(buffer, length, Poco::Net::SocketAddress("5.255.255.255", 26903));
	socket.sendTo(buffer, length, Poco::Net::SocketAddress("5.255.255.255", 26904));
	socket.sendTo(buffer, length, Poco::Net::SocketAddress("5.255.255.255", 26905));
	socket.sendTo(buffer, length, Poco::Net::SocketAddress("5.255.255.255", 26900));
	socket.sendTo(buffer, length, Poco::Net::SocketAddress("5.255.255.255", 4242));
	socket.sendTo(buffer, length, Poco::Net::SocketAddress("5.255.255.255", 27215));
}

void Broadcaster::OnReadable(const Poco::AutoPtr<Poco::Net::ReadableNotification>&)
{
	printf("test");
}
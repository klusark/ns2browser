#include "Broadcaster.hpp"
#include <Poco/NObserver.h>

struct ServerInfo
{
	std::string ServerName;
	std::string CurrentLevel;
	std::string Game;
	std::string Mod;
};

Broadcaster::Broadcaster()
{
	reactor.addEventHandler(socket, Poco::NObserver<Broadcaster, Poco::Net::ReadableNotification	>(*this, &Broadcaster::OnReadable	));
	socket.setBroadcast(true);
	socket.bind(Poco::Net::SocketAddress("0.0.0.0", 27020));
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
	char *buffer = new char[512];
	Poco::Net::SocketAddress socketAddress;
	//Put the packet into the buffer
	int length = socket.receiveFrom(buffer, 512, socketAddress);
	
	printf("Packet from %s\n", socketAddress.toString().c_str());
	if (strcmp(buffer, "\xff\xff\xff\xffTSource Engine Query\0") == 0){
		char *buffer = "\xff\xff\xff\xffI\aThis is fake\0maps/ns2_dm.level\0ns2\0Practice\0\x38\x13\0\x10\0lw\0\0\x31.0.0.0\0\x91\x87\x69\5\xec\xdb\x09\x4c\6\x40\1\x38\x13\0\0\0\0\0\0";
		socket.sendTo(buffer, 111, socketAddress);
	}else{
		int pos = 6;
		ServerInfo info;
		info.ServerName = std::string(buffer+pos);
		pos += info.ServerName.length()+1;
		info.CurrentLevel = std::string(buffer+pos);
		pos += info.CurrentLevel.length()+1;
		info.Game = std::string(buffer+pos);
		pos += info.Game.length()+1;
		info.Mod = std::string(buffer+pos);
		printf("Server %s on map %s from %s\n", info.ServerName.c_str(), info.CurrentLevel.c_str(), socketAddress.toString().c_str());
	}
}
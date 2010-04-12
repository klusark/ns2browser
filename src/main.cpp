#include "Broadcaster.hpp"
#include "Proxy.hpp"

int main()
{
	Proxy proxy(27040, Poco::Net::SocketAddress("5.99.12.77", 27015));
	
	Broadcaster broadcast;
	broadcast.Broadcast();
	while (1){
		Sleep(1);
	}
}
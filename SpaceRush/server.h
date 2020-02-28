#include <SFML/Network.hpp>

class Server
{
public:
	Server();
	void send(sf::Packet, sf::IpAddress, unsigned short);
	void listen();
	void thread();
	//void sendPlaySignal();
	void recieveConnection();
private:
	sf::UdpSocket s_socket;
	sf::IpAddress serverIp;
	unsigned short port = 8000;
	sf::IpAddress otherIp;
	unsigned short otherPort;
	unsigned short hostPort;
	sf::Thread listenThread;
};
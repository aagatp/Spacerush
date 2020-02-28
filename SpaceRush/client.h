#include <SFML/Network.hpp>

class Client
{
public:
	Client();
	Client(sf::IpAddress);
	void listen();
	void send(sf::Packet);
	void thread();
	sf::Vector2f getPosition(int);
	float getDirection(int);
	unsigned int getHealth(int);
	//bool isReady();
	//void recieveSignal();
	bool isShooting(int);
	void sendConnection();
private:
	int playerId;
	bool readytoplay=false;
	sf::UdpSocket c_socket;
	sf::IpAddress serverIp;
	sf::Thread listenThread;
	unsigned short port;
	sf::Vector2f positions[2];
	float directions[2];
	unsigned int healths[2];
	bool shoots[2];
};
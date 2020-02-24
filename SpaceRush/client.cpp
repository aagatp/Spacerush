//#include "client.h"
//
//using namespace std;
//Client::Client() : m_listenThread(&Client::Listen, this) //, m_readytoplayThread(&Client::PlaySignal, this)
//{
//    c_socket.bind(sf::Socket::AnyPort);
//    std::cout << "Enter server ip: ";
//    std::cin >> sIp;
//    sf::IpAddress send(sIp);
//    serverIp = send;
//
//    sf::RenderWindow dummy_window(sf::VideoMode(500, 500), "Dummy Window");
//
//    for (int i = 0; i < 10; i++)
//    {
//        BulletCounter[i] = 0;
//    }
//    for (int i = 0; i < 1000; i++)
//    {
//        BulletDirection[i] = { 0, 0 };
//    }
//}
//
//Client::Client(sf::IpAddress l_ip) : m_listenThread(&Client::Listen, this)
//{
//    c_socket.bind(sf::Socket::AnyPort);
//    serverIp = l_ip;
//    SendConnection();
//}
//
//void Client::SendConnection()
//{
//    sf::Socket::Status value;
//    value = c_socket.send(text.c_str(), text.length() + 1, serverIp, 2000);
//    if (value == 0)
//    {
//        std::cout << "Request to Connect Sent " << std::endl;
//    }
//}
//
//void Client::ReceiveConfirmation()
//{
//    sf::Packet packet;
//
//    std::string confirmation;
//
//    sf::IpAddress ip;
//    unsigned short port;
//    c_socket.receive(packet, ip, port);
//    packet >> confirmation >> m_totalplayers >> m_playerid;
//    if (sizeof(confirmation) > 10)
//    {
//        std::cout << confirmation << endl
//            << "Total Players: " << m_totalplayers << endl
//            << "Your Player No: " << m_playerid << endl;
//
//        std::cout << "\n\n\t\tWAITING FOR OTHER PLAYERS...\n\n"
//            << std::endl;
//    }
//    m_playerid = m_playerid - 1;
//}
//
//bool Client::ReadyToPlay()
//{
//    return readytoplay;
//}
//void Client::PlaySignal()
//{
//    sf::Packet packet;
//
//    int playnum;
//
//    sf::IpAddress ip;
//    unsigned short port;
//    c_socket.receive(packet, ip, port);
//
//    packet >> playnum;
//    if (playnum == -2)
//    {
//        readytoplay = true;
//    }
//}
//void Client::Send(sf::Packet packet)
//{
//    c_socket.send(packet, serverIp, 2000);
//}
//
//void Client::Listen()
//{
//    float xtank, ytank, xbullet, ybullet, angle;
//    int playerid, bulletno;
//    unsigned int health;
//
//    sf::Socket::Status value;
//    sf::IpAddress tempip;
//    unsigned short tempport;
//    sf::Packet packet;
//    while (1)
//    {
//        value = c_socket.receive(packet, tempip, tempport);
//        if (value == 0)
//        {
//            packet >> playerid >> xtank >> ytank >> angle >> health >> bulletno >> xbullet >> ybullet;
//            setState(playerid, { xtank, ytank }, angle, health, bulletno, { xbullet, ybullet });
//        }
//    }
//}
//
//void Client::setState(int playerid, sf::Vector2f position, float angle, unsigned int health, int bulletno, sf::Vector2f bulletdirection)
//{
//    Tankpositionarray[playerid] = position;
//    TankRotationArray[playerid] = angle;
//    TankHealthArray[playerid] = health;
//    BulletDirection[playerid * 100 + bulletno] = bulletdirection;
//    if (bulletno != BulletCounter[playerid])
//    {
//        BulletCounter[playerid] = bulletno;
//    }
//}
//
//sf::Vector2f Client::getTankPosition(int playerid) { return Tankpositionarray[playerid]; }
//
//sf::Vector2f Client::getBulletDirection(int playerid) { return BulletDirection[playerid * 100 + BulletCounter[playerid]]; }
//
//int Client::SendBulletNotoState(int playerid) { return BulletCounter[playerid]; }
//
//float Client::getTankDirection(int playerid) { return TankRotationArray[playerid]; }
//
//unsigned int Client::getTankHealth(int playerid) { return TankHealthArray[playerid]; }
//
//void Client::sendState()
//{
//    for (int i = 0; i < m_totalplayers; i++)
//    {
//        if (i == m_playerid)
//        {
//            continue;
//        }
//    }
//}
//
//void Client::Thread()
//{
//    m_listenThread.launch();
//}
//
//int Client::getPlayerId() { return m_playerid; }
//int Client::getTotalPlayer() { return m_totalplayers; }
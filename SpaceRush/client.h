//#pragma once
//
//
//#include <iostream>
//#include <SFML/Network.hpp>
//#include <SFML/Graphics.hpp>
//#include <SFML/Window.hpp>
//#include <conio.h>
//#include <map>
//#include <string>
//
//class Client
//{
//private:
//    std::string text = "Connected to: ";
//
//    int m_totalplayers;
//    int m_playerid;
//
//    unsigned short port;
//    sf::IpAddress serverIp;
//
//    sf::Vector2f Tankpositionarray[10];
//    float TankRotationArray[10];
//    unsigned int TankHealthArray[10];
//
//    int BulletCounter[10];
//    sf::Vector2f BulletDirection[1000];
//
//    sf::UdpSocket c_socket;
//    std::string sIp;
//    char m_buffer[200];
//
//    sf::Thread m_listenThread;
//
//    bool readytoplay = false;
//
//public:
//    Client(); //Constructor-Asks for ip address of the server
//    Client(sf::IpAddress); //Automatically sets the ip address of the server
//    void Thread(); //Function to start the listen thread
//    void Listen(); //Listens to packet from the server
//
//    int getTotalPlayer(); //Returns the total players in the game
//    int getPlayerId(); //Returns the player id of the player
//
//    void SendConnection(); //Send the Connection to Connect with the Server
//    void ReceiveConfirmation(); //Receive the packet from the server confirming that the server has received the connection
//    void WaitforSignal(); //Wait for playsignal to start the game
//    void PlaySignal();
//    bool ReadyToPlay(); //Returns the boolean value if all the players have joined the server and it is ready to start the game
//
//    void Send(sf::Packet); //Sends the packet to the server
//    void setState(int, sf::Vector2f, float, unsigned int, int, sf::Vector2f); //Set the state of other players in the client
//    void sendState(); //Send the state of m_player to the server
//    sf::Vector2f getTankPosition(int);
//    sf::Vector2f getBulletDirection(int);
//    unsigned int getTankHealth(int);
//    float getTankDirection(int);
//    int SendBulletNotoState(int);
//};
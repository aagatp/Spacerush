#include "computer.h"

Computer::Computer() {}

void Computer::setIp(sf::IpAddress address) { ip = address; }
void Computer::setPort(unsigned short portno) { port = portno; }
sf::IpAddress Computer::getIp() { return ip; }
unsigned short Computer::getPort() { return port; }
#include <iostream>
#include <stdlib.h>
#include "NetworkSnifferManager.h"


#pragma mark Network Sniffer Manager construction/destruction

NetworkSnifferManager::NetworkSnifferManager(int BufferSize) {
  bufferSize = BufferSize;
  readBuffer = new unsigned char[bufferSize]();
  tcpSocketFD = 0;
  tcp = 0;
  udp = 0;
  icmp = 0;
  others = 0;
  igmp = 0;
  total = 0;

}

NetworkSnifferManager::~NetworkSnifferManager() {
  // Clean up and newly declared memory.
  delete[] readBuffer;
}

void NetworkSnifferManager::OpenConnection() {

  unsigned int saddrSize;
  int dataSize;
  int index = 0;
  struct sockaddr socketAddress;

  // https://stackoverflow.com/questions/6878603/strange-raw-socket-on-mac-os-x
  this->tcpSocketFD = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
  std::cout << "Socket " << this->tcpSocketFD << std::endl;
  if (this->tcpSocketFD < 0) {
  	// terminate program with message
  	std::cout << "Connection failed to open" << std::endl;
  	exit (EXIT_FAILURE);
  }
  
  while (index < 10) {
	saddrSize = sizeof socketAddress;
	dataSize = recvfrom(tcpSocketFD, this->readBuffer, 
						 this->bufferSize, 0, &socketAddress, &saddrSize);
	std::cout << "Data Size" << dataSize << std::endl;
	if (dataSize < 0) {
		// terminate program with message
		std::cout << "Failed to receive data from packets" << std::endl;
  	    exit (EXIT_FAILURE);
	}
 	this->ReadPacket(this->readBuffer, dataSize);
 	index += 1;
  }
  close(this->tcpSocketFD);

}


void NetworkSnifferManager::ReadPacket(unsigned char *read_buffer, int dataSize) {

  // struct iphdr for Linux
  //struct iphdr *iph = (struct iphdr *)read_buffer;
  // struct ip for macOS
  struct ip *iph = (struct ip *)read_buffer;
  this->total++;

  switch (iph->ip_p) {
    case 1: // ICMP 
      this->icmp++;
      break;
    case 2: // IGMP
      this->igmp++;
      break;
    case 6: // TCP
      this->tcp++;
      break;
    case 17: // UDP
      this->udp++;
  }
  std::cout << "TCP : " << this->tcp << " UDP : " << this->udp << " ICMP : " << this->icmp << " Total : " << this->total << "\r" << std::endl;
}
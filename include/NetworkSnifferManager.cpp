#include <iostream>
#include <stdlib.h>
#include "NetworkSnifferManager.h"


#pragma mark Network Sniffer Manager construction/destruction

NetworkSnifferManager::NetworkSnifferManager(size_t BufferSize) {
  bufferSize = BufferSize;
  readBuffer = new unsigned char[bufferSize]();
  socketFD = 0;
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

  int dataSize;
  int index = 0;
  struct sockaddr_in socketAddress; // IPv4
  socklen_t socketAddressSize = sizeof(struct sockaddr_in);

  // https://stackoverflow.com/questions/6878603/strange-raw-socket-on-mac-os-x
  this->socketFD = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
  if (this->socketFD < 0) {
  	// terminate program with message
  	std::cout << "Connection failed to open" << std::endl;
  	exit (EXIT_FAILURE);
  }

  while (index < 20) {
	  
	  dataSize = recvfrom(this->socketFD, 
                        this->readBuffer, 
						            this->bufferSize, 
                        0, 
                        (struct sockaddr *)&socketAddress, 
                        &socketAddressSize);

	  std::cout << "Data Size " << dataSize << std::endl;
	  if (dataSize < 0) {
		  // terminate program with message
		  std::cout << "Failed to receive data from packets" << std::endl;
  	    exit (EXIT_FAILURE);
	  }


 	  this->ReadPacket(this->readBuffer, dataSize);
 	  index += 1;
  }
  close(this->socketFD);

}


void NetworkSnifferManager::ReadPacket(unsigned char *read_buffer, int dataSize) {
  
  // nano /usr/include/netinet/ip.h
  // http://www.msg.ucsf.edu/local/ganglia/ganglia-monitor-core-2.5.3/lib/dnet/ip.h
  // struct ip for usage on all *nix system  
  // iph->ip_p reads as an unsigned char is c++ gcc 0-255
  struct ip *iph = (struct ip *)read_buffer;
  this->total++; 

  std::cout << "Protocol " << (int)(iph->ip_p) << std::endl;
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
      break;
    default:
      this->others++;
      break;

  }
  std::cout << "TCP : " << this->tcp << " UDP : " << this->udp << " ICMP : " << this->icmp << " Others : " << this->others << " Total : " << this->total << "\r" << std::endl;
}
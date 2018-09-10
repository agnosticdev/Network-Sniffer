#include <cstdint>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>


class NetworkSnifferManager {

public:
	NetworkSnifferManager(size_t BufferSize);
	~NetworkSnifferManager();
	void OpenConnection();
	void ReadPacket(unsigned char *read_buffer, int dataSize);

	// Create IPv6 Socket Address structures and try to use for IPv4 also.
	// sockaddr_in* sockAddressIPv4 = (sockaddr_in*)&sockAddressIPv6Source;
	// http://man7.org/linux/man-pages/man7/ipv6.7.html
	sockaddr_in6 sockAddressIPv6Source, sockAddressIPv6Dest;
	unsigned char *readBuffer;

	size_t bufferSize;
	int socketFD;
	int tcp;
	int udp;
	int icmp;
	int others;
	int igmp;
	int total;
	int i, d;

};
#include <stdio.h>
#include <string.h>

#include <net/if.h>
#include <sys/ioctl.h>

int main()
{
	struct ifreq ifr;
	int sockfd, rc;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		perror("socket");
		return -1;
	}
	strcpy(ifr.ifr_name, "eth0");

	rc = ioctl(sockfd, SIOCGIFHWADDR, &ifr);
	if (rc < 0) {
		perror("ioctl");
		return -1;
	}

	printf("mac addr is: %02x:%02x:%02x:%02x:%02x:%02x\n",
			(unsigned char)ifr.ifr_ifru.ifru_hwaddr.sa_data[0],
			(unsigned char)ifr.ifr_ifru.ifru_hwaddr.sa_data[1],
			(unsigned char)ifr.ifr_ifru.ifru_hwaddr.sa_data[2],
			(unsigned char)ifr.ifr_ifru.ifru_hwaddr.sa_data[3],
			(unsigned char)ifr.ifr_ifru.ifru_hwaddr.sa_data[4],
			(unsigned char)ifr.ifr_ifru.ifru_hwaddr.sa_data[5]
	      );

	return 0;
}

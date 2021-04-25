/**
 * @file: prints_packets.cpp
 * @author: Vojtěch Bůbela
 * @login: xbubel08
 * @brief: definition of steal_packets function
 *         and other supportive functions
 */

#include <pcap.h>
#include <iostream>
#include <string>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
#include <net/ethernet.h>

#include "print_packets.hpp"

bool print_packets(argument_structure *store_args, pcap_t *interface) {

    // typedef void (*pcap_handler)(u_char *user, const struct pcap_pkthdr *h, const u_char *bytes);
    pcap_loop(interface, store_args->packets, handle_packet, NULL);

    return true;
}

void handle_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) {

    // int size = header->len;
    // int total = 0;
    // int icmp = 0;
    // int igmp = 0;
    // int tcp = 0;
    // int udp = 0;
    // int others = 0;

	struct sockaddr_in src;
	struct sockaddr_in dest;

	
	// get ip header
	struct iphdr *ip_header = (struct iphdr*)(packet + sizeof(struct ethhdr));

	// get tcp header
	struct tcphdr *tcph=(struct tcphdr*)(packet + ip_header->ihl*4 + sizeof(struct ethhdr));

	// print timestamp
	struct timeval tv;
	tv = header->ts;
  	char buf[28];
  	gettimeofday(&tv, NULL);

  	if(format_timeval(&tv, buf, sizeof(buf)) > 0) {
    	printf("%s ", buf);
	}

	memset(&src, 0, sizeof(src));
	src.sin_addr.s_addr = ip_header->saddr;
	
	memset(&dest, 0, sizeof(dest));
	dest.sin_addr.s_addr = ip_header->daddr;

	// print src IP and port
	printf("%s : %u > ", inet_ntoa(src.sin_addr), ntohs(tcph->source));
	printf("%s : %u, ", inet_ntoa(dest.sin_addr), ntohs(tcph->dest));

	// print packet length
	printf("length %d bytes\n", ntohs(ip_header->tot_len));

	// check protocol
	switch (ip_header->protocol)
	{
		case 1:  //ICMP Protocol
			// ++icmp;
			// print_icmp_packet( buffer , size);
			break;
		
		case 6:  //TCP Protocol
			// ++tcp;
			// print_tcp_packet(buffer , size);
			break;
		
		case 17: //UDP Protocol
			// ++udp;
			// print_udp_packet(buffer , size);
			break;	
		
		// #TODO handle arp
		default:
			break;
	}
	// printf("protocol number: %d TCP : %d   UDP : %d   ICMP : %d   IGMP : %d   Others : %d   Total : %d\n", iph->protocol, tcp , udp , icmp , igmp , others);

}


ssize_t format_timeval(struct timeval *tv, char *buf, size_t sz)
{
  ssize_t written = -1;
  struct tm *gm = gmtime(&tv->tv_sec);

  if (gm)
  {
    written = (ssize_t)strftime(buf, sz, "%Y-%m-%dT%H:%M:%S", gm);
    if ((written > 0) && ((size_t)written < sz))
    {
      int w = snprintf(buf+written, sz-(size_t)written, ".%06dZ",(int) tv->tv_usec);
      written = (w > 0) ? written + w : -1;
    }
  }
  return written;
}
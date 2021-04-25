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
#include <ctype.h>

#include "print_packets.hpp"

bool print_packets(argument_structure *store_args, pcap_t *interface) {

    // typedef void (*pcap_handler)(u_char *user, const struct pcap_pkthdr *h, const u_char *bytes);
    pcap_loop(interface, store_args->packets, handle_packet, NULL);

    return true;
}

void handle_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) {

	struct sockaddr_in src;
	struct sockaddr_in dest;
	struct iphdr *ip_header;
	struct tcphdr *tcp_header;
	struct timeval tv;
	char buf[28];
	int size_of_headers;

	// get ip header
	ip_header = (struct iphdr*)(packet + sizeof(struct ethhdr));

	// get tcp header
	tcp_header = (struct tcphdr*)(packet + ip_header->ihl*4 + sizeof(struct ethhdr));

	// print timestamp
	tv = header->ts;
  	gettimeofday(&tv, NULL);

  	if(format_timeval(&tv, buf, sizeof(buf)) > 0) {
    	printf("%s ", buf);
	}

	// get src and dest
	memset(&src, 0, sizeof(src));
	src.sin_addr.s_addr = ip_header->saddr;
	
	memset(&dest, 0, sizeof(dest));
	dest.sin_addr.s_addr = ip_header->daddr;

	// print src IP and port
	printf("%s : %u > ", inet_ntoa(src.sin_addr), ntohs(tcp_header->source));
	printf("%s : %u, ", inet_ntoa(dest.sin_addr), ntohs(tcp_header->dest));

	// print packet length
	printf("length %d bytes\n", ntohs(ip_header->tot_len));

	//set size of headers
	size_of_headers = sizeof(struct ethhdr) + ip_header->ihl*4 + tcp_header->doff * 4;

	// print packet payload
	print_data(packet + size_of_headers, header->len);	
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

void print_data(const u_char *packet_data, int size_of_data) {

	// mask that will result everything non zero as truth when &
	// 1111
	int mask_true = 15;
	char buffer[200];
	buffer[0] = '0';
	int buf_pos = 0;
	// std::string ascii_string = "";

	// print hexadecimal representation
	for(int i = 0; i < size_of_data; i++) {
		// zacatek radku
    	if((i & mask_true) == 0) {
       		printf("0x%04x: ",i);
		}

		printf("%02x%c",(unsigned char)packet_data[i], ' ');
		buffer[buf_pos] = (unsigned char)packet_data[i];
		buf_pos++;
		
		if(((i + 1) & mask_true) == 0) {
			for(int i = 0; i < 8; i++) {
					if(isprint(buffer[i])) {
						printf("%c", buffer[i]);
					} else {
						printf(".");
					}
				}

				printf(" ");

				for(int i = 8; i < 16; i++) {
					if(isprint(buffer[i])) {
						printf("%c", buffer[i]);
					} else {
						printf(".");
					}
				}
			buf_pos = 0;
			printf("\n");
		}

	}

	if(buf_pos != 0) {
		for(int i = buf_pos; i < 16; i++) {
			printf("   ");
		}

		for(int i = 0; i < buf_pos; i++) {
			if(i == 8) {
				printf(" ");
			}

			if(isprint(buffer[i])) {
				printf("%c", buffer[i]);
			} else {
				printf(".");
			}
		}
	}

	printf("\n");

	// print ACII representation


}
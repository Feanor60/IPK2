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

    pcap_loop(interface, store_args->packets, handle_packet, NULL);

    return true;
}

void handle_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) {

	struct sockaddr_in src;
	struct sockaddr_in dest;
	struct iphdr *ip_header;
	struct tcphdr *tcp_header;
	struct timeval tv;
	char buffer[28];
	int size_of_headers;

	// get ip header
	ip_header = (struct iphdr*)(packet + sizeof(struct ethhdr));

	// get tcp header
	tcp_header = (struct tcphdr*)(packet + ip_header->ihl*4 + sizeof(struct ethhdr));

	// print timestamp
	tv = header->ts;
  	gettimeofday(&tv, NULL);

  	if(format_time(&tv, buffer, sizeof(buffer)) > 0) {
    	printf("%s ", buffer);
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


bool format_time(struct timeval *tv, char *buffer, size_t size) {
  
	ssize_t formated = -1;
	struct tm *gm_t = gmtime(&tv->tv_sec);

	if(gm_t) {
    	formated = (ssize_t) strftime(buffer, size, "%Y-%m-%dT%H:%M:%S", gm_t);

    	if ((formated > 0) && ((size_t)formated < size)) {

      		int ret_val = snprintf(buffer + formated, size-(size_t)formated, ".%06dZ",(int) tv->tv_usec);
			
			if(ret_val < 0) {
				return false;
			}
    	}
  	}
  return true;
}

void print_data(const u_char *packet_data, int size_of_data) {

	// mask that will result everything non zero as truth when &
	// 1111
	int mask_true = 15;
	char buffer[200];
	buffer[0] = '0';
	int buf_pos = 0;

	// print hexadecimal representation
	for(int i = 0; i < size_of_data; i++) {
		// start of new line
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
}
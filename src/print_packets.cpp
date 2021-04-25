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

#include <netinet/ip_icmp.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
#include<net/ethernet.h>

#include "print_packets.hpp"

bool print_packets(argument_structure *store_args, pcap_t *interface) {

    // typedef void (*pcap_handler)(u_char *user, const struct pcap_pkthdr *h, const u_char *bytes);
    pcap_loop(interface, store_args->packets, handle_packet, NULL);
    return true;
}

void handle_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) {

    // int size = header->len;
    int total = 0;
    int icmp = 0;
    int igmp = 0;
    int tcp = 0;
    int udp = 0;
    int others = 0;
	
	//Get the IP Header part of this packet , excluding the ethernet header
	struct iphdr *iph = (struct iphdr*)(packet + sizeof(struct ethhdr));
	++total;
	switch (iph->protocol) //Check the Protocol and do accordingly...
	{
		case 1:  //ICMP Protocol
			++icmp;
			// print_icmp_packet( buffer , size);
			break;
		
		case 2:  //IGMP Protocol
			++igmp;
			break;
		
		case 6:  //TCP Protocol
			++tcp;
			// print_tcp_packet(buffer , size);
			break;
		
		case 17: //UDP Protocol
			++udp;
			// print_udp_packet(buffer , size);
			break;
		
		default: //Some Other Protocol like ARP etc.
			++others;
			break;
	}
	printf("protocol number: %d TCP : %d   UDP : %d   ICMP : %d   IGMP : %d   Others : %d   Total : %d\n", ntohs(iph->protocol), tcp , udp , icmp , igmp , others , total);
    // std::cout << "and now here\n";
    // std::cout << "timestamp: " << timestamp_string(header->ts) << "\n";
}

const char *timestamp_string(struct timeval ts)
	{
	static char timestamp_string_buf[256];

	sprintf(timestamp_string_buf, "%d.%06d",
		(int) ts.tv_sec, (int) ts.tv_usec);

	return timestamp_string_buf;
	}
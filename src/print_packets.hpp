/**
 * @file: print_packets.hpp
 * @author: Vojtěch Bůbela
 * @login: xbubel08
 * @brief: declaration of print_packets and other supportive functions
 */

#ifndef __PRINT_PACKETS__
#define __PRINT_PACKETS__

#include <pcap.h>

#include "argument_structure.hpp"

/**
 * @brief: function prints information about stolen packet. Then prints
 *         stolen data according to command line specification
 * @param store_args: structure with stored command line arguments
 * @param interface: pcap_t instance which is handle used to read packets
 * @retval: returns true if no problem else false
 */
bool print_packets(argument_structure *store_args, pcap_t *interface);

ssize_t format_timeval(struct timeval *tv, char *buf, size_t sz);

void handle_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet);

void print_data(const u_char *packet_data, int size_of_data);

#endif



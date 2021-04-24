/**
 * @file: steal_packets.hpp
 * @author: Vojtěch Bůbela
 * @login: xbubel08
 * @brief: declaration of steal_packets function
 */

#ifndef __STEAL_PACKETS__
#define __STEAL_PACKETS__

#include "argument_structure.hpp"

/**
 * @brief: steal_packets takes specified interface and steals packets from it,
 *         depending on other flags given on command line
 * @param store_args: structure with stored command line arguments
 * @retval: returns true on success otherwise returns false
 */
bool steal_packets(argument_structure *store_args);

typedef void (*pcap_handler)(u_char *user, const struct pcap_pkthdr *h, const u_char *bytes);

void handle_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet);

#endif
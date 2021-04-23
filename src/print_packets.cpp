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

#include "print_packets.hpp"

bool print_packets(argument_structure *store_args, pcap_t *interface) {


    // pcap_loop(interface, store_args->packets, handle_packet , NULL)

    return true;
}

void handle_packet(char *args, const struct pcap_pkthdr *header, const u_char *buffer) {

}
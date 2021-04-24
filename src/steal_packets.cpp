/**
 * @file: steal_packets.cpp
 * @author: Vojtěch Bůbela
 * @login: xbubel08
 * @brief: definition of steal_packets function
 */

#include <pcap.h>
#include <iostream>
#include <string>

#include "argument_structure.hpp"
#include "steal_packets.hpp"
#include "print_packets.hpp"
#include "setup_filter.hpp"

bool steal_packets(argument_structure *store_args) {

    const char* interface_name;
    char error_buffer[PCAP_ERRBUF_SIZE];
    pcap_if_t *alldevs;
    pcap_if_t *d;
    pcap_t *interface;

    int retval = pcap_findalldevs(&alldevs, error_buffer);
    if(retval != 0) {
        std::cout << error_buffer;
        return false;
    }

    for(d = alldevs; d != NULL; d = d->next) {
        if(store_args->interface.compare(d->name) == 0) {
            interface_name = d->name;
        }
    }

    if(interface_name == NULL) {
        std::cout << "Error: invalid interface name\n";
        return false;
    }

    interface = pcap_open_live(interface_name, 65536, 1, 0, error_buffer);
    if(interface == NULL) {
        std::cout << error_buffer << "\n";
        return false;
    }


    // filter stolen packets
    setup_filter(interface, store_args);

    // print stolen packets
    if(!print_packets(store_args, interface)) {
        return false;
    }

    pcap_freealldevs(alldevs);
    return true;
}

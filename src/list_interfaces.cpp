/**
 * @file: list_interfaces.cpp
 * @author: Vojtěch Bůbela
 * @login: xbubel08
 * @brief: file with definition of list_interfaces
 */

#include <pcap.h>
#include <iostream>
#include "list_interfaces.hpp"

bool list_interfaces() {
    
    pcap_if_t *alldevs;
    pcap_if_t *d;

    char error_buffer[PCAP_ERRBUF_SIZE];

    int retval = pcap_findalldevs(&alldevs, error_buffer);
    if(retval != 0) {
        std::cout << error_buffer;
        return false;
    }

    for(d = alldevs; d != NULL; d = d->next) {
        std::cout << d->name << "\n";
    }

    pcap_freealldevs(alldevs);
    return true;
}

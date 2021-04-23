/**
 * @file: list_interfaces.cpp
 * @author: Vojtěch Bůbela
 * @login: xbubel08
 * @brief: file with definition of list_interfaces
 */

#include <pcap.h>
#include <iostream>
#include "list_interfaces.hpp"

int list_interfaces() {
    
    pcap_if_t *alldevs;
    pcap_if_t *d;

    char *error_buffer =(char*) malloc(1000);

    int retval = pcap_findalldevs(&alldevs, error_buffer);
    if(retval != 0) {
        std::cout << error_buffer;
        return -1;
    }

    for(d = alldevs; d != NULL; d = d->next) {
        std::cout << "interface name is: " << d->name << "\n";
        if(d->description != NULL)
            std::cout << "  description: " << d->description << "\n\n";
    }

    return 0;

}

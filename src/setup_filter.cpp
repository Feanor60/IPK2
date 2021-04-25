/**
 * @file: setup_filter.cpp
 * @author: Vojtěch Bůbela
 * @login: xbubel08
 * @brief: definition of setup_fitler function
 */


#include <pcap.h>
#include <string>
#include <string.h>
#include <iostream>

#include "setup_filter.hpp"
#include "argument_structure.hpp"

bool setup_filter(pcap_t *interface, argument_structure *store_args) {

    // variables needed for filter setup
    // from http://homes.di.unimi.it/~gfp/SiRe/2002-03/progetti/libpcap-tutorial.html
    struct bpf_program filter;
    char *filter_params = (char*) malloc (100 * sizeof(char));
    bpf_u_int32 mask;
    bpf_u_int32 net;
    const char * device = store_args->interface.c_str();
    char error_buffer[PCAP_ERRBUF_SIZE];

    int retval = pcap_lookupnet(device, &mask, &net, error_buffer);
    if(retval != 0) {
        std::cout << error_buffer;
        free(filter_params);
        return false;
    }

    int arg_counter = -1;

    if(store_args->icmp)
        arg_counter++;

    if(store_args->tcp)
        arg_counter++;

    if(store_args->udp)
        arg_counter++;

    if(store_args->arp)
        arg_counter++;

    // enter filter options
    // -i eth0 -p 80 --tcp --udp --icmp --arp
    // icmp or icmp6 or arp or udp port 80 or tcp port 80

    filter_params[0] = '\0';
    if(store_args->icmp) {
        strcat(filter_params, "icmp or icmp6");
        if(arg_counter > 0) {
            strcat(filter_params, " + ");
            arg_counter--;
        }
    }

    if(store_args->tcp) {
        strcat(filter_params, "tcp");
        if(arg_counter > 0) {
            strcat(filter_params, " + ");
            arg_counter--;
        }
    }

    if(store_args->udp) {
        strcat(filter_params, "udp");
        if(arg_counter > 0) {
            strcat(filter_params, " + ");
            arg_counter--;
        }
    }

    if(store_args->arp) {
        strcat(filter_params, "arp");
        if(arg_counter > 0) {
            strcat(filter_params, " + ");
            arg_counter--;
        }
    }

    if(store_args->port > 0) {
        strcat(filter_params, " port ");
        std::string s = std::to_string(store_args->port);
        char const *pchar = s.c_str();
        strcat(filter_params, pchar);
    }

    // std::cout << filter_params << "\n";
    printf("filter_params is: %s\n", filter_params);

    pcap_compile(interface, &filter, filter_params, 0, net);
    retval = pcap_setfilter(interface, &filter);
    if(retval != 0) {
        std::cout << "somethng went wrong\n\n";
    }

    free(filter_params);
    return true;
}
/**
 * @file: main.cpp
 * @author: Vojtěch Bůbela
 * @login: xbubel08
 * @brief: main.cpp implements packet sniffer, a application for IPK second project
 * @description: packet sniffer can steal packets on given network.
 *               It's behaviour can be configured with arguments 
 */

// -- includes -- 
#include <iostream>
#include <list>
#include <string>

#include "argument_structure.hpp"
#include "parse_args.hpp"
#include "list_interfaces.hpp"
#include "steal_packets.hpp"

/**
 * @name: main  
 * @param argc: number of arguments
 * @param argv: 2d array of arguments
 * @return return 0 when no error
 *         return -1 when error while parsing arguments
 * @brief: main function of program
 */
int main(int argc, char *argv[]) {

    // parse command line arguments
    // init structure for storing commnad line arguments
    argument_structure *store_arg = new argument_structure;
    store_arg->packets = 1;
    store_arg->port = -1;
    store_arg->icmp = false;
    store_arg->tcp = false;
    store_arg->udp = false;
    store_arg->arp = false;
    std::string all_interfaces = "all_interfaces";
    store_arg->interface = all_interfaces;

    // fill strcture with arguments
    if(!parse_args(store_arg, argv, argc)) {
        fprintf(stderr, "Error while parsing arguments\n");
        delete store_arg;
        return -1;
    }

    if(store_arg->arp) {
        std::cout << "ARP tato aplikace bohužel nepodporuje\n";
        return 0;
    }

    // list all interfaces
    if(store_arg->interface.compare("all_interfaces") == 0) {
        if(!list_interfaces()) {
            fprintf(stderr, "Error while printing interfaces\n");
            delete store_arg;
            return -1;
        } else {
            delete store_arg;
            return 0;
        }
    }

    if(!steal_packets(store_arg)) {
        delete store_arg;
        std::cout << "Error while sniffing packets\n";
        return -1;
    }

    delete store_arg;
    return 0;
}

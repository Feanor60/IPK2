/**
 * @file: main.cpp
 * @author: Vojtěch Bůbela
 * @login: xbubel08
 * @brief: main.cpp implements packet sniffer, a application for IPK second project
 * @description: packet sniffer can steal packets on given network
 *               behaivour can be configured with arguments 
 */

// -- includes -- 

#include <iostream>
#include <list>
#include <string>

#include "argument_structure.hpp"
#include "parse_args.hpp"
#include "list_interfaces.hpp"

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
        return -1;
    }

    std::cout << " --- given arguments --- \n\n";
    std::cout << "interface: " << store_arg->interface << "\n";
    std::cout << "packets: "   << store_arg->packets << "\n";
    std::cout << "port: "      << store_arg->port << "\n";
    std::cout << "icmp: "      << store_arg->icmp << "\n";
    std::cout << "tcp: "       << store_arg->tcp << "\n";
    std::cout << "udp: "       << store_arg->udp << "\n";
    std::cout << "arp: "       << store_arg->arp << "\n";
    std::cout << " ----------------------- \n" ;


    // list all interfaces
    if(store_arg->interface.compare("all_interfaces") == 0) {
        int retval = list_interfaces();
        if(retval != 0) {
            fprintf(stderr, "Error while printing interfaces\n");
            return -1;
        }
    }
  

    delete store_arg;
    // finish program
    return 0;
}

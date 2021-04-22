/**
 * @file: argument_structure.h
 * @author: Vojtěch Bůbela
 * @login: xbubel08
 * @brief: header file for structure that is used to store command line
 *         packet sniffer arguments
 */

#ifndef __ARGUMENT_STRUCTURE__
#define __ARGUMENT_STRUCTURE__

#include <string>

struct argument_structure {
    public:
        std::string *interface;
        int packets;
        int port;
        bool icmp;
        bool tcp;
        bool udp;
        bool arp;


}typedef arg_struct;

#endif

/**
 * @file: list_interfaces.cpp
 * @author: Vojtěch Bůbela
 * @login: xbubel08
 * @brief: file with definition of list_interfaces
 */

#include <ifaddrs.h>
#include <iostream>
#include "list_interfaces.hpp"

int list_interfaces() {
    //create iffaddrs struct
    struct ifaddrs *ifaddr, *ifaddr_head;

    if(getifaddrs(&ifaddr_head) == -1) {
        return -1;
    }

    for(ifaddr = ifaddr_head; ifaddr != NULL; ifaddr = ifaddr->ifa_next) {
        std::cout << ifaddr->ifa_name << "\n";
    }

    return 0;

}

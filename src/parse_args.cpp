/**
 * @file: parse_args.cpp
 * @author: Vojtěch Bůbela
 * @login: xbubel08
 * @brief: definition of parse_args function
 */

// includes

#include <string>
#include <algorithm>
#include <list>
#include <iostream>

#include "parse_args.hpp"

bool parse_args(argument_structure *arg_struct, char *argv[], int argc){


    std::list<std::string> list = create_arg_list();
    std::string argument;
    std::string all_interfaces = "all_interfaces";


    for(int i = 0; i < argc; i++) {

        argument = argv[i];

        if((argument.compare("-i") == 0) || (argument.compare("--interface") == 0)) {
            int iter_next = i + 1;

            if(iter_next >= argc) {
                arg_struct->interface = all_interfaces;
                return true;
            }

            argument = argv[iter_next];

            if(!(std::find(list.begin(), list.end(), argument) != list.end())) {
                arg_struct->interface = argument;
                i++;
            }

        } else if(argument.compare("-p") == 0) {
            int iter_next = i + 1;

            if(iter_next >= argc) {
                return false;
            }

            argument = argv[iter_next];

            if(std::find(list.begin(), list.end(), argument) != list.end()) {
                return false;
            } else {
                arg_struct->port = std::stoi(argument);
                i++;
            }
        } else if(argument.compare("-n") == 0) {
            int iter_next = i + 1;

            if(iter_next >= argc) {
                return false;
            }

            argument = argv[iter_next];

            if(std::find(list.begin(), list.end(), argument) != list.end()) {
                return false;
            } else {
                arg_struct->packets = std::stoi(argument);
                i++;
            }
        } else if((argument.compare("-t") == 0) || (argument.compare("--tcp") == 0)) {
            arg_struct->tcp = true;
        } else if((argument.compare("-u") == 0) || (argument.compare("--udp") == 0)) {
            arg_struct->udp = true;
        } else if(argument.compare("--icmp") == 0) {
            arg_struct->icmp = true;
        } else if(argument.compare("--arp") == 0) {
            arg_struct->arp = true;
        } else {
            if(i != 0) {
                return false;
            }
        }
    }


    return true;
}

std::list<std::string> create_arg_list() {
    std::list<std::string> list;
    std::string arg;

    arg = "-i";
    list.push_front(arg);
    arg = "--interface";
    list.push_front(arg);
    arg = "-p";
    list.push_front(arg);
    arg = "--tcp";
    list.push_front(arg);
    arg = "-p";
    list.push_front(arg);
    arg = "--udp";
    list.push_front(arg);
    arg = "-u";
    list.push_front(arg);
    arg = "--arp";
    list.push_front(arg);
    arg = "--icmp";
    list.push_front(arg);
    arg = "-n";
    list.push_front(arg);

    return list;
}
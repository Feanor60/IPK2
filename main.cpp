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
#include <algorithm>
#include "./header_folder/argument_structure.h"

// -- other functions declarations --

bool parse_args(struct argument_structure, char *argv[], int argc);

std::list<std::string> create_arg_list();

// -- main func --
int main(int argc, char *argv[]) {

    // parse command line arguments
    // init structure for storing commnad line arguments
    arg_struct store_arg;
    parse_args(store_arg, argv, argc);



    

    // finish program
    return 0;
}

// -- other functions definitions --

/**
 * @name: parse_args
 * @arg argument_structure: instance of structure
 *      for storing command line arguments
 * @arg argv: 2d array of arguments
 * @arg argc: number of arguments
 * @retval: return true if arguments were loaded correctly else false
 * @brief: parses command line arguments and stores them in argument
 *         structure 
 */
bool parse_args(struct argument_structure, char *argv[], int argc){


    std::list<std::string> list = create_arg_list();
    std::string argument;

    for(int i = 0; i < argc; i++) {

        argument = argv[i];
        if(argument.compare("-i") == 0) {
            int iter_next = i + 1;
            argument = argv[iter_next];

            if(std::find(list.begin(), list.end(), argument) != list.end()) {
                argument_structure.interface = "";
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
}

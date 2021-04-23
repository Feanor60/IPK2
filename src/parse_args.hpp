/**
 * @file: parse_args.hpp
 * @author: Vojtěch Bůbela
 * @login: xbubel08
 * @brief: declaration of parse_args function
 */

#ifndef __PARSE_ARGS__
#define __PARSE_ARGS__

#include "argument_structure.hpp"

/**
 * @name: parse_args
 * @param argument_structure: instance of structure
 *      for storing command line arguments
 * @param argv: 2d array of arguments
 * @param argc: number of arguments
 * @retval: return true if arguments were loaded correctly else false
 * @brief: parses command line arguments and stores them in argument
 *         structure 
 */ 
bool parse_args(argument_structure *arg_struct, char *argv[], int argc);

/**
 * @name: create_arg_list
 * @return: returns list of possible program options
 * @brief: creates and returns list of options that the ipk-sniffer
 *         accepts. Its is used to check command line arguments against
 */
std::list<std::string> create_arg_list();

#endif
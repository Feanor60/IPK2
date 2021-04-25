/**
 * @file: setup_filter.hpp
 * @author: Vojtěch Bůbela
 * @login: xbubel08
 * @brief: declaration of setup_filter function
 */

#ifndef __SETUP_FILTER__
#define __SETUP_FILTER__

#include <pcap.h>

#include "argument_structure.hpp"

/**
 * @brief: function sets up a filter for stealing packets according to
 *         command line arguments
 * @param interface: handle that was open for sniffing
 * @param stre_args: structure containing command line arguments
 */
bool setup_filter(pcap_t *interface, argument_structure *store_args);

#endif
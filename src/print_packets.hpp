/**
 * @file: print_packets.hpp
 * @author: Vojtěch Bůbela
 * @login: xbubel08
 * @brief: declaration of print_packets and other supportive functions
 */

#ifndef __PRINT_PACKETS__
#define __PRINT_PACKETS__

#include <pcap.h>

#include "argument_structure.hpp"

/**
 * @brief: function prints information about stolen packet. Then prints
 *         stolen data according to command line specification
 * @param store_args: structure with stored command line arguments
 * @param interface: pcap_t instance which is handle used to read packets
 * @retval: returns true if no problem else false
 */
bool print_packets(argument_structure *store_args, pcap_t *interface);

/**
 * @brief: function for formating timestamp
 * @param tv: timeval structure
 * @param buffer: buffer to store formated timestamp
 * @param size: size of buffer
 * @retval: terurn true on succes, else false
 */
bool format_time(struct timeval *tv, char *buffer, size_t size);

/**
 * @brief: typedef for callback function used in pcap_loop()
 */
typedef void (*pcap_handler)(u_char *user, const struct pcap_pkthdr *h, const u_char *bytes);

/**
 * @brief: callback function for pcap_loop()
 * @param args: arguments
 * @param header: header with information
 * @param packet: pointer to content of packet
 */
void handle_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet);

/**
 * @brief: prints information about packet
 * @param packet_data: pointer to packet data
 * @param size_of_data: size of packet data
 */
void print_data(const u_char *packet_data, int size_of_data);

#endif



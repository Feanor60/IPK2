# @file: Makefile
# @author: Vojtěch Bůbela
# @login: xbubel08
# @brief: Makefile for IPK second project

# compiler
CXX = g++
CC = $(CXX)

# flags
CFLAGS = -g -Wall -Werror

# source files
SRC_FILES = main.cpp\

# source files directory
SRC_DIR = ./src_folder/

# header files directory
HEADER_DIR = ./header_folder/

# target file
TARGET = ipk-sniffer

all: $(TARGET)

$(TARGET): $(SRC_FILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC_FILES)

clean:
	rm $(TARGET)
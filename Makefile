# @file: Makefile
# @author: Vojtěch Bůbela
# @login: xbubel08
# @brief: Makefile for IPK second project, makelevel 0

# compiler
CXX = g++
CC = $(CXX)

SRC_DIR := ./src
OBJ_DIR := ./obj

# flags
CPPFLAGS = -g -Wall -Werror

# source files
SRC_FILES = $(SRC_DIR)/*.cpp
HEADER_FILES = $(SRC_DIR)/*.hpp

# target file
TARGET = ipk-sniffer

all: $(TARGET)

$(TARGET): $(SRC_FILES) $(HEADER_FILES)
	$(CC) $(CPPFLAGS) -o $(TARGET) $(SRC_FILES)

clean:
	rm $(TARGET)
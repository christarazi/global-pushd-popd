# Copyright (C) 2017 Chris Tarazi
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

CC = g++
CXXFLAGS = -Wall -Wextra -pedantic
INC = include
SRC = src
BUILD = build
BIN = bin
OBJS = $(BUILD)/stack.o $(BUILD)/helper.o
DEPS = $(INC)/stack.h $(INC)/helper.h
EXES = gpushdir global_pop_dir

all: $(EXES)

gpushdir: $(BUILD)/gpushdir.o $(OBJS)
	$(CC) $(CXXFLAGS) $(BUILD)/gpushdir.o $(OBJS) -o $(BIN)/gpushdir

global_pop_dir: $(BUILD)/gpopdir.o $(OBJS)
	$(CC) $(CXXFLAGS) $(BUILD)/gpopdir.o $(OBJS) -o $(BIN)/global_pop_dir

$(BUILD)/gpushdir.o: $(SRC)/gpushdir.cpp $(DEPS)
	$(CC) $(CXXFLAGS) -c $(SRC)/gpushdir.cpp -o $(BUILD)/gpushdir.o

$(BUILD)/gpopdir.o: $(SRC)/gpopdir.cpp $(DEPS)
	$(CC) $(CXXFLAGS) -c $(SRC)/gpopdir.cpp -o $(BUILD)/gpopdir.o

$(BUILD)/stack.o:  $(SRC)/stack.cpp $(INC)/stack.h
	$(CC) $(CXXFLAGS) -c $(SRC)/stack.cpp -o $(BUILD)/stack.o

$(BUILD)/helper.o: $(SRC)/helper.cpp $(INC)/helper.h
	$(CC) $(CXXFLAGS) -c $(SRC)/helper.cpp -o $(BUILD)/helper.o

clean:
	rm -rf $(BUILD)/* $(BIN)/*

CXX = g++
CXXFLAGS = -g -Wall
TARGET = aoc04

$(TARGET).o: $(TARGET).cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET).o $(TARGET).cpp

run: $(TARGET).o
	cat input.txt | ./$(TARGET).o

valids: $(TARGET).o
	cat all_valid.txt | ./$(TARGET).o

invalids: $(TARGET).o
	cat all_invalid.txt | ./$(TARGET).o

time:
	cat input.txt | strace -c ./$(TARGET).o

test: $(TARGET).o
	cat test.txt | ./$(TARGET).o

debug: $(TARGET).o
	cat input.txt | valgrind ./$(TARGET).o

clean:
	$(RM) $(TARGET).o

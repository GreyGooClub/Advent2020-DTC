CXX = g++
CXXFLAGS = -g -Wall -O3 -std=c++17
TARGET = aoc25

$(TARGET).o: $(TARGET).cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET).o $(TARGET).cpp

run: $(TARGET).o
	cat input.txt | ./$(TARGET).o

time:
	cat input.txt | strace -c ./$(TARGET).o

test: $(TARGET).o
	cat test.txt | ./$(TARGET).o

test2: $(TARGET).o
	cat test2.txt | ./$(TARGET).o

debug: $(TARGET).o
	cat input.txt | valgrind ./$(TARGET).o

clean:
	$(RM) $(TARGET).o

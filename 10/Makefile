CXX = g++
CXXFLAGS = -g -Wall
TARGET = aoc10

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

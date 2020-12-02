CXX = g++
CXXFLAGS = -g -Wall
TARGET = aoc01

$(TARGET).o: $(TARGET).cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET).o $(TARGET).cpp

run: $(TARGET).o
	cat input.txt | ./$(TARGET).o

test: $(TARGET).o
	cat test.txt | ./$(TARGET).o

debug: $(TARGET).o
	cat input.txt | valgrind ./$(TARGET).o

clean:
	$(RM) $(TARGET).o

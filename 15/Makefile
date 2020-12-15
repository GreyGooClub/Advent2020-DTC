CXX = g++
CXXFLAGS = -g -Wall -O3
TARGET = aoc15

$(TARGET).o: $(TARGET).cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET).o $(TARGET).cpp

run: $(TARGET).o
	cat input.txt | ./$(TARGET).o

time:
	time bash -c "cat input.txt | ./$(TARGET).o"

test: $(TARGET).o
	cat test.txt | ./$(TARGET).o

debug: $(TARGET).o
	cat input.txt | valgrind ./$(TARGET).o

clean:
	$(RM) $(TARGET).o

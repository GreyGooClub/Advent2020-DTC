CXX = g++
CXXFLAGS = -g -Wall
TARGET = aoc01

run: $(TARGET)
	cat input.txt | ./$(TARGET)

debug: $(TARGET)
	cat input.txt | valgrind ./$(TARGET)

clean:
	$(RM) $(TARGET)

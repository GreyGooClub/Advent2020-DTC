CXX = g++
CXXFLAGS = -g -Wall
TARGET = aoc02

run: $(TARGET)
	cat input.txt | ./$(TARGET)

test: $(TARGET)
	cat test.txt | ./$(TARGET)

debug: $(TARGET)
	cat input.txt | valgrind ./$(TARGET)

clean:
	$(RM) $(TARGET)

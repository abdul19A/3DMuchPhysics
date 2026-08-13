CXX = g++
CXXFLAGS = -O2 -Wall -Wextra -std=c++17
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRCS = $(wildcard *.cpp)
HDRS = $(wildcard *.h)
OBJS = $(SRCS:.cpp=.o)
TARGET = main

# Default rule
build: $(TARGET)

# Link executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LIBS)

# Compile .cpp files (rebuilds if ANY header file changes, zero extra files created)
%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run target
run: $(TARGET)
	./$(TARGET)

# Clean build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: build run clean
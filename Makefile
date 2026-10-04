CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2 -Iinclude
TARGET := sysguard

SRC := src/main.cpp \
       src/cpu_monitor.cpp \
       src/memory_monitor.cpp \
       src/process_monitor.cpp \
       src/disk_monitor.cpp \
       src/system_info.cpp \
       src/health_monitor.cpp

OBJ := $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET) sysguard.log

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run

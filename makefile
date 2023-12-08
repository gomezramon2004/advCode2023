CXX = g++
CXXFLAGS = -Wall -std=c++17
TARGET = main
FUN = functions

SRCS = main.cpp \
	$(FUN)/functions.cpp \
	$(FUN)/auxFunctions.cpp \

EXECUTABLE = a.out

all: $(EXECUTABLE)

$(EXECUTABLE): $(SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $@

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)

.PHONY: all run clean
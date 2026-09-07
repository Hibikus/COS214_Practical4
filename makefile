CXX = g++
CXXFLAGS = -g --coverage -pthread -Wall
GCOVFLAGS = -f -m -r -j

TARGET = main
DEMO_TARGET = demo

SRCS = $(filter-out DemoMain.cpp, $(wildcard *.cpp))
DEMO_SRCS = $(filter-out main.cpp, $(wildcard *.cpp))

OBJS = $(SRCS:.cpp=.o)
DEMO_OBJS = $(DEMO_SRCS:.cpp=.o)

GCOV_FILES = $(SRCS:.cpp=.cpp.gcov)

HDRS = $(wildcard *.h)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

$(DEMO_TARGET): $(DEMO_OBJS)
	$(CXX) $(CXXFLAGS) -o $(DEMO_TARGET) $(DEMO_OBJS)

%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

run-demo: $(DEMO_TARGET)
	./$(DEMO_TARGET)

coverage: run
	gcov $(GCOVFLAGS) $(SRCS)

clean:
	rm -f $(OBJS) $(DEMO_OBJS) $(TARGET) $(DEMO_TARGET) *.gcda *.gcno *.gcov *.gcov.json.gz

.PHONY: all run run-demo coverage clean
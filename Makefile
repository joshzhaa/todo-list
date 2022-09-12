EXECUTABLE  = todo.exe

PROJECTFILE = todo.cpp

SOURCES     = $(wildcard *.cpp)
OBJECTS     = $(SOURCES:%.cpp=%.o)

CXX         = clang++
CXXFLAGS = -std=c++2b -Wall -Wextra -pedantic

release: CXXFLAGS += -O3
release:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(EXECUTABLE)

debug: CXXFLAGS += -g3 -DDEBUG
debug:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(EXECUTABLE)

# make clean - remove .o files, executables, tarball
clean:
	rm -f $(EXECUTABLE) $(EXECUTABLE)_debug $(EXECUTABLE)_profile
	rm -Rf *.dSYM

# Set compiler = g++.
CXX = g++
# Set folders with .h files.
INCLUDES_DIRS = . ./include/
# Set folders with libraries files.
LIBRARIES_DIRS = ./lib
# Set compiler flags as wall, C++ standart, include, libraries folders paths.
CXXFLAGS = -Wall -std=c++17 -I$(INCLUDES_DIRS) -L$(LIBRARIES_DIRS)
# Set folders for generating object files.
OBJECTS_DIR = ./objects/
# Set dependencies list.
DEPENDENCIES_LIST_ORIGINAL = hellomake.h
DEPENDENCIES_LIST_ABSOLUTE = $(patsubst %, $(INCLUDES_DIRS)/%, $(DEPENDENCIES_LIST_ORIGINAL))
# Set objects list.
OBJECTS_LIST_ORIGINAL = hellomake.o hellofunc.o 
OBJECTS_LIST_ABSOLUTE = $(patsubst %,$(ODIR)/%,$(OBJECTS_LIST_ORIGINAL))

$(OBJECTS_DIR)/%.o: %.c $(DEPENDENCIES_LIST_ABSOLUTE)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

# Set libraries.
#LIBS = -lm ; LDFLAGS = -lgdi32
TetrisimoEsp: $(OBJECTS_LIST_ABSOLUTE)
	$(CXX) -o $@ $^ $(CXXFLAGS)
	# $(LIBS) ; $(LDFLAGS)

.PHONY: clean

clean:
	# rm -f $(OBJECTS_DIR)/*.o *~ core $(INCLUDES_DIRS)/*~ 
    del $(OBJECTS_DIR)

# src = $(wildcard *.cpp)
# obj = $(src:.cpp=.o)
# all: myprog
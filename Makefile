# Set compiler = g++.
CXX = g++
CXXFLAGS = -Wall -std=c++17

INCLUDES_DIRS = ./src/crossplatform ./src/windows ./src/lib/include
INCLUDES_DIRS_WITH_KEY = $(foreach dir, $(INCLUDES_DIRS), $(addprefix -I, $(dir)))
INCLUDES_FILES = $(wildcard $(addsuffix /*.h,$(INCLUDES_DIRS)))

SOURCES_DIRS = ./src/crossplatform ./src/windows
SOURCES_FILES = $(wildcard $(addsuffix /*.cpp,$(SOURCES_DIRS)))

OBJECTS_DIR = ./build/windows/objects
TMP_LIST = $(patsubst %.cpp,%.o,$(SOURCES_FILES))
OBJECTS_LIST_ORIGINAL = $(patsubst %/, %, $(TMP_LIST))
$(info $(OBJECTS_LIST_ORIGINAL))

LIBRARIES_DIRS = ./src/lib
# Set compiler flags as wall, C++ standart, include, libraries folders paths.
# DEPENDENCIES_LIST_ORIGINAL = $(wildcard $(addsuffix /*.h,$(INCLUDES_DIRS)))
# DEPENDENCIES_LIST_ABSOLUTE = $(patsubst %, $(INCLUDES_DIRS)/%, $(DEPENDENCIES_LIST_ORIGINAL))
# SOURCES_LIST_ABSOLUTE = $(patsubst %, $(SOURCES_DIRS)/%, $(SOURCES_LIST_ORIGINAL))
# OBJECTS_LIST_ABSOLUTE = $(patsubst %,$(OBJECTS_DIR)/%,$(OBJECTS_LIST_ORIGINAL))

# $(OBJECTS_LIST_ORIGINAL): $(SOURCES_LIST_ORIGINAL)
# 	$(CXX) -c -o $@ $< $(CXXFLAGS) $(INCLUDES)

# TetrisimoEsp: $(OBJECTS_LIST_ORIGINAL)
# 	$(CXX) -o $@ $^ $(CXXFLAGS)


# .PHONY: clean

# clean:
# 	del $(OBJECTS_DIR)
# rm -f $(OBJECTS_DIR)/*.o *~ core $(INCLUDES_DIRS)/*~ 

# src = $(wildcard *.cpp)
# obj = $(src:.cpp=.o)
# all: myprog


	# $(LIBS) ; $(LDFLAGS)
# DEPENDENCIES_SUBDIRS = ./src/crossplatform ./src/windows
# Super commands list.
# subdirs := $(wildcard */)
# sources := $(wildcard $(addsuffix *.cpp,$(subdirs)))
# objects := $(patsubst %.cpp,%.o,$(sources))
# $(objects) : %.o : %.cpp.
# -I$(INCLUDES_DIRS) -L$(LIBRARIES_DIRS)

	# $(info $(CXX))
	# $(info $(INCLUDES_DIRS))
	# $(info $(SOURCES_DIRS))
	# $(info $(LIBRARIES_DIRS))
	# $(info $(CXXFLAGS))
	# $(info $(OBJECTS_DIR))
	# $(info $(DEPENDENCIES_LIST_ORIGINAL))
	# $(info $(DEPENDENCIES_LIST_ABSOLUTE))
	# $(info $(SOURCES_LIST_ORIGINAL))
	# $(info $(SOURCES_LIST_ABSOLUTE))
	# $(info $(OBJECTS_LIST_ORIGINAL))
	# $(info $(OBJECTS_LIST_ABSOLUTE))
    #LIBS = -lm ; LDFLAGS = -lgdi32
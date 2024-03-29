CXX = g++
FILE_NAME_WINDOWS = TetrisimoEsp.exe
FILE_NAME_LINUX = TetrisimoEsp
CXXFLAGS = -std=c++17 -ggdb

BUILD_DIRECTORY = build
SOURCES_DIRECTORY = src

BUILD_WINDOWS_DIRECTORY = $(BUILD_DIRECTORY)/windows
BUILD_LINUX_DIRECTORY = $(BUILD_DIRECTORY)/linux

OBJECTS_WINDOWS_DIRECTORY = $(BUILD_WINDOWS_DIRECTORY)/objects
OBJECTS_LINUX_DIRECTORY = $(BUILD_LINUX_DIRECTORY)/objects

SOURCES_CROSSPLATFORM_DIRECTORY = $(SOURCES_DIRECTORY)/crossplatform
SOURCES_WINDOWS_DIRECTORY = $(SOURCES_DIRECTORY)/windows
SOURCES_LINUX_DIRECTORY = $(SOURCES_DIRECTORY)/linux
SOURCES_LINUX_WINDOWS_DIRECTORY = $(SOURCES_DIRECTORY)/linux-windows
SOURCES_LIBRARIES_DIRECTORY = $(SOURCES_DIRECTORY)/lib

DEPENDENCIES_LIBRARIES_FLAG := $(SOURCES_LIBRARIES_DIRECTORY)
DEPENDENCIES_LIBRARIES_FLAG := $(foreach dir, $(DEPENDENCIES_LIBRARIES_FLAG), $(addprefix -L, $(dir)))
DEPENDENCIES_WINDOWS_LIBRARIES = -lglfw3dll -lgdi32 -lopengl32
DEPENDENCIES_LINUX_LIBRARIES = -ldl -lglfw

INCLUDES_CROSSPLATFORM_DIRECTORY = $(SOURCES_DIRECTORY)/crossplatform
INCLUDES_WINDOWS_DIRECTORY = $(SOURCES_DIRECTORY)/windows
INCLUDES_LINUX_DIRECTORY = $(SOURCES_DIRECTORY)/linux
INCLUDES_LINUX_WINDOWS_DIRECTORY = $(SOURCES_DIRECTORY)/linux-windows
INCLUDES_LIBRARIES_DIRECTORY = $(SOURCES_DIRECTORY)/lib/include

INCLUDES_WINDOWS_FLAG := $(INCLUDES_CROSSPLATFORM_DIRECTORY) $(INCLUDES_LINUX_WINDOWS_DIRECTORY) $(INCLUDES_WINDOWS_DIRECTORY) $(INCLUDES_LIBRARIES_DIRECTORY)
INCLUDES_WINDOWS_FLAG := $(foreach dir, $(INCLUDES_WINDOWS_FLAG), $(addprefix -I, $(dir)))

INCLUDES_LINUX_FLAG := $(INCLUDES_CROSSPLATFORM_DIRECTORY) $(INCLUDES_LINUX_WINDOWS_DIRECTORY) $(INCLUDES_LINUX_DIRECTORY) $(INCLUDES_LIBRARIES_DIRECTORY)
INCLUDES_LINUX_FLAG := $(foreach dir, $(INCLUDES_LINUX_FLAG), $(addprefix -I, $(dir)))

OBJECTS_CROSSPLATFORM = $(patsubst %.cpp, %.o, $(wildcard $(addsuffix /*.cpp, $(SOURCES_CROSSPLATFORM_DIRECTORY))))
OBJECTS_WINDOWS = $(patsubst %.cpp, %.o, $(wildcard $(addsuffix /*.cpp, $(SOURCES_WINDOWS_DIRECTORY))))
OBJECTS_LINUX = $(patsubst %.cpp, %.o, $(wildcard $(addsuffix /*.cpp, $(SOURCES_LINUX_DIRECTORY))))
OBJECTS_LINUX_WINDOWS = $(patsubst %.cpp, %.o, $(wildcard $(addsuffix /*.cpp, $(SOURCES_LINUX_WINDOWS_DIRECTORY))))
OBJECTS_LIBRARIES = $(patsubst %.cpp, %.o, $(wildcard $(addsuffix /*.cpp, $(SOURCES_LIBRARIES_DIRECTORY))))

OBJECTS_WINDOWS_FLAG := $(OBJECTS_CROSSPLATFORM) $(OBJECTS_LINUX_WINDOWS) $(OBJECTS_WINDOWS) $(OBJECTS_LIBRARIES)
OBJECTS_WINDOWS_FLAG := $(foreach file, $(OBJECTS_WINDOWS_FLAG), $(addprefix $(OBJECTS_WINDOWS_DIRECTORY)/, $(file)))
OBJECTS_WINDOWS_FLAG := $(subst $(SOURCES_DIRECTORY)/,, $(OBJECTS_WINDOWS_FLAG))

OBJECTS_LINUX_FLAG := $(OBJECTS_CROSSPLATFORM) $(OBJECTS_LINUX_WINDOWS) $(OBJECTS_LINUX) $(OBJECTS_LIBRARIES)
OBJECTS_LINUX_FLAG := $(foreach file, $(OBJECTS_LINUX_FLAG), $(addprefix $(OBJECTS_LINUX_DIRECTORY)/, $(file)))
OBJECTS_LINUX_FLAG := $(subst $(SOURCES_DIRECTORY)/,, $(OBJECTS_LINUX_FLAG))

windows: $(FILE_NAME_WINDOWS)
linux: $(FILE_NAME_LINUX)

$(FILE_NAME_WINDOWS): $(OBJECTS_WINDOWS_FLAG)
	$(CXX) $(CXXFLAGS) $(INCLUDES_WINDOWS_FLAG) $(DEPENDENCIES_LIBRARIES_FLAG) -o $(BUILD_WINDOWS_DIRECTORY)/$@ $^ $(DEPENDENCIES_WINDOWS_LIBRARIES)

$(FILE_NAME_LINUX): $(OBJECTS_LINUX_FLAG)
	$(CXX) $(CXXFLAGS) $(INCLUDES_LINUX_FLAG) $(DEPENDENCIES_LIBRARIES_FLAG) -o $(BUILD_LINUX_DIRECTORY)/$@ $^ $(DEPENDENCIES_LINUX_LIBRARIES)

$(OBJECTS_WINDOWS_FLAG): $(OBJECTS_WINDOWS_DIRECTORY)/%.o : $(SOURCES_DIRECTORY)/%.cpp
	"mkdir" -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDES_WINDOWS_FLAG) $(DEPENDENCIES_LIBRARIES_FLAG) -c -o $@  $< $(DEPENDENCIES_WINDOWS_LIBRARIES)

$(OBJECTS_LINUX_FLAG): $(OBJECTS_LINUX_DIRECTORY)/%.o : $(SOURCES_DIRECTORY)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDES_LINUX_FLAG) $(DEPENDENCIES_LIBRARIES_FLAG) -c -o $@  $< $(DEPENDENCIES_LINUX_LIBRARIES)

.PHONY: windows linux clean

clean:
	rm -rf $(SOURCES_CROSSPLATFORM_DIRECTORY)/*.o
	rm -rf $(SOURCES_WINDOWS_DIRECTORY)/*.o
	rm -rf $(SOURCES_LINUX_DIRECTORY)/*.o
	rm -rf $(SOURCES_LINUX_WINDOWS_DIRECTORY)/*.o
	rm -rf $(SOURCES_LIBRARIES_DIRECTORY)/*.o
	rm -rf $(OBJECTS_WINDOWS_DIRECTORY)/*
	rm -rf $(OBJECTS_LINUX_DIRECTORY)/*
	rm -rf $(BUILD_WINDOWS_DIRECTORY)/$(FILE_NAME_WINDOWS)
	rm -rf $(BUILD_LINUX_DIRECTORY)/$(FILE_NAME_LINUX)

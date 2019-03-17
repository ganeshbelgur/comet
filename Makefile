########## COMMON VARIABLES ##########
CXX = g++
CFLAGS = -Wall
MODULE_NAME = beamdish
BUILD_DIR = bin

SOURCE_FILES = \
	$(wildcard beamdish/*.cpp) \
	$(wildcard beamdish/lights/*.cpp) \
	$(wildcard beamdish/materials/*.cpp) \
	$(wildcard beamdish/primitives/*.cpp) \
	$(wildcard beamdish/textures/*.cpp) \
	$(wildcard beamdish/utils/*.cpp)

OBJECT_FILES = $(patsubst %,$(BUILD_DIR)/%, $(notdir $(SOURCE_FILES:.cpp=.o)))

########## BUILD ##########
$(BUILD_DIR)/$(MODULE_NAME): $(OBJECT_FILES)
	$(CXX) -o $@ $^

# Using the vpath directive to fetch the right 
# source file to build the right object file.
vpath %.cpp $(dir $(SOURCE_FILES))

# Since the timestamps on directories change whenever a file is
# added, removed, or renamed, we certainly don’t want to rebuild all
# the targets whenever the build directory’s timestamp changes. 
# One way to manage this is with order-only prerequisites: 
# make the directory an order-only prerequisite on all the targets
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CFLAGS) -I. -c $< -o $@

# This is an order-only prerequisite for
# the creation of the build directory before
# the generation of the object files
$(BUILD_DIR):
	@mkdir -p "$(BUILD_DIR)"

########## HELP ##########
.PHONY: help
help:
	@echo "SOURCE_FILES: $(SOURCE_FILES)"

########## CLEAN ##########
.PHONY: clean
clean:
	@echo "Removing the build folder..."
	rm -rf bin


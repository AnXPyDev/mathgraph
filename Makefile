define \n


endef

SOURCE_DIR=src/
BUILD_DIR=build/
INCLUDE_DIR=include/

NAME=mathgraph
CC=g++
MAINFLAGS=
OBJECTFLAGS=-I $(INCLUDE_DIR)
DIRS=./ algebra algebra/operations
OBJECTS=main algebra/scope algebra/expression algebra/error algebra/symbol algebra/integer algebra/float algebra/fraction algebra/exponentiation algebra/list algebra/addition algebra/multiplication algebra/function algebra/assignment algebra/call algebra/operations/equal algebra/operations/add algebra/operations/multiply algebra/operations/power algebra/operations/gcd

main: build_dir objects
	@echo "Linking objects into executable: $(NAME)" && $(CC) $(MAINFLAGS) -o $(NAME) $(foreach object,$(OBJECTS),$(BUILD_DIR)$(object).o) || echo "Linking into executable failed"

build_dir:
	@[ ! -d $(BUILD_DIR) ] && mkdir $(BUILD_DIR) && echo "Created build directory: $(BUILD_DIR)" || echo "Build directory exists: $(BUILD_DIR)"	
	$(foreach subdir,$(DIRS),@[ ! -d $(BUILD_DIR)$(subdir) ] && mkdir $(BUILD_DIR)$(subdir) && echo "Created subdirectory: $(BUILD_DIR)$(subdir)" || echo "Subdirectory already exists: $(BUILD_DIR)$(subdir)"${\n})

objects:
	$(foreach object,$(OBJECTS),@[ ! -f $(BUILD_DIR)$(object).o ] && echo "Compiling to object: $(SOURCE_DIR)$(object).cpp" && $(CC) -c $(OBJECTFLAGS) $(SOURCE_DIR)$(object).cpp -o $(BUILD_DIR)$(object).o || echo "Skipping compilation: $(SOURCE_DIR)$(object).cpp"${\n})

clean:
	@[ -d $(BUILD_DIR) ] && rm -rf $(BUILD_DIR) && echo "Cleaned build" || echo "Already clean"

SOURCE_DIR=src
BUILD_DIR=build
DIFF_DIR=diff
INCLUDE_DIR=include
OBJECT_EXTENTION=cpp
NAME=mathgraph

CC=g++
CC_ARGS=
CC_OBJECT_ARGS=-c -I $(INCLUDE_DIR)
CC_MAIN_ARGS=

DIRECTORIES=$(shell $(SHELL) -c 'find $(SOURCE_DIR) -type d -mindepth 1 | sed -e "s/$(SOURCE_DIR)\///g" | tr "\n" " "')
OBJECTS=$(shell $(SHELL) -c 'find $(SOURCE_DIR) -type f -regex ".*\.\$(OBJECT_EXTENTION)" | sed -e "s/$(SOURCE_DIR)\///g" -e "s/\.$(OBJECT_EXTENTION)//g" | tr "\n" " "')

main: build_objects
	@echo -e "linking objects into executable: \"$(NAME)\" \c" && $(CC) $(CC_ARGS) $(CC_MAIN_ARGS) $(foreach object,$(OBJECTS),$(BUILD_DIR)/$(object).o ) -o $(NAME) && echo "+success" || echo "-fail"

build_objects: create_build_dir _build_objects create_diff_dir

_build_objects:
	@$(foreach object,$(OBJECTS),\
		if [[ ( ! -f "$(BUILD_DIR)/$(object).o" ) || ( ( -f "$(DIFF_DIR)/$(object).cpp" ) && $$(diff -q "$(DIFF_DIR)/$(object).cpp" "$(SOURCE_DIR)/$(object).cpp") ) ]]; then\
			echo -e "building object: \"$(object)\" \c";\
			if $(CC) $(CC_ARGS) $(CC_OBJECT_ARGS) "$(SOURCE_DIR)/$(object).cpp" -o "$(BUILD_DIR)/$(object).o"; then\
				echo "+success"\
			;else\
				echo "-fail"\
			;fi\
		;else\
			echo "skipping object: \"$(object)\""\
		;fi\
	;)

create_build_dir:
	@echo -e "creating build directory: \"$(BUILD_DIR)\" \c" && mkdir -p $(BUILD_DIR) && echo "+success" || echo "-fail"
	@$(foreach subdir,$(DIRECTORIES),\
		if [[ ! -d "$(BUILD_DIR)/$(subdir)" ]]; then\
			echo -e "creating build subdirectory: \"$(BUILD_DIR)/$(subdir)\" \c";\
			mkdir -p "$(BUILD_DIR)/$(subdir)" && echo "+success" || echo "-fail"\
		;else\
			echo "build subdirectory already exists: \"$(BUILD_DIR)/$(subdir)\""\
		;fi\
	;)

create_diff_dir:
	$(eval operation=$(shell $(SHELL) -c '[ ! -d "$(DIFF_DIR)" ] && echo "creating" || echo "updating"'))
	@echo -e "$(operation) diff directory: \"$(DIFF_DIR)\" \c" && cp -rf $(SOURCE_DIR) $(DIFF_DIR) && echo "+success" || echo "-fail"

clean:
	@echo -e "removing diff directory: \"$(DIFF_DIR)\" \c" && rm -rf $(DIFF_DIR) && echo "+success" || echo "-fail"
	@echo -e "removing build directory: \"$(BUILD_DIR)\" \c" && rm -rf $(BUILD_DIR) && echo "+success" || echo "-fail"

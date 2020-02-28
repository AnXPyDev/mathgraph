CC=g++

SOURCE_DIR=src
BUILD_DIR=build
DIFF_DIR=diff
INCLUDE_DIR=include
OBJECT_EXTENTION=cpp

DIRECTORIES=$(shell bash -c 'find $(SOURCE_DIR) -type d -mindepth 1 | sed -e "s/$(SOURCE_DIR)\///g" | tr "\n" " "')
OBJECTS=$(shell bash -c 'find $(SOURCE_DIR) -type f -regex ".*\.\$(OBJECT_EXTENTION)" | sed -e "s/$(SOURCE_DIR)\///g" -e "s/\.$(OBJECT_EXTENTION)//g" | tr "\n" " "')

main:
	@echo "OBJECTS:" $(OBJECTS)
	@echo "DIRECTORIES:" $(DIRECTORIES)

clean:
	@echo -e "removing diff directory:" $(DIFF_DIR) " \c" && rm -rf $(DIFF_DIR) && echo "sucess" || echo "fail"
	@echo -e "removing build directory:" $(BUILD_DIR) " \c" && rm -rf $(BUILD_DIR) && echo "sucess" || echo "fail"

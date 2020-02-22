define \n


endef

NAME=mathgraph
CC=g++
MAINFLAGS=
OBJECTFLAGS=
DIFF_FOLDER=temp
OBJECTS=src/main src/algebra/scope src/algebra/expression src/algebra/error src/algebra/symbol src/algebra/integer src/algebra/float src/algebra/fraction src/algebra/exponentiation src/algebra/list src/algebra/addition src/algebra/multiplication src/algebra/operations/equal src/algebra/operations/add src/algebra/operations/multiply src/algebra/operations/power src/algebra/operations/gcd

main: objects
	@$(CC) $(MAINFLAGS) -o $(NAME) $(foreach object,$(OBJECTS),$(object).o)
	@echo "Linking objects into executable: $(NAME)"

objects:
	$(foreach object,$(OBJECTS),@[ ! -f $(object).o ] && echo "Compiling to object: $(object).cpp" && $(CC) -c $(OBJECTFLAGS) $(object).cpp -o $(object).o || echo "Skipping compilation: $(object).cpp"${\n})

clean:
	$(foreach object,$(OBJECTS),@rm -f "$(object).o" && echo "Removed object: $(object).o" || "Failed to remove object: $(object).o"${\n})
	@rm -rf $(NAME) && echo "Removed executable: $(NAME)" || "Failed to remove executable: $(NAME)"

define \n


endef

NAME=mathgraph
CC=g++
MAINFLAGS=
OBJECTFLAGS=
OBJECTS=src/main src/algebra/scope src/algebra/expression src/algebra/symbol src/algebra/number src/algebra/boolean src/algebra/list src/algebra/addition src/algebra/inversion src/algebra/negation src/algebra/multiplication src/algebra/operations/compare src/algebra/exponentiation

main: objects
	@$(CC) $(MAINFLAGS) -o $(NAME) $(foreach object,$(OBJECTS),$(object).o)
	@echo "Linking objects into executable: $(NAME)"

objects:
	$(foreach object,$(OBJECTS),@[ ! -f $(object).o ] && echo "Compiling to object: $(object).cpp" && $(CC) -c $(OBJECTFLAGS) $(object).cpp -o $(object).o || echo "Skipping compilation: $(object).cpp"${\n})

smart_objects:

clean:
	$(foreach object,$(OBJECTS),@rm -f "$(object).o" && echo "Removed object: $(object).o" || "Failed to remove object: $(object).o"${\n})
	@rm -rf $(NAME) && echo "Removed executable: $(NAME)" || "Failed to remove executable: $(NAME)"

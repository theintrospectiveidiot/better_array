start_machine: tokenizer.c
	gcc -g  tokenizer.c -o tokenizer

get_names: tokenizer $(MAIN)	
	: > stuff.c && ./tokenizer $(MAIN)

do_stuff: stuff.c
	clang -g stuff.c -o stuff && valgrind --leak-check=full --show-leak-kinds=all ./stuff

run: start_machine get_names do_stuff

start_machine_cpp: tokenizer.cpp
	clang++ tokenizer.cpp -o tokenizer

get_names_cpp: tokenizer $(MAIN)	
	: > stuff.cpp && ./tokenizer $(MAIN)

do_stuff_cpp: stuff.cpp
	clang++ -o stuff stuff.cpp && ./stuff

walk: start_machine_cpp get_names_cpp do_stuff_cpp


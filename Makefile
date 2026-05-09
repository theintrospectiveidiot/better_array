start_machine: tokenizer.c
	gcc tokenizer.c -o tokenizer

get_names: tokenizer $(MAIN)	
	: > stuff.c && ./tokenizer $(MAIN)

do_stuff: stuff.c
	clang -o stuff stuff.c && ./stuff

run: start_machine get_names do_stuff

get_names_cpp: tokenizer $(MAIN)	
	: > stuff.cpp && ./tokenizer $(MAIN)

do_stuff_cpp: stuff.cpp
	clang++ -o stuff stuff.cpp && ./stuff

walk: start_machine get_names_cpp do_stuff_cpp


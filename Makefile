start_machine: tokenizer.c
	gcc tokenizer.c -o tokenizer

get_names: tokenizer $(MAIN)	
	: > stuff.c && ./tokenizer $(MAIN)

do_stuff: stuff.c input.txt
	gcc stuff.c -lm && ./a.out

run: start_machine get_names do_stuff 


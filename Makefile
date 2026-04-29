start_machine: tokenizer.c
	gcc tokenizer.c -o tokenizer

get_names: tokenizer $(MAIN)	
	touch stuff.c && ./tokenizer $(MAIN)

do_stuff: stuff.c input.txt
	gcc stuff.c && ./a.out && rm stuff.c

run: start_machine get_names do_stuff 


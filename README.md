## better_array

Arrays in C never really felt boring, but... always less interesting.

Like, I can't decide the dimensions of an integer array at run time. Thats so uncool!!

So, I tried to implement a system similar to how `numpy` implements arrays. Its `shape` can be anything!

And numpy is fast because its implemented in C!! (Besides the optimizations they have applied to make it faster and the vectorization they use which makes it so cool!!)

The main idea behind this is if you wanna use a 2D or a higher dimensional array, you don't really need a 2D array (like `int A[1][2]`), instead you can have a 1D array and some way to traverse through it, you can do all the stuff you were able to do with 2D or higher arrays in a much cooler way!

## Metadata and Data

We need some sort of metadata (which stores stuff like `dimension`, how many `rows`, `coulumns`, the `height`, etc.).

I saw this sort of implementation [here](https://youtu.be/gtk3RZHwJUA) and that has heavily inspired this project. (Do check it out, it's really nice.)

The metadata we store is like this: 

```c
typedef struct {
	int *traverse;   //The shape of the array basically
	int *strides;    //The strides, which help in accessing data from each row and column
	int dim;         //The dimension of the array
	int count;       //How many elements have been filled in
	int total;       //How many elements can be filled (from the shape)
	int capacity;    //How many elements can be stored (from the memory stuff)
	long make_sure;  //To make sure that the integer pointer we got as argument is initialised by init()
	                 //helps in not corrupting memory when we try to vectorize it...
} god_stuff;
```

Now, this goes right before our array. How? Watch it [here](https://youtu.be/gtk3RZHwJUA) or continue reading.

What we essentially do is store the `array` with its `metadata` like this:

```c
[metadata][array]
^
```

(`metadata` is of type `god_stuff` and `array` is of type `int` here)

And `metadata + 1` takes us to the `array`:

```c
[metadata][array]
          ^
```

This way, we can go from the array to its metadata to know about it, and move through it like we know everything about it (even though we do).

We initialize our array like this:

```c
int *init(int dim,int *shape) {																				
	god_stuff *headr = malloc(sizeof(god_stuff) + (sizeof(int)*CAPACITY));  
	headr->make_sure = 28602529;             //Some key to ensure that the operation we are doing is on our array and not just some garbage in the memory
	headr->count = 0;	
	headr->dim = dim;	
	headr->total = 1;														
	headr->traverse = malloc(sizeof(int)*headr->dim);	
	headr->strides = malloc(sizeof(int)*headr->dim);	
	init_to_num(headr->strides,headr->dim,1);	
	headr->capacity = CAPACITY;	
	//printf("shape >> ");							
	for (int i=0;i<headr->dim;i++) {			
		//scanf("%d",&headr->traverse[i]);	
		//getchar();
		headr->traverse[i] = shape[i];										
		headr->total *= headr->traverse[i];			
	}			
																
	for (int i=0;i<headr->dim;i++) {								
		for(int j=headr->dim - 1;j>=1+i;j-- ) {				
			*(headr->strides + i) *= *(headr->traverse + j);	
		}	
	}																														
	if(headr->total > headr->capacity) {					
		while (headr->total > headr->capacity) {	
			headr->capacity *= 2;	
		}																							
		headr = realloc(headr,sizeof(god_stuff) + (sizeof(int)*headr->capacity));	
	}										
	int *numbrs = (int *)(headr + 1);	
    return numbrs;	
}
```

So, its something like this:

```c
[headr][numbrs]
       ^
```

Now we got our function, lets initialise in main():

```c
int *numbrs = init(3,(int[]){3,3,3})   //Dimension is 3. It doesn't matter, works for n dimensions (n must be natural)
                                       //A 3x3 matrix basically... Obviously can be decided at runtime too
```

To get metadata of `numbrs`, just do something like this:

```c
god_stuff *metadata = (god_stuff *)numbrs - 1;

//And, now you have access to everything!

metadata->dim           //dimension
metadata->count         //How many have we filled
metadata->traverse      //How to traverse through the array
metadata->strides       //which no. u gotta multiply with the location coordinates to get that value... 
                        //(cuz our array is flattened into 1 dimension and doesn't exist as some higher dimension array in the memory)

```

## Start doing cool stuff!!

You can `push` elements into the array, and the count will keep track of the index! 

```c

#define push(numbrs,...) push_with_size(numbrs,sizeof((int[]){__VA_ARGS__})/sizeof(int),__VA_ARGS__)  //because u dont know how many elements you are pushing, so, a number which u dont need to worry about can be used internally

int push_with_size(int *numbrs,int wow,...) {
	va_list arg;
	god_stuff *headr = (god_stuff *)numbrs - 1;
	
	va_start(arg,wow);
	
	for(int i=0;i<wow;i++) {
		if(headr->count >= headr->total) {
			printf("\nFull!\n");              //If it exceeds how many elements I need, shape will be ruined...
			return 1;
		}
		
		numbrs[headr->count] = va_arg(arg,int);
		headr->count += 1;                   //for the next element to take the correct position
	}

	va_end(arg);
	return 0;
}

```

Similarly, you can summon the element by giving its coordinates: 

```c

int summon(int *numbrs,...) {
	va_list arg;
	god_stuff *headr = (god_stuff *)numbrs - 1;
	int location[headr->dim];

	va_start(arg,numbrs);
	for(int i=0;i<headr->dim;i++) {
		location[i] = va_arg(arg,int);
	}
	va_end(arg);
	int val = 0;
	for(int i=0;i<headr->dim;i++) {
		val += location[i]*headr->strides[i];
	}
	return numbrs[val];
}

```


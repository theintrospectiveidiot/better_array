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
	int dim;         //The dimension of the array
	int count;       //How many elements have been filled in
	int total;       //How many elements can be filled (from the shape)
	int capacity;    //How many elements can be stored (from the memory stuff)
} god_stuff;
```

Now, this goes right before our array. How? Watch it [here](https://youtu.be/gtk3RZHwJUA) or continue reading.

What we essentially do is store the array with its metadata like this:

```c
[metadata][array]
^
```

()`metadata` is of type `god_stuff` and `array` is of type `int` here)

And `metadata + 1` gives us:

```c
[metadata][array]
          ^
```

This way, we can go from the array to its metadata to know about it, and move through it like we know everything about it (even though we do).

We initialize our array like this:

```c
#define CAPACITY 1024

int *init(int dim) {
	god_stuff *headr = malloc(sizeof(god_stuff) + (sizeof(int)*CAPACITY));    //allocating the memory
	headr->count = 0;
	headr->dim = dim;
	headr->total = 1;
	headr->traverse = malloc(sizeof(int)*headr->dim);
	headr->capacity = CAPACITY;
	for (int i=0;i<headr->dim;i++) {
		scanf("%d",&headr->traverse[i]);               //can be given directly too, but taking from the user seemed
		getchar();                                     //fine at the moment.
		headr->total *= headr->traverse[i];
	}

	if(headr->total > headr->capacity) {
		headr->capacity *= 2;                          
		headr = realloc(headr,sizeof(god_stuff) + (sizeof(int)*headr->capacity));    //updates the capacity and reallocates the memory
	}
	int *numbrs = (int *)(headr + 1);
    return numbrs;
}
```


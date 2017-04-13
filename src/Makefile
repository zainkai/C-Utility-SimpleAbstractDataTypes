ADTArray_NC := ADTArray_NonContiguous
ADTStack := ADTStack
FLAGS := -Wall -g

all: ADTArray_NC ADTStack

ADTStack:
	gcc $(ADTStack).c $(FLAGS) -o $(ADTStack)
ADTArray_NC:
	gcc $(ADTArray_NC).c $(FLAGS) -o $(ADTArray_NC)
clean:
	rm $(ADTArray_NC)
	rm $(ADTStack)
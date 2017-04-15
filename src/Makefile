ADTArray_NC := ADTArray_NonContiguous
ADTArray := ADTArray
ADTStack := ADTStack
MacroStack := ADTStack_GenericMacros
FLAGS := -Wall -g

all: MacroStack 

ADTStack:
	gcc $(ADTStack).c $(FLAGS) -o $(ADTStack)
ADTArray:
	gcc $(ADTArray).c $(FLAGS) -o $(ADTArray)
MacroStack:
	gcc $(MacroStack).c $(FLAGS) -o macros
clean:
	# CLEANING
	rm macros
#rm $(ADTArray)
# rm $(ADTStack)
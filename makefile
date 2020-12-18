all: BHNbody

BHNbody:
	gcc BHNbody.c BHTree.c BHTree.h -o BHNbody -lm

clean:
	rm BHNbody
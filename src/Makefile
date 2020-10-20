
CFLAGS=-g -O3

all: tokenizer

tokenizer.o: tokenizer.h
tokenizer_UI.o: tokenizer.h 
history.o: tokenizer.h 

tokenizer: tokenizer.o tokenizer_UI.o 
	cc -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o tokenizer

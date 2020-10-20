
CFLAGS=-g -O3

all: tokenizer

tokenizer.o: tokenizer.h
tokenizer_UI.o: tokenizer.h history.h
history.o: tokenizer.h history.h

tokenizer: tokenizer.o tokenizer_UI.o history.o
	cc -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o tokenizer

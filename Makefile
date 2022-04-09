target:	cipher run

cipher: cipher.c
	gcc cipher.c -o cipher

run:
	./cipher

clean:
	rm cipher
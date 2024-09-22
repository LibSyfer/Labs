all: libstdb.so

libstdb.so: stackDouble.o
	gcc -shared stackDouble.o -o libstdb.so

stackDouble.o: stackDouble.c stackDouble.h
	gcc -fPIC -c stackDouble.c

clean:
	rm -rf *.o libstdb.so

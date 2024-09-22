all: dyLinking dyLoaging

dyLinking: dyLinking.o
	gcc dyLinking.o -o dyLinking -lstdb -Wl,-rpath=./libstackdouble -L./libstackdouble/
dyLoaging: dyLoading.o
	gcc dyLoading.o -o dyLoaging -rdynamic -ldl

dyLinking.o: dynamicLinking.c
	gcc -c dynamicLinking.c -o dyLinking.o
dyLoading.o: dynamicLoading.c
	gcc -c dynamicLoading.c -o dyLoading.o

clean:
	rm -rf *.o dyLoaging dyLinking
clean-dyLoading:
	rm -rf dyLoading.o dyLoading
clean-dyLinking:
	rm -rf dyLinking.o dyLinking

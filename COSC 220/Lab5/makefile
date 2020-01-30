
prog: prog.o foo.o bar.o
	g++ -o foo.cpp
	
prog: prog.cpp foo.h bar.h
	g++ -c prog.cpp
	
foo.o: foo.cpp foo.h
	g++ -c foo.cpp

bar.o: bar.cpp bar.h
	g++ -c bar.cpp
	
clean:
	rm prog.o foo.o bar.o



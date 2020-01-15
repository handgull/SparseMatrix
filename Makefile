main.exe: main.o
	g++ main.o -o main.exe

main.o: main.cpp
	g++ -c main.cpp -o main.o

.PHONY: clean doc

clean:
	rm -rf *.o *.exe ./html ./latex

doc:
	doxygen Doxyfile

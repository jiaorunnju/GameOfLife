test: main.cpp model.cpp
	g++ main.cpp model.cpp -o test -lncurses -lpthread

.PHONY : clean
clean:
	rm -f ./*.o test

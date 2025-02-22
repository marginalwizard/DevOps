all: series

series: main.o Series.o
	g++ -g -O2 -Wall -Wextra -Werror main.o Series.o -o series

main.o: main.cpp Series.h
	g++ -c -g -O2 -Wall -Wextra -Werror main.cpp

Series.o: Series.cpp Series.h
	g++ -c -g -O2 -Wall -Wextra -Werror Series.cpp

clean:
	rm -rf *.o *.gch series

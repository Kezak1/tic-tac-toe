all: tictactoe

tictactoe: main.cpp
	g++ -std=c++20 -Wall -Wextra -O2 main.cpp -o tictactoe

run: tictactoe
	./tictactoe

clean:
	rm -f tictactoe
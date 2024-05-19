2polar:
	clang++ -W -Wextra -pedantic -std=c++11 -DPOLAR_2 -DREALTIME_UPDATE source/*.cpp -o build/2polar -lraylib -lm

3polar:
	clang++ -W -Wextra -pedantic -std=c++11 -DPOLAR_3 -DREALTIME_UPDATE source/*.cpp -o build/3polar -lraylib -lm

all: 2polar 3polar



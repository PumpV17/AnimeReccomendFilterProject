@echo off

REM Build main program
g++ -std=c++11 -I include -c src/AnimeReccomend.cpp -o build/AnimeReccomend.o
g++ -std=c++11 build/AnimeReccomend.o -o AnimeReccomend

REM Build and run tests
g++ -std=c++11 -I include -c tests/animefiltertestcases.cpp -o build/animefiltertestcases.o
g++ -std=c++11 build/animefiltertestcases.o build/AnimeReccomend.o -o test_runner
test_runner

# 42CodinGameArena - CodinGame Spring Challenge 2021

Local arena to test your code against everyone else's

</br>

<h2> Prerequisites </h2>

The arena was made to compile on Mac.

<h2> Installation </h2>

+ Clone the repository, then Make; an executable `arena` will be created and player object files in `playerObject/` will be turned into executables
+ The executable of each player will be in `player/`, you may want to copy the bots you're interested to fight against to `opponent/`

<h2> Usage </h2>

`./arena your_executable opponent_executable1 opponent_executable2 ... 2> /dev/null` to confront your executable against all other executables passed as parameter, as many times as specified on the `#define PLAYOUT` on arena.cpp (`2> /dev/null` to get rid of the stderr output)

<img src="https://github.com/martingarcialopez/42CodinGameArena/blob/main/.images/arena2.png" width="100%" />

`./arena your_executable` to confront your executable against all other executables in `opponent/`

<img src="https://github.com/martingarcialopez/42CodinGameArena/blob/main/.images/arena1.png" width="100%" />

  
<h2> What we need from you </h2>

We need you to compile your arena code to an object file (with the flag `-arch x86_64`) and to do a Pull Request to playerObject/your_login.o

The idea is to have plenty of bots there to do some serious benchmarking, and therefore to boost the school performance during the last days of challenge

</br>
<h3> Player Compile </h3>

To work in your code and see the results of your changes in real time you propably want to have your source code in the arena (locally). You can place your source `login.cpp` in `compilePlayer/`, and then Make will compile that, update your object and create the appropiate executable. 
Make will try to compile your source as C++, you will need to change the Makefile if you code in another language 

`/!\ There is already a .gitignore, so you cannot push your source code to the arena by error /!\`

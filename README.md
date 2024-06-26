# Project Information

This is a _player-versus-player snake game_ made in C++ using the library Raylib.

I've used a pre-made Raylib template available [here](https://github.com/educ8s/Raylib-CPP-Starter-Template-for-VSCODE-V2).

At the beginning, I was using [this tutorial](https://www.youtube.com/watch?v=1zVlRXd8f7g), but after learning the basics, I continued the work on my own and made certain original modifications (notably, I've turned it into a two-player game).

## How to download, install and run the game

### Set up Raylib
Details on how to set up the Raylib C++ library can be found at [the beginning of this tutorial](https://www.youtube.com/watch?v=RGzj-PF7D74).

### Install the project on your machine
1. Clone this repository

    > For instance, you can use Git Bash. Inside Git Bash, go to the directory of your choice and type the following command:
    > 
    > `git clone https://github.com/miqnni/multiplayer-snake-game.git`
    >
    > This should create a folder with this repository.

2. Find the file named `main.code-workspace` and open it with Visual Studio Code.
3. If asked whether you trust the authors of the files in this folder, click "Yes, I trust the authors".
4. Inside Visual Studio Code, go to the directory `src/` and open the file `main.cpp`. Press F5 to run the game.


## How to play

Press Space to start the game.

One player controls the snake with W, A, S, D and the other one controls it with arrow keys. Eat the appearing food to enlarge your snake. If your snake collides with (any of the following):

-   itself
-   map edges
-   the opponent's snake

you lose and the other player wins. If both snakes collide (with map edges or any snake body) at the same time, the game ends in a draw.

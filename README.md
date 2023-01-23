Game Boy Snake
==============

This is my little snake implementation for Game Boy to learn to program
for this platform.

How to play
-----------

Download the latest .gb release file and load it in your favorite
Game Boy emulator.

Here are some emulators to choose from if you don't know any:
* https://bgb.bircd.org
* https://mgba.io

Compile from source
-------------------

You need the
[gbdk-2020](https://github.com/gbdk-2020/gbdk-2020/releases) Game Boy
development kit downloaded somewhere on your PC.

Edit the path to your gbdk-2020 installation in the files
`/CMakeLists.txt` and `/Makefile`.

Go into the directory of the `/Makefile` and compile the cartridge with
```shell
make build
```

I only use the `/CMakeLists.txt` to give me code completion for the
gbdk header files in CLion, to compile the game only the `/Makefile` is
needed.

Todo
----

* find a more efficient way to place a new apple at random location
* initialize the random seed at the beginning
* add levels with different borders
* add score
* add menu
* add animations
* save high scores
* add music and maybe sound effects

# Snake

## Background

_Snake_ is a classic form of video game that originated in the 1970s.
The gameplay involves navigating a line ('snake') around a board seeking to
collide with dots ('food'). Each time a piece of food is eaten, the snake
increases in length and the player gains a point. The game is over when the
snake collides either with its own body or with a wall - something that becomes
progressively harder to avoid as the snake grows longer.
An implementation of the _Snake_ concept was famously included in Nokia mobile
phones in the late 1990s, where it formed part of this developer's childhood.

## Language

This implementation of _Snake_ uses the C++ programming language.  

## Motivation

My primary motivation in developing this implementation of _Snake_ was to
practice developing in C++. Additionally, I was interested to deepen my
experience in using the SDL2 multimedia library, which I had been exposed to
in previous projects. Finally, I felt that 2D video game development provided
a good opportunity to explore Object Oriented Design methodology.

## Target Platforms

The two target platforms for the game are _Linux_ and _MacOS_. A Makefile is
included that attempts to detect which of these two types of Operating Systems
you are using and to adjust the compilation commands accordingly. To compile
on another Operating System, you would most likely need to make your own
adjustments to the Makefile and possibly to preprocessor statements in the
source cpp files. The game was developed and tested on
 _Ubuntu_ and _MacOS High Sierra_ specifically.

## Dependencies

The game has broadly two types of dependencies: those that are included
inside the Git repository by default and those that you need to install by
yourself independently before compilation. The reason why some dependencies
were not included is that they have platform-specific implementations. The
dependencies that were included are broadly cross-platform.

### Included in Repository

1. __Catch2 Testing Framework__ - A header-only C++ unit testing framework
developed by [Catch Org](https://github.com/catchorg)
2. __Noto Mono Font__ - A monospace TTF Font developed by
[Google](https://www.google.com/get/noto/). The font's SIL Open Font
License is included alongside the .ttf file itself

### Not included in Repository

1. __GNU Compiler Collection (GCC)__ - The project Makefile compiles
using the command _g++_. GCC is frequently pre-installed on machines anyway
2. __SDL2__ - Popular cross-platform multimedia library written in C and
commonly used to make games. Please see installation instructions for
[Linux](http://lazyfoo.net/tutorials/SDL/01_hello_SDL/linux/index.php) or
[MacOS](http://lazyfoo.net/tutorials/SDL/01_hello_SDL/mac/index.php)
3. __SDL2_ttf__ - An [extension library]
(http://www.libsdl.org/projects/SDL_ttf/) to enable use of TTF fonts
within SDL2 applications.

## Compilation guide

To compile and run the game, navigate to the top level directory of the
repository using the command line and type 'make'. To compile and run all
game unit tests, type 'make test' instead.

## About me

I am a software developer active in East Asia. I learned
Object Oriented Programming (OOP) and video games development while
studying at the University of Bristol, where I graduated with
an MSc in Computer Science (Distinction) in 2019.

## Copyright

For information on the licensing of the included third-party dependencies,
please contact their respective developers listed above. The rest of the files
are Copyright Toby Bladen, 2019.

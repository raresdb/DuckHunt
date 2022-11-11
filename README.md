#Butilca Rares

About:
    This is an implementation of the Duck Hunt game using the gfx-framework presented in the README
inside the folder gfx-framework-master + DuckHunt.

    My implementation of the game can be found at the path gfx-framework-master +
DuckHunt/src/lab-m1/Tema1. To open the project, open the main folder in Visual Studio or use the
.sln file in gfx-framework-master + DuckHunt/build.

Gameplay:
    In this game the player has to shoot ducks that come out of the grass(the green field) by
clicking on them (3 bullets available). If the duck survives for a certain time(depending on
the difficulty), then the duck will escape and the players will lose one of the 3 lives they own.
Upon losing all lives, further attempts to shoot will print on the console a message that there are
no more lives left.
    After every 5 ducks hit, the difficulty increases, which means the speed of the duck increases
and the time they are available to be hit decreases. Furthermore, the points each duck offers is
increased by one with every increase in difficulty. After getting the score 50/50 (which can be seen
at the top left corner of the screen), the player will win the game and further attempts to shoot
will print on the console the message that the player has already won the game.

Other observations:
    The game hasn' been tested in full screen, so I advice against resizing the window :)
    On some slower computers, some clicks might not be processed by the program, leading to them
being ignored.

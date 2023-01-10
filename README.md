# LastDefense
A mixture of pacman and tower defense.

# Run the Code on Ubuntu
- Install the C++ SFML library by typing
```
sudo apt-get install libsfml-dev
```
into the terminal, or otherwise install at https://www.sfml-dev.org/download/sfml/2.5.1/
- Make sure C++ and g++ is installed
- Download LastDefense code from github
- run
```
make fresh
```
in the downloaded folder to compile all files into the obj directory and link dependencies.
- run
```
./run
```
in the same folder to run the program. It may take a second of black screen to load.

Note: This game has only been tested on Ubuntu 20.04, though it may work on other versions or platforms.

# How to Play
Kings make many enemies, and explosive killer drones are trying to assassinate you!
Use arrow keys to move the player, the king, on the grid and around black walls. Dodge explosive enemies as you collect cash lying around the board. Spend 100 cash in order to temporarily hire a soldier to defend you, they will attack enemies one square away and act as barriers that enemies cannot go through. The player and enemies have health bars, while the soldier has a timer bar which shows the amount of time left they will help protect you. Beware the red edges where the enemies spawn from! Collect as much cash and summon as many soldiers as possible before the swarm catches you.

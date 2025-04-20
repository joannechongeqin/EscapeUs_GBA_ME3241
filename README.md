### Code Structure
- header/include dependency chain: `main.c -> game.h -> menu.h -> level.h -> mygbalib.h -> player.h -> sprites.h -> gba.h`
- note: need to split `.h` and `.c`, else might get `multiple definitions` error
- helpful shortcut keys: `F10` to `clean` (remove all build files) and `F7` to `Build + Run in VBA`

| File(s)              | Description / Notes                                                                                  |
|----------------------|------------------------------------------------------------------------------------------------------|
| `main.c`             | project entry point                                                                                  |
| `game.h`             | checkbutton, main gameplay logic (update game state)                                                 |
| `menu.h`             | simple menu to start a session, display win / lose ending screen                                     |
| `level.h/.c`         | level designs, store and get data for each level, draw level on screen                               |
| `mygbalib.h/.c`      | graphics rendering (drawSprite, clearScreen etc)                                                     |
| `player.h/.c`        | player movement (left/right, jump), gravity, switch player, update players                           |
| `sprites.h/.c`       | sprites info *(if changing `#define` values, update both `.h` and `.c`, technically the `.h` one is being used everywhere else but just putting in `.c` for easy reference)* |
| `gba.h`              | gba constant value defines                                                                             |


### Current Progress
- dummy start + ending screen
- correct win / lose gamestate detection
- using sprites/tiles of 16x16 pixels (GBA screen size 240x160), able to create [levels with static background of size 10x16 tiles](https://docs.google.com/spreadsheets/d/1p4TTlj3i2GXlGYyscvo-ErYltRo4AOVGPNbYYW5sz0M/edit?gid=0#gid=0)
- support two characters -> can switch players, left/right/jump movements with correct position update, ground + left/right/top obstacles detection, player can stand on each other
- sprite data for basic letters (A-Z)
- first level (kinda completed): 
    - to reach the key, player has to step on each other to reach a tile that is unable to reach by a normal jump from ground
    - got a few gaps that player(s) can fall and die
    - got a bomb in between which when player(s) touch will die
- second level (still in progress):
    - thinking of a moving monster that walks back and forth between two points
    - thinking of having a shield before the key where one player has to press the button to deeactivate the shield, so that the other player can get the key


### Controls
To play, open and run `final_project.gba` using `VisualBoyAdvance.exe`. `()` are keybindings for PC/laptop keyboard. 
| Key                            | Action                                                               |
|--------------------------------|----------------------------------------------------------------------|
| `START (ENTER)` or `A (Z)`     | start game from main menu, go to next level, return to main menu after game has ended |
| `RIGHT`                        | move right                                                           |
| `LEFT`                         | move left                                                            |
| `UP` or `A (Z)`                | jump                                                                 |
| `B (X)`                        | switch player                                                        |

### TODOs
- think of a game title!
- `menu.h`
    - fix start screen, youLose / youWin screen -> refactor into a for loop? ✅
- `sprites.h/.c`
    - fix sprites data (player, bomb, arrow, key, door etc) and color palette data 
- game logic `game.h` and `player.h/.c`: 
    - detect if get key -> key follows player around after obtaining it ✅
    - detect if reach door with key -> WIN ✅
    - detect if hit bomb -> LOSE ✅
    - detect if fall off platform -> LOSE ✅
- tile/collision detection `level.c`:
    - add some tolerance to getTileXXX() -> or math got some issue i think TT ✅ IT'S FINALLY WORKING NOW (I HOPE), basically just added more checks at diff pixels, lmk if noticed any bug
- `player.c`:
    - logic for: (1) players cannot walk into each other, (2) players can step on each other ✅
- ideas: 
    - make two players and press `A` to switch player to control? -> need to refactored `player.h/.c` into a "class"-like structure first (C dont support real class) ✅
    - random falling bombs from the top?
    - button / pushable box? for the two players to co-op
    - bug to fix: sometimes player switched more than once when `A` is pressed once -> add cooldown/delay for button press ✅
    - bug to fix: after restarting the game for a few times, some of the tile elements not rendering properly -> not sure if is a memory overflow thing or what hmmmm ✅ (yes it's an overflow thing cuz `level_sprite_N` was a global variable that keep on adding without resetting)
    - press `UP` and enter door effect to win? both players need to enter door instead of one only?
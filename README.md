### Code Structure
- header/include dependency chain: `main.c -> game.h -> menu.h -> level.h -> mygbalib.h -> player.h -> sprites.h -> gba.h`
- note: need to split `.h` and `.c`, else might get `multiple definitions` error


| File(s)              | Description / Notes                                                                                  |
|----------------------|------------------------------------------------------------------------------------------------------|
| `main.c`             | project entry point                                                                                  |
| `game.h`             | checkbutton, main logic of the game(?) *(hmm still thinking if this is the best way to structure it)*|
| `menu.h`             | simple menu to start a session, display win / lose ending screen                                     |
| `level.h/.c`         | design levels, store and get data for each level, draw level on screen                               |
| `mygbalib.h/.c`      | `drawSprite`, `delSprite`, `fillPalette`, `fillSprites`                                              |
| `player.h/.c`        | player movement (left/right, jump), gravity                                                        |
| `sprites.h/.c`       | sprites info *(if changing `#define` values, update both `.h` and `.c`, technically the `.h` one is being used everywhere else but just putting in `.c` for easy reference)* |
| `gba.h`              | constant definitions                                                                                 |


### Current Progress
- dummy start + ending screen
- using sprites/tiles of 16x16 pixels (GBA screen size 240x160), able to create [levels with static background of size 10x16 tiles](https://docs.google.com/spreadsheets/d/1p4TTlj3i2GXlGYyscvo-ErYltRo4AOVGPNbYYW5sz0M/edit?gid=0#gid=0)
- support single player -> left/right/jump movements with correct ground + left/right obstacles detection


### Controls
To play, open and run `final_project.gba` using `VisualBoyAdvance.exe`.
| Key                 | Action                              |
|---------------------|-------------------------------------|
| `START (ENTER)`     | start game from main menu / return to main menu after game  has ended          |
| `RIGHT`             | move right                          |
| `LEFT`              | move left                           |
| `UP`                | jump                                |
| `A (Z)`             | switch player                       |

### TODOs
- think of a game title!
- `menu.h`
    - fix start screen, youLose / youWin screen -> refactor into a for loop?
- `sprites.h/.c`
    - fix sprites data (player, start screen "title?", "START", "YOU WIN", "YOU LOSE" letters) -> NONE of them is done ahhhh
- game logic `game.h` and `player.h/.c`: 
    - detect if get key -> key follows player around after obtaining it
    - detect if reach door with key -> WIN
    - detect if hit bomb -> LOSE
    - detect if fall off platform -> LOSE
- tile/collision detection `level.c`:
    - add some tolerance to getTileXXX()
- `player.c`:
    - logic for: (1) players cannot walk into each other, (2) players can step on each other
- ideas: 
    - make two players and press `A` to switch player to control? -> need to refactored `player.h/.c` into a "class"-like structure first (C dont support real class) ✅
    - random falling bombs from the top?
    - button / pushable box? for the two players to co-op
    - bug to fix: sometimes player switched more than once when `A` is pressed once -> add debouncing(?)/cooldown/delay ✅
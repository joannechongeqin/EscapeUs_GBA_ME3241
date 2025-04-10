### Code Structure
- header / include dependency chain: `````main.c -> game.h -> menu.h -> level.h -> mygbalib.h -> player.h -> sprites.h -> gba.h`
- note: need to split `.h` and `.c`, else might get `multiple definitions` error


| File(s)              | Description / Notes                                                                                  |
|----------------------|------------------------------------------------------------------------------------------------------|
| `main.c`             | project entry point                                                                                  |
| `game.h`             | checkbutton, main logic of the game(?) *(hmm still thinking if this is the best way to structure it)*|
| `menu.h`             | simple menu to start a session                                                                       |
| `level.h/.c`         | design levels, store and get data for each level, draw level on screen                               |
| `mygbalib.h/.c`      | `drawSprite`, `delSprite`, `fillPalette`, `fillSprites`                                              |
| `player.h/.c`        | player movement (left / right, jump), gravity                                                        |
| `sprites.h/.c`       | sprites info *(if changing `#define` values, update both `.h` and `.c`, technically the `.h` one is being used everywhere else but just putting in `.c` for easy reference)* |
| `gba.h`              | constant definitions                                                                                 |


### TODOs
- think of a game title
- fix sprites data (player, menu screen title and start letters) `sprites.h/.c`
- fix menu screen spacing `menu.h`
- idea: make two players and press `B` to switch player to control? -> need to refactored `player.h/.c` into a "class"-like structure first (C dont support real class)

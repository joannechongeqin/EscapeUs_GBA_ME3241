### Code Structure
- ```main.c```: project entry point
- ```sprites.h/.c```: sprites info *(if wanna change ```#define``` value rmb to change manually in both  in .h and .c, technically the .h one is being used everywhere else but just putting in .c for easy reference)*
- ```game.h```: check button, main logic of the game(?) *(hmm still thinking if this is the best way to structure it)*
- ```menu.h```: simple menu to start a session
- ```player.h/.c```: player movement (left / right, jump), gravity
- ```level.h/.c```: store and get data for each level, draw level on screen

### TODOs
- fix sprites data (player, menu screen title and start letters)
- fix menu spacing
- think of a game title
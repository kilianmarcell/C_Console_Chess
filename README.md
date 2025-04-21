# C Console Chess

A chess game that runs in the console/terminal, now available in both English and Hungarian.

## Translation Information

This chess program was originally written in Hungarian. It has been completely translated to English, including:
- File names
- Variable names
- Function names
- Comments
- User interface text

### File Name Translations

| Hungarian Original | English Translation |
|-------------------|-------------------|
| babu_lepesek.c/h | piece_moves.c/h |
| hasznalati_utmutato.c/h | user_guide.c/h |
| hibauzenet.c/h | error_message.c/h |
| jatszma.c/h | game.c/h |
| jatszma_lepesek.c/h | game_moves.c/h |
| kilepes.c/h | exit.c/h |
| konvertalasok.c/h | conversions.c/h |
| lepes.h | move.h |
| lepes_ellenorzo.c/h | move_validator.c/h |
| mentes_beolvas.c/h | save_load.c/h |
| menu.c | menu_new.c |
| mezo.h | square.h |
| sakk_ellenorzo.c/h | check_validator.c/h |

### Key Data Structure Translations

| Hungarian Name | English Name | Description |
|---------------|-------------|------------|
| Mezo | Square | Represents a square on the chess board |
| Lepes | Move | Represents a chess move in the game |
| tabla | board | The 8x8 chess board |
| feher_kiraly | white_king | Pointer to the white king |
| fekete_kiraly | black_king | Pointer to the black king |
| babu | piece | Chess piece type |
| szin | color | Color of the chess piece |

### Key Function Translations

| Hungarian Name | English Name | Description |
|---------------|-------------|------------|
| uj_jatek | new_game | Starts a new chess game |
| egy_lepes | make_move | Makes a chess move |
| tabla_betolt | load_board | Sets up the chess board |
| aktualis_megjelenit | display_current_board | Displays the current board state |
| elozo_lepesek_kiir | print_previous_moves | Prints previous moves |
| lepes_ellenorzes | validate_move | Validates if a move is legal |
| pozicio_cserel | exchange_positions | Exchanges positions of two squares |
| paraszt_cserelese | promote_pawn | Handles pawn promotion |
| lo_lepes | knight_move | Validates knight moves |
| atlosan_jo_e | is_diagonal_valid | Validates diagonal moves |
| sakk_ellenoriz | validate_check | Checks if a king is in check |
| jatek_mentese | save_game | Saves the current game |
| jatek_betolt | load_game | Loads a saved game |

## Building the Program

### Using CMake

```bash
mkdir build
cd build
cmake ..
make
```

This will build both versions:
- `chess_english` - The English version
- `chess_hungarian` - The Hungarian version

### Using GCC directly

For the English version:

```bash
gcc main_english.c chess_constants.c board_setup.c game.c piece_moves.c move_validator.c check_validator.c game_moves.c conversions.c save_load.c memory_utils.c exit.c error_message.c user_guide.c menu_new.c util.c position_exchange.c pawn_promotion.c -o chess_english
```

For the original Hungarian version:

```bash
gcc main.c chess_constants.c jatszma.c babu_lepesek.c lepes_ellenorzo.c sakk_ellenorzo.c jatszma_lepesek.c konvertalasok.c mentes_beolvas.c kilepes.c hibauzenet.c hasznalati_utmutato.c menu.c util.c -o chess_hungarian
```

## Playing the Game

Run the program and follow the on-screen instructions:

1. New Game - Starts a new chess game
2. Load Game - Loads a previously saved game
3. User Guide - Shows how to play the game
9. Exit - Exits the program

When playing, enter moves in algebraic notation, such as:
```
e2 e4
```
to move the piece from e2 to e4.

## Special Commands During Game

- Type '1' to save the game
- Type '2' to take back a move
- Type '9' to exit to the main menu

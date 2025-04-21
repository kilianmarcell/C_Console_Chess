cmake_minimum_required(VERSION 3.10)
project(Chess C)

set(CMAKE_C_STANDARD 99)

# English version source files
set(ENGLISH_SOURCES
    main_english.c
    chess_constants.c
    board_setup.c
    game.c
    piece_moves.c
    move_validator.c
    check_validator.c
    game_moves.c
    conversions.c
    save_load.c
    memory_utils.c
    exit.c
    error_message.c
    user_guide.c
    menu_new.c
    util.c
    position_exchange.c
    pawn_promotion.c
)

# Hungarian version source files (original)
set(HUNGARIAN_SOURCES
    main.c
    chess_constants.c
    jatszma.c
    babu_lepesek.c
    lepes_ellenorzo.c
    sakk_ellenorzo.c
    jatszma_lepesek.c
    konvertalasok.c
    mentes_beolvas.c
    kilepes.c
    hibauzenet.c
    hasznalati_utmutato.c
    menu.c
    util.c
)

# Create the English version executable
add_executable(chess_en ${ENGLISH_SOURCES})

# Create the Hungarian version executable
add_executable(chess_hu ${HUNGARIAN_SOURCES})

# Set output names
set_target_properties(chess_en PROPERTIES OUTPUT_NAME "chess_english")
set_target_properties(chess_hu PROPERTIES OUTPUT_NAME "chess_hungarian")

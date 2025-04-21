// English Chess - Build File
// Compile with:
// gcc main_new.c chess_constants.c square.c move.c game.c piece_moves.c move_validator.c check_validator.c game_moves.c conversions.c save_load.c memory_utils.c exit.c error_message.c user_guide.c menu_new.c util.c board_setup.c position_exchange.c pawn_promotion.c -o chess.exe

// This file lists all the translated source files needed to build the English version of the chess program

/*
Original Hungarian Files -> English Translations:
-------------------------------------------------
babu_lepesek.c/h         -> piece_moves.c/h
hasznalati_utmutato.c/h  -> user_guide.c/h
hibauzenet.c/h           -> error_message.c/h
jatszma.c/h              -> game.c/h
jatszma_lepesek.c/h      -> game_moves.c/h
kilepes.c/h              -> exit.c/h
konvertalasok.c/h        -> conversions.c/h
lepes.h                  -> move.h
lepes_ellenorzo.c/h      -> move_validator.c/h
mentes_beolvas.c/h       -> save_load.c/h
menu.c/h                 -> menu_new.c (still using menu.h)
mezo.h                   -> square.h
sakk_ellenorzo.c/h       -> check_validator.c/h

New files:
-------------------------------------------------
board_setup.c            -> Contains load_board() function (formerly tabla_betolt())
position_exchange.c      -> Contains exchange_positions() function (formerly pozicio_cserel())
pawn_promotion.c         -> Contains promote_pawn() function (formerly paraszt_cserelese())
*/

#!/bin/bash
# Build script for Console Chess program (Unix/Linux version)

echo "Console Chess - Build Script"
echo ""
echo "Select which version to build:"
echo "1. English version"
echo "2. Hungarian version"
echo "3. Build both versions"

read -p "Enter your choice (1-3): " choice

case $choice in
    1)
        echo "Building English version..."
        gcc main.c chess_constants.c board_setup.c game.c piece_moves.c move_validator.c check_validator.c game_moves.c conversions.c save_load.c memory_utils.c exit.c error_message.c user_guide.c menu.c util.c position_exchange.c pawn_promotion.c king_moves.c -o chess
        echo "English version built: chess"
        ;;
    *)
        echo "Only English version is available now"
        ;;
        echo "Both versions built:"
        echo "- chess_english"
        echo "- chess_hungarian"
        ;;
    *)
        echo "Invalid choice!"
        ;;
esac

echo ""
read -p "Press Enter to continue..."

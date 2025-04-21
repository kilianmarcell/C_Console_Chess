#ifndef MOVE_H_INCLUDED
#define MOVE_H_INCLUDED

// This struct stores a chess move (was "Lepes")
typedef struct Move {
     int from_x;      // was "honnan_x"
     int from_y;      // was "honnan_y"
     int to_x;        // was "hova_x"
     int to_y;        // was "hova_y"
     char captured_color;  // was "leutott_szin"
     char captured_piece;  // was "leutott_babu"
     struct Move *previous;   // was "elozo"
} Move;

#endif

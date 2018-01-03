//Projet Rabidja - SDL 2.0
//Partie2_06Rabidja_LvlEditor
//defs.h

#ifndef DEF_DEFS
#define DEF_DEFS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>

/* On inclut les libs supplémentaires */
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h >

// Lageur des commande de l'éditeur
#define EDITOR_TOOLS_WIDTH 380

// Largeur de l'image de l'éditeur
#define EDITOR_IMAGE_WIDTH 1020

// AHuteur de la barre de navaigation en bas de l'écran
#define SCROLLBAR_HEIGHT 32

// Hauteur des onglets
#define TABS_HEIGHT 32

/* Valeur RGB pour la transparence (canal alpha) */
#define TRANS_R 255
#define TRANS_G 0
#define TRANS_B 255

/* Taille maxi de la map : on voit large : 400 x 300 tiles */
#define MAX_MAP_X 400
#define MAX_MAP_Y 150
#define MAX_CTRL_Z 16

/* Taille d'une tile (32 x 32 pixels) */
#define TILE_SIZE 32

// Nombre de Tiles à l'horizontal et à la vertical dans le Tileset
#define NB_TILES_H 10
#define NB_TILES_V 10

/* N° de la tile transparente */
#define BLANK_TILE 0

/* MAX_TILES = numéro de la dernière tile */
#define MAX_TILES 140

 //Nombre maximum de levels
 #define LEVEL_MAX   20

 //Nombre max de tilesets
 #define MAX_TILESETS   1

 //Durée des messages
 #define DUREE_MESSAGE   60

 //Action à effectuer après la message box
 #define LOAD 1
 #define SAVE 2
 #define LEVELUP 3
 #define LEVELDOWN 4
 #define RESET 5
 #define PASTE 6
 #define QUIT 7

// Zoom minimum, maximum et pallier (en pourcent)
#define MAP_ZOOM_MIN 10			// ATTENTION ! MAP_ZOOM_MIN doit toujours être >= 4 ! (sinon on obtient une taille de Tile de 0)
#define MAP_ZOOM_MAX 100
#define MAP_ZOOM_STEP 10

// TILE utilisée pour dessiner les limites de la Map lors du dézoom
#define TILE_MAP_LIMIT 129		// Tile rouge

// Numéro des Tiles dans le Tileset
#define TILE_TREE_1_A 3
#define TILE_TREE_1_B 5
#define TILE_TREE_2_A 6
#define TILE_TREE_2_B 8
#define TILE_PALM_1_A 13
#define TILE_PALM_1_B 16
#define TILE_PALM_2_A 14
#define TILE_PALM_2_B 15
#define TILE_PALM_3_A 17
#define TILE_PALM_3_B 18
#define TILE_PALM_4_A 19
#define TILE_PALM_4_B 20
#define TILE_WALL_1_A 27
#define TILE_WALL_1_B 29
#define TILE_WALL_2_A 32
#define TILE_WALL_2_B 34
#define TILE_DOOR_1_A 36
#define TILE_DOOR_1_B 37
#define TILE_SLOPE_1_A 56
#define TILE_SLOPE_1_B 58
#define TILE_SLOPE_2_A 59
#define TILE_SLOPE_2_B 61
#define TILE_SLOPE_3_A 62
#define TILE_SLOPE_3_B 64
#define TILE_SLOPE_4_A 67
#define TILE_SLOPE_4_B 68
#define TILE_SLOPE_5_A 69
#define TILE_SLOPE_5_B 72
#define TILE_SLOPE_6_A 70
#define TILE_SLOPE_6_B 71
#define TILE_ROOF_1_A 80
#define TILE_ROOF_1_B 82
#define TILE_DECOR_1_A 83
#define TILE_DECOR_1_B 85
#define TILE_GROUND_1_A 91
#define TILE_GROUND_1_B 92
#define TILE_DECOR_2_A 104
#define TILE_DECOR_2_B 105
#define TILE_DECOR_3_A 106
#define TILE_DECOR_3_B 107
#define TILE_GROUND_2_A 116
#define TILE_GROUND_2_B 117
#define TILE_SLOPE_7_A 118
#define TILE_SLOPE_7_B 119
#define TILE_GROUND_3_A 120
#define TILE_GROUND_3_B 121
#define TILE_WALL_3_A 122
#define TILE_WALL_3_B 123
#define TILE_LIGHT_1_A 142
#define TILE_LIGHT_1_B 144




#endif

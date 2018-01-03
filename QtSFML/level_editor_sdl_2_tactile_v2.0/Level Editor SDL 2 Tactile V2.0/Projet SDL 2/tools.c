#include "tools.h"


// Gestion des Flips
const int FLIP_HORIZONTAL = 0;
const int FLIP_VERTICAL = 1;
int smartMove(int tileValue,  int flipType);

// Gestion du CTRL+Z
//const int MAX_CTRL_Z = 16;		// Nombre d'actions maximum mémorisées -> Remplacée par une def pour que ça compile en C classique
                                    //La const ne suffit pas en C car elle est read only mais peut quand même être modifiée, ce qui
                                    //rendrait le tableau (la matrice) instable.
int mActualPos = -1;			// Position du dernier élément mémorisé
int mBackPos = 0;				// Position précédente à restorer
int mTabFull = 0;				// Pour savoir si le tableau CTRL+Z est rempli
int mNbBack = 0;				// Nombre de back réalisé
int mNbFoward = 0;				// Nombre de Forward réalisable

// Tableau contenant les précédents états
int memorizeMapBackground[MAX_CTRL_Z][MAX_MAP_Y][MAX_MAP_X];
int memorizeMapAction[MAX_CTRL_Z][MAX_MAP_Y][MAX_MAP_X];
int memorizeMapForeground[MAX_CTRL_Z][MAX_MAP_Y][MAX_MAP_X];


/*
 * Ajoute une colonne vide après à la position données
 * et décale tout le reste vers la droite
 */
void addEmptyColumn(int xPos){

    int x, y;

	// On part le la fin vers la colonne cible
	for (x = MAX_MAP_X-1 ; x >= xPos ; x--)
    {
        for (y = 0; y < MAX_MAP_Y; y++)
        {
            if(x > xPos){
				// On décale chaque Tile vers la droite
				map.tileBackground[y][x] = map.tileBackground[y][x-1];
				map.tileAction[y][x] = map.tileAction[y][x-1];
				map.tileForeground[y][x] = map.tileForeground[y][x-1];
			}else{
				// On met une Tile vide à l'endroit d'insertion
				map.tileBackground[y][x] = 0;
				map.tileAction[y][x] = 0;
				map.tileForeground[y][x] = 0;
			}
        }
    }
}

/*
 * Supprime une colonne à la position données
 * et décale tout le reste vers la gauche
 */
void deleteColumn(int xPos){

    int x, y;

	for (x = xPos ; x < MAX_MAP_X ; x++)
    {
        for (y = 0; y < MAX_MAP_Y; y++)
        {
            if(x < MAX_MAP_X-2){
				// On décale chaque Tile vers la gauche
				map.tileBackground[y][x] = map.tileBackground[y][x+1];
				map.tileAction[y][x] = map.tileAction[y][x+1];
				map.tileForeground[y][x] = map.tileForeground[y][x+1];
			}else{
				// On met une Tile vide à la fin
				map.tileBackground[y][x] = 0;
				map.tileAction[y][x] = 0;
				map.tileForeground[y][x] = 0;
			}
        }
    }
}


/*
 * Ajoute une ligne vide après à la position données
 * et décale tout le reste vers le bas
 */
void addEmptyRow(int yPos){

    int x, y;

	// On part le la fin vers la ligne cible
	for (y = MAX_MAP_Y-1 ; y >= yPos ; y--)
    {
        for (x = 0; x < MAX_MAP_X; x++)
        {
            if(y > yPos){
				// On décale chaque Tile vers le bas
				map.tileBackground[y][x] = map.tileBackground[y-1][x];
				map.tileAction[y][x] = map.tileAction[y-1][x];
				map.tileForeground[y][x] = map.tileForeground[y-1][x];
			}else{
				// On met une Tile vide à l'endroit d'insertion
				map.tileBackground[y][x] = 0;
				map.tileAction[y][x] = 0;
				map.tileForeground[y][x] = 0;
			}
        }
    }
}

/*
 * Supprime une ligne à la position données
 * et décale tout le reste vers le haut
 */
void deleteRow(int yPos){

    int x, y;

	for (y = yPos ; y < MAX_MAP_Y ; y++)
    {
        for (x = 0; x < MAX_MAP_X; x++)
        {
            if(x < MAX_MAP_Y-2){
				// On décale chaque Tile vers la gauche
				map.tileBackground[y][x] = map.tileBackground[y+1][x];
				map.tileAction[y][x] = map.tileAction[y+1][x];
				map.tileForeground[y][x] = map.tileForeground[y+1][x];
			}else{
				// On met une Tile vide à la fin
				map.tileBackground[y][x] = 0;
				map.tileAction[y][x] = 0;
				map.tileForeground[y][x] = 0;
			}
        }
    }
}


// Remplie la zone passée en paramètre avec la Tile active
void fillWith(int xStart, int yStart, int xEnd, int yEnd){

    int x, y;

	for (y = yStart ; y <= yEnd ; y++)
    {
        for (x = xStart; x <= xEnd; x++)
        {
			// En fonction de la couche active
			if ( input.layerDrawn == 1 ){
				map.tileAction[y-0][x] = cursor.tileID; 		// -1 à cause des onglets
			}
			else if ( input.layerDrawn == 2 ){
				map.tileBackground[y-0][x] = cursor.tileID;
			}
			else if ( input.layerDrawn == 3 ){
				map.tileForeground[y-0][x] = cursor.tileID;
			}
        }
    }
}

/*
 * Inverse toutes les Tiles de la sélection sur le plan vertical
 */
void flipVertical(int fromX, int fromY, int toX, int toY){

	int temp, newPos;

	// Nombre d'éléments dans la sélection
	int nbElement = toY - fromY + 1;
	if (nbElement <= 0) { return; }
	int newToY = toY - (nbElement / 2);

	for(int i = fromY ; i <= newToY ; i++){
		for(int j = fromX ; j <= toX ; j++){
			// En fonction de la couche active (ou toutes si elles sont toutes actives !)
			if ( input.layerDrawn == 1 || input.layerDrawn == 4){
				newPos = fromY + nbElement - (i - fromY) - 1;
				temp = map.tileAction[newPos][j];
				map.tileAction[newPos][j] = map.tileAction[i][j];
				map.tileAction[i][j] = temp;
			}
			if ( input.layerDrawn == 2 || input.layerDrawn == 4){
				newPos = fromY + nbElement - (i - fromY) - 1;
				temp = map.tileBackground[newPos][j];
				map.tileBackground[newPos][j] = map.tileBackground[i][j];
				map.tileBackground[i][j] = temp;
			}
			if ( input.layerDrawn == 3 || input.layerDrawn == 4){
				newPos = fromY + nbElement - (i - fromY) - 1;
				temp = map.tileForeground[newPos][j];
				map.tileForeground[newPos][j] = map.tileForeground[i][j];
				map.tileForeground[i][j] = temp;
			}
		}
	}
}
/*
 * Inverse toutes les Tiles de la sélection sur le plan horizontal
 */
void flipHorizontal(int fromX, int fromY, int toX, int toY){

	int temp, newPos;

	// Nombre d'éléments dans la sélection
	int nbElement = toX - fromX + 1;
	if (nbElement <= 0) { return; }
	int newToX = toX - (nbElement / 2);

	for(int i = fromY ; i <= toY ; i++){
		for(int j = fromX ; j <= newToX ; j++){
			// En fonction de la couche active
			if ( input.layerDrawn == 1 || input.layerDrawn == 4){
				newPos = fromX + nbElement - (j - fromX) - 1;
				temp = smartMove(map.tileAction[i][newPos], FLIP_HORIZONTAL);
				map.tileAction[i][newPos] = smartMove(map.tileAction[i][j], FLIP_HORIZONTAL);
				map.tileAction[i][j] = temp;
			}
			if ( input.layerDrawn == 2 || input.layerDrawn == 4){
				newPos = fromX + nbElement - (j - fromX) - 1;
				temp = smartMove(map.tileBackground[i][newPos], FLIP_HORIZONTAL);
				map.tileBackground[i][newPos] = smartMove(map.tileBackground[i][j], FLIP_HORIZONTAL);
				map.tileBackground[i][j] = temp;
			}
			if ( input.layerDrawn == 3 || input.layerDrawn == 4){
				newPos = fromX + nbElement - (j - fromX) - 1;
				temp = smartMove(map.tileForeground[i][newPos], FLIP_HORIZONTAL);
				map.tileForeground[i][newPos] = smartMove(map.tileForeground[i][j], FLIP_HORIZONTAL);
				map.tileForeground[i][j] = temp;
			}
		}
	}
}

// Fonction permettant d'échanger intelligement les Tiles lors du Flip
// (ex : pour les toits, on prend la Tile avec la pente opposée)
int smartMove(int tileValue, int flipType){
	int newTile = tileValue;

	if(flipType == FLIP_HORIZONTAL){

		switch(tileValue){

			case TILE_TREE_1_A:
				newTile = TILE_TREE_1_B;
				break;
			case TILE_TREE_1_B:
				newTile = TILE_TREE_1_A;
				break;

			case TILE_TREE_2_A:
				newTile = TILE_TREE_2_B;
				break;
			case TILE_TREE_2_B:
				newTile = TILE_TREE_2_A;
				break;

			case TILE_PALM_1_A:
				newTile = TILE_PALM_1_B;
				break;
			case TILE_PALM_1_B:
				newTile = TILE_PALM_1_A;
				break;

			case TILE_PALM_2_A:
				newTile = TILE_PALM_2_B;
				break;
			case TILE_PALM_2_B:
				newTile = TILE_PALM_2_A;
				break;

			case TILE_PALM_3_A:
				newTile = TILE_PALM_3_B;
				break;
			case TILE_PALM_3_B:
				newTile = TILE_PALM_3_A;
				break;

			case TILE_PALM_4_A:
				newTile = TILE_PALM_4_B;
				break;
			case TILE_PALM_4_B:
				newTile = TILE_PALM_4_A;
				break;

			case TILE_WALL_1_A:
				newTile = TILE_WALL_1_B;
				break;
			case TILE_WALL_1_B:
				newTile = TILE_WALL_1_A;
				break;

			case TILE_WALL_2_A:
				newTile = TILE_WALL_2_B;
				break;
			case TILE_WALL_2_B:
				newTile = TILE_WALL_2_A;
				break;

			case TILE_DOOR_1_A:
				newTile = TILE_DOOR_1_B;
				break;
			case TILE_DOOR_1_B:
				newTile = TILE_DOOR_1_A;
				break;

			case TILE_SLOPE_1_A:
				newTile = TILE_SLOPE_1_B;
				break;
			case TILE_SLOPE_1_B:
				newTile = TILE_SLOPE_1_A;
				break;

			case TILE_SLOPE_2_A:
				newTile = TILE_SLOPE_2_B;
				break;
			case TILE_SLOPE_2_B:
				newTile = TILE_SLOPE_2_A;
				break;

			case TILE_SLOPE_3_A:
				newTile = TILE_SLOPE_3_B;
				break;
			case TILE_SLOPE_3_B:
				newTile = TILE_SLOPE_3_A;
				break;

			case TILE_SLOPE_4_A:
				newTile = TILE_SLOPE_4_B;
				break;
			case TILE_SLOPE_4_B:
				newTile = TILE_SLOPE_4_A;
				break;

			case TILE_SLOPE_5_A:
				newTile = TILE_SLOPE_5_B;
				break;
			case TILE_SLOPE_5_B:
				newTile = TILE_SLOPE_5_A;
				break;

			case TILE_SLOPE_6_A:
				newTile = TILE_SLOPE_6_B;
				break;
			case TILE_SLOPE_6_B:
				newTile = TILE_SLOPE_6_A;
				break;

			case TILE_ROOF_1_A:
				newTile = TILE_ROOF_1_B;
				break;
			case TILE_ROOF_1_B:
				newTile = TILE_ROOF_1_A;
				break;

			case TILE_DECOR_1_A:
				newTile = TILE_DECOR_1_B;
				break;
			case TILE_DECOR_1_B:
				newTile = TILE_DECOR_1_A;
				break;

			case TILE_GROUND_1_A:
				newTile = TILE_GROUND_1_B;
				break;
			case TILE_GROUND_1_B:
				newTile = TILE_GROUND_1_A;
				break;

			case TILE_DECOR_2_A:
				newTile = TILE_DECOR_2_B;
				break;
			case TILE_DECOR_2_B:
				newTile = TILE_DECOR_2_A;
				break;

			case TILE_DECOR_3_A:
				newTile = TILE_DECOR_3_B;
				break;
			case TILE_DECOR_3_B:
				newTile = TILE_DECOR_3_A;
				break;

			case TILE_GROUND_2_A:
				newTile = TILE_GROUND_2_B;
				break;
			case TILE_GROUND_2_B:
				newTile = TILE_GROUND_2_A;
				break;

			case TILE_SLOPE_7_A:
				newTile = TILE_SLOPE_7_B;
				break;
			case TILE_SLOPE_7_B:
				newTile = TILE_SLOPE_7_A;
				break;

			case TILE_GROUND_3_A:
				newTile = TILE_GROUND_3_B;
				break;
			case TILE_GROUND_3_B:
				newTile = TILE_GROUND_3_A;
				break;

			case TILE_WALL_3_A:
				newTile = TILE_WALL_3_B;
				break;
			case TILE_WALL_3_B:
				newTile = TILE_WALL_3_A;
				break;

			case TILE_LIGHT_1_A:
				newTile = TILE_LIGHT_1_B;
				break;
			case TILE_LIGHT_1_B:
				newTile = TILE_LIGHT_1_A;
				break;

		}
	}
	return newTile;
}


// Si on appuie sur [Suppr] ([del]), on "supprime" la Tile active ou la sélection en insérant une Tile vide
void deleteTile(int fromX, int fromY, int toX, int toY){

	for (int y = fromY ; y <= toY ; y++)
    {
        for (int x = fromX; x <= toX; x++)
        {
			// En fonction de la couche active
			if ( input.layerDrawn == 1 || input.layerDrawn == 4){
				map.tileAction[y][x] = 0;
			}
			if ( input.layerDrawn == 2 || input.layerDrawn == 4 ){
				map.tileBackground[y][x] = 0;
			}
			if ( input.layerDrawn == 3 || input.layerDrawn == 4 ){
				map.tileForeground[y][x] = 0;
			}
        }
    }

}


/***********************/
/*  GESTION DU CTRL+Z  */
/***********************/

// Memorise l'état de la Map
void memorizeMapState()
{
	// Controle (Debug)
	/*if(mActualPos < -1 || mActualPos > MAX_CTRL_Z){
		int stopMe = 1;
	}*/

	// On incrémente tant que le tableau n'est pas plein
	if(mActualPos+1 < MAX_CTRL_Z){
		mActualPos++;
	}
	// Si le tableau est plein, on boucle
	else{
		if(mActualPos + 1 >= MAX_CTRL_Z){
			mActualPos = mActualPos + 1 - MAX_CTRL_Z;
		}else{
			mActualPos++;
		}
		mTabFull = 1;
	}

	// On mémorise l'état en cours
	for(int y = 0; y < MAX_MAP_Y; y++)
    {
        for(int x = 0; x < MAX_MAP_X; x++)
        {
            memorizeMapBackground[mActualPos][y][x] = map.tileBackground[y][x];
			memorizeMapAction[mActualPos][y][x] = map.tileAction[y][x];
			memorizeMapForeground[mActualPos][y][x] = map.tileForeground[y][x];
        }
    }

	// On réinitialise les Back
	mNbBack = 0;
}

// Restore la Map dans l'état précédent mémorisé
// Renvoie 1 si cela a été possible, sinon 0.
int control_Z(){

	// Position à pointer dans les tableaux
	mNbBack++;
	mBackPos = mActualPos - 1;

	// Contrôle de la position, en fonction de l'état des tableaux : plein ou non
	if(mTabFull == 0){
		if(mBackPos < 0){
			printf("No more back \n");
			mNbBack--;
			return 0;
		}
		// On corrige la position actuelle
		mActualPos--;
	}else{
		if(mNbBack >= MAX_CTRL_Z){
			printf("No more back \n");
			mNbBack = MAX_CTRL_Z-1;
			return 0;
		}
		if(mBackPos < 0){
			mBackPos  = mBackPos + MAX_CTRL_Z;
		}

		// On corrige la position actuelle
		mActualPos--;
		if(mActualPos < 0){
			mActualPos = MAX_CTRL_Z - 1;
		}
	}

	// On restore l'état précédent
	for(int y = 0; y < MAX_MAP_Y; y++)
    {
        for(int x = 0; x < MAX_MAP_X; x++)
        {
            map.tileBackground[y][x] = memorizeMapBackground[mBackPos][y][x];
			map.tileAction[y][x] = memorizeMapAction[mBackPos][y][x];
			map.tileForeground[y][x] = memorizeMapForeground[mBackPos][y][x];
        }
    }
	return 1;
}

// Restore la Map dans l'état suivant mémorisé
// Renvoie 1 si cela a été possible, sinon 0.
int control_Y(){

	// Il y a autant de Foward qu'il y a eu de Back
	mNbFoward = mNbBack;

	// Contrôle
	if(mNbFoward <= 0){
		printf("No more Foward \n");
		return 0;
	}

	// Étant donné qu'on a avancé, on rend Back disponible
	mNbBack--;

	// En fonction de l'état des tableaux
	if(mTabFull == 0){
		mActualPos++;
	}else{
		if(mActualPos + 1 >= MAX_CTRL_Z){
			mActualPos = mActualPos + 1 - MAX_CTRL_Z;
		}else{
			mActualPos++;
		}
	}

	// On restore l'état suivant
	for(int y = 0; y < MAX_MAP_Y; y++)
    {
        for(int x = 0; x < MAX_MAP_X; x++)
        {
            map.tileBackground[y][x] = memorizeMapBackground[mActualPos][y][x];
			map.tileAction[y][x] = memorizeMapAction[mActualPos][y][x];
			map.tileForeground[y][x] = memorizeMapForeground[mActualPos][y][x];
        }
    }
	return 1;
}

// Remise à zéro de la mémoire des actions réalisées
void resetMemorizeMapState()
{
	mTabFull = 0;
	mActualPos = -1;
	mBackPos = 0;
	mNbBack = 0;
	mNbFoward = 0;
	memorizeMapState();
}

//Projet Rabidja - SDL 2.0
//Partie2_06Rabidja_LvlEditor
//map.c

#include "map.h"


void loadMap(char *name)
{
    int x, y;
    FILE *fp;

    fp = fopen(name, "rb");

    /* Si on ne peut pas ouvrir le fichier, on quitte */
    if (fp == NULL)
    {
        printf("Failed to open map %s\n", name);
        exit(1);
    }

    /* Lit les données du fichier dans la map */

	/* Lit les coordonnées de début du joueur */
	fscanf(fp, "%d", &map.beginx);
	fscanf(fp, "%d", &map.beginy);

	/* Read the number of the tileset */
	fscanf(fp, "%d", &map.tilesetAffiche);


    for (y = 0; y < MAX_MAP_Y; y++)
    {
        for (x = 0; x < MAX_MAP_X; x++)
        {
            /* On lit le numéro de la tile et on le copie dans notre tableau */
            fscanf(fp, "%d", &map.tileAction[y][x]);
        }
    }

    //Deuxième couche de tiles
    for (y = 0; y < MAX_MAP_Y; y++)
    {
        for (x = 0; x < MAX_MAP_X; x++)
        {
            /* On lit le numéro de la tile et on le copie dans notre tableau */
            fscanf(fp, "%d", &map.tileBackground[y][x]);
        }
    }

	//Troisième couche de tiles
	for (y = 0; y < MAX_MAP_Y; y++)
	{
		for (x = 0; x < MAX_MAP_X; x++)
		{
			/* On lit le numéro de la tile et on le copie dans notre tableau */
			fscanf(fp, "%d", &map.tileForeground[y][x]);
		}
	}

    /* On change ces coordonnées pour qu'on puisse scroller et éditer la map
	au maximum */

	map.maxX = MAX_MAP_X * TILE_SIZE;
	map.maxY = MAX_MAP_Y * TILE_SIZE;

    /* Remet à 0 les coordonnées de départ de la map */
    map.startX = map.startY = 0;

    /* Et on referme le fichier */
    fclose(fp);

}


void saveMap(char *name)
{
	int x, y;
	FILE *fp;

	fp = fopen(name, "wb");

	/* Si on ne peut pas charger la map, on quitte */

	if (fp == NULL)
	{
		printf("Failed to open map %s\n", name);

		exit(1);
	}

	/* Sauve les coordonnées du début du niveau */
    fprintf(fp, "%d ", map.beginx);
    fprintf(fp, "%d ", map.beginy);

    /* Sauve le numéro du tileset */
    fprintf(fp, "%d ", map.tilesetAffiche);

    /* Sauvegarde la map : couche 1 */

	for (y=0;y<MAX_MAP_Y;y++)
	{
		for (x=0;x<MAX_MAP_X;x++)
		{
			fprintf(fp, "%d ", map.tileAction[y][x]);
		}

		fprintf(fp, "\n");
	}

	/* Sauvegarde la map : couche 2 */
    for (y = 0; y < MAX_MAP_Y; y++)
    {
        for (x = 0; x < MAX_MAP_X; x++)
        {
            fprintf(fp, "%d ", map.tileBackground[y][x]);
        }

        fprintf(fp, "\n");
    }

    /* Sauvegarde la map : couche 3 */
    for (y = 0; y < MAX_MAP_Y; y++)
    {
        for (x = 0; x < MAX_MAP_X; x++)
        {
            fprintf(fp, "%d ", map.tileForeground[y][x]);
        }

        fprintf(fp, "\n");
    }

	/* On referme le fichier */

	fclose(fp);
}


void reinitMap()
{
	int x, y;

    /* On réinitialise les coordonnées du début du niveau */
    map.beginx = 0;
    map.beginy = 0;

    /* On réinitialise le numéro du tileset */
    map.tilesetAffiche = 1;


    /* Remplit la map de 0 (3 couches) */
    for (y = 0; y < MAX_MAP_Y; y++)
    {
        for (x = 0; x < MAX_MAP_X; x++)
        {
            map.tileAction[y][x] = 0;
        }
    }

    //Deuxième couche de tiles
    for (y = 0; y < MAX_MAP_Y; y++)
    {
        for (x = 0; x < MAX_MAP_X; x++)
        {
            map.tileBackground[y][x] = 0;
        }
    }

	//Troisième couche de tiles
	for (y = 0; y < MAX_MAP_Y; y++)
	{
		for (x = 0; x < MAX_MAP_X; x++)
		{
			map.tileForeground[y][x] = 0;
		}
	}

}


void drawMap(int layerAffichee, int transparence)
{
    int x, y, mapX, x1, x2, mapY, y1, y2, xsource, ysource, a;

	// Taille des Tiles en fonction du ZOOM
	map.newTileSize = TILE_SIZE * (map.zoom/100.0);

    /* On initialise mapX à la 1ère colonne qu'on doit blitter.
    Celle-ci correspond au x de la map (en pixels) divisés par la taille d'une tile (32)
    pour obtenir la bonne colonne de notre map
    Exemple : si x du début de la map = 1026, on fait 1026 / 32
    et on sait qu'on doit commencer par afficher la 32eme colonne de tiles de notre map */
    mapX = map.startX / map.newTileSize;

    /* Coordonnées de départ pour l'affichage de la map : permet
    de déterminer à quels coordonnées blitter la 1ère colonne de tiles au pixel près
    (par exemple, si la 1ère colonne n'est visible qu'en partie, on devra commencer à blitter
    hors écran, donc avoir des coordonnées négatives - d'où le -1). */
	x1 = (map.startX % map.newTileSize) * 1;


    /* Calcul des coordonnées de la fin de la map : jusqu'où doit-on blitter ?
    Logiquement, on doit aller à x1 (départ) + SCREEN_WIDTH (la largeur de l'écran).
    Mais si on a commencé à blitter en dehors de l'écran la première colonne, il
    va falloir rajouter une autre colonne de tiles sinon on va avoir des pixels
    blancs. C'est ce que fait : x1 == 0 ? 0 : TILE_SIZE qu'on pourrait traduire par:
    if(x1 != 0)
        x2 = x1 + SCREEN_WIDTH + TILE_SIZE , mais forcément, c'est plus long ;)*/
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

    /* On fait exactement pareil pour calculer y */
    mapY = map.startY / map.newTileSize;
	y1 = (map.startY % map.newTileSize) * 1;
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

    //Layer 1 :
    if(layerAffichee == LAYER_ACTION)
    {
        /* Dessine la carte en commençant par startX et startY */

        /* On dessine ligne par ligne en commençant par y1 (0) jusqu'à y2 (480)
        A chaque fois, on rajoute TILE_SIZE (donc 32), car on descend d'une ligne
        de tile (qui fait 32 pixels de hauteur) */
        for (y = y1; y < y2; y += map.newTileSize)
        {
            /* A chaque début de ligne, on réinitialise mapX qui contient la colonne
            (0 au début puisqu'on ne scrolle pas) */
            mapX = map.startX / map.newTileSize;

            /* A chaque colonne de tile, on dessine la bonne tile en allant
            de x = 0 à x = 640 */
            for (x = x1; x < x2; x += map.newTileSize)
            {

                // Si la partie négative en haut/gauche de la Map est affichée, on dessine la limite
				if(mapY >= 0 && mapX >= 0){
					// Suivant le numéro de notre tile, on découpe le tileset (a = le numéro de la tile)
					a = map.tileAction[mapY][mapX];
				}else{
					a = TILE_MAP_LIMIT;
				}

                /* Calcul pour obtenir son y (pour un tileset de 10 tiles
                par ligne, d'où le NB_TILES_V */
                ysource = a / NB_TILES_H * TILE_SIZE;
                /* Et son x */
                xsource = a % NB_TILES_V * TILE_SIZE;

                /* Fonction qui blitte la bonne tile au bon endroit */
                if(transparence == 1){
					drawTileZoomed(map.tileSetTransparent, x, y + TABS_HEIGHT, xsource, ysource, map.newTileSize);
				}else{
					drawTileZoomed(map.tileSet, x, y + TABS_HEIGHT, xsource, ysource, map.newTileSize);
				}
                mapX++;

				// Si on dépasse la taille max affichable (à cause du Zoom), on remplie le "hors-limite" de la Map avec une Tile rouge
				if(mapX > MAX_MAP_X){
					a = TILE_MAP_LIMIT;  // Tile rouge
					ysource = a / NB_TILES_H * TILE_SIZE;
					xsource = a % NB_TILES_V * TILE_SIZE;
					drawTileZoomed(map.tileSet, x, y + TABS_HEIGHT, xsource, ysource, map.newTileSize);
				}

            }

            mapY++;

			// Si on dépasse la taille max affichable (à cause du Zoom), on remplie le "hors-limite" de la Map avec une Tile rouge
			if(mapY > MAX_MAP_Y){
				mapX = 0;
				for (x = x1; x < x2; x += map.newTileSize)
				{
					a = TILE_MAP_LIMIT;  // Tile rouge
					ysource = a / NB_TILES_H * TILE_SIZE;
					xsource = a % NB_TILES_V * TILE_SIZE;
					drawTileZoomed(map.tileSet, x, y + TABS_HEIGHT, xsource, ysource, map.newTileSize);
					mapX++;
				}
			}
        }
    }

    //Layer 2 :
    else if(layerAffichee == LAYER_BACKGROUD )
    {
        //Deuxième couche de tiles ;)
        for (y = y1; y < y2; y += map.newTileSize)
        {
            mapX = map.startX / map.newTileSize;

            for (x = x1; x < x2; x += map.newTileSize)
            {
				if(mapY >= 0 && mapX >= 0){
					a = map.tileBackground[mapY][mapX];
				}else{
					a = TILE_MAP_LIMIT;
				}
                ysource = a / NB_TILES_H * TILE_SIZE;
                xsource = a % NB_TILES_V * TILE_SIZE;
                if(transparence == 1){
					drawTileZoomed(map.tileSetTransparent, x, y + TABS_HEIGHT, xsource, ysource, map.newTileSize);
				}else{
					drawTileZoomed(map.tileSet, x, y + TABS_HEIGHT, xsource, ysource, map.newTileSize);
				}
                mapX++;
				if(mapX > MAX_MAP_X){
					a = TILE_MAP_LIMIT;
					ysource = a / NB_TILES_H * TILE_SIZE;
					xsource = a % NB_TILES_V * TILE_SIZE;
					drawTileZoomed(map.tileSet, x, y + TABS_HEIGHT, xsource, ysource, map.newTileSize);
				}
            }
            mapY++;
			if(mapY > MAX_MAP_Y){
				mapX = 0;
				for (x = x1; x < x2; x += map.newTileSize){
					a = TILE_MAP_LIMIT;  // Tile rouge
					ysource = a / NB_TILES_H * TILE_SIZE;
					xsource = a % NB_TILES_V * TILE_SIZE;
					drawTileZoomed(map.tileSet, x, y + TABS_HEIGHT, xsource, ysource, map.newTileSize);
					mapX++;
				}
			}
        }

    }

    //Layer 3 :
    else if(layerAffichee == LAYER_FOREGROUD)
    {
        //Troisième couche de tiles ;)
        for (y = y1; y < y2; y += map.newTileSize)
        {
            mapX = map.startX / map.newTileSize;

            for (x = x1; x < x2; x += map.newTileSize)
            {
                if(mapY >= 0 && mapX >= 0){					
					a = map.tileForeground[mapY][mapX];
				}else{
					a = TILE_MAP_LIMIT;
				}
                ysource = a / NB_TILES_H * TILE_SIZE;
                xsource = a % NB_TILES_V * TILE_SIZE;
                if(transparence == 1){
					drawTileZoomed(map.tileSetTransparent, x, y + TABS_HEIGHT, xsource, ysource, map.newTileSize);
				}else{
					drawTileZoomed(map.tileSet, x, y + TABS_HEIGHT, xsource, ysource, map.newTileSize);
				}
                mapX++;
				if(mapX > MAX_MAP_X){
					a = TILE_MAP_LIMIT;  // Tile rouge
					ysource = a / NB_TILES_H * TILE_SIZE;
					xsource = a % NB_TILES_V * TILE_SIZE;
					drawTileZoomed(map.tileSet, x, y + TABS_HEIGHT, xsource, ysource, map.newTileSize);
				}
            }
            mapY++;
			if(mapY > MAX_MAP_Y){
				mapX = 0;
				for (x = x1; x < x2; x += map.newTileSize){
					a = TILE_MAP_LIMIT;  // Tile rouge
					ysource = a / NB_TILES_H * TILE_SIZE;
					xsource = a % NB_TILES_V * TILE_SIZE;
					drawTileZoomed(map.tileSet, x, y + TABS_HEIGHT, xsource, ysource, map.newTileSize);
					mapX++;
				}
			}
        }
    }
}


void drawSelectedTile(){

	int xsource, ysource;

	// On affiche la tile sélectionnée à côté du curseur
    ysource = cursor.tileID / 10 * TILE_SIZE;
    xsource = cursor.tileID % 10 * TILE_SIZE;
    drawTile(map.tileSet, SCREEN_WIDTH + 42, 275, xsource, ysource);
}

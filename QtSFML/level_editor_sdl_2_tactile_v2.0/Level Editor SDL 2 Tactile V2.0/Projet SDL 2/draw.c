//Projet Rabidja - SDL 2.0
//Partie2_06Rabidja_LvlEditor
//draw.c

#include "draw.h"


void drawImage(SDL_Texture *image, int x, int y)
{
	SDL_Rect dest;

	/* Règle le rectangle à dessiner selon la taille de l'image source */

	dest.x = x;
	dest.y = y;

	/* Dessine l'image entière sur l'écran aux coordonnées x et y */
    SDL_QueryTexture(image, NULL, NULL, &dest.w, &dest.h);
	SDL_RenderCopy(jeu.renderer, image, NULL, &dest);
}


// Blit une image dont les dimensions dépendent d'une variable
void drawImageScaled(SDL_Texture *image, int x, int y, int w, int h)
{
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = w;
	dest.h = h;

	/* Dessine l'image sur l'écran aux coordonnées x et y */
	SDL_RenderCopy(jeu.renderer, image, NULL, &dest);
}


void drawTile(SDL_Texture *image, int destx, int desty, int srcx, int srcy)
{
    /* Rectangle de destination à dessiner */
	SDL_Rect dest;

	dest.x = destx;
	dest.y = desty;
	dest.w = TILE_SIZE;
	dest.h = TILE_SIZE;

	/* Rectangle source */
	SDL_Rect src;

	src.x = srcx;
	src.y = srcy;
	src.w = TILE_SIZE;
	src.h = TILE_SIZE;

	/* Dessine la tile choisie sur l'écran aux coordonnées x et y */

	SDL_RenderCopy(jeu.renderer, image, &src, &dest);
}

void drawTileZoomed(SDL_Texture *image, int destx, int desty, int srcx, int srcy, int zoomedTileSize)
{
	SDL_Rect src = {srcx, srcy, TILE_SIZE, TILE_SIZE};
	SDL_Rect dest = {destx, desty, zoomedTileSize, zoomedTileSize};

	/* Dessine la tile choisie sur l'écran aux coordonnées x et y */
	SDL_RenderCopy(jeu.renderer, image, &src, &dest);
}

void drawTilePlus(SDL_Texture *image, int destx, int desty, int srcx, int srcy, int w, int h)
{
    /* Rectangle de destination à dessiner */
	SDL_Rect dest;

	dest.x = destx;
	dest.y = desty;
	dest.w = w;
	dest.h = h;

	/* Rectangle source */
	SDL_Rect src;

	src.x = srcx;
	src.y = srcy;
	src.w = w;
	src.h = h;

	/* Dessine la tile choisie sur l'écran aux coordonnées x et y */

	SDL_RenderCopy(jeu.renderer, image, &src, &dest);
}


void drawTileset()
{
    int srcy = (map.tilesetPart) * 6 * 32;
    drawTilePlus(map.tileSet, SCREEN_WIDTH + 10, 42, 0, srcy, 320, 192);
}


void drawMessageBox()
{
    char text[200];

    /* Enregistre les coordonnées de la souris */
    SDL_GetMouseState(&input.mouseX, &input.mouseY);

    /* On récupère les coordonnées de la souris */
    cursor.x = input.mouseX;
	cursor.y = input.mouseY;

    /* Affiche la boîte de dialogue */
    drawImage(map.messageBox, 300, 180);

    //Affiche le message
    sprintf(text, "%s", jeu.messageBoxText);
    drawString(text, 390, 220, font, 255, 255, 255, 255);

    //Affiche YES / NO
    if (cursor.x > 450 && cursor.x < 490
            && cursor.y > 280 && cursor.y < 310)
    {
        drawString("YES", 450, 280, font, 255, 255, 0, 255);
    }
    else
        drawString("YES", 450, 280, font, 255, 255, 255, 255);

    if (cursor.x > 550 && cursor.x < 590
            && cursor.y > 280 && cursor.y < 310)
    {
        drawString("NO", 550, 280, font, 255, 255, 0, 255);
    }
    else
        drawString("NO", 550, 280, font, 255, 255, 255, 255);


}


void draw(void)
{

    char text[100];
    int i;

	// On affiche le fond blanc
	drawImage(map.background_full, 0, 0);

    /* Affiche le background */
    drawImageScaled(map.background, 0, TABS_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);

    /* Affiche la map de tiles */
    if(input.layerDrawn == LAYER_ACTION)
    {
        //On les affiche dans le bon ordre ;)
        drawMap(2, 1);
        drawMap(1, 0);
        drawMap(3, 1);
    }
    else if(input.layerDrawn == LAYER_BACKGROUD)
    {
        //On les affiche dans le bon ordre ;)
        drawMap(2, 0);
        drawMap(1, 1);
        drawMap(3, 1);
    }
    else if(input.layerDrawn == LAYER_FOREGROUD)
    {
        //On les affiche dans le bon ordre ;)
        drawMap(2, 1);
        drawMap(1, 1);
        drawMap(3, 0);
    }
    else if(input.layerDrawn == LAYER_ALL)
    {
        //On les affiche dans le bon ordre ;)
        drawMap(2, 0);
        drawMap(1, 0);
        drawMap(3, 0);
    }


	// On affiche la selection
	if(jeu.selectActivated){
		drawImageScaled(jeu.select_Img, (jeu.selectFirstX * map.newTileSize) - map.startX, (jeu.selectFirstY * map.newTileSize) - map.startY  + TABS_HEIGHT, map.newTileSize, map.newTileSize);
	}
	// Ou la zone de sélection
	else if(jeu.selectZoneActivated){
		int posX, posY, sizeW, sizeH;
		// En fonction de la selection la plus en haut à gauche
		if(jeu.selectFirstX <= jeu.selectLastX){
			posX = (jeu.selectFirstX * map.newTileSize) - map.startX;
			sizeW = abs(jeu.selectFirstX - (jeu.selectLastX + 1)) * map.newTileSize;
		}else{
			posX = (jeu.selectLastX * map.newTileSize) - map.startX;
			sizeW = abs(jeu.selectLastX - (jeu.selectFirstX + 1)) * map.newTileSize;
		}
		if(jeu.selectFirstY <= jeu.selectLastY){
			posY = (jeu.selectFirstY * map.newTileSize) - map.startY + TABS_HEIGHT;
			sizeH = abs(jeu.selectFirstY - (jeu.selectLastY + 1)) * map.newTileSize;
		}else{
			posY = (jeu.selectLastY * map.newTileSize) - map.startY + TABS_HEIGHT;
			sizeH = abs(jeu.selectLastY - (jeu.selectFirstY + 1)) * map.newTileSize;
		}
		// On dessine la zone avec la bonne dimension
		drawImageScaled(jeu.selectZone_Img, posX, posY, sizeW, sizeH);
	}


    /* Affiche le fond de l'éditeur */
    drawImage(map.fond, SCREEN_WIDTH - (EDITOR_IMAGE_WIDTH - EDITOR_TOOLS_WIDTH), 0);

	/* Affiche la barre de défilement en bas de l'écran */
	drawImage(map.scrollbarUp, 0, 0);

	/* Affiche la barre de défilement en bas de l'écran */
	drawImage(map.scrollbarDown, 0, SCREEN_HEIGHT + TABS_HEIGHT);

	// Affiche la Tile sélectionnée
	drawSelectedTile();

    /* Affiche le numero de la layer (couche) affichée */
    if(input.layerDrawn == LAYER_ALL)
    {
        //Dernier jaune
        for(i = 0; i < 3; i++)
        {
            int srcx = (i * 96);
            drawTilePlus(map.onglets, i * 96, 0, srcx, 0, 96, TABS_HEIGHT);
            drawTilePlus(map.onglets, 3 * 96, 0, 7 * 96, 0, 96, TABS_HEIGHT);
        }
        sprintf(text, "Resultat - Pas de modifs");
    }
    else if(input.layerDrawn == LAYER_ACTION)
    {
        int srcx = 96 * 3;
        drawTilePlus(map.onglets, 0, 0, srcx, 0, 96, TABS_HEIGHT);

        for(i = 0; i < 2; i++)
        {
            srcx = (i * 96) + 96;
            drawTilePlus(map.onglets, i * 96 + 96, 0, srcx, 0, 96, TABS_HEIGHT);
        }
        drawTilePlus(map.onglets, 3 * 96, 0, 6 * 96, 0, 96, TABS_HEIGHT);
        sprintf(text, "Action");
    }
    else if(input.layerDrawn == LAYER_BACKGROUD)
    {
        drawTilePlus(map.onglets, 0, 0, 0, 0, 96, TABS_HEIGHT);
        drawTilePlus(map.onglets, 96, 0, 96 * 4, 0, 96, TABS_HEIGHT);
        drawTilePlus(map.onglets, 96 * 2, 0, 96 * 2, 0, 96, TABS_HEIGHT);
        drawTilePlus(map.onglets, 3 * 96, 0, 6 * 96, 0, 96, TABS_HEIGHT);
        sprintf(text, "Background (derriere)");
    }
    else if(input.layerDrawn == LAYER_FOREGROUD)
    {
        int srcx = 96 * 5;
        drawTilePlus(map.onglets, 96 * 2, 0, srcx, 0, 96, TABS_HEIGHT);
        for(i = 0; i < 2; i++)
        {
            srcx = (i * 96);
            drawTilePlus(map.onglets, i * 96, 0, srcx, 0, 96, TABS_HEIGHT);
        }
        drawTilePlus(map.onglets, 3 * 96, 0, 6 * 96, 0, 96, TABS_HEIGHT);
        sprintf(text, "Foreground (devant)");
    }

	// Onglet choisi
    drawString(text, 10, 40, font, 0, 0, 0, 255);
    drawString(text, 8, 38, font, 255, 255, 255, 255);

	// Affichage du Zoom en cours
	sprintf(text, "Zoom %d%%", map.zoom);
    drawString(text, 400, 6, font, 0, 0, 0, 255);

	// Affichage de l'effet pour indiquer que le Mode Zoom est actif
	jeu.ModeZoom_X = SCREEN_WIDTH + 255;
	jeu.ModeZoom_Y = 449;
	if(input.modeZoom){
		drawImage(jeu.ModeZoomActivated, jeu.ModeZoom_X, jeu.ModeZoom_Y);
	}else{
		drawImage(jeu.ModeZoomDesactivated, jeu.ModeZoom_X, jeu.ModeZoom_Y);
	}


	// Affichage de la grille 32x32
	if(jeu.displayGrille){
		// On cache la grille si on dézoome
		if(map.zoom == 100){
			// On place la grille correctement
			int posX = -TILE_SIZE + (map.startX % TILE_SIZE);
			int posY = TABS_HEIGHT + (map.startY % TILE_SIZE);
			drawTilePlus(jeu.grille32, posX, posY, 0, 0, SCREEN_WIDTH + 32, SCREEN_HEIGHT);
		}
	}	

    //Affiche le numéro du niveau
    sprintf(text, "Level edited : %d", jeu.level);
    drawString(text, SCREEN_WIDTH + 15, 380, font, 0, 0, 0, 255);

    //Affiche les coordonnées de la souris
    sprintf(text, "Mouse (%d, %d)", cursor.x, cursor.y);
    drawString(text, SCREEN_WIDTH + 15, 492, font, 0, 0, 0, 255);

	//Affiche les coordonnées de la souris depuis le début du niveau, ainsi que les coordonnées de la Tile survolée
	sprintf(text, "(%d, %d - Tile: %d, %d)", cursor.x + map.startX, cursor.y + map.startY, (cursor.x + map.startX)/map.newTileSize, (cursor.y + map.startY - TABS_HEIGHT)/map.newTileSize);
    drawString(text, SCREEN_WIDTH + 15, 515, font, 0, 0, 0, 255);

    //Affiche le numéro du tileset en cours
    sprintf(text, "Tileset number : %d", map.tilesetAffiche);
    drawString(text, SCREEN_WIDTH + 15, 415, font, 0, 0, 0, 255);

    //Affiche le texte pour placer le point de départ
    sprintf(text, "Choose Start Point");
    drawString(text, SCREEN_WIDTH + 15, 450, font, 0, 0, 0, 255);

    //Affiche le tilesetpart
    sprintf(text, "%d", map.tilesetPart);
    drawString(text, SCREEN_WIDTH + 353, 120, font, 0, 0, 0, 255);

	// Affiche le point de départ du niveau
    if(map.beginx - map.startX <= 610){
		// On corrige la taille du Sprite en fonction du Zoom
		SDL_Rect tmp;
		SDL_QueryTexture(map.startpoint, NULL, NULL, &tmp.w, &tmp.h);
		tmp.w *=  (map.zoom/100.0);
		tmp.h *=  (map.zoom/100.0);
		// Affiche le point de départ du héros
		int posX = map.beginx;
		int posY = map.beginy;
		posX *=  (map.zoom/100.0);
		posY *=  (map.zoom/100.0);
		posX -=  map.startX;
		posY -=  map.startY;
		drawImageScaled(map.startpoint, posX, posY, tmp.w, tmp.h);
	}

	// Affichage du message d'information
    if (jeu.displayInformation)
    {
		drawImage(jeu.information_Img, 0, 32);
    }

    //Affiche les messages s'il y en a
    if(jeu.message == 1)
    {
        sprintf(text, "%s", jeu.messageText);
        drawString(text, SCREEN_WIDTH + 20, 336, font, 0, 0, 0, 255);
        jeu.message_timer--;
        if(jeu.message_timer < 0)
        {
            jeu.message_timer = DUREE_MESSAGE;
            jeu.message = 0;
        }

    }

	// Affiche le numéro de la Tile sélectionnée	
	sprintf(text, "%d", cursor.tileID);
    drawString(text, SCREEN_WIDTH + 48, 302, font, 255, 255, 255, 255);
    drawString(text, SCREEN_WIDTH + 47, 303, font, 0, 0, 0, 255);

    //Affiche le message pour choisir le début du niveau
    if(jeu.placeBegin == 1 && jeu.message == 0)
    {
        sprintf(text, "Place start and hit +1!");
        drawString(text, SCREEN_WIDTH + 10, 325, font, 0, 0, 0, 255);
    }

    //Affiche le tileset à faire défiler à droite
    drawTileset();

    //Affiche la boite de dialogue, s'il y en a une
    if(jeu.messageBox == 1)
    {
        drawMessageBox();
    }


    /* Affiche l'écran */
    SDL_RenderPresent(jeu.renderer);

    /* Delai */
    SDL_Delay(1);
}


SDL_Texture *loadImage(char *name)
{
	/* Charge les images avec SDL Image dans une SDL_Surface */

	SDL_Surface *loadedImage = NULL;
	SDL_Texture *texture = NULL;
    loadedImage = IMG_Load(name);

	if (loadedImage != NULL)
	{
		// Conversion de l'image en texture
		texture = SDL_CreateTextureFromSurface(jeu.renderer, loadedImage);

		// On se débarrasse du pointeur vers une surface
		SDL_FreeSurface(loadedImage);
		loadedImage = NULL;
	}
	else
		printf("L'image n'a pas pu être chargée! SDL_Error :  %s\n", SDL_GetError());

		return texture;
}


void delay(unsigned int frameLimit)
{

    /* Gestion des 60 fps */

    unsigned int ticks = SDL_GetTicks();

    if (frameLimit < ticks)
    {
        return;
    }

    if (frameLimit > ticks + 16)
    {
        SDL_Delay(16);
    }

    else
    {
        SDL_Delay(frameLimit - ticks);
    }
}


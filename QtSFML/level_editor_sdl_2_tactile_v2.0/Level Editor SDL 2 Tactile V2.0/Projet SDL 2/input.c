//Projet Rabidja - SDL 2.0
//Partie2_06Rabidja_LvlEditor
//input.c

#include "input.h"

// Variable pour la gestion du CTRL+Z
int memoLeftClicAction;

void getInput(void)
{
    SDL_Event event;

    /* Keymapping : gère les appuis sur les touches et les enregistre
    dans la structure input */

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {

        case SDL_QUIT:
            jeu.messageBox = 1;
            sprintf(jeu.messageBoxText, "Do you want to quit?");
            jeu.messageBoxAction = QUIT;
            break;

        // Gestion du redimensionnement de la fenêtre
		case SDL_WINDOWEVENT:
			if(event.window.event == SDL_WINDOWEVENT_RESIZED){
				//printf("New Window Size= %d, %d\n", event.window.data1, event.window.data2);
				SCREEN_WIDTH = event.window.data1 - EDITOR_TOOLS_WIDTH;
				SCREEN_HEIGHT = event.window.data2 - (TABS_HEIGHT + SCROLLBAR_HEIGHT);
			}
			break;

		// Gestion des touches clavier
		case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
                //case SDLK_ESCAPE:
                //	exit(0);
                //break;

            case SDLK_LEFT:
                input.left = 1;
                break;

            case SDLK_RIGHT:
                input.right = 1;
                break;

            case SDLK_UP:
                input.up = 1;
                break;

            case SDLK_DOWN:
                input.down = 1;
                break;

            /* La touche S sauvegardera */
            case SDLK_s:
                input.save = 1;
                break;

            /* La touche L chargera la map */
            case SDLK_l:
                input.load = 1;
                break;

            // Suppr pour mettre une Tile vide à la place d'une sélection
            case SDLK_DELETE:
                input.deleteTile = 1;
                break;

            //Choix du niveau
            case SDLK_F1:
                input.changeLayer = 1;
                break;

            case SDLK_F2:
                input.leveldown = 1;
                break;

            case SDLK_F3:
                input.levelup = 1;
                break;

			// Activation/Désactivation du mode Zoom
			// et gestion des CTRL+Z et CTRL+Y
			case SDLK_z:
				// Gestion du CTRL+Z
				if(input.ctrl){
					input.ctrl_Z = 1;
				}
				// Activation du Zoom
				else{
					if(input.modeZoom){
						input.modeZoom = 0;
					}else{
						input.modeZoom = 1;
					}
				}
            break;
			case SDLK_y:
				if(input.ctrl){
					input.ctrl_Y = 1;
				}
			break;

			// Gestion du Copy/Cut/Paste
			case SDLK_c:
				if(input.ctrl){
					input.shortcutCopy = 1;
				}
				break;
			case SDLK_v:
				if(input.ctrl){
					input.shortcutPaste = 1;
				}
				break;
			case SDLK_x:
				if(input.ctrl){
					input.shortcutCut = 1;
				}
				break;
			case SDLK_LCTRL:
			case SDLK_RCTRL:
				input.ctrl = 1;
				break;


            default:
                break;
            }
            break;

        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
            case SDLK_LEFT:
                input.left = 0;
                break;

            case SDLK_RIGHT:
                input.right = 0;
                break;

            case SDLK_UP:
                input.up = 0;
                break;

            case SDLK_DOWN:
                input.down = 0;
                break;

			// Gestion du Copy/Cut/Paste
			case SDLK_LCTRL:
			case SDLK_RCTRL:
				input.ctrl = 0;
				input.shortcutCopy = 0;
				input.shortcutCut = 0;
				input.shortcutPaste = 0;
				break;

            default:
                break;
            }
            break;

        case SDL_FINGERUP:
        {
            input.add = 0;
        }
        break;

        case SDL_FINGERDOWN:
        {
            input.add = 1;
            input.mouseX = event.tfinger.x * 1020;
            input.mouseY = event.tfinger.y * 544;
        }
        break;


        case SDL_MOUSEBUTTONDOWN:
        {
            /* Enregistre les coordonnées de la souris */
            SDL_GetMouseState(&input.mouseX, &input.mouseY);

            switch(event.button.button)
            {
            // Le clic gauche de la souris ajoutera la tile en cours
            case SDL_BUTTON_LEFT:
                input.add = 1;
                break;

            // Le clic central de la souris effacera la tile sélectionnée
            case SDL_BUTTON_MIDDLE:
                input.remove = 1;
                break;

            // Le clic droit de la souris copiera la tile sélectionnée
            case SDL_BUTTON_RIGHT:
                input.copy = 1;
                break;
            }
        }
        break;


        case SDL_MOUSEWHEEL:
            //cas du SDL_BUTTON_WHEELUP
            if(event.button.x > 0)
                input.next = 1;
            //cas du SDL_BUTTON_WHEELDOWN
            else if(event.button.x < 0)
                input.previous = 1;
            break;

        case SDL_MOUSEBUTTONUP:
            switch(event.button.button)
            {
            case SDL_BUTTON_LEFT:
                input.add = 0;
                break;

            case SDL_BUTTON_MIDDLE:
                input.remove = 0;
                break;

            default:
                break;
            }
            break;


        }
    }




}


void updateMessageBox(void)
{
    //On réinitialise le résultat pour éviter les faux positifs
    jeu.messageBoxResult = 0;

    /* Enregistre les coordonnées de la souris */
    SDL_GetMouseState(&input.mouseX, &input.mouseY);

    /* On récupère les coordonnées de la souris */
    cursor.x = input.mouseX;
    cursor.y = input.mouseY;

    //Si on clique YES, on renvoie 1 (dans la variable jeu.messageBoxResult,
    //sinon 0 et on quitte la messageBox.
    if (input.add == 1)
    {
        if (cursor.x > 450 && cursor.x < 490
                && cursor.y > 280 && cursor.y < 310)
        {
            jeu.messageBoxResult = 1;
            jeu.messageBox = 0;
            jeu.doMessageBoxAction = 1;
        }
        else if (cursor.x > 550 && cursor.x < 590
                 && cursor.y > 280 && cursor.y < 310)
        {
            jeu.messageBoxResult = 0;
            jeu.messageBox = 0;
            jeu.doMessageBoxAction = 1;
        }
    }

}


void doMessageBoxAction(void)
{
    char file[120];

    switch (jeu.messageBoxAction)
    {

    case LEVELUP:
        if(jeu.messageBoxResult == 1)
        {
            sprintf(file, "map/map%d.txt", jeu.level);
            saveMap(file);

            jeu.message = 1;
            sprintf(jeu.messageText, "Map saved !");
        }
        jeu.level++;
        if (jeu.level > LEVEL_MAX )
            jeu.level = 1;
        loadGame();
        input.layerDrawn = 4;
        jeu.doMessageBoxAction = 0;
        break;


    case LEVELDOWN:
        if(jeu.messageBoxResult == 1)
        {
            sprintf(file, "map/map%d.txt", jeu.level);
            saveMap(file);

            jeu.message = 1;
            sprintf(jeu.messageText, "Map saved !");
        }
        jeu.level--;
        if (jeu.level < 1 )
            jeu.level = LEVEL_MAX;
        loadGame();
        input.layerDrawn = 4;
        jeu.doMessageBoxAction = 0;
        break;

    case SAVE:
        if(jeu.messageBoxResult == 1)
        {
            sprintf(file, "map/map%d.txt", jeu.level);
            saveMap(file);

            jeu.message = 1;
            sprintf(jeu.messageText, "Map saved !");
        }
        input.layerDrawn = 4;
        jeu.doMessageBoxAction = 0;
        break;

    case LOAD:
        if(jeu.messageBoxResult == 1)
        {
            sprintf(file, "map/map%d.txt", jeu.level);
            loadMap(file);

            jeu.message = 1;
            sprintf(jeu.messageText, "Map loaded !");
        }
        input.layerDrawn = 4;
        jeu.doMessageBoxAction = 0;
        break;


    case RESET:
        if(jeu.messageBoxResult == 1)
        {
            reinitMap();
            jeu.message = 1;
            sprintf(jeu.messageText, "Map reseted (but not saved) !");
        }
        input.layerDrawn = 4;
        jeu.doMessageBoxAction = 0;
        break;


    case PASTE:
        if(jeu.messageBoxResult == 1)
        {
            sprintf(file, "map/pastebin.txt");
            loadMap(file);

            jeu.message = 1;
            sprintf(jeu.messageText, "Map pasted (but not saved) !");
        }
        input.layerDrawn = 4;
        jeu.doMessageBoxAction = 0;
        break;


    case QUIT:
        if(jeu.messageBoxResult == 1)
        {
            exit(0);
        }
        input.layerDrawn = 4;
        jeu.doMessageBoxAction = 0;
        break;

    }

}


void update(void)
{
    char file[120];

    /* Enregistre les coordonnées de la souris */
    SDL_GetMouseState(&input.mouseX, &input.mouseY);

    /* On récupère les coordonnées de la souris */
    cursor.x = input.mouseX;
    cursor.y = input.mouseY;

	// Numéro de la Tile sous la souris
	int currentTileX = (map.startX + cursor.x) / map.newTileSize;
	int currentTileY = ((map.startY + cursor.y) - TABS_HEIGHT) / map.newTileSize;

	// Si on est hors des limites de la Map, on interdit les modifications
	int offLimits = 0;
	if(	currentTileX < 0 || currentTileY < 0 ||
		currentTileX > MAX_MAP_X || currentTileY > MAX_MAP_Y ){
		offLimits = 1;
	}

	// Permet de savoir si la Map a été modifié (Gestion CTRL+Z)
	int mapWasModified = 0;
	//int isNewAction = 0;

	if(offLimits == 0){
		// Gestion de l'ajout/suppression de ligne/colonne
		if(jeu.selectActivated){
			if(input.addColumn){
				addEmptyColumn(jeu.selectFirstX);
				mapWasModified = 1;
				input.addColumn = 0;
				jeu.message = 1;
				sprintf(jeu.messageText, "Column added!");
			}else if(input.deleteColumn){
				deleteColumn(jeu.selectFirstX);
				input.deleteColumn = 0;
				mapWasModified = 1;
				jeu.message = 1;
				sprintf(jeu.messageText, "Column deleted!");
			}else if(input.addRow){
				addEmptyRow(jeu.selectFirstY - 0);	// -1 pour les onglets
				input.addRow = 0;
				mapWasModified = 1;
				jeu.message = 1;
				sprintf(jeu.messageText, "Row added!");
			}else if(input.deleteRow){
				deleteRow(jeu.selectFirstY - 0);	// -1 pour les onglets
				input.deleteRow = 0;
				mapWasModified = 1;
				jeu.message = 1;
				sprintf(jeu.messageText, "Row deleted!");
			}
			// Si on appuie sur [Suppr] ([del]), on "supprime" la Tile active en insérant une Tile vide
			else if(input.deleteTile == 1){
				input.deleteTile = 0;
				mapWasModified = 1;
				deleteTile(jeu.selectFirstX, jeu.selectFirstY, jeu.selectFirstX, jeu.selectFirstY);
			}
		}

		// Action sur une zone séléctionnée
		if(jeu.selectZoneActivated){
			// Remplissage
			if(input.fillWith){
				if(input.layerDrawn == LAYER_ALL){
					jeu.message = 1;
					sprintf(jeu.messageText, "Choose a layer first!");
				}else{
					fillWith(jeu.zoneMemFromX, jeu.zoneMemFromY, jeu.zoneMemToX, jeu.zoneMemToY);
					input.fillWith = 0;
					mapWasModified = 1;
					jeu.message = 1;
					sprintf(jeu.messageText, "Area filled!");
				}
			}
			// Flip horizontal et vertical
			else if(input.flipHorizontal == 1){
				flipHorizontal(jeu.zoneMemFromX, jeu.zoneMemFromY, jeu.zoneMemToX, jeu.zoneMemToY);
				mapWasModified = 1;
				input.flipHorizontal = 0;
				jeu.message = 1;
				sprintf(jeu.messageText, "Horizontal Inversion done!");
			}
			else if(input.flipVertical == 1){
				flipVertical(jeu.zoneMemFromX, jeu.zoneMemFromY, jeu.zoneMemToX, jeu.zoneMemToY);
				mapWasModified = 1;
				input.flipVertical = 0;
				jeu.message = 1;
				sprintf(jeu.messageText, "Vertical Inversion done!");
			}
			// Si on appuie sur [Suppr] ([del]), on "supprime" la Tile active en insérant une Tile vide
			else if(input.deleteTile == 1){
				input.deleteTile = 0;
				deleteTile(jeu.zoneMemFromX, jeu.zoneMemFromY, jeu.zoneMemToX, jeu.zoneMemToY);
				mapWasModified = 1;
			}
		}

		// Gestion du Copy/Paste et du Cut/Paste  d'une sélection
		if(input.shortcutCopy || input.shortcutCut){

			// Si une zone est selectionnée, on copie la zone
			if(jeu.selectZoneActivated){

				// On vide les tableaux
				jeu.selectCopyAll = 0;
				for(int x = 0 ; x < MAX_MAP_X ; x++){
					for(int y = 0 ; y < MAX_MAP_Y ; y++){
						jeu.selectCopyTab_L[y][x] = 0;
						jeu.selectCopyTab_B[y][x] = 0;
						jeu.selectCopyTab_A[y][x] = 0;
						jeu.selectCopyTab_F[y][x] = 0;
					}
				}

				// Début et fin de la sélection
				if(jeu.selectFirstX <= jeu.selectLastX){
					jeu.zoneMemFromX_CP = jeu.selectFirstX;
					jeu.zoneMemToX_CP = jeu.selectLastX;
				}else{
					jeu.zoneMemFromX_CP = jeu.selectLastX;
					jeu.zoneMemToX_CP = jeu.selectFirstX;
				}
				if(jeu.selectFirstY <= jeu.selectLastY){
					jeu.zoneMemFromY_CP = jeu.selectFirstY;
					jeu.zoneMemToY_CP = jeu.selectLastY;
				}else{
					jeu.zoneMemFromY_CP = jeu.selectLastY;
					jeu.zoneMemToY_CP = jeu.selectFirstY;
				}

				// Taille de la sélection
				int nbTileX = jeu.zoneMemToX_CP - jeu.zoneMemFromX_CP;
				int nbTileY = jeu.zoneMemToY_CP - jeu.zoneMemFromY_CP;

				// On mémorise les Tiles du calque actif
				for(int x = 0 ; x <= nbTileX ; x++){
					for(int y = 0 ; y <= nbTileY ; y++){
						if ( input.layerDrawn == LAYER_BACKGROUD ){
							jeu.selectCopyTab_L[y][x] = map.tileBackground[jeu.zoneMemFromY_CP + y][jeu.zoneMemFromX_CP + x];
						}
						else if ( input.layerDrawn == LAYER_ACTION ){
							jeu.selectCopyTab_L[y][x] = map.tileAction[jeu.zoneMemFromY_CP + y][jeu.zoneMemFromX_CP + x];
						}
						else if ( input.layerDrawn == LAYER_FOREGROUD ){
							jeu.selectCopyTab_L[y][x] = map.tileForeground[jeu.zoneMemFromY_CP + y][jeu.zoneMemFromX_CP + x];
						}
						else if ( input.layerDrawn == LAYER_ALL ){
							jeu.selectCopyTab_B[y][x] = map.tileBackground[jeu.zoneMemFromY_CP + y][jeu.zoneMemFromX_CP + x];
							jeu.selectCopyTab_A[y][x] = map.tileAction[jeu.zoneMemFromY_CP + y][jeu.zoneMemFromX_CP + x];
							jeu.selectCopyTab_F[y][x] = map.tileForeground[jeu.zoneMemFromY_CP + y][jeu.zoneMemFromX_CP + x];
							jeu.selectCopyAll = 1;
						}
					}
				}
				jeu.message = 1;
				if(input.shortcutCopy){
					sprintf(jeu.messageText, "Area copied!");
				}else{
					sprintf(jeu.messageText, "Area cut!");
				}
			}
			input.shortcutCopy = 0;

			// Si on a "coupé", on vide les Tiles sélectionnées
			if(input.shortcutCut){
				input.shortcutCut = 0;
				deleteTile(jeu.selectFirstX, jeu.selectFirstY, jeu.selectLastX, jeu.selectLastY);
				mapWasModified = 1;
			}

		}else if(input.shortcutPaste){

			// Si une Tile est selectionnée
			if(jeu.selectActivated){

				// Taille de la sélection
				int nbTileX = jeu.zoneMemToX_CP - jeu.zoneMemFromX_CP;
				int nbTileY = jeu.zoneMemToY_CP - jeu.zoneMemFromY_CP;

				// On colle la zone copiée
				int raiseError = 0;
				for(int x = 0 ; x <= nbTileX ; x++){
					for(int y = 0 ; y <= nbTileY ; y++){
						// En fonction de la couche active (si on a copier tous les layers, on ne permet de coller dans 1 seul)
						if ( input.layerDrawn == LAYER_BACKGROUD && jeu.selectCopyAll == 0 ){
							map.tileBackground[jeu.selectFirstY + y][jeu.selectFirstX + x] = jeu.selectCopyTab_L[y][x];
						}
						if ( input.layerDrawn == LAYER_ACTION && jeu.selectCopyAll == 0 ){
							map.tileAction[jeu.selectFirstY + y][jeu.selectFirstX + x] =jeu.selectCopyTab_L[y][x];
						}
						if ( input.layerDrawn == LAYER_FOREGROUD && jeu.selectCopyAll == 0 ){
							map.tileForeground[jeu.selectFirstY + y][jeu.selectFirstX + x] = jeu.selectCopyTab_L[y][x];
						}
						else if ( input.layerDrawn == LAYER_ALL ){
							map.tileBackground[jeu.selectFirstY + y][jeu.selectFirstX + x] = jeu.selectCopyTab_B[y][x];
							map.tileAction[jeu.selectFirstY + y][jeu.selectFirstX + x] =jeu.selectCopyTab_A[y][x];
							map.tileForeground[jeu.selectFirstY + y][jeu.selectFirstX + x] = jeu.selectCopyTab_F[y][x];
						}
						else{
							// On tombe ici si on a copier tous les layers et qu'on a voulu copier dans un seul
							raiseError = 1;
						}
					}
				}
				mapWasModified = 1;
				jeu.message = 1;
				if(raiseError == 1){
					sprintf(jeu.messageText, "You must paste in [All] tab!");
				}else{
					sprintf(jeu.messageText, "Area pasted!");
				}

				// On réactive la zone de sélection pour voir ce qui a été copié et
				// pour pouvoir appliquer une autre fonction au besoin
				jeu.selectZoneActivated = 1;
				jeu.selectActivated = 0;
				jeu.selectLastX += nbTileX;
				jeu.selectLastY += nbTileY;
				jeu.zoneMemFromX = jeu.selectFirstX;
				jeu.zoneMemToX = jeu.selectLastX;
				jeu.zoneMemFromY = jeu.selectFirstY;
				jeu.zoneMemToY = jeu.selectLastY;
			}
			input.shortcutPaste = 0;

		}
	}

    // Gestion du scrolling
	int scrollSpeendMin = 24;
 	if (input.left == 1 || input.Tactileleft == 1)
	{
		// On déplace toujours la Map d'une valeur multiple de la taille d'une Tile.
		// Afin d'éviter que le Scrolling soit trop lent lorsqu'on dézoome,
		// on fait en sorte de déplacer la Map de minimum "scrollSpeendMin"
		// (mais toujours d'une valuer multiple de map.newTileSize !)
		int scrollMapValue = TILE_SIZE * (map.zoom / 100.0);

		// Si la valeur est < "scrollSpeendMin", on ajoute ce qu'il manque
		if(scrollMapValue < scrollSpeendMin){
			scrollMapValue = TILE_SIZE + map.newTileSize - (TILE_SIZE %  map.newTileSize);
		}
		map.startX -= scrollMapValue;

		//printf("scrollMapValue = %d\n", scrollMapValue);
	}
	else if (input.right == 1 || input.Tactileright == 1)
	{
		int scrollMapValue = TILE_SIZE * (map.zoom / 100.0);
		if(scrollMapValue < scrollSpeendMin){
			scrollMapValue = TILE_SIZE + map.newTileSize - (TILE_SIZE %  map.newTileSize);
		}
		map.startX += scrollMapValue;
	}

	if (input.up == 1 || input.Tactileup == 1)
	{
		int scrollMapValue = TILE_SIZE * (map.zoom / 100.0);
		if(scrollMapValue < scrollSpeendMin){
			scrollMapValue = TILE_SIZE + map.newTileSize - (TILE_SIZE %  map.newTileSize);
		}
		map.startY -= scrollMapValue;
	}
	else if (input.down == 1 || input.Tactiledown == 1)
	{
		int scrollMapValue = TILE_SIZE * (map.zoom / 100.0);
		if(scrollMapValue < scrollSpeendMin){
			scrollMapValue = TILE_SIZE + map.newTileSize - (TILE_SIZE %  map.newTileSize);
		}
		map.startY += scrollMapValue;
	}

    //Gestion du passage d'une map à l'autre
    if (input.levelup == 1)
    {
        jeu.messageBox = 1;
        sprintf(jeu.messageBoxText, "Do you want to save first?");
        jeu.messageBoxAction = LEVELUP;
        input.levelup = 0;
    }

    if (input.leveldown == 1)
    {
        jeu.messageBox = 1;
        sprintf(jeu.messageBoxText, "Do you want to save first?");
        jeu.messageBoxAction = LEVELDOWN;
        input.leveldown = 0;
    }

    //On remet à 0 les inputs tactiles
    input.Tactileleft = input.Tactileright = input.Tactileup = input.Tactiledown = 0;

    /* Gestion de la copie de tile :
    on retrouve les coordonnées de la tile pointée par la souris et on remplace
    sa valeur par celle de la tile sélectionnée dans le curseur */
    if (input.add == 1)
    {
		// GESTION DE LA SELECTION
		// Si on presse CTRL et qu'on est dans la Map
		if(input.ctrl && cursor.x <= SCREEN_WIDTH && offLimits == 0){

			// Si la selection était déjà acitvée ET que le nouvelle selection est différente,
			// on active la zone de selection
			if(jeu.selectActivated == 1 && !(jeu.selectFirstX == currentTileX && jeu.selectFirstY == currentTileY)){

				jeu.selectZoneActivated = 1;
				jeu.selectActivated = 0;

				// On mémorise la zone de selection
				jeu.selectLastX = currentTileX;
				jeu.selectLastY = currentTileY;

				// Début et fin de la sélection
				if(jeu.selectFirstX <= jeu.selectLastX){
					jeu.zoneMemFromX = jeu.selectFirstX;
					jeu.zoneMemToX = jeu.selectLastX;
				}else{
					jeu.zoneMemFromX = jeu.selectLastX;
					jeu.zoneMemToX = jeu.selectFirstX;
				}
				if(jeu.selectFirstY <= jeu.selectLastY){
					jeu.zoneMemFromY = jeu.selectFirstY;
					jeu.zoneMemToY = jeu.selectLastY;
				}else{
					jeu.zoneMemFromY = jeu.selectLastY;
					jeu.zoneMemToY = jeu.selectFirstY;
				}

			}else{

				jeu.selectActivated = 1;
				jeu.selectZoneActivated = 0;

				// On mémorise la selection
				jeu.selectFirstX = currentTileX;
				jeu.selectFirstY = currentTileY;
				jeu.selectLastX = currentTileX;
				jeu.selectLastY = currentTileY;

			}

			input.add = 0;

		}else{

			// Dans la Map
			if(cursor.x < SCREEN_WIDTH && !jeu.displayInformation)
			{
				// On désactive la selection si c'est sur la Map (pas les onglets)
				if(cursor.y > TABS_HEIGHT){
					jeu.selectActivated = 0;
					jeu.selectZoneActivated = 0;
				}

				//Si on doit placer le début du niveau
				if (jeu.placeBegin == 1 && cursor.y > TABS_HEIGHT)
				{
					//Calcul pour obtenir la tile exacte
					map.beginx = ((map.startX + cursor.x) / map.newTileSize) * map.newTileSize;
					map.beginy = ((map.startY + cursor.y - TABS_HEIGHT) / map.newTileSize) * map.newTileSize;
				}

				//Sélection de la couche (layer)
				else if (cursor.x > 0 && cursor.x < 94
						 && cursor.y > 0 && cursor.y < 30)
				{
					input.layerDrawn = LAYER_ACTION;
				}
				else if (cursor.x > 96 && cursor.x < 190
						 && cursor.y > 0 && cursor.y < 30)
				{
					input.layerDrawn = LAYER_BACKGROUD;
				}
				else if (cursor.x > 195 && cursor.x < 287
						 && cursor.y > 0 && cursor.y < 30)
				{
					input.layerDrawn = LAYER_FOREGROUD;
				}
				else if (cursor.x > 290 && cursor.x < 383
						 && cursor.y > 0 && cursor.y < 30)
				{
					input.layerDrawn = LAYER_ALL;
				}

				//Défilement de la map Haut / Bas
				else if (cursor.x > 555 && cursor.x < 587
						 && cursor.y > 0 && cursor.y < 32)
				{
					input.Tactileup = 1;
				}
				else if (cursor.x > 608 && cursor.x < 639
						 && cursor.y > 0 && cursor.y < 32)
				{
					input.Tactiledown = 1;
				}

				//Défilement de la map Gauche / Droite
				else if (cursor.x > 0 && cursor.x < 34
						 && cursor.y > SCREEN_HEIGHT + 33 && cursor.y < SCREEN_HEIGHT + 63)
				{
					input.Tactileleft = 1;
				}
				else if (cursor.x > 608 && cursor.x < 640
						 && cursor.y > SCREEN_HEIGHT + 33 && cursor.y < SCREEN_HEIGHT + 63)
				{
					input.Tactileright = 1;
				}

				//Sinon on copie
				else if(offLimits == 0 && cursor.y < SCREEN_HEIGHT + TABS_HEIGHT)
				{
					if ( input.layerDrawn == 1 ){
						map.tileAction[currentTileY][currentTileX] = cursor.tileID;
						// On mémorise l'action réalisée
						memoLeftClicAction = 1;
					}
					else if ( input.layerDrawn == 2 ){
						map.tileBackground[currentTileY][currentTileX] = cursor.tileID;
						memoLeftClicAction = 1;
					}
					else if ( input.layerDrawn == 3 ){
						map.tileForeground[currentTileY][currentTileX] = cursor.tileID;
						memoLeftClicAction = 1;
					}
				}
			}
			//Gestion des options à droite de la map
			else
			{
				//Choix d'un tile dans le tileset
				if(cursor.x >= SCREEN_WIDTH + 10 && cursor.x <= SCREEN_WIDTH + 330
						&& cursor.y >= 40 && cursor.y <= 240)
					cursor.tileID = ((cursor.y -42) / TILE_SIZE + ((map.tilesetPart) * 6))
									* 10 + (cursor.x - SCREEN_WIDTH - 10) / TILE_SIZE;

				//Ascenseur tileset
				else if (cursor.x > SCREEN_WIDTH + 343 && cursor.x < SCREEN_WIDTH + 375
						 && cursor.y > 35 && cursor.y < 76)
				{
					if (map.tilesetPart >= 1)
						map.tilesetPart--;
				}
				else if (cursor.x > SCREEN_WIDTH + 343 && cursor.x < SCREEN_WIDTH + 375
						 && cursor.y > 198 && cursor.y < 237)
				{
					if (map.tilesetPart < 5)
						map.tilesetPart++;
				}

				//Sélection de levels
				else if (cursor.x > SCREEN_WIDTH + 215 && cursor.x < SCREEN_WIDTH + 247
						 && cursor.y > 377 && cursor.y < 408)
				{
					input.levelup = 1;
				}
				else if (cursor.x > SCREEN_WIDTH + 255 && cursor.x < SCREEN_WIDTH + 285
						 && cursor.y > 377 && cursor.y < 408)
				{
					input.leveldown = 1;
				}


				//Load
				else if (input.mouseX >= SCREEN_WIDTH + 123 && input.mouseX <= SCREEN_WIDTH + 223
						 && input.mouseY >= 289 && input.mouseY <= 321)
				{
					input.load = 1;
				}


				//Reset
				else if (input.mouseX >= SCREEN_WIDTH + 232 && input.mouseX <= SCREEN_WIDTH + 372
						 && input.mouseY >= 291 && input.mouseY <= 320)
				{
					input.reinit = 1;
				}


				//Save
				else if (input.mouseX >= SCREEN_WIDTH + 124 && input.mouseX <= SCREEN_WIDTH + 223
						 && input.mouseY >= 248 && input.mouseY <= 281)
				{
					input.save = 1;
				}

				//Copy
				else if (input.mouseX >= SCREEN_WIDTH + 233 && input.mouseX <= SCREEN_WIDTH + 298
						 && input.mouseY >= 248 && input.mouseY <= 280)
				{
					input.copyMap = 1;
				}

				//Paste
				else if (input.mouseX >= SCREEN_WIDTH + 306 && input.mouseX <= SCREEN_WIDTH + 372
						 && input.mouseY >= 248 && input.mouseY <= 280)
				{
					input.pasteMap = 1;
				}

				//Tileset + et -
				else if (input.mouseX >= SCREEN_WIDTH + 255 && input.mouseX <= SCREEN_WIDTH + 285
						 && input.mouseY >= 412 && input.mouseY <= 444)
				{
					map.tilesetAffiche--;
					if(map.tilesetAffiche < 1)
						map.tilesetAffiche = MAX_TILESETS;
					reloadTileset();
				}
				else if (input.mouseX >= SCREEN_WIDTH + 215 && input.mouseX <= SCREEN_WIDTH + 248
						 && input.mouseY >= 412 && input.mouseY <= 444)
				{
					map.tilesetAffiche++;
					if(map.tilesetAffiche > MAX_TILESETS)
						map.tilesetAffiche = 1;
					reloadTileset();
				}
				//Pour placer le début du niveau
				else if (input.mouseX >= SCREEN_WIDTH + 215 && input.mouseX <= SCREEN_WIDTH + 247
						 && input.mouseY >= 449 && input.mouseY <= 480)
				{
					if (jeu.placeBegin == 1)
						jeu.placeBegin = 0;
					else
						jeu.placeBegin = 1;
				}

				// Pour afficher la grille 32x32
				else if (input.mouseX >= SCREEN_WIDTH + 215 && input.mouseX <= SCREEN_WIDTH + 247
						 && input.mouseY >= 485 && input.mouseY <= 516)
				{
					jeu.displayGrille = !jeu.displayGrille;
				}

				// Pour activer le Mode Zoom
				else if (input.mouseX >= jeu.ModeZoom_X && input.mouseX <= jeu.ModeZoom_X + 32
							 && input.mouseY >= jeu.ModeZoom_Y && input.mouseY <= jeu.ModeZoom_Y + 32)
				{
					input.modeZoom = !input.modeZoom;
				}

				// Pour ajouter une colonne
				else if (input.mouseX >= SCREEN_WIDTH + 300 && input.mouseX <= SCREEN_WIDTH + 332
						 && input.mouseY >= 378 && input.mouseY <= 408)
				{
					if(jeu.selectActivated){
						input.addColumn = 1;
					}
				}

				// Pour supprimer une colonne
				else if (input.mouseX >= SCREEN_WIDTH + 339 && input.mouseX <= SCREEN_WIDTH + 370
						 && input.mouseY >= 378 && input.mouseY <= 408)
				{
					if(jeu.selectActivated){
						input.deleteColumn = 1;
					}
				}

				// Pour ajouter une ligne
				else if (input.mouseX >= SCREEN_WIDTH + 300 && input.mouseX <= SCREEN_WIDTH + 332
						 && input.mouseY >= 414 && input.mouseY <= 444)
				{
					if(jeu.selectActivated){
						input.addRow = 1;
					}
				}

				// Pour supprimer une ligne
				else if (input.mouseX >= SCREEN_WIDTH + 339 && input.mouseX <= SCREEN_WIDTH + 370
						 && input.mouseY >= 414 && input.mouseY <= 444)
				{
					if(jeu.selectActivated){
						input.deleteRow = 1;
					}
				}

				// Pour remplir une zone avec la Tile active
				else if (input.mouseX >= SCREEN_WIDTH + 300 && input.mouseX <= SCREEN_WIDTH + 332
						 && input.mouseY >= 452 && input.mouseY <= 482)
				{
					if(jeu.selectZoneActivated){
						input.fillWith = 1;
					}
				}

				// Inverse Vertival
				else if (input.mouseX >= SCREEN_WIDTH + 300 && input.mouseX <= SCREEN_WIDTH + 332
							&& input.mouseY >= 488 && input.mouseY <= 518)
				{
					if(jeu.selectZoneActivated){
						input.flipVertical = 1;
					}
				}

				// Inverse Horizontal
				else if (input.mouseX >= SCREEN_WIDTH + 339 && input.mouseX <= SCREEN_WIDTH + 370
							&& input.mouseY >= 488 && input.mouseY <= 518)
				{
					if(jeu.selectZoneActivated){
						input.flipHorizontal = 1;
					}
				}

				// Pour afficher/cacher de l'information
				else if (input.mouseX >= SCREEN_WIDTH + 339 && input.mouseX <= SCREEN_WIDTH + 370
						 && input.mouseY >= 452 && input.mouseY <= 482)
				{
					jeu.displayInformation = !jeu.displayInformation;
				}

				input.add = 0;
			}
		}
    }

	// Si on appuie sur la molette de la souris, on réinitialise la tile pointée en lui donnant la valeur BLANK_TILE (0 par défaut)
    else if (input.remove == 1 && offLimits == 0)
    {
        if(cursor.x < SCREEN_WIDTH + 1)
        {
            int posX = (map.startX + cursor.x) / map.newTileSize;
			int posY = (map.startY + cursor.y - TABS_HEIGHT) / map.newTileSize;
			deleteTile(posX, posY, posX, posY);
			mapWasModified = 1;
            cursor.tileID = 0;
        }
    }

    // Actions réalisées avec la molette de la souris (haut ou bas)
	if (input.previous == 1)
    {
        // Si on utilise la molette, soit on dézoome, soit on sélectionne la Tile suivante dans le Tileset
		if(input.modeZoom == 1){

			// Mode Zoom activé, on dézoome la Map
			if(map.zoom > MAP_ZOOM_MIN){
				map.zoom -= MAP_ZOOM_STEP;

				if(map.zoom < MAP_ZOOM_MIN)
				{
					map.zoom = MAP_ZOOM_MIN;
				}

				// On calcul à partir de quel point on doit à présent dessiner la Map
				// pour que la Tile sous le pointeur de la souris reste la même (enfin, à peu près ^^)

				// Tile sous le pointeur
				int pointedTileX = ((input.mouseX + map.startX) / (map.newTileSize*1.0) );
				int pointedTileY = ((input.mouseY - TABS_HEIGHT + map.startY) / (map.newTileSize*1.0) );

				// Nouvelle taille d'une Tile en fonction du zoom
				float newTileSize = TILE_SIZE * (map.zoom/100.0);
				map.newTileSize = (int) newTileSize;

				// On calcul l'écart causé par la perte de précision de la taille d'une Tile (arrondie à l'entier inférieur)
				float gapCorrectionX = (float)(newTileSize - (int)newTileSize) * pointedTileX;
				float gapCorrectionY = (float)(newTileSize - (int)newTileSize) * pointedTileY;


				// Calcul du nouveau point de départ
				map.startX = (pointedTileX * newTileSize - input.mouseX) - gapCorrectionX ;
				map.startY = (pointedTileY * newTileSize - input.mouseY) + TABS_HEIGHT - gapCorrectionY;

				// On place toujours le debut de la Map à une valeur multiple de la taille d'une Tile
				float marginX = map.startX % map.newTileSize;
				float marginY = map.startY % map.newTileSize;
				if(marginX > map.newTileSize/2){
					map.startX += map.newTileSize - marginX;
				}else{
					map.startX -= marginX;
				}
				if(marginY > map.newTileSize/2){
					map.startY += map.newTileSize - marginY;
				}else{
					map.startY -= marginY;
				}
			}
		}
		else
		{
			// On sélectionne la Tile précédente
			cursor.tileID--;
			if (cursor.tileID < 0){
				cursor.tileID = MAX_TILES;
			}else if (cursor.tileID > MAX_TILES){
				cursor.tileID = 0;
			}
		}
        input.previous = 0;
    }

    if (input.next == 1)
    {
		// Si on utilise la molette, soit on zoome, soit on sélectionne la Tile précédente dans le Tileset
		if(input.modeZoom == 1){

			if(map.zoom < MAP_ZOOM_MAX){
				map.zoom += MAP_ZOOM_STEP;

				if(map.zoom > MAP_ZOOM_MAX){
					map.zoom = MAP_ZOOM_MAX;
				}

				// On calcul à partir de quel point on doit à présent dessiner la Map
				// pour que la Tile sous le pointeur de la souris reste la même (enfin, à peu près ^^)

				// Tile sous le pointeur
				int pointedTileX = ((input.mouseX + map.startX) / (map.newTileSize*1.0) );
				int pointedTileY = ((input.mouseY - TABS_HEIGHT + map.startY) / (map.newTileSize*1.0) );

				// Nouvelle taille d'une Tile en fonction du zoom
				float newTileSize = TILE_SIZE * (map.zoom/100.0);
				map.newTileSize = (int) newTileSize;

				// On calcul l'écart causé par la perte de précision de la taille d'une Tile (arrondie à l'entier inférieur)
				float gapCorrectionX = (newTileSize - (int)newTileSize) * pointedTileX;
				float gapCorrectionY = (newTileSize - (int)newTileSize) * pointedTileY;

				// Calcul du nouveau point de départ
				map.startX = (pointedTileX * newTileSize - input.mouseX)- gapCorrectionX ;
				map.startY = (pointedTileY * newTileSize - input.mouseY) + TABS_HEIGHT - gapCorrectionY;

				// On place toujours le debut de la Map à une valeur multiple de la taille d'une Tile
				float marginX = map.startX % map.newTileSize;
				float marginY = map.startY % map.newTileSize;
				if(marginX > map.newTileSize/2){
					map.startX += map.newTileSize - marginX;
				}else{
					map.startX -= marginX;
				}
				if(marginY > map.newTileSize/2){
					map.startY += map.newTileSize - marginY;
				}else{
					map.startY -= marginY;
				}
			}
		}
		else
		{
			// On sélectionne la Tile suivante
			cursor.tileID++;
			if (cursor.tileID < 0){
				cursor.tileID = MAX_TILES - 1;
			}else if (cursor.tileID > MAX_TILES){
				cursor.tileID = 0;
			}
		}
        input.next = 0;
    }



    /* On copie le numéro de la tile pointée dans le curseur pour qu'il affiche et colle
    désormais cette tile */
    if (input.copy == 1  && offLimits == 0)
    {
		// On reset la sélection
		jeu.selectActivated = 0;
		jeu.selectZoneActivated = 0;

        if(cursor.x <= SCREEN_WIDTH)
        {
            // On copie la Tile
			if ( input.layerDrawn == LAYER_ACTION ){
				cursor.tileID = map.tileAction[currentTileY][currentTileX];
			}
			else if ( input.layerDrawn == LAYER_BACKGROUD ){
				cursor.tileID = map.tileBackground[currentTileY][currentTileX];
			}
			else if ( input.layerDrawn == LAYER_FOREGROUD ){
				cursor.tileID = map.tileForeground[currentTileY][currentTileX];
			}
            input.copy = 0;
        }
    }

    /* Pour réinitialiser la map, on appelle la fonction reinitMap puis on recharge la map */
    if (input.reinit == 1)
    {
        jeu.messageBox = 1;
        sprintf(jeu.messageBoxText, "Do you want to reset?");
        jeu.messageBoxAction = RESET;
        input.reinit = 0;
    }

    /* Sauvegarde la map (cf. plus loin) */
    if (input.save == 1)
    {
        jeu.messageBox = 1;
        sprintf(jeu.messageBoxText, "Do you want to save?");
        jeu.messageBoxAction = SAVE;
        input.save = 0;
    }

    /* Charge la map (notre bonne vieille fonction ;) ) */
    if (input.load == 1)
    {
        jeu.messageBox = 1;
        sprintf(jeu.messageBoxText, "Do you want to reload?");
        jeu.messageBoxAction = LOAD;
        input.load = 0;
    }

    /* Copie la map dans le fichier pastebin.txt */
    if (input.copyMap == 1)
    {
        sprintf(file, "map/pastebin.txt");
        saveMap(file);
        jeu.message = 1;
        sprintf(jeu.messageText, "Map copied !");
        input.copyMap = 0;
    }

    /* Colle la map depuis pastebin.txt */
    if (input.pasteMap == 1)
    {
        jeu.messageBox = 1;
        sprintf(jeu.messageBoxText, "Do you want to paste?");
        jeu.messageBoxAction = PASTE;
        input.pasteMap = 0;
    }

    if (input.changeLayer == 1)
    {
        input.layerDrawn++;
        if ( input.layerDrawn > 4 ){
            input.layerDrawn = 1;
		}
        input.changeLayer = 0;
    }

	// *****************************
	// Gestion du CTRL+Z et CTRL+Y
	// *****************************

	// Lorsqu'on colle des Tiles sur la Map, on attend que le bouton gauche
	// soit relâché avant de sauvegarder les modifications.
	if(memoLeftClicAction == 1 && input.add == 0){
		memoLeftClicAction = 0;
		mapWasModified = 1;
	}
	// Si une modification a été apportée à la Map, on la mémorise
	if(mapWasModified == 1){
		// On mémorise l'état de la Map
		memorizeMapState();
	}
	else if(input.ctrl_Z == 1){
		input.ctrl_Z = 0;
		int rez = control_Z();
		if( rez == 0){
			sprintf(jeu.messageText, "No data available...");
		}else{
			sprintf(jeu.messageText, "Previous Map restored!");
		}
		jeu.message = 1;
	}
	else if(input.ctrl_Y == 1){
		input.ctrl_Y = 0;
		int rez = control_Y();
		if( rez == 0){
			sprintf(jeu.messageText, "Nothing to restore...");
		}else{
			sprintf(jeu.messageText, "Next saved Map restored!");
		}
		jeu.message = 1;
	}

    /* On rajoute un délai entre 2 tours de boucle pour que le scrolling soit moins rapide */
    if (input.left == 1 || input.right == 1 || input.up == 1 || input.down == 1 ||
            input.Tactileleft == 1 || input.Tactileright == 1 || input.Tactileup == 1 || input.Tactiledown == 1)
    {
        SDL_Delay(10);
    }

}


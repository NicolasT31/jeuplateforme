#include "map.h"

using namespace std;
using namespace sf;

Map::Map()
{ 
    //Chargement du background
    if(!backgroundTexture.loadFromFile("graphics/background.png")) {
        cout << "Erreur lors du chargement du background" << endl;
    } else {
        background.setTexture(backgroundTexture);
    }

    //Chargement des tilesets
    if(!tileSet1Texture.loadFromFile("graphics/tileset1.png")) {
        cout << "Erreur lors du chargement du tileset 1";
    } else {
        tileSet1.setTexture(tileSet1Texture);
    }

   if (!tileSet1BTexture.loadFromFile("graphics/tileset1b.png"))
   {
        cout << "Erreur durant le chargement de l'image du tileset 1b." << endl;
   }
   else {
        tileSet1B.setTexture(tileSet1BTexture);
   }

   //Variables
   mapTimer = TIME_BETWEEN_2_FRAMES * 3;
   tileSetNumber = 0;
   level = 1;
   startX = startY = 0;
}

//Accesseurs
int Map::getBeginX(void) { return beginx; }
int Map::getBeginY(void) { return beginy; }
int Map::getStartX(void) { return startX; }
int Map::getStartY(void) { return startY; }
int Map::getMaxX(void) { return maxX; }
int Map::getMaxY(void) { return maxY; }
int Map::getTile(int y, int x) const { return tile[y][x]; }
int Map::getLevel(void) const { return level; }

//Mutateurs
void Map::setLevel(int valeur) { level = valeur; }
void Map::setStartX(int valeur) { startX = valeur; }
void Map::setStartY(int valeur) { startY = valeur; }
void Map::setTile(int y, int x, int valeur) { tile[y][x] = valeur; }

//Fonctions

void Map::changeLevel(void) {
    string filename;
    filename = "map/map" + to_string(level) + ".txt";
    loadMap(filename);
}

void Map::drawBackground(RenderWindow &window) {
    window.draw(background);
}

void Map::loadMap(string filename) {
    fstream fin;
    int x = 0;
    int y = 0;

    maxX = 0;
    maxY = 0;

    vector<vector<int>> lignes;

    vector<int> myVectData; //temporaire
    string strBuf, strTmp; //temporaire

    stringstream iostr;

    fin.open(filename, fstream::in);

    if(!fin.is_open()) {
        cerr << "Erreur de chargement de fichier.";
        exit(1);
    }

    while(!fin.eof()) {
        getline(fin, strBuf);

        if(!strBuf.size()) {
            continue;
        }

        iostr.clear();
        iostr.str(strBuf);
        myVectData.clear();

        while(true) {
            getline(iostr, strTmp, ' ');
            myVectData.push_back(atoi(strTmp.c_str()));
            if(!iostr.good()) {
                break;
            }
        }

        if(myVectData.size()) {
            lignes.push_back(myVectData);
        }
    }

    fin.close();

    beginx = lignes[0][0];
    beginy = lignes[0][1];
    tilesetAffiche = lignes[0][2];

    for(x = 3; x < MAX_MAP_X; x++) {
        tile[y][x-3] = lignes[y][x];
    }

    for(y = 1; y < MAX_MAP_Y; y++) {
        for(x = 0; x < MAX_MAP_X; x++) {
            tile[y][x] = lignes[y][x];
            if(tile[y][x] > 0) {
                if(x > maxX) {
                    maxX = x;
                }
                if( y > maxY) {
                    maxY = y;
                }
            }
        }
    }

   for (y = 0; y < MAX_MAP_Y; y++)
   {
        for (x = 0; x < MAX_MAP_X; x++)
        {
             tile2[y][x] = lignes[y + MAX_MAP_Y][x];
        }
   }

  for (y = 0; y < MAX_MAP_Y; y++)
  {
      for (x = 0; x < MAX_MAP_X; x++)
      {
          tile3[y][x] = lignes[y + MAX_MAP_Y * 2][x];
      }
  }

  maxX = (maxX + 1) * TILE_SIZE;
  maxY = (maxY + 1) * TILE_SIZE;
}

void Map::draw(int layer, RenderWindow &window) {
    int x, y, mapX, x1, x2, mapY, y1, y2, xsource, ysource, a;

    mapX = startX / TILE_SIZE;
    x1 = (startX % TILE_SIZE) * -1;
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

    mapY = startY / TILE_SIZE;
    y1 = (startY % TILE_SIZE) * -1;
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

    if(mapTimer <= 0) {
        if(tileSetNumber = 0) {
            tileSetNumber = 1;
            mapTimer = TIME_BETWEEN_2_FRAMES *3;
        } else {
            tileSetNumber = 0;
            mapTimer = TIME_BETWEEN_2_FRAMES *3;
        }
    } else {
        mapTimer--;
    }

    if(layer == 1) {
        for(y = y1; y < y2; y += TILE_SIZE) {
            mapX = startX / TILE_SIZE;

            for(x = x1; x < x2; x += TILE_SIZE) {
                a = tile[mapY][mapX];
                ysource = a/10*TILE_SIZE;
                xsource = a%10*TILE_SIZE;

                if(tileSetNumber == 0) {
                    tileSet1.setPosition(Vector2f(x,y));
                    tileSet1.setTextureRect(sf::IntRect(xsource, ysource, TILE_SIZE, TILE_SIZE));
                    window.draw(tileSet1);
                } else {
                    tileSet1B.setPosition(Vector2f(x,y));
                    tileSet1B.setTextureRect(sf::IntRect(xsource, ysource, TILE_SIZE, TILE_SIZE));
                    window.draw(tileSet1B);
                }

                mapX++;
            }

            mapY++;
        }
    } else if (layer == 2) {
        for(y = y1; y < y2; y += TILE_SIZE) {
            mapX = startX / TILE_SIZE;

            for(x = x1; x < x2; x += TILE_SIZE) {
                a = tile2[mapY][mapX];
                ysource = a/10*TILE_SIZE;
                xsource = a%10*TILE_SIZE;

                if(tileSetNumber == 0) {
                    tileSet1.setPosition(Vector2f(x,y));
                    tileSet1.setTextureRect(sf::IntRect(xsource, ysource, TILE_SIZE, TILE_SIZE));
                    window.draw(tileSet1);
                } else {
                    tileSet1B.setPosition(Vector2f(x,y));
                    tileSet1B.setTextureRect(sf::IntRect(xsource, ysource, TILE_SIZE, TILE_SIZE));
                    window.draw(tileSet1B);
                }

                mapX++;
            }

            mapY++;
        }
    } else if(layer == 3) {
        for(y = y1; y < y2; y += TILE_SIZE) {
            mapX = startX / TILE_SIZE;

            for(x = x1; x < x2; x += TILE_SIZE) {
                a = tile3[mapY][mapX];
                ysource = a/10*TILE_SIZE;
                xsource = a%10*TILE_SIZE;

                if(tileSetNumber == 0) {
                    tileSet1.setPosition(Vector2f(x,y));
                    tileSet1.setTextureRect(sf::IntRect(xsource, ysource, TILE_SIZE, TILE_SIZE));
                    window.draw(tileSet1);
                } else {
                    tileSet1B.setPosition(Vector2f(x,y));
                    tileSet1B.setTextureRect(sf::IntRect(xsource, ysource, TILE_SIZE, TILE_SIZE));
                    window.draw(tileSet1B);
                }

                mapX++;
            }

            mapY++;
        }
    }
}

void Map::testDefilement(void) {
    if(startX < maxX - SCREEN_WIDTH - 10) {
        startX += 10;
    }
}

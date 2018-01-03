#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Map;
class Input;

class Player
{
public:
    Player();

      struct Point { int x, y; };

    //Accesseurs
   int getX(void) const ;
   int getY(void) const;
   int getW(void) const;
   int getH(void) const;
   float getDirX(void) const;
   float getDirY(void) const;
   int getOnGround(void) const;
   int getLife(void) const;
   int getVies(void) const;
   int getEtoiles(void) const;
   int getDirection(void) const;

   //Mutateurs
   void setX(int valeur);
   void setY(int valeur);
   void setW(int valeur);
   void setH(int valeur);
   void setDirX(float valeur);
   void setDirY(float valeur);
   void setOnGround(bool valeur);
   void setTimerMort(int valeur);
   void setVies(int valeur);
   void setEtoiles(int valeur);
   void setCheckpoint(bool valeur);

   void initialize(Map &map, bool newLevel);
   void draw(Map &map, sf::RenderWindow &window);
   void update(Input &input, Map &map);
   void centerScrolling(Map &map);
   void mapCollision(Map &map);

   //Pentes

   Point segment2segment(int Ax0, int Ay0, int Bx0, int By0, int Cx0, int Cy0, int Dx0, int Dy0);
   void getSlopeSegment(int tx, int ty, int pente, Point &s1, Point &s2);
   int slopeEquation(int pente, double *a, double *b);
   int checkSlope(Map &map);

private:

   int life, invincibleTimer;
   int vies, etoiles;
   int x, y; int h, w;
   bool checkpointActif;
   int respawnX, respawnY;
   int frameNumber, frameTimer, frameMax;
   int etat, direction;
   int timerMort;
   bool onGround;
   float dirX, dirY;
   int saveX, saveY;
   bool Playerjump;
   float dirXmem, dirYmem;
   int posXmem, posYmem;
   int wasOnGround;
   int wasOnSlope;

   sf::Texture rabidjaTexture;
   sf::Sprite rabidja;

   //Constantes

   const int LEVEL_MAX = 2;
   const int MAX_MAP_X = 400;
  const int MAX_MAP_Y = 150;

  const int TILE_SIZE = 32;

  /* Constante pour l'animation */
  const int TIME_BETWEEN_2_FRAMES_PLAYER = 4;

  const int PLAYER_WIDTH = 40;
  const int PLAYER_HEIGTH = 50;
  const int PLAYER_SPEED = 4;

  //Etats
  const int IDLE = 0;
  const int WALK = 1;
  const int JUMP1 = 2;
  const int JUMP2 = 3;
  const int DEAD = 4;

  const int RIGHT = 1;
  const int LEFT = 2;

  const double GRAVITY_SPEED = 0.6;
  const int MAX_FALL_SPEED = 15;
  const int JUMP_HEIGHT = 10;

  const int SCREEN_WIDTH = 800;
  const int SCREEN_HEIGHT = 480;

 //Constantes pour les limites de la caméra avant scrolling
  const int LIMITE_X = 400;
  const int LIMITE_Y = 220;
  const int LIMITE_W = 100;
  const int LIMITE_H = 80;

  enum{ up, down, right, left, attack, jump, enter };

  const int BLANK_TILE = 99;

  const int TILE_TRAVERSABLE = 80;

  const int TILE_POWER_UP_DEBUT = 77;
  const int TILE_POWER_UP_FIN = 79;
  const int TILE_POWER_UP_COEUR = 78;

  //Autres Tiles spéciales
  const int TILE_RESSORT = 125;
  const int TILE_CHECKPOINT = 23;
  const int TILE_MONSTRE = 136;
  const int TILE_PIKES = 127;

 //Tiles plateformes mobiles
  const int TILE_PLATEFORME_DEBUT = 130;
  const int TILE_PLATEFORME_FIN = 131;

  // Tiles pentes à 26.5° ; BenH = de BAS en HAUT ; HenB = De HAUT en BAS
  const int TILE_PENTE_26_BenH_1 = 69;
  const int TILE_PENTE_26_BenH_2 = 70;
  const int TILE_PENTE_26_HenB_1 = 71;
  const int TILE_PENTE_26_HenB_2 = 72;
};

#endif // PLAYER_H

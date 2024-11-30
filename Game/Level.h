#ifndef LEVEL_H
#define LEVEL_H
#include <SFML/Graphics.h>

#include "Map.h"

#define NUMB_BACKGROUND 6

typedef struct Level
{
	sfSprite* background[NUMB_BACKGROUND];
	sfVector2f backgroundSize;
	Map map;
	sfTexture* texture;
	sfSprite* tileSprite;
} Level;


// Prototypes de fonctions
void LoadLevel(Level* const _level);
void UpdateBackgroundParalax(float const _dt, Level* const _level);

void DrawTile(sfRenderWindow* const _renderWindow, Map* _map, sfVector2i _tileSize, sfSprite** _sprite);
void DrawLevel(sfRenderWindow* const _renderWindow, const Level* const _level);

#endif

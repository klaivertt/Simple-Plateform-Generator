#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.h>

#define MAX_PLATEFORME 5

typedef struct Plateforme
{
	sfVector2i size;
	sfVector2i tileID[200];
	sfVector2i origine;
} Plateforme;

typedef struct Map {
	sfVector2i size;
	Plateforme plateforme[MAX_PLATEFORME];
	sfVector2i tileSize;
} Map;

void CreatePlateformeWithBorder(Plateforme* _plateforme, sfVector2i _plateformeLength, sfVector2i _baseID, sfVector2i _randID, sfVector2i _finalID, sfVector2i _origine);
void CreatePlateformeWithLeftBorder(Plateforme* _plateforme, sfVector2i _plateformeLength, sfVector2i _baseID, sfVector2i _randID, sfVector2i _finalID, sfVector2i _origine);
void CreatePlateformeWithRightBorder(Plateforme* _plateforme, sfVector2i _plateformeLength, sfVector2i _baseID, sfVector2i _randID, sfVector2i _finalID, sfVector2i _origine);
void CreatePlateformeWithNoBorder(Plateforme* _plateforme, sfVector2i _plateformeLength, sfVector2i _baseID, sfVector2i _randID, sfVector2i _finalID, int _boderID, int _bottomHeightBorder, int _topHeightBorder, sfVector2i _origine);
// Prototypes de fonctions
void LoadMap(Map* _map);

#endif

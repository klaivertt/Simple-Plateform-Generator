#include <stdio.h>
#include <stdlib.h>
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

void CreatePlateformeWithBorder(Plateforme* _plateforme, sfVector2i _plateformeLength, sfVector2i _baseID, sfVector2i _randID, sfVector2i _finalID, sfVector2i _origine)
{
	_plateforme->size = _plateformeLength;
	_plateforme->origine = _origine;

	size_t max_tiles = _plateformeLength.x * _plateformeLength.y;
	if (max_tiles > 200) {
		printf("Error: Platform size exceeds tileID capacity.\n");
		return;
	}

	for (size_t y = 0; y < _plateformeLength.y; y++) {
		printf("\n");
		printf("\n");
		for (size_t x = 0; x < _plateformeLength.x; x++) {
			sfVector2i id = { 0, 0 };

			if (y == 0)
			{
				if (x == 0)
				{
					id.x = _baseID.x;
				}
				else if (x == _plateformeLength.x - 1)
				{
					id.x = _finalID.x;
				}
				else
				{
					id.x = rand() % _randID.x + _baseID.x + 1;
				}
			}
			else if (y == _plateformeLength.y - 1)
			{
				if (x == 0)
				{
					id.x = _baseID.x;
					id.y = _finalID.y;
				}
				else if (x == _plateformeLength.x - 1)
				{
					id.x = _finalID.x;
					id.y = _finalID.y;
				}
				else
				{
					id.x = rand() % _randID.x + _baseID.x + 1;
					id.y = _finalID.y;
				}
			}
			else
			{
				if (x == 0)
				{
					id.x = _baseID.x;
					id.y = rand() % _randID.y + _baseID.y + 1;
				}
				else if (x == _plateformeLength.x - 1)
				{
					id.x = _finalID.x;
					id.y = rand() % _randID.y + _baseID.y + 1;
				}
				else
				{
					id.x = rand() % _randID.x + _baseID.x + 1;
					id.y = rand() % _randID.y + _baseID.y + 1;
				}
			}
			//printf("Id value : x = %d, y = %d\t value inside x = %d, y = %d\n", x, y, id.x, id.y);
			_plateforme->tileID[(y * _plateformeLength.x) + x].x = id.x;
			_plateforme->tileID[(y * _plateformeLength.x) + x].y = id.y;
		}
	}
}

void CreatePlateformeWithLeftBorder(Plateforme* _plateforme, sfVector2i _plateformeLength, sfVector2i _baseID, sfVector2i _randID, sfVector2i _finalID, sfVector2i _origine)
{
	_plateforme->size = _plateformeLength;
	_plateforme->origine = _origine;

	size_t max_tiles = _plateformeLength.x * _plateformeLength.y;
	if (max_tiles > 200) {
		printf("Error: Platform size exceeds tileID capacity.\n");
		return;
	}

	for (size_t y = 0; y < _plateformeLength.y; y++) {
		printf("\n");
		printf("\n");
		for (size_t x = 0; x < _plateformeLength.x; x++) {
			sfVector2i id = { 0, 0 };

			if (y == 0)
			{
				if (x == 0)
				{
					id.x = _baseID.x;
				}
				else
				{
					id.x = rand() % _randID.x + _baseID.x + 1;
				}
			}
			else if (y == _plateformeLength.y - 1)
			{
				if (x == 0)
				{
					id.x = _baseID.x;
					id.y = _finalID.y;
				}
				else
				{
					id.x = rand() % _randID.x + _baseID.x + 1;
					id.y = _finalID.y;
				}
			}
			else
			{
				if (x == 0)
				{
					id.x = _baseID.x;
					id.y = rand() % _randID.y + _baseID.y + 1;
				}
				else
				{
					id.x = rand() % _randID.x + _baseID.x + 1;
					id.y = rand() % _randID.y + _baseID.y + 1;
				}
			}
			_plateforme->tileID[(y * _plateformeLength.x) + x].x = id.x;
			_plateforme->tileID[(y * _plateformeLength.x) + x].y = id.y;
		}
	}
}

void CreatePlateformeWithRightBorder(Plateforme* _plateforme, sfVector2i _plateformeLength, sfVector2i _baseID, sfVector2i _randID, sfVector2i _finalID, sfVector2i _origine)
{
	_plateforme->size = _plateformeLength;
	_plateforme->origine = _origine;

	size_t max_tiles = _plateformeLength.x * _plateformeLength.y;
	if (max_tiles > 200) {
		printf("Error: Platform size exceeds tileID capacity.\n");
		return;
	}

	for (size_t y = 0; y < _plateformeLength.y; y++) {
		printf("\n");
		printf("\n");
		for (size_t x = 0; x < _plateformeLength.x; x++) {
			sfVector2i id = { 0, 0 };

			if (y == 0)
			{
				if (x == _plateformeLength.x - 1)
				{
					id.x = _finalID.x;
				}
				else
				{
					id.x = rand() % _randID.x + _baseID.x + 1;
				}
			}
			else if (y == _plateformeLength.y - 1)
			{
				if (x == _plateformeLength.x - 1)
				{
					id.x = _finalID.x;
					id.y = _finalID.y;
				}
				else
				{
					id.x = rand() % _randID.x + _baseID.x + 1;
					id.y = _finalID.y;
				}
			}
			else
			{
				if (x == _plateformeLength.x - 1)
				{
					id.x = _finalID.x;
					id.y = rand() % _randID.y + _baseID.y + 1;
				}
				else
				{
					id.x = rand() % _randID.x + _baseID.x + 1;
					id.y = rand() % _randID.y + _baseID.y + 1;
				}
			}
			_plateforme->tileID[(y * _plateformeLength.x) + x].x = id.x;
			_plateforme->tileID[(y * _plateformeLength.x) + x].y = id.y;
		}
	}
}

void CreatePlateformeWithNoBorder(Plateforme* _plateforme, sfVector2i _plateformeLength, sfVector2i _baseID, sfVector2i _randID, sfVector2i _finalID, int _boderID, int _bottomHeightBorder, int _topHeightBorder, sfVector2i _origine)
{
	_plateforme->size = _plateformeLength;
	_plateforme->origine = _origine;

	size_t max_tiles = _plateformeLength.x * _plateformeLength.y;
	if (max_tiles > 200) {
		printf("Error: Platform size exceeds tileID capacity.\n");
		return;
	}

	for (size_t y = 0; y < _plateformeLength.y; y++) {
		printf("\n");
		printf("\n");
		for (size_t x = 0; x < _plateformeLength.x; x++) {
			sfVector2i id = { 0, 0 };

			if (y == 0)
			{
				if (x == 0)
				{
					id.x = _baseID.x;
				}
				else if (x == _plateformeLength.x - 1)
				{
					id.x = _finalID.x;
				}
				else
				{
					id.x = rand() % _randID.x + _baseID.x + 1;
				}
			}


			if (_bottomHeightBorder == 0 && y == _plateformeLength.y - 1)
			{
				if (y == _topHeightBorder - 1)
				{
					if (x == 0)
					{
						id.x = _baseID.x;
						id.y = _boderID + 1;
					}
					else if (x == _plateformeLength.x - 1)
					{
						id.x = _finalID.x;
						id.y = _boderID + 1;
					}
					else
					{
						id.x = rand() % _randID.x + _baseID.x + 1;
						id.y = _finalID.y;
					}
				}
				else
				{
					id.x = rand() % _randID.x + _baseID.x + 1;
					id.y = _finalID.y;
				}
			}
			else if (y > 0)
			{
				if (y == _plateformeLength.y - 1)
				{
					if (x == 0)
					{
						id.x = _baseID.x;
						id.y = _finalID.y;
					}
					else if (x == _plateformeLength.x - 1)
					{
						id.x = _finalID.x;
						id.y = _finalID.y;
					}
					else
					{
						id.x = rand() % _randID.x + _baseID.x + 1;
						id.y = _finalID.y;
					}
				}
				else if (y < _topHeightBorder)
				{
					if (x == 0)
					{
						id.x = _baseID.x;
						id.y = rand() % _randID.y + _baseID.y + 1;
					}
					else if (x == _plateformeLength.x - 1)
					{
						id.x = _finalID.x;
						id.y = rand() % _randID.y + _baseID.y + 1;
					}
					else
					{
						id.x = rand() % _randID.x + _baseID.x + 1;
						id.y = rand() % _randID.y + _baseID.y + 1;
					}
				}
				else if (y == _topHeightBorder)
				{
					if (x == 0)
					{
						id.x = _baseID.x;
						id.y = _boderID;
					}
					else if (x == _plateformeLength.x - 1)
					{
						id.x = _finalID.x;
						id.y = _boderID;
					}
					else
					{
						id.x = rand() % _randID.x + _baseID.x + 1;
						id.y = rand() % _randID.y + _baseID.y + 1;
					}
				}
				else if (y > _plateformeLength.y - _bottomHeightBorder - 1)
				{
					if (x == 0)
					{
						id.x = _baseID.x;
						id.y = rand() % _randID.y + _baseID.y + 1;
					}
					else if (x == _plateformeLength.x - 1)
					{
						id.x = _finalID.x;
						id.y = rand() % _randID.y + _baseID.y + 1;
					}
					else
					{
						id.x = rand() % _randID.x + _baseID.x + 1;
						id.y = rand() % _randID.y + _baseID.y + 1;
					}
				}
				else if (y == _plateformeLength.y - _bottomHeightBorder - 1)
				{

					if (x == 0)
					{
						id.x = _baseID.x + 1;
						id.y = _boderID;
					}
					else if (x == _plateformeLength.x - 1)
					{
						id.x = _finalID.x - 1;
						id.y = _boderID;
					}
					else
					{
						id.x = rand() % _randID.x + _baseID.x + 1;
						id.y = rand() % _randID.y + _baseID.y + 1;
					}
				}
				else
				{
					id.x = rand() % _randID.x + _baseID.x + 1;
					id.y = rand() % _randID.y + _baseID.y + 1;
				}
			}


			_plateforme->tileID[(y * _plateformeLength.x) + x].x = id.x;
			_plateforme->tileID[(y * _plateformeLength.x) + x].y = id.y;
		}
	}
}

void LoadMap(Map* _map)
{
	_map->size.y = 23;
	_map->size.x = 40;
	_map->tileSize.x = 48;
	_map->tileSize.y = 48;


	CreatePlateformeWithBorder(&_map->plateforme[0], (sfVector2i) { 5, 1 }, (sfVector2i) { 0, 0 }, (sfVector2i) { 2, 2 }, (sfVector2i) { 3, 3 }, (sfVector2i) { (0 * _map->tileSize.x), (10 * _map->tileSize.y) });
	CreatePlateformeWithLeftBorder(&_map->plateforme[1], (sfVector2i) { 10, 7 }, (sfVector2i) { 5, 0 }, (sfVector2i) { 2, 2 }, (sfVector2i) { 8, 3 }, (sfVector2i) { (5 * _map->tileSize.x), (8 * _map->tileSize.y) });
	CreatePlateformeWithNoBorder(&_map->plateforme[2], (sfVector2i) { 10, 12 }, (sfVector2i) { 5, 0 }, (sfVector2i) { 2, 2 }, (sfVector2i) { 8, 3 }, 4, 2, 3, (sfVector2i) { (15 * _map->tileSize.x), (5 * _map->tileSize.y) });
	CreatePlateformeWithRightBorder(&_map->plateforme[3], (sfVector2i) { 10, 7 }, (sfVector2i) { 5, 0 }, (sfVector2i) { 2, 2 }, (sfVector2i) { 8, 3 }, (sfVector2i) { (25 * _map->tileSize.x), (8 * _map->tileSize.y) });
}

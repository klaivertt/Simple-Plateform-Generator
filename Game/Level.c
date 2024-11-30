#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.h>
#include <SFML/Audio.h>

#include "Map.h"
#include "Utilities.h"

#define NUMB_BACKGROUND 6

typedef struct Level
{
	sfSprite* background[NUMB_BACKGROUND];
	sfVector2f backgroundSize;
	Map map;
	sfTexture* texture;
	sfSprite* tileSprite;
} Level;

void LoadLevel(Level* const _level)
{
	sfVector2f backgroundPosition = { 0, 0 };
	CreateSprite(&_level->background[0], backgroundPosition, "Assets/Sprites/Background/background_layer_1.png");
	sfVector2u size = sfTexture_getSize(sfSprite_getTexture(_level->background[0]));

	_level->backgroundSize.x = (float)size.x;
	_level->backgroundSize.y = (float)size.y;


	CreateSprite(&_level->background[1], backgroundPosition, "Assets/Sprites/Background/background_layer_2.png");

	CreateSprite(&_level->background[2], backgroundPosition, "Assets/Sprites/Background/background_layer_3.png");
	backgroundPosition.x += _level->backgroundSize.x;
	CreateSprite(&_level->background[3], (sfVector2f) { backgroundPosition.x, backgroundPosition.y }, "Assets/Sprites/Background/background_layer_1.png");

	CreateSprite(&_level->background[4], (sfVector2f) { backgroundPosition.x, backgroundPosition.y }, "Assets/Sprites/Background/background_layer_2.png");

	CreateSprite(&_level->background[5], (sfVector2f) { backgroundPosition.x, backgroundPosition.y }, "Assets/Sprites/Background/background_layer_3.png");

	LoadMap(&_level->map);

	_level->texture = sfTexture_createFromFile("Assets/Sprites/tileset.png", NULL);

	_level->tileSprite = sfSprite_create();
	sfSprite_setTexture(_level->tileSprite, _level->texture, sfTrue);
}

void UpdateBackgroundParalax(float const _dt, Level* const _level)
{
	float speed = 300;

	for (int i = 0; i < NUMB_BACKGROUND; i++)
	{
		if (sfKeyboard_isKeyPressed(sfKeyD))
		{
			sfSprite_move(_level->background[i], (sfVector2f) { -speed * _dt, 0 });
		}
		else if (sfKeyboard_isKeyPressed(sfKeyQ))
		{
			sfSprite_move(_level->background[i], (sfVector2f) { speed* _dt, 0 });
		}

		// Vérifie et réinitialise la position pour créer la boucle
		sfVector2f pos = sfSprite_getPosition(_level->background[i]);
		if (pos.x < -_level->backgroundSize.x)
		{
			sfSprite_setPosition(_level->background[i], (sfVector2f) { pos.x + _level->backgroundSize.x * 2, pos.y });
		}
		else if (pos.x > _level->backgroundSize.x)
		{
			sfSprite_setPosition(_level->background[i], (sfVector2f) { pos.x - _level->backgroundSize.x * 2, pos.y });
		}
	}
}

void DrawTile(sfRenderWindow* const _renderWindow, Map* _map, sfVector2i _tileSize, sfSprite** _sprite)
{
	size_t sizeOf = sizeof(_map->plateforme) / sizeof(_map->plateforme[0]);
	for (int i = 0; i < sizeOf; i++)
	{
		for (int y = 0; y < _map->plateforme[i].size.y; y++)
		{
			for (int x = 0; x < _map->plateforme[i].size.x; x++)
			{
				int idY = _map->plateforme[i].tileID[y * _map->plateforme[i].size.x + x].y;
				//printf("%d \n", _map->plateforme[i].tileID[y].y);
				int idX = _map->plateforme[i].tileID[y * _map->plateforme[i].size.x + x].x;

				int newTileX = idX * _tileSize.x;
				int newTileY = idY * _tileSize.y;

				// Définir la sous-texture de la tuile
				sfIntRect textureRect = { newTileX, newTileY, _tileSize.x, _tileSize.y };
				sfSprite_setTextureRect(*_sprite, textureRect);

				// Calculer la position dans la fenêtre
				sfVector2f position = { (x * _tileSize.x) + _map->plateforme[i].origine.x, (y * _tileSize.y) + _map->plateforme[i].origine.y};
				sfSprite_setPosition(*_sprite, position);

				sfRenderWindow_drawSprite(_renderWindow, *_sprite, NULL);
			}
		}
	}
}

void DrawLevel(sfRenderWindow* const _renderWindow, const Level* const _level)
{
	for (int i = 0; i < NUMB_BACKGROUND; i++)
	{
		sfRenderWindow_drawSprite(_renderWindow, _level->background[i], NULL);
	}

	DrawTile(_renderWindow , &_level->map, _level->map.tileSize, &_level->tileSprite);
}

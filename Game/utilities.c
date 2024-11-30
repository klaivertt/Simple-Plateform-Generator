#include <SFML/Graphics.h>

void CreateSprite(sfSprite** const _sprite, sfVector2f position, const char* _filepath)
{
	*_sprite = sfSprite_create();
	sfSprite_setPosition(*_sprite, position);

	sfTexture* texture = sfTexture_createFromFile(_filepath, NULL);
	sfSprite_setTexture(*_sprite, texture, sfTrue);
}
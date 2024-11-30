#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include "Level.h"
#pragma region Define
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define BPP 32
#define MAX_FPS 240
#define SCREEN_NAME "Simple Plateform Generator"

#pragma endregion


#pragma region Struct and enum
typedef enum GameState
{
	MENU,
	GAME,
} GameState;

typedef struct MainData
{
	sfRenderWindow* renderWindow;
	sfClock* clock;
}MainData;

typedef struct Player
{
	int x, y;
}Player;

typedef struct Color
{
	sfColor blueGrey;
}Color;

typedef struct HUD
{
	sfFont* font;
	sfFont* fontTitle;
	sfText* fpsText;
	sfSprite* munuBackground;
	sfText* titleText;
	sfText* playText;
	sfBool isColidingPlay;
	sfText* quitText;
	sfBool isColidingQuit;
}HUD;

typedef struct GameData
{
	Player player;
	Color color;
	HUD hud;
	GameState currentState;
	Level level;
}GameData;
#pragma endregion

#pragma region CoreDefine
void Load(MainData* const _mainData, GameData* const _gameData);

void PollEvent(const sfRenderWindow* const _renderWindow, GameData* const _gameData);
void OnKeyPressed(sfKeyEvent _key, const sfRenderWindow* const _renderWindow, GameData* const _gameData);
void OnMouseButtonPressed(sfMouseButtonEvent _button, const sfRenderWindow* const _renderWindow, GameData* const _gameData);
void OnMouseMoved(sfMouseButtonEvent _button, const sfRenderWindow* const _renderWindow, GameData* const _gameData);

void Update(MainData* const _mainData, GameData* const _gameData);
void Draw(sfRenderWindow* const _renderWindow, const GameData* const _gameData);
void Cleanup(MainData* const _mainData, GameData* const _gameData);
#pragma endregion

void CreateSprite(sfSprite** const _sprite, sfVector2f position, const char* _filepath);
sfBool IsMouseOverText(sfText* _text, sfVector2i _mousePos);

void LoadScreen(MainData* const _mainData);
void LoadHud(HUD* const _hud);

void LoadPlayer(Player* const _player);
void PlayerUpdate(float _dt, GameData* const _gameData);

#pragma region Core
int main(void)
{
	MainData mainData = { 0 };
	GameData gameData = { 0 };
	Load(&mainData, &gameData);

	while (sfRenderWindow_isOpen(mainData.renderWindow))
	{
		PollEvent(mainData.renderWindow, &gameData);

		Update(&mainData, &gameData);

		Draw(mainData.renderWindow, &gameData);
	}

	Cleanup(&mainData, &gameData);

	return EXIT_SUCCESS;
}

void Load(MainData* const _mainData, GameData* const _gameData)
{
	LoadScreen(_mainData);
	LoadPlayer(&_gameData->player);
	LoadHud(&_gameData->hud);
	LoadLevel(&_gameData->level);

	_gameData->color.blueGrey = sfColor_fromRGB(119, 136, 153);
	_gameData->currentState = GAME;

	_mainData->clock = sfClock_create();
}

void PollEvent(const sfRenderWindow* const _renderWindow, GameData* const _gameData)
{
	sfEvent event;
	while (sfRenderWindow_pollEvent(_renderWindow, &event))
	{
		switch (event.type)
		{
		case sfEvtClosed:
			sfRenderWindow_close(_renderWindow);
			break;
		case sfEvtKeyPressed:
			OnKeyPressed(event.key, _renderWindow, _gameData);
			break;
		case sfEvtMouseButtonPressed:
			OnMouseButtonPressed(event.mouseButton, _renderWindow, _gameData);
			break;
		case sfEvtMouseMoved:
			OnMouseMoved(event.mouseButton, _renderWindow, _gameData);
			break;
		default:
			break;
		}
	}
}

void OnKeyPressed(sfKeyEvent _key, const sfRenderWindow* const _renderWindow, GameData* const _gameData)
{
	switch (_key.code)
	{
	case sfKeyEscape:
		sfRenderWindow_close(_renderWindow);
		break;
	default:
		break;
	}
}

void OnMouseMoved(sfMouseButtonEvent _button, const sfRenderWindow* const _renderWindow, GameData* const _gameData)
{
}

void OnMouseButtonPressed(sfMouseButtonEvent _button, const sfRenderWindow* const _renderWindow, GameData* const _gameData)
{
	switch (_button.button)
	{
	case sfMouseLeft:
		if (_gameData->currentState == MENU)
		{
			sfVector2i mousePos = { _button.x, _button.y };

			if (IsMouseOverText(_gameData->hud.playText, mousePos))
			{
				_gameData->currentState = GAME;
			}
			else if (IsMouseOverText(_gameData->hud.quitText, mousePos))
			{
				sfRenderWindow_close(_renderWindow);
			}
		}
		break;
	default:
		printf("touche souris enfoncer\n");
		break;
	}
}

void Update(MainData* const _mainData, GameData* const _gameData)
{
	float dt = sfTime_asSeconds(sfClock_restart(_mainData->clock));
	char buffer[12];
	snprintf(buffer, sizeof(buffer), "Fps: %.2f", 1 / dt);
	sfText_setString(_gameData->hud.fpsText, buffer);
	PlayerUpdate(dt, _gameData);
	UpdateBackgroundParalax(dt, &_gameData->level);

	if (_gameData->currentState == MENU)
	{
		sfVector2i mousePos = sfMouse_getPositionRenderWindow(_mainData->renderWindow);

		if (IsMouseOverText(_gameData->hud.playText, mousePos))
		{
			_gameData->hud.isColidingPlay = sfTrue;
		}
		else
		{
			_gameData->hud.isColidingPlay = sfFalse;
		}

		if (IsMouseOverText(_gameData->hud.quitText, mousePos))
		{
			_gameData->hud.isColidingQuit = sfTrue;
		}
		else
		{
			_gameData->hud.isColidingQuit = sfFalse;
		}
	}
}

void Draw(sfRenderWindow* const _renderWindow, const GameData* const _gameData)
{
	sfRenderWindow_clear(_renderWindow, _gameData->color.blueGrey);

	if (_gameData->currentState == MENU)
	{
		sfRenderWindow_drawSprite(_renderWindow, _gameData->hud.munuBackground, NULL);
		sfRenderWindow_drawText(_renderWindow, _gameData->hud.titleText, NULL);
		if (_gameData->hud.isColidingPlay)
		{
			sfText_setColor(_gameData->hud.playText, sfColor_fromRGB(255, 100, 100));
		}
		else
		{
			sfText_setColor(_gameData->hud.playText, sfColor_fromRGB(255, 255, 255));
		}

		if (_gameData->hud.isColidingQuit)
		{
			sfText_setColor(_gameData->hud.quitText, sfColor_fromRGB(255, 100, 100));
		}
		else
		{
			sfText_setColor(_gameData->hud.quitText, sfColor_fromRGB(255, 255, 255));
		}
		sfRenderWindow_drawText(_renderWindow, _gameData->hud.playText, NULL);
		sfRenderWindow_drawText(_renderWindow, _gameData->hud.quitText, NULL);
	}
	else if (_gameData->currentState == GAME)
	{
		DrawLevel(_renderWindow, &_gameData->level);
	}
	sfRenderWindow_drawText(_renderWindow, _gameData->hud.fpsText, NULL);
	sfRenderWindow_display(_renderWindow);
}

void Cleanup(MainData* const _mainData, GameData* const _gameData)
{
	sfRenderWindow_destroy(_mainData->renderWindow);
	_mainData->renderWindow = NULL;

	sfClock_destroy(_mainData->clock);
	_mainData->clock = NULL;
}
#pragma endregion

sfBool IsMouseOverText(sfText* _text, sfVector2i _mousePos)
{
	sfFloatRect bounds = sfText_getGlobalBounds(_text);
	return sfFloatRect_contains(&bounds, _mousePos.x, _mousePos.y);
}

void LoadScreen(MainData* const _mainData)
{
	sfVideoMode videoMode = { SCREEN_WIDTH, SCREEN_HEIGHT, BPP };
	_mainData->renderWindow = sfRenderWindow_create(videoMode, SCREEN_NAME, sfDefaultStyle, NULL);
	sfRenderWindow_setVerticalSyncEnabled(_mainData->renderWindow, sfFalse);
	sfRenderWindow_setFramerateLimit(_mainData->renderWindow, MAX_FPS);
}

void LoadHud(HUD* const _hud)
{
	_hud->font = sfFont_createFromFile("Assets/Fonts/arial.ttf");
	_hud->fpsText = sfText_create();
	sfText_setCharacterSize(_hud->fpsText, 20);
	sfText_setFont(_hud->fpsText, _hud->font);
	sfVector2f textPosition = { 20, 20 };
	sfText_setPosition(_hud->fpsText, textPosition);

	sfVector2f munuBackgroundPosition = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	CreateSprite(&_hud->munuBackground, munuBackgroundPosition, "Assets/Sprites/Background.png");
	sfVector2u  munuBackgroundSize = sfTexture_getSize(sfSprite_getTexture(_hud->munuBackground));
	sfSprite_setOrigin(_hud->munuBackground, (sfVector2f) { munuBackgroundSize.x / 2, munuBackgroundSize.y / 2 });

	_hud->fontTitle = sfFont_createFromFile("Assets/Fonts/Roman.ttf");

	_hud->titleText = sfText_create();
	sfText_setCharacterSize(_hud->titleText, 90);
	sfText_setFont(_hud->titleText, _hud->fontTitle);
	sfVector2f titleTextPosition = { 70, 125 };
	sfText_setPosition(_hud->titleText, titleTextPosition);
	char buffer[20];
	snprintf(buffer, sizeof(buffer), "Tartarus King");
	sfText_setString(_hud->titleText, buffer);

	_hud->playText = sfText_create();
	sfText_setCharacterSize(_hud->playText, 50);
	sfText_setFont(_hud->playText, _hud->fontTitle);
	titleTextPosition.x += 40;
	titleTextPosition.y += 200;
	sfText_setPosition(_hud->playText, titleTextPosition);
	snprintf(buffer, sizeof(buffer), "Play");
	sfText_setString(_hud->playText, buffer);

	_hud->quitText = sfText_create();
	sfText_setCharacterSize(_hud->quitText, 50);
	sfText_setFont(_hud->quitText, _hud->fontTitle);
	titleTextPosition.y += 70;
	sfText_setPosition(_hud->quitText, titleTextPosition);
	snprintf(buffer, sizeof(buffer), "Quit");
	sfText_setString(_hud->quitText, buffer);

	_hud->isColidingQuit = sfFalse;
	_hud->isColidingPlay = sfFalse;
}

void LoadPlayer(Player* const _player)
{

}

void PlayerUpdate(float _dt, GameData* const _gameData)
{

}

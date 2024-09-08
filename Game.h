#pragma once

#ifndef GAME_H
#define GAME_H

#include<sstream>	// Secuencia de cadenas
#include <SFML/Graphics.hpp>

#include "Renderer.h"
#include "AudioManager.h"
#include "InputMAnager.h"
#include "FontManager.h"
#include "Player.h"
#include "Pelotas.h"

class Game {

public:

	Game();								// Constructor

	void Update(float dt);				// Controlador del juego
	void Draw(Renderer& renderer);		// Renderizado del juego

	void InitGameWindow(sf::RenderWindow* window);	// Metodo para guardar la ventana del motor

private:
	sf::RenderWindow* _Window;

	FontManager _FontManager;			// Font manager del motor
	AudioManager _AudioManager;			// AudioManager del motor
	InputManager _InputManager;

	sf::Text _UiText;					// Texto de la interfaz
	sf::Text _EndGameText;

	bool _EndGame;						// Esta variable nos dice si el juego ha terminado o no
	Player _Player;
	unsigned _Points;					// Aqui almacenamos los puntos conseguidos en el juego

	std::vector<Pelotas> _Pelotas;
	std::map<std::string, sf::Texture*> _Textures;	// Diccionario donde vamos a guardar las texturas

	float _SpawnTimer;					// Variable para calcular el tiempo hasta invocar un nuevo enemigo
	float _SpawnTimerMax;				// Tiempo para invocar un enemigo
	int _MaxBalls;					// Cantidad maxima de enemigos

	sf::Texture _WorldBackGroundTexture;					// Textura del background
	sf::Sprite _WorldBackGround;							// Background

	const bool& GetEndGame() const;

	void InitVariables();							// Metodo para inicializar variables
	void InitFonts();								// Metodo para inicializar el FontManager
	void InitText();								// Metodo para inicializar el texto de la interfaz
	void InitTextures();
	void InitSprites();

	void SpawnBalls();
	const int RandomizeBallType() const;

	void UpdateCollision();
	void UpdateText();								// Metodo para actualizar el texto en pantalla
	void UpdatePlayer();

	void RenderBackground(Renderer& renderer);		// Metodo para renderizar el background
	void RenderGui(Renderer& renderer);			// Metodo para renderizar el texto de la interfaz
};

#endif

#include "Game.h"

void Game::InitGameWindow(sf::RenderWindow* window)
{
    _Window = window;
}


/// <summary>
/// En esta funcion se cargan las variables de inicio del juego
/// </summary>
void Game::InitVariables()
{
    _EndGame = false;
    _Points = 0;
    _SpawnTimerMax = 10.f;
    _SpawnTimer = _SpawnTimerMax;
    _MaxBalls = 10;
}

const bool& Game::GetEndGame() const
{
    return _EndGame;
}

/// <summary>
/// Cargamos las fuentes del motor
/// </summary>
void Game::InitFonts()
{
    _FontManager.LoadFonts();
}

/// <summary>
/// Asignamos la fuente al texto de la ventat y le damos tamaño y color
/// </summary>
void Game::InitText()
{

    _UiText.setFont(_FontManager.GetFont("Choco"));
    _UiText.setFillColor(sf::Color::White);
    _UiText.setCharacterSize(24);

    _EndGameText.setFont(_FontManager.GetFont("Choco"));
    _EndGameText.setFillColor(sf::Color::Red);
    _EndGameText.setCharacterSize(60);
    _EndGameText.setPosition(sf::Vector2f(20, 300));
    _EndGameText.setString("YOU ARE DEAD!");
}

/// <summary>
/// Inicializamos las texturas 
/// </summary>
void Game::InitTextures()
{

    _Textures["t1"] = new sf::Texture();
    _Textures["t1"]->loadFromFile("./Resources/Textures/t1.png");

    _Textures["t2"] = new sf::Texture();
    _Textures["t2"]->loadFromFile("./Resources/Textures/t2.png");

    _Textures["t3"] = new sf::Texture();
    _Textures["t3"]->loadFromFile("./Resources/Textures/t3.png");

    if (!_WorldBackGroundTexture.loadFromFile("./Resources/bg.png")) {

        std::cout << "Error al cargar la imagen del background" << " \n";
    }
    
}

/// <summary>
/// Cargamos el sprite del background
/// </summary>
void Game::InitSprites()
{
    _WorldBackGround.setTexture(_WorldBackGroundTexture);
}

void Game::SpawnBalls()
{
    if (_SpawnTimer < _SpawnTimerMax) {

        _SpawnTimer += 1.f;
    }
    else {

        if (_Pelotas.size() < _MaxBalls) {

            int rng = RandomizeBallType();

            Pelotas newPelota = Pelotas(*_Window, rng);

            std::cout << rng << " \n";

            switch (rng)
            {
                case 0: 
                    newPelota.SetTexture(_Textures["t2"]);
                    break;
                case 1:
                    newPelota.SetTexture(_Textures["t3"]);
                    break;
                case 2:
                    newPelota.SetTexture(_Textures["t1"]);
                    break;
            }

            _Pelotas.push_back(newPelota);
            _SpawnTimer = 0.f;
        }
    }
}

const int Game::RandomizeBallType() const
{
    int _Type = PelotasTypes::DEFAULT;
    int _RandValue = rand() % 100 + 1;

    if (_RandValue > 60 && _RandValue <= 80) _Type = PelotasTypes::DAMAGING;
    else if (_RandValue > 80 && _RandValue <= 100) _Type = PelotasTypes::HEALING;

    return _Type;
}


// Constructor donde se inizializa el juego
Game::Game()
{
	InitVariables();
	InitFonts();
	InitText();
    InitTextures();
    InitSprites();
}

void Game::UpdateCollision()
{
    // Check collision
    for (size_t i = 0; i < _Pelotas.size(); i++) {

        if (this->_Player.GetShape().getGlobalBounds().intersects(_Pelotas[i].GetShape().getGlobalBounds())) {

            switch (_Pelotas[i].getType())
            {
            case PelotasTypes::DEFAULT:
                _Points++;
                break;
            case PelotasTypes::DAMAGING:
                _Player.TakeDamage(2);
                break;
            case PelotasTypes::HEALING:
                _Player.GainHealth(1);
                break;
            }

            _Pelotas.erase(_Pelotas.begin() + i);


        }

    }
}

/// <summary>
/// Actualiza los puntos de vida
/// </summary>
void Game::UpdateText()
{

    std::stringstream ss;

    ss << " Points: " << _Points << " \n"
        << " Health: " << _Player.GetHp() << " / " << _Player.GetHpMax() << " \n";

    _UiText.setString(ss.str());
}

void Game::UpdatePlayer()
{
    _Player.Update(this->_Window);

    if (_Player.GetHp() <= 0) this->_EndGame = true;
}


/// <summary>
/// Funcion que se encarga de la logica del juego
/// </summary>
/// <param name="dt"> delta time </param>
void Game::Update(float dt)
{
    if (!_EndGame) {
        SpawnBalls();
        UpdatePlayer();
        UpdateCollision();
        UpdateText();
    }
    
}

/// <summary>
/// Funcion para renderizar el fondo del juego
/// </summary>
/// <param name="renderer"></param>
void Game::RenderBackground(Renderer& renderer)
{
    renderer.Draw(_WorldBackGround);
}


/// <summary>
/// Funcion para renderizar el texto de los puntos
/// </summary>
/// <param name="renderer"></param>
void Game::RenderGui(Renderer& renderer)
{
    renderer.Draw(_UiText);
}


/// <summary>
/// Funcion que se encarga de dibujar todos los elementos del juego
/// </summary>
/// <param name="renderer"></param>
void Game::Draw(Renderer& renderer) {
    
    RenderBackground(renderer);

    _Player.Render(_Window);

    for (auto p : _Pelotas) {

        p.Render(_Window);
    }

    RenderGui(renderer);

    if (_EndGame) renderer.Draw(_EndGameText);

    
}





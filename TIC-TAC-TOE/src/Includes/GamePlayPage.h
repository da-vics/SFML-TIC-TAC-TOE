#pragma once

#include "BasePageClass.h"
#include "TicTacGen.h"

enum class ActivePlayer
{
	Player1,
	Player2,
	Computer
};

class GamePlayPage : public BasePageClass
{

public:

	GamePlayPage(sf::RenderWindow* window, bool compPlay) : BasePageClass(window)
	{
		this->_pageID = "MainPage";
		this->NavTOPage = GamePages::None;
		this->computerPlay = compPlay;
		this->setUp();
	}

	bool computerPlay; // if true "AI" is playing
	void Display() override;
	void HandleEvents(sf::Event*) override;

private:
	void setUp();
	void MouseMoveTigger();
	void HoverCheck(sf::RectangleShape*, sf::Text*);
	void OnFocusEvent();

	float boardOriginX{};
	float boardOriginY{};
	bool GamePlay{ true };

	ActivePlayer _currentPlayer{ ActivePlayer::Player1 };
	TicTacGen _ticTacMap;
	sf::RectangleShape _gameBoard;
	sf::RectangleShape _vLine1;
	sf::RectangleShape _vLine2;
	sf::RectangleShape _hLine1;
	sf::RectangleShape _hLine2;
	sf::RectangleShape _gameGridMap[TicTacGen::MaxSize][TicTacGen::MaxSize];
	sf::Text _textGridMap[TicTacGen::MaxSize][TicTacGen::MaxSize];
	sf::RectangleShape _winLine;
	sf::Text _CurrentPlayerTurn;
	const sf::Color LineColor = sf::Color(119, 128, 120);

};


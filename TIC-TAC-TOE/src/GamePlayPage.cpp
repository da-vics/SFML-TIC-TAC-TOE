#include "Includes/GamePlayPage.h"

void GamePlayPage::setUp() {

	this->_gameBoard.setFillColor(sf::Color(69, 74, 70));
	this->_gameBoard.setSize(sf::Vector2f(500.f, 450.f));
	this->_gameBoard.setPosition(sf::Vector2f(this->_window->getSize().x / 2.f - this->_gameBoard.getLocalBounds().width / 2.f,
		this->_window->getSize().y / 2.f - this->_gameBoard.getLocalBounds().height / 2.f));

#pragma region Vertical BoardLine

	boardOriginX = this->_gameBoard.getPosition().x;
	boardOriginY = this->_gameBoard.getPosition().y;

	this->_vLine1.setFillColor(LineColor);
	this->_vLine1.setSize(sf::Vector2f(3.f, 450));
	this->_vLine1.setPosition(sf::Vector2f(boardOriginX + 166.7f, boardOriginY));

	this->_vLine2.setFillColor(LineColor);
	this->_vLine2.setSize(sf::Vector2f(3.f, 450));
	this->_vLine2.setPosition(sf::Vector2f(boardOriginX + 333.3f, boardOriginY));

#pragma endregion

#pragma region Horizontal BoardLine

	this->_hLine1.setFillColor(LineColor);
	this->_hLine1.setSize(sf::Vector2f(500.f, 3.f));
	this->_hLine1.setPosition(sf::Vector2f(boardOriginX, boardOriginY + 150.f));

	this->_hLine2.setFillColor(LineColor);
	this->_hLine2.setSize(sf::Vector2f(500.f, 3.f));
	this->_hLine2.setPosition(sf::Vector2f(boardOriginX, boardOriginY + 300.f));

#pragma endregion

#pragma region SetInitGrid

	auto gridPosX = boardOriginX;
	auto gridPosY = boardOriginY;

	this->_CurrentPlayerTurn.setFont(this->_HeaderFont);
	this->_CurrentPlayerTurn.setCharacterSize(30);
	this->_CurrentPlayerTurn.setFillColor(sf::Color::White);
	this->_CurrentPlayerTurn.setString("Player1's Turn");
	this->_CurrentPlayerTurn.setPosition(gridPosX, boardOriginY - 40);
	this->_CurrentPlayerTurn.setStyle(sf::Text::Bold);

	for (int i = 0; i < TicTacGen::MaxSize;++i) {

		for (int j = 0; j < TicTacGen::MaxSize;++j) {

			this->_gameGridMap[i][j].setFillColor(sf::Color(223, 229, 237));
			this->_gameGridMap[i][j].setSize(sf::Vector2f(166.66f, 150.f));
			this->_gameGridMap[i][j].setPosition(sf::Vector2f(gridPosX, gridPosY));

			this->_textGridMap[i][j].setFont(this->_HeaderFont);
			this->_textGridMap[i][j].setCharacterSize(80);

			gridPosX += 166.66f;
		}
		gridPosY += 150.f;
		gridPosX = boardOriginX;
	}

#pragma endregion

}


void GamePlayPage::Display() {

	this->_window->clear();

	this->_window->draw(this->_bgSprite);
	this->_window->draw(this->_gameBoard);
	this->_window->draw(this->_CurrentPlayerTurn);

	for (int i = 0; i < TicTacGen::MaxSize;++i) {

		for (int j = 0; j < TicTacGen::MaxSize;++j) {

			this->_window->draw(this->_gameGridMap[i][j]); //

			if (this->_ticTacMap.gameMap[i][j] == ' ')
				continue;
			this->_window->draw(this->_textGridMap[i][j]);
		}
	}//

	this->_window->draw(this->_vLine1);
	this->_window->draw(this->_vLine2);
	this->_window->draw(this->_hLine1);
	this->_window->draw(this->_hLine2);

	if (this->GamePlay == false)
		this->_window->draw(this->_winLine);

	this->_window->display();

}

void GamePlayPage::MouseMoveTigger() {


	for (int i = 0; i < TicTacGen::MaxSize; ++i) {

		for (int j = 0; j < TicTacGen::MaxSize; ++j) {

			if (this->IsMouseOverButton(this->_gameGridMap[i][j]))
				this->_gameGridMap[i][j].setFillColor(LineColor);
			else
			{
				this->_gameGridMap[i][j].setFillColor(sf::Color(223, 229, 237));
			}
		}
	}//
}

void GamePlayPage::HoverCheck(sf::RectangleShape* button, sf::Text* buttonText) {

	if (this->IsMouseOverButton(*button))
	{
		button->setFillColor(sf::Color::White);
		buttonText->setFillColor(LineColor);
	}
	else
	{
		button->setFillColor(LineColor);
		buttonText->setFillColor(sf::Color::White);
	}
}


void GamePlayPage::OnFocusEvent() {

	for (int i = 0; i < TicTacGen::MaxSize; ++i) {

		for (int j = 0; j < TicTacGen::MaxSize; ++j) {

			if (this->IsMouseOverButton(this->_gameGridMap[i][j])) {

				if (this->_ticTacMap.gameMap[i][j] == ' ')
				{

					Field fieldPoints{ 0,0 };

					if (this->_currentPlayer == ActivePlayer::Player1) {

						this->_ticTacMap.gameMap[i][j] = 'X';
						this->_textGridMap[i][j].setString("X");
						this->_textGridMap[i][j].setFillColor(sf::Color::Red);

						auto pnts = this->_ticTacMap.GetWin('X');

						if (this->computerPlay && pnts.size() == 0 && this->_ticTacMap.GetWinType != WinType::Stalemate) {

							fieldPoints = this->_ticTacMap.ComputeAI();
							this->_ticTacMap.gameMap[fieldPoints.row][fieldPoints.col] = 'O';
							this->_textGridMap[fieldPoints.row][fieldPoints.col].setString("O");
							this->_textGridMap[fieldPoints.row][fieldPoints.col].setFillColor(sf::Color::Blue);
						}
					}

					else if (this->_currentPlayer == ActivePlayer::Player2) {

						this->_ticTacMap.gameMap[i][j] = 'O';
						this->_textGridMap[i][j].setString("O");
						this->_textGridMap[i][j].setFillColor(sf::Color::Blue);
					}

#pragma region SetPos

					auto sizex = this->_textGridMap[i][j].getLocalBounds().width / 1.f;
					auto sizey = this->_textGridMap[i][j].getLocalBounds().height / 2.f;
					auto gridPosX = this->_gameGridMap[i][j].getPosition().x;
					auto gridPosY = this->_gameGridMap[i][j].getPosition().y;
					this->_textGridMap[i][j].setPosition(sf::Vector2f(gridPosX + sizex, gridPosY + sizey));

					if (computerPlay)
					{
						sizex = this->_textGridMap[fieldPoints.row][fieldPoints.col].getLocalBounds().width / 1.f;
						sizey = this->_textGridMap[fieldPoints.row][fieldPoints.col].getLocalBounds().height / 2.f;
						gridPosX = this->_gameGridMap[fieldPoints.row][fieldPoints.col].getPosition().x;
						gridPosY = this->_gameGridMap[fieldPoints.row][fieldPoints.col].getPosition().y;
						this->_textGridMap[fieldPoints.row][fieldPoints.col].setPosition(sf::Vector2f(gridPosX + sizex, gridPosY + sizey));
					}
#pragma endregion

					std::vector<Field> points;

					if (!this->computerPlay) {

						if (this->_currentPlayer == ActivePlayer::Player1)
							points = this->_ticTacMap.GetWin('X');

						else if (this->_currentPlayer == ActivePlayer::Player2 || this->_currentPlayer == ActivePlayer::Computer)
							points = this->_ticTacMap.GetWin('O');
					}

					if (this->computerPlay) {

						points = this->_ticTacMap.GetWin('X');

						if (points.size() == 0)
							points = this->_ticTacMap.GetWin('O');
					}

					if (points.size() != 0)
					{
						this->_winLine.setFillColor(sf::Color::Black);

						if (this->_ticTacMap.GetWinType == WinType::Horizontal)
						{
							this->_winLine.setSize(sf::Vector2f(500.f, 5.f));
							this->_winLine.setPosition(this->_gameGridMap[points[0].row][points[0].col].getPosition().x, (this->_gameGridMap[points[2].row][points[2].col].getPosition().y) + 83.33f);
						}
						else if (this->_ticTacMap.GetWinType == WinType::Vertical)
						{
							this->_winLine.setSize(sf::Vector2f(5.f, 450.f));
							this->_winLine.setPosition((this->_gameGridMap[points[0].row][points[0].col].getPosition().x) + 75.f, this->_gameGridMap[points[0].row][points[0].col].getPosition().y);
						}


						else if (this->_ticTacMap.GetWinType == WinType::Diagonal_1) {
							this->_winLine.setSize(sf::Vector2f(500.f, 5.f));
							this->_winLine.setPosition(this->_gameBoard.getPosition().x + 80.f, this->_gameBoard.getPosition().y + 60.f);
							this->_winLine.rotate(45);
						}

						else if (this->_ticTacMap.GetWinType == WinType::Diagonal_2) {
							this->_winLine.setSize(sf::Vector2f(500.f, 5.f));
							this->_winLine.setPosition(this->_gameBoard.getPosition().x + 50.f, this->_gameBoard.getPosition().y + 420.f);
							this->_winLine.rotate(315);
						}

						this->GamePlay = false;
						this->_gameGridMap[i][j].setFillColor(sf::Color(223, 229, 237));
						/*		std::string message;

								if (this->_currentPlayer == ActivePlayer::Player1)
									message = "Player1 Won!";

								else if (this->_currentPlayer == ActivePlayer::Player2)
									message = "Player2 Won!";

								else if (this->_currentPlayer == ActivePlayer::Computer)
									message = "Computer Won!";*/

									//this->AlertWindow(this->_HeaderFont, message, 200, 100, sf::Color(69, 74, 70), sf::Color::White);
					}

					else if (this->_ticTacMap.GetWinType == WinType::Stalemate)
					{
						this->GamePlay = false;

						for (int i = 0; i < TicTacGen::MaxSize; ++i)
						{
							for (int j = 0; j < TicTacGen::MaxSize; ++j)
							{
								this->_gameGridMap[i][j].setFillColor(sf::Color::Yellow);

							}
						}//
					}

					if (this->computerPlay == false)
						this->_currentPlayer = (this->_currentPlayer == ActivePlayer::Player1) ? ActivePlayer::Player2 : ActivePlayer::Player1; // switch Player

					std::string setString = " ";

					if (this->GamePlay == false)
						setString = "Game Over!";

					else if (this->computerPlay == false)
						setString = (this->_currentPlayer == ActivePlayer::Player1) ? "Player1's Turn" : "Player2's Turn";

					else if (this->computerPlay == true)
						setString = (this->_currentPlayer == ActivePlayer::Player1) ? "Player1's Turn" : "Computer's Turn";

					this->_CurrentPlayerTurn.setString(setString);

				}
				break;
			}
		}
	}
}

void GamePlayPage::HandleEvents(sf::Event* event) {

	if (event->type == sf::Event::KeyPressed)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) // Go back to startPage
		{
			this->ChangePage = true;
			this->NavTOPage = GamePages::StartPage;
		}
	}

	if (this->GamePlay == true) {

		if (event->type == sf::Event::MouseMoved)
			this->MouseMoveTigger();

		if (event->type == sf::Event::MouseButtonPressed)
			this->OnFocusEvent();
	}

}
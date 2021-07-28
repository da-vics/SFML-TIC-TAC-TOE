#include "Includes/PagesManager.h"
#include"Includes/GamePlayPage.h"

void PagesManager::HandleEvents(sf::Event* event) {

	this->_currentPage->HandleEvents(event);
}

void PagesManager::Display() {

	if (this->_currentPage->ChangePage) {

		if (this->_currentPage->NavTOPage == GamePages::StartPage)
			this->_currentPage = new StartPage(this->_window);

		else if (this->_currentPage->NavTOPage == GamePages::GamePlayPage_P)
			this->_currentPage = new GamePlayPage(this->_window, false);

		else if (this->_currentPage->NavTOPage == GamePages::GamePlayPage_C)
			this->_currentPage = new GamePlayPage(this->_window, true);

		return;
	}

	this->_currentPage->Display();
}

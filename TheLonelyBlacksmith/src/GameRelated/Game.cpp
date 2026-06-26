#include "GameRelated/Game.h"
#include <Utility/Util.h>
#include <GameRelated/GameSettings/GameSettings.h>
#include <Builders/PlayerBuilder.h>
#include <Managers/MenuManager.h>
#include <iostream>

Game::Game()
{
	isRunning = false;
	totalTurnCount = 1;
	score = 0;
}

void Game::internalStart()
{
	Util::Debug("Starting game..");
	internalInit();
	isRunning = true;
	internalGameLoop();
}

void Game::internalTerminate(const std::string& _terminateReasons)
{
	Util::Debug("Game stopped: " + _terminateReasons);

	isRunning = false;
}

void Game::internalGameLoop()
{
	while (isRunning)
	{
		//Shows menu informations
		internalDisplay();

		//Waits for player input
		const int _playerActionIndex = internalPlayerRequestInput();

		//Press to continue
		std::string _failContext;
		const bool _success = MenuManager::ExecuteMenuAtIndex(_playerActionIndex - 1, _failContext);
		if (!_success)
		{
			Util::PrintEmbed(_failContext, BRIGHT_RED);
			Util::Continue();
		}
	}
}

void Game::internalInit()
{
	internalInitPlayer();
	internalInitMenus();
}

void Game::internalInitPlayer()
{
	//I used a builder just to try this out
	player = PlayerBuilder()
		.InitializeResourcesFromSettings()
		.Build();
}

void Game::internalInitMenus()
{
	MenuManager::InitMenus();
}

void Game::internalIncrementGameTurn()
{
	totalTurnCount++;
	//If total turn count > number of turn in general settings, we Terminate the game
	if (totalTurnCount > GameSettings::TURN_TOTAL_COUNT)
		Terminate("You have no more turns to play");
}

void Game::internalDisplay()
{
	Util::Clear();
	internalDisplayGameInformations();
	internalDisplayMenu();
}

void Game::internalDisplayGameInformations()
{
	Util::Separation();
	Util::PrintTitle("The Lonely Blacksmith");
	Util::PrintEmbed("Day " + std::to_string(totalTurnCount) + "/" + std::to_string(GameSettings::TURN_TOTAL_COUNT));
	Util::PrintEmbed("Score " + std::to_string(score));
	Util::Separation();
}

void Game::internalDisplayMenu()
{
	MenuManager::DisplayCurrentMenu();

}

int Game::internalPlayerRequestInput()
{
	std::cout << std::endl;
	Util::PrintEmbed("Player, what would you like to do?\n Select an index corresponding to your desired action", BRIGHT_RED);
	std::cout << std::endl;
	std::string _returnedValue;

	std::cin >> _returnedValue;
	int _playerInputIndex;
	try
	{
		_playerInputIndex = std::stoi(_returnedValue);
	}
	catch (const std::exception&)
	{
		std::cout << std::endl;
		Util::PrintEmbed("Please enter a valid index", BRIGHT_RED);
		std::cout << std::endl;
		return internalPlayerRequestInput();
	}

	return _playerInputIndex;
}

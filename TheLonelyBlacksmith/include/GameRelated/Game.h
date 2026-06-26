#pragma once
#include <string>
#include <memory>
#include <GameRelated/Player.h>
#include <VisualRelated/Menu.h>

class Game
{
	static Game& GetInstance()
	{
		static Game _instance;
		return _instance;
	}

private:
	// main loop runs ? 
	bool isRunning;
	
	// number of "days" / turns
	int totalTurnCount;

	// the total score
	int score; //Should it be personal to player ? I don't think so
	
	// the player created for this
	std::unique_ptr<Player> player;

private:
	Game();

public:
	Game(const Game& _game) = delete;

	void operator=(const Game& _other) = delete;

public:
	__forceinline static void Start()
	{
		GetInstance().internalStart();
	}

	__forceinline static void Terminate(const std::string& _terminateReasons)
	{
		GetInstance().internalTerminate(_terminateReasons);
	}

	__forceinline static Player* GetPlayer() {
		return GetInstance().player.get();
	}

	__forceinline static int GetTotalTurnCount() {
		return GetInstance().totalTurnCount;
	}

	__forceinline static void IncrementTotalTurnCount(const int value) {
		GetInstance().totalTurnCount += value;
	}

	__forceinline static void IncrementTotalScore(const int value) {
		GetInstance().score += value;
	}


private: //Base gameloop logic
	void internalStart();
	void internalTerminate(const std::string& _terminateReasons);
	void internalGameLoop();
	
private: //Inits
	/// <summary>
	/// Inits important game datas
	/// </summary>
	void internalInit();

	/// <summary>
	/// Builds the player
	/// </summary>
	void internalInitPlayer();

	/// <summary>
	/// Initialize menus, and initialize the current menu
	/// </summary>
	void internalInitMenus();

private: //misc
	/// <summary>
	/// Increment the turn count, terminating the game if the count is > to the max allowed count for the game
	/// </summary>
	void internalIncrementGameTurn();

private: //Display / Menu related
	void internalDisplay();

	/// <summary>
	/// Display informations about the game, such as total turn count
	/// </summary>
	void internalDisplayGameInformations();

	/// <summary>
	/// Displays the current open menu
	/// </summary>
	void internalDisplayMenu();

private: 
	/// <summary>
	/// Request the player to send an input. 
	/// This input will then be used to execute an action from the menus
	/// </summary>
	int internalPlayerRequestInput();
};


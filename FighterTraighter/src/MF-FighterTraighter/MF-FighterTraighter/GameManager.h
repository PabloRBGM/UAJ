#pragma once
#include <vector>
#include <string>
#include "HID.h"

class Entity;
class App;
class GameStateMachine;

class GameManager
{

public:	
	enum AbilityID {
	//------level 1------//
		ShrugOff,		
		ReachingStrike,
		MorePower,
		Pollo,
	//------level 2------//
		AcidSplit,
		Dash,
		VampiricStrike,
		LaserLineal,
	//------level 3------//
		Mina,
		Hookshot,	
		HailBall,
		KnockDown,
	//------level 4------//
		ExplosiveWillpower,
		FlyingKicks,		
		NadoKick,
	//------level 5------//
		MegatonGrip,
		SeismicShock,
	//---to know the number of abilities---//
		_last_ability,
	};

	//To choose between various abilities levels
	enum AbilityFlags {		
		level1_flag = ShrugOff,
		level2_flag = AcidSplit,
		level3_flag = Mina,
		level4_flag = ExplosiveWillpower,
		level5_flag = MegatonGrip,
		max_level_flag = _last_ability
	};
	// TODO: Move from here to somewhere else
	enum CharacterID {
		/*None,*/
		F10R,
		MKWh00p,
		Mockingbird,
		Aisha
	};

	struct PlayerInfo {
		CharacterID character;
		std::vector<AbilityID> abilities; //habilidades que tiene cada personaje en una ronda
		int ability1Index;
		int ability2Index;
		HID* hid;
		virtual ~PlayerInfo() {
			delete hid;
		}

	};
	GameManager(App* app);

	// To update HIDs
	void handleInput();

	// To inform this that start/escape was pressed
	void pressedStart();
	// To inform that player (0 or 1) lost a round, or that it's a draw (-1)
	// Maybe there's something better than an int?
	void playerLost(int player);
	void AIWin();
	void ResetRounds();
	// To inform that saco has lost all its health
	void trainingEnded(int winner);
	void setCharacter(CharacterID char_, int n) {
		if (n == 1) {
			player1_.character = char_;
		}
		else {

			player2_.character = char_;
		}
	}

	void resetCharacters();
	
	//void setPlayer1
	//void setPlayerInfo1(Entity* p1, std::string character, std::vector<std::string> abilities, AbilityID ability1Index, AbilityID ability2Index);
	//void setPlayerInfo2(Entity* p2, std::string character, std::vector<std::string> abilities, AbilityID ability1Index, AbilityID ability2Index);
	const PlayerInfo& getPlayerInfo(int player) {
		if (player == 1) return player1_;
		return player2_;
	}

	void addHability(AbilityID hab, int player) {
		if (player == 1){
			player1_.abilities.push_back(hab);
		}
		else {
			player2_.abilities.push_back(hab);
		}
	}

	void setFirstHab(int hab, int player) {
		if (player == 1) {
			player1_.ability1Index = hab;
		}
		else {
			player2_.ability1Index = hab;
		}
	}

	void setSecondHab(int hab, int player) {
		if (player == 1) {
			player1_.ability2Index = hab;
		}
		else {
			player2_.ability2Index = hab;
		}
	}

	virtual ~GameManager() {

	}
	inline unsigned int getPlayerRounds(int player) {
		if (player == 1) return playerLrounds_;
		return playerRrounds_;
	}

	inline void increasePlayerRounds(int player) {
		if (player == 1) ++playerLrounds_;
		else ++playerRrounds_;
	}
	inline unsigned int getTotalRounds() { return totalRounds_; }

	void GoBackToMain();
	void GoToEndMenu(int winner);
protected:
	unsigned int playerLrounds_ = 0;
	unsigned int playerRrounds_ = 0;
	unsigned int totalRounds_ = 5;
	unsigned int currentRound_ = 0;

	PlayerInfo player1_;
	PlayerInfo player2_;

	Vector2D p;

	App* app_;
};


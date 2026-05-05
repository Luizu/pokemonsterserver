// Copyright 2023 The Forgotten Server Authors. All rights reserved.
// Use of this source code is governed by the GPL-2.0 License that can be found in the LICENSE file.
//
// Refactor: PlayerCatchSystem extracted from Player class.
// Responsible for all Pokeball / catch attempt tracking state.

#ifndef FS_PLAYER_CATCH_SYSTEM_H
#define FS_PLAYER_CATCH_SYSTEM_H

#include "enums.h"
#include "item.h"

#include <map>
#include <string>
#include <vector>
#include <algorithm>

struct pokeballsInfo {
	uint32_t poke = 0;
	uint32_t great = 0;
	uint32_t ultra = 0;
	uint32_t saffari = 0;
	uint32_t master = 0;
	uint32_t moon = 0;
	uint32_t tinker = 0;
	uint32_t sora = 0;
	uint32_t dusk = 0;
	uint32_t yume = 0;
	uint32_t tale = 0;
	uint32_t net = 0;
	uint32_t janguru = 0;
	uint32_t magu = 0;
	uint32_t fast = 0;
	uint32_t heavy = 0;
	uint32_t premier = 0;
	uint32_t delta = 0;
	uint32_t esferadepal = 0;
	uint32_t esferamega = 0;
	uint32_t esferagiga = 0;
	uint32_t esferatera = 0;
	uint32_t esferaultra = 0;
	uint32_t esferalendaria = 0;
	uint32_t super = 0;
	uint32_t especial = 0;
	uint32_t divine = 0;
};

class PlayerCatchSystem {
public:
	// ----- Pokeball type resolution -----
	static PokeballType resolvePokeballType(const std::string& ballName) {
		static const std::map<std::string, PokeballType> pokeballMap = {
			{"poke",            PokeballType::Poke},
			{"great",           PokeballType::Great},
			{"ultra",           PokeballType::Ultra},
			{"saffari",         PokeballType::Saffari},
			{"master",          PokeballType::Master},
			{"moon",            PokeballType::Moon},
			{"tinker",          PokeballType::Tinker},
			{"sora",            PokeballType::Sora},
			{"dusk",            PokeballType::Dusk},
			{"yume",            PokeballType::Yume},
			{"tale",            PokeballType::Tale},
			{"net",             PokeballType::Net},
			{"janguru",         PokeballType::Janguru},
			{"magu",            PokeballType::Magu},
			{"fast",            PokeballType::Fast},
			{"heavy",           PokeballType::Heavy},
			{"premier",         PokeballType::Premier},
			{"delta",           PokeballType::Delta},
			{"esferadepal",     PokeballType::Esferadepal},
			{"esferamega",      PokeballType::Esferamega},
			{"esferagiga",      PokeballType::Esferagiga},
			{"esferatera",      PokeballType::Esferatera},
			{"esferaultra",     PokeballType::Esferaultra},
			{"esferalendaria",  PokeballType::Esferalendaria},
			{"super",           PokeballType::Super},
			{"especial",        PokeballType::Especial},
			{"divine",          PokeballType::Divine},
		};
		auto it = pokeballMap.find(ballName);
		if (it != pokeballMap.end()) {
			return it->second;
		}
		return PokeballType::Unknown;
	}

	// ----- Brokes (failed throws) tracking -----
	void loadBrokes(const std::string& pokemonName, const pokeballsInfo& brokes) {
		playerBrokes[pokemonName] = brokes;
	}

	void resetBrokes(const std::string& pokemonName) {
		playerBrokes.erase(pokemonName);
	}

	void addBroke(const std::string& pokemonName, const std::string& ballName) {
		auto& info = playerBrokes[pokemonName];
		switch (resolvePokeballType(ballName)) {
			case PokeballType::Poke:           info.poke++;          break;
			case PokeballType::Great:          info.great++;         break;
			case PokeballType::Ultra:          info.ultra++;         break;
			case PokeballType::Saffari:        info.saffari++;       break;
			case PokeballType::Master:         info.master++;        break;
			case PokeballType::Moon:           info.moon++;          break;
			case PokeballType::Tinker:         info.tinker++;        break;
			case PokeballType::Sora:           info.sora++;          break;
			case PokeballType::Dusk:           info.dusk++;          break;
			case PokeballType::Yume:           info.yume++;          break;
			case PokeballType::Tale:           info.tale++;          break;
			case PokeballType::Net:            info.net++;           break;
			case PokeballType::Janguru:        info.janguru++;       break;
			case PokeballType::Magu:           info.magu++;          break;
			case PokeballType::Fast:           info.fast++;          break;
			case PokeballType::Heavy:          info.heavy++;         break;
			case PokeballType::Premier:        info.premier++;       break;
			case PokeballType::Delta:          info.delta++;         break;
			case PokeballType::Esferadepal:    info.esferadepal++;   break;
			case PokeballType::Esferamega:     info.esferamega++;    break;
			case PokeballType::Esferagiga:     info.esferagiga++;    break;
			case PokeballType::Esferatera:     info.esferatera++;    break;
			case PokeballType::Esferaultra:    info.esferaultra++;   break;
			case PokeballType::Esferalendaria: info.esferalendaria++; break;
			case PokeballType::Super:          info.super++;         break;
			case PokeballType::Especial:       info.especial++;      break;
			case PokeballType::Divine:         info.divine++;        break;
			default:
				std::cout << "[PlayerCatchSystem] Pokebola desconhecida: " << ballName << std::endl;
				break;
		}
	}

	pokeballsInfo getBrokes(const std::string& pokemonName) const {
		auto it = playerBrokes.find(pokemonName);
		if (it != playerBrokes.end()) {
			return it->second;
		}
		return pokeballsInfo{};
	}

	const std::map<std::string, pokeballsInfo>& getAllBrokes() const {
		return playerBrokes;
	}

	uint32_t countUsedPokeballs(const std::string& pokemonName) const {
		const pokeballsInfo b = getBrokes(pokemonName);
		return b.poke + b.great + b.ultra + b.saffari + b.master + b.moon +
		       b.tinker + b.sora + b.dusk + b.yume + b.tale + b.net +
		       b.janguru + b.magu + b.fast + b.heavy + b.premier + b.delta +
		       b.esferadepal + b.esferamega + b.esferagiga + b.esferatera +
		       b.esferaultra + b.esferalendaria + b.super + b.especial + b.divine;
	}

	// ----- Catch points -----
	void addCatchPoints(const std::string& pokemonName, uint16_t points) {
		playerPoints[pokemonName] += points;
	}

	void resetCatchPoints(const std::string& pokemonName) {
		playerPoints.erase(pokemonName);
	}

	void loadCatchPoints(const std::string& pokemonName, uint16_t points) {
		playerPoints[pokemonName] = points;
	}

	uint16_t getCatchPoints(const std::string& pokemonName) const {
		auto it = playerPoints.find(pokemonName);
		if (it != playerPoints.end()) {
			return it->second;
		}
		return 0;
	}

	// ----- Pokeball item cache (for fast iteration) -----
	void insertPokeball(Item* pokeball) {
		pokeballs.push_back(pokeball);
	}

	void clearPokeballs() {
		pokeballs.clear();
	}

	void removeBallFromCache(Item* pokeball) {
		if (!pokeball) return;
		auto it = std::find(pokeballs.begin(), pokeballs.end(), pokeball);
		if (it != pokeballs.end()) {
			pokeballs.erase(it);
		}
	}

	const std::vector<Item*>& getCachedPokeballs() const {
		return pokeballs;
	}

	// Last interaction timestamp (public for direct read/write, matches original pattern)
	int64_t lastPokeballInteraction = 0;

private:
	std::map<std::string, pokeballsInfo> playerBrokes;
	std::map<std::string, uint16_t>      playerPoints;
	std::vector<Item*>                   pokeballs;
};

#endif // FS_PLAYER_CATCH_SYSTEM_H

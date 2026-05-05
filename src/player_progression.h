// Copyright 2023 The Forgotten Server Authors. All rights reserved.
// Use of this source code is governed by the GPL-2.0 License that can be found in the LICENSE file.
//
// Refactor: PlayerProgression extracted from Player class.
// Responsible for experience, levels, stamina, mana progression, offline training and bank balance.

#ifndef FS_PLAYER_PROGRESSION_H
#define FS_PLAYER_PROGRESSION_H

#include <cstdint>
#include <algorithm>

class PlayerProgression {
public:
	// ----- Experience / Level -----
	uint64_t getExperience() const { return experience; }
	void setExperience(uint64_t exp) { experience = exp; }

	uint32_t getLevel() const { return level; }
	void setLevel(uint32_t lvl) { level = lvl; }

	uint8_t getLevelPercent() const { return levelPercent; }
	void setLevelPercent(uint8_t pct) { levelPercent = pct; }

	static uint64_t getExpForLevel(int32_t lv) {
		lv--;
		return ((50ULL * lv * lv * lv) - (150ULL * lv * lv) + (400ULL * lv)) / 3ULL;
	}

	static uint8_t getPercentLevel(uint64_t count, uint64_t nextLevelCount) {
		if (nextLevelCount == 0) return 0;
		uint64_t result = (count * 100) / nextLevelCount;
		return static_cast<uint8_t>(std::min<uint64_t>(result, 100));
	}

	// ----- Magic Level -----
	uint32_t getMagicLevel() const { return magLevel; }
	void setMagicLevel(uint32_t ml) { magLevel = ml; }

	uint8_t getMagicLevelPercent() const { return magLevelPercent; }
	void setMagicLevelPercent(uint8_t pct) { magLevelPercent = pct; }

	uint64_t getManaSpent() const { return manaSpent; }
	void setManaSpent(uint64_t spent) { manaSpent = spent; }
	void addManaSpent(uint64_t amount) { manaSpent += amount; }

	// ----- Soul -----
	uint8_t getSoul() const { return soul; }
	void setSoul(uint8_t s) { soul = s; }

	// ----- Stamina -----
	uint16_t getStaminaMinutes() const { return staminaMinutes; }
	void setStaminaMinutes(uint16_t minutes) { staminaMinutes = minutes; }

	// ----- Offline Training -----
	int32_t getOfflineTrainingSkill() const { return offlineTrainingSkill; }
	void setOfflineTrainingSkill(int32_t skill) { offlineTrainingSkill = skill; }

	int32_t getOfflineTrainingTime() const { return offlineTrainingTime; }
	void addOfflineTrainingTime(int32_t addTime) {
		offlineTrainingTime = std::min<int32_t>(12 * 3600 * 1000, offlineTrainingTime + addTime);
	}
	void removeOfflineTrainingTime(int32_t removeTime) {
		offlineTrainingTime = std::max<int32_t>(0, offlineTrainingTime - removeTime);
	}

	// ----- Bank Balance -----
	uint64_t getBankBalance() const { return bankBalance; }
	void setBankBalance(uint64_t balance) { bankBalance = balance; }

private:
	uint64_t experience         = 0;
	uint64_t manaSpent          = 0;
	uint64_t bankBalance        = 0;

	uint32_t level              = 1;
	uint32_t magLevel           = 0;

	int32_t  offlineTrainingSkill = -1;
	int32_t  offlineTrainingTime  = 0;

	uint16_t staminaMinutes     = 2520;

	uint8_t  soul               = 0;
	uint8_t  levelPercent       = 0;
	uint8_t  magLevelPercent    = 0;
};

#endif // FS_PLAYER_PROGRESSION_H

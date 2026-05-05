// Copyright 2023 The Forgotten Server Authors. All rights reserved.
// Use of this source code is governed by the GPL-2.0 License that can be found in the LICENSE file.
//
// Refactor: PlayerGuildState extracted from Player class.
// Responsible for guild membership, guild inbox and guild contribution tracking.

#ifndef FS_PLAYER_GUILD_STATE_H
#define FS_PLAYER_GUILD_STATE_H

#include "guild.h"

#include <cstdint>
#include <ctime>
#include <map>
#include <string>
#include <vector>

// ---------------------------------------------------------------------------
// GuildInbox structures (moved here from player.h)
// ---------------------------------------------------------------------------

struct GuildInbox {
	uint32_t id;
	time_t   date;
	uint8_t  type;
	std::string text;
	bool     finished;
	uint32_t targetId;
	uint32_t guildId;

	GuildInbox(uint32_t id, time_t date, uint8_t type, std::string& text,
	           bool finished = false, uint32_t targetId = 0, uint32_t guildId = 0)
	    : id(id), date(date), type(type), text(std::move(text)),
	      finished(finished), targetId(targetId), guildId(guildId) {}
};

// Ordered insertion map (preserves insertion order)
class GuildInboxMap {
public:
	void insert(uint32_t key, const GuildInbox& value) {
		auto entry = data_map.try_emplace(key, value);
		if (entry.second) {
			insertion_order.push_back(key);
		}
	}

	bool contains(uint32_t key) const {
		return data_map.find(key) != data_map.end();
	}

	GuildInbox& get(uint32_t key) {
		return data_map.at(key);
	}

	const std::vector<uint32_t>& keys() const { return insertion_order; }
	const std::map<uint32_t, GuildInbox>& data() const { return data_map; }
	std::size_t size() const { return insertion_order.size(); }

	typename std::vector<uint32_t>::const_iterator begin() const { return insertion_order.cbegin(); }
	typename std::vector<uint32_t>::const_iterator end()   const { return insertion_order.cend(); }

private:
	std::map<uint32_t, GuildInbox> data_map;
	std::vector<uint32_t>          insertion_order;
};

// ---------------------------------------------------------------------------
// PlayerGuildState
// ---------------------------------------------------------------------------

class PlayerGuildState {
public:
	// ----- Membership -----
	Guild* getGuild() const { return guild; }
	void setGuild(Guild* g) { guild = g; }

	GuildRank_ptr getGuildRank() const { return guildRank; }
	void setGuildRank(GuildRank_ptr rank) { guildRank = rank; }

	const std::string& getGuildNick() const { return guildNick; }
	void setGuildNick(std::string nick) { guildNick = std::move(nick); }

	const std::vector<uint32_t>& getGuildInvites() const { return guildInvites; }
	void addGuildInvite(uint32_t guildId) { guildInvites.push_back(guildId); }
	void removeGuildInvite(uint32_t guildId) {
		auto it = std::find(guildInvites.begin(), guildInvites.end(), guildId);
		if (it != guildInvites.end()) guildInvites.erase(it);
	}

	bool isGuildMate(const Player* player) const {
		if (!player || !guild) return false;
		return guild == player->getGuild();
	}

	// ----- Inbox -----
	void addInboxMessage(uint32_t id, time_t date, uint8_t type, std::string& text,
	                     bool finished = false, uint32_t targetId = 0, uint32_t guildId = 0) {
		inbox.insert(id, GuildInbox(id, date, type, text, finished, targetId, guildId));
	}

	GuildInboxMap& getInbox() { return inbox; }
	const GuildInboxMap& getInbox() const { return inbox; }

	// ----- Contribution -----
	uint64_t getContribution() const { return guildContribution; }
	void addContribution(uint64_t amount) { guildContribution += amount; }
	void setContribution(uint64_t amount) { guildContribution = amount; }

private:
	Guild*        guild       = nullptr;
	GuildRank_ptr guildRank   = nullptr;
	std::string   guildNick;
	std::vector<uint32_t> guildInvites;
	GuildInboxMap inbox;
	uint64_t      guildContribution = 0;
};

#endif // FS_PLAYER_GUILD_STATE_H

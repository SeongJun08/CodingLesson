#pragma once

#include <string>
#include <vector>

struct Status
{
	int mLevel;
	int mHP;
	int mMP;
};

struct Item
{
	std::string mName;
	int mPrice;
};

class Monster
{
private:
	std::string mName;
	Status mStatus;
	std::vector<Item> mDropItems;

public:
	Monster() : mName(), mStatus(), mDropItems() {}

	std::string GetName() const { return mName; }
	void SetName(const char *name) { mName = name; }

	Status GetStatus() const { return mStatus; }
	void SetStatus(const Status &stat) { mStatus = stat; }

	std::vector<Item>& GetDropItems() { return mDropItems; }
	void AddDropItem(const Item &item) { mDropItems.push_back(item); }

};

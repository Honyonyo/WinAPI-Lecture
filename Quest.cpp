#include "stdafx.h"
#include "Quest.h"

void Quest::init(string name, int gold, int exp, string description, string item, int monster, string questCheck, string monsterName, string questStage)
{
	_name = name;
	_description = description;
	_questCheck = questCheck;
	_questStage = questStage;
	_monsterName = monsterName;
	_item = item;
	_exp = exp;
	_monster = monster;
	_gold = gold;
}

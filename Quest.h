#pragma once
enum QUEST_TYPE
{
	QUEST_STAGE_1,
};
/*
	  "_name": "��������1 - ���� ��ġ",
	  "_exp": 500,
	  "_description": "���� 10�� ��ġ",
	  "_item": "����",
	  "_moster": 3,
	  "_questCheck": "����",
	  "_gold": 1000,
	  "_mosterName": "������",
	  "_questStage":  "1 ��������"

*/
class Quest
{
protected:
	string _name;
	string _description;
	string _questCheck;
	string _questStage;
	string _monsterName;
	string _item;
	int _exp;
	int _monster;
	int _gold;

	QUEST_TYPE _questType;

public:
	void init(string name, int gold, int exp, string description, string item, int monster, string questCheck, string monsterName, string questStage);
	
#pragma region ������
	string GetName() { return _name; }
	string GetDescription() { return _description; }
	string GetQuestCheck() { return _questCheck; }
	string GetQuestStage() { return _questStage; }
	string GetMonsterName() { return _monsterName; }
	string GetItem() { return _item; }
	int GetExp() { return _exp; }
	int GetMoster() { return _monster; }
	int GetGold() { return _gold; }

	QUEST_TYPE GetType() { return _questType; }
#pragma endregion
};


#pragma once
/*
ť�� ���� ������ �����ϴ�
  - ����Ʈ�� �����̴�.(����Ʈ���� ������)
���Լ��ⱸ�� FIFO
������ �Ͼ�� ���� ��(rear), ������ �Ͼ�� ���� ��(front)�̶�� �Ѵ�.

 * ť�� ����ϸ� ���� ��Ȳ
 -����Ʈť : ť������. item
 -cpu�����ٸ�
 -�����͹���Ȯ���۾�
 -bfs/dfs
 �ʺ���/���̱��
*/

class Quest;
using namespace std;
class QuestSample
{
private:
	queue<Quest*> _quest;
public:
	void init(void);
	void questSetUp(Quest* pQuest = nullptr);

	queue<Quest*>* getQuest() { return &this->_quest; }
};


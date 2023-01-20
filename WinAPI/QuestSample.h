#pragma once
/*
큐는 삽입 삭제가 용이하다
  - 리스트의 일종이다.(리스트보다 가볍다)
선입선출구조 FIFO
삽입이 일어나는 쪽을 뒤(rear), 삭제가 일어나는 쪽을 앞(front)이라고 한다.

 * 큐를 사용하면 좋은 상황
 -프린트큐 : 큐의일종. item
 -cpu스케줄링
 -데이터버퍼확인작업
 -bfs/dfs
 너비기반/깊이기반
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


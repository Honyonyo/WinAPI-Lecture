#include "stdafx.h"
#include "TmpSoundManager.h"

HRESULT TmpSoundManager::init()
{
	return S_OK;
}

void TmpSoundManager::addMp3FileWithKey(string key, string filename) {
	//===== 내부적으로 정해진 약소쿠 =====
	string first = "open \"";
	string end = "\" type mpegvideo alias ";
	//=====end 내부적으로 정해진 약소쿠=====
	string finalQuery = first + filename + end + key;

	//장치관리자에서 사운드카드를 찾아서 출력할당을 한다
	//사운드카드가 없으면 소리가 안난다.
	const char* str = finalQuery.c_str();
	//cout << "작동 : addMp3FileWithKey" << endl;
	//cout << "	finalQuery:" << finalQuery << endl;
	//cout << "	str:" << str << endl;
	//mciSendString() : 장치에 특정 명령어를 전송하여 구동시킨다.
	// 인자(문자열명령어, 반환값을알려줄문자열, 반환될길이, 콜백(반환후 실행할거 있니? 우린 코드로 다 할거니까 ㄴㄴ_)
	//mp3파일을 넣는다.
	mciSendString(str, NULL, 0, NULL);
};
void TmpSoundManager::addWaveFileWithKey(string key, string filename) {
	string first = "open \"";
	string end = "\" type waveaudio alias ";
	string finalQuery = first + filename + end + key;
	const char* str = finalQuery.c_str();
	//cout << "작동 : addWaveFileWithKey" << endl;
	//cout << "	finalQuery:" << finalQuery << endl;
	//cout << "	str:" << str << endl;

	mciSendString(str, NULL, 0, NULL);

};
void TmpSoundManager::playEffectSoundWave(char* fileName) {
	//PlaySound : 사운드재생함수. 빨라서 test에 많이 쓰인다.
	// 인자 (파일이름(파일경로), vs리소스를 사용하면 해당 인스턴스 핸들, fdwSound(옵션 | 옵션 | 옵션)
	/**옵션중요**
	* 
	* SND_ASYNK : 비동기플래그. 재생하면서 다음코드 실행
	* SND_LOOP
	* SND_NODEFAULT : 지정경로에 파일 없을경우 나오는 경고음 재생X
	*/

	//cout << "작동 : playEffectSoundWave" << endl;

	PlaySound(fileName, NULL, SND_ASYNC);
};
void TmpSoundManager::playSoundWithKey(string key) {
	string first = "play ";
	string finalQuery = first + key;

	const char* str = finalQuery.c_str();
	//cout << "작동 : playSoundWithKey" << endl;
	//cout << "	finalQuery:" << finalQuery << endl;
	//cout << "	str:" << str << endl;

	mciSendString(str, NULL, 0, NULL);
};
void TmpSoundManager::stopMp3WithKey(string key) {
	string first = "play ";
	string finalQuery = "";
	finalQuery = first + key;

	const char* str = finalQuery.c_str();
	//cout << "작동 : stopMp3WithKey" << endl;
	//cout << "	finalQuery:" << finalQuery << endl;
	//cout << "	str:" << str << endl;

	mciSendString(str, NULL, 0, NULL);

};
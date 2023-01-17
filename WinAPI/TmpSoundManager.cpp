#include "stdafx.h"
#include "TmpSoundManager.h"

HRESULT TmpSoundManager::init()
{
	return S_OK;
}

void TmpSoundManager::addMp3FileWithKey(string key, string filename) {
	//===== ���������� ������ ����� =====
	string first = "open \"";
	string end = "\" type mpegvideo alias ";
	//=====end ���������� ������ �����=====
	string finalQuery = first + filename + end + key;

	//��ġ�����ڿ��� ����ī�带 ã�Ƽ� ����Ҵ��� �Ѵ�
	//����ī�尡 ������ �Ҹ��� �ȳ���.
	const char* str = finalQuery.c_str();
	//cout << "�۵� : addMp3FileWithKey" << endl;
	//cout << "	finalQuery:" << finalQuery << endl;
	//cout << "	str:" << str << endl;
	//mciSendString() : ��ġ�� Ư�� ��ɾ �����Ͽ� ������Ų��.
	// ����(���ڿ���ɾ�, ��ȯ�����˷��ٹ��ڿ�, ��ȯ�ɱ���, �ݹ�(��ȯ�� �����Ұ� �ִ�? �츰 �ڵ�� �� �ҰŴϱ� ����_)
	//mp3������ �ִ´�.
	mciSendString(str, NULL, 0, NULL);
};
void TmpSoundManager::addWaveFileWithKey(string key, string filename) {
	string first = "open \"";
	string end = "\" type waveaudio alias ";
	string finalQuery = first + filename + end + key;
	const char* str = finalQuery.c_str();
	//cout << "�۵� : addWaveFileWithKey" << endl;
	//cout << "	finalQuery:" << finalQuery << endl;
	//cout << "	str:" << str << endl;

	mciSendString(str, NULL, 0, NULL);

};
void TmpSoundManager::playEffectSoundWave(char* fileName) {
	//PlaySound : ��������Լ�. ���� test�� ���� ���δ�.
	// ���� (�����̸�(���ϰ��), vs���ҽ��� ����ϸ� �ش� �ν��Ͻ� �ڵ�, fdwSound(�ɼ� | �ɼ� | �ɼ�)
	/**�ɼ��߿�**
	* 
	* SND_ASYNK : �񵿱��÷���. ����ϸ鼭 �����ڵ� ����
	* SND_LOOP
	* SND_NODEFAULT : ������ο� ���� ������� ������ ����� ���X
	*/

	//cout << "�۵� : playEffectSoundWave" << endl;

	PlaySound(fileName, NULL, SND_ASYNC);
};
void TmpSoundManager::playSoundWithKey(string key) {
	string first = "play ";
	string finalQuery = first + key;

	const char* str = finalQuery.c_str();
	//cout << "�۵� : playSoundWithKey" << endl;
	//cout << "	finalQuery:" << finalQuery << endl;
	//cout << "	str:" << str << endl;

	mciSendString(str, NULL, 0, NULL);
};
void TmpSoundManager::stopMp3WithKey(string key) {
	string first = "play ";
	string finalQuery = "";
	finalQuery = first + key;

	const char* str = finalQuery.c_str();
	//cout << "�۵� : stopMp3WithKey" << endl;
	//cout << "	finalQuery:" << finalQuery << endl;
	//cout << "	str:" << str << endl;

	mciSendString(str, NULL, 0, NULL);

};
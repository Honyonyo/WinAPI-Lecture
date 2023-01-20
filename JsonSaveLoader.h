#pragma once
#include "SingletonBase.h"

#pragma region Json
/*
���� cpp json sourceforge �˻�
���ñ⹹�ñ� ���� 3���� ����
������Ʈ/�Ӽ�/����������/���߽���������MTD->MDD ->��Ʈ��F5
//����-vs71����� ���̺귯�� ��¼����¼�� �ȿ� �ִ� ���� �����̸��� �� ������ ì���.
//��Ŀ �Է� �߰����Ӽ�
#pragma comment(lib, "JsonCPP/lib_json/json_vc71_libmtd.lib")
#include "JsonCPP/include/json/json.h"
*/

/*
	��BOM (Byte Of/Order Mark)
	����Ʈ ���� ǥ�ñ�
		WORD BOM = 0xFEFF;
	
	��ǻ�ʹ� �����͸� �޸𸮿� ������ �� ����Ʈ������ ������ ������ �Ѵ�.
	������ �����ڵ��� ��� ���ڵ� ����̳� ����� ��Ŀ� ���� BOM�� �ʿ��� ��찡 �ִ�.
	����Ʈ�� ����Ǵ� ������ ���� �� �����, ��Ʋ ��������� ������.
	 (�����찡 ����ϴ� ����� UTF-16 ( U+FEFF) -> BOM
	
	 - �� �����(Big-endian) ��->��
		���� �ּҿ� �������� ���� ����Ʈ���� �����ϴ� ���
		�޸𸮿� ���������� ����Ǳ� ������ �״�� ���� ���� �ִ�.
		(����� ���ϴ�.)

	 - ��Ʋ ����� ��<-��
		���� �ּ��� �����Ϳ� ���� ����Ʈ�� �����ϴ� ���.
		��� ����� �д� ������ �ݴ�� �о���ϱ� ������ ���ټ��� ��������.

	���� ���� ���� ���ʿ� 0xFEFF�� ���̳ʸ� �������� ä���ؼ� ������ ���� ���ڳ� ���ڿ��� �о���̰� �ϴ� ��Ķ����� ����Ѵ�.
*/

/*
	���̽�(Json (JavaScript Object Notation)
	-���̽��� ��ü�� ������ �Ӽ��� �ؽ�Ʈ �������� �����ϱ� ���� ��ȵ� ����̴�.
		���ͳݿ��� �ڷḦ �ְ���� �� �ڷ� ǥ��������� �ַ� �̿�Ǵ� ����
	-�ڷ��� ������ ū ������ ������, Ư�� ��ǻ�� ���α׷����� �������� ǥ���ϴµ� �����ϴ�.
	-���̽��� ������ �ڹٽ�ũ��Ʈ�� ���� ������ ��������, ���α׷��� �� �÷����� �������̹Ƿ� C, C++, C#, Java, JavaScript, ��, ���̽�, ��� ��� ���� ���� ���ǰ��ִ�.
	-XML, HTTP, CSV���� "�Ϲ�����'ȯ�濡�� �� ������.
	
	*���̽� ���Ŀ��� ����ϴ� ��ȣ�� �ǹ̴� ������ ����.
	{} : ��ü
	Ű : �� = ��ü�� ���� �Ӽ�
	"" : ���ڿ� ������
	[] : �迭

	Value root�� �б� �����ϴ� ��
	BOM = Byte of Mark

	- asString()
	 : ������ string�� �ƴϰų� null���� ����ִٸ� ������ ���� ���� �׳� NULL�� ��ȯ�Ѵ�.

	- ToString()
	 : ToString�� ������ NULL���̶�� ���� �߻�

*/
#pragma endregion

#define DATA_FILE_NAME "SaveData.json"
using namespace std;
class JsonSaveLoader : public SingletonBase<JsonSaveLoader>
{
private:
	void saveString(char* fileName, string data);
	void saveStringWithFileStream(char* fileName, string data);

	string loadString(char* fileName);
	string loadStringWithFileStream(char* fileName);
public:
	HRESULT init(void);
	void release(void);
	void saveJsonFile(char* fileName, Json::Value root);

	Json::Value loadJsonFile(char* fileName);


};
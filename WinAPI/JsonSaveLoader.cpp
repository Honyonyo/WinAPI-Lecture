#include "stdafx.h"
#include "JsonSaveLoader.h"

HRESULT JsonSaveLoader::init(void)
{
	return S_OK;
}

void JsonSaveLoader::release(void)
{

}

void JsonSaveLoader::saveJsonFile(char* fileName, Json::Value root)
{
	Json::StyledWriter writer;
	string outputConfig = writer.write(root);

	saveStringWithFileStream(fileName, outputConfig);
}

Json::Value JsonSaveLoader::loadJsonFile(char* fileName)
{
	string jsonStr = loadStringWithFileStream(fileName);
	if (jsonStr == "")
	{
		MessageBox(_hWnd, "�����Ͱ� ����.", "���", MB_OK);
		return NULL;
	}

	Json::Reader reader;
	Json::Value root;

	//�Ľ� : Ư�� ������ �о�鿩�� �̸� �ٸ� ���α׷��̳� ���� ��ƾ�� ����� �� �ְ� ������ ǥ�� ������� ��ȯ���ִ� ��
	//�ļ� : �Ľ����ִ¾�

	bool parsingRet = reader.parse(jsonStr, root);
	if (!parsingRet)
	{
		string errMsg = reader.getFormatedErrorMessages();
		MessageBox(_hWnd, errMsg.c_str(), "����", MB_OK);
		PostQuitMessage(0);
	}

	return Json::Value();
}

void JsonSaveLoader::saveString(char* fileName, string data)
{
	TCHAR* buf = (TCHAR*)data.c_str();

	//�����쿡�� �ο��� ���� �ĺ���ȣ
	HANDLE file;
	WORD BOM = 0xFEFF;	//UTF-16
	DWORD dwBytes = 0;
	DWORD dwRead;

	/*
	* CreateFile ������ ����ų� �о�´�.
	*
	����
	1. �����ϰų� �� ������ �̸�
	2. ����Ÿ�� (WRITE/READ)
	3. ������ ������ ���� ����(0�� ������ ���ϰڴ�.)
	4. �ڽĿ��� ��ӿ���
	5. ���� ������� ����
		CREATE_ALWAYS:���ο� ���� ���� ->�̹� �����ϸ� ������.
	6. ������ �ɼǰ� ����
		�б�����/�������� ���
		FILE_ATTRIBUTE_NORMAL : �Ϲ����� ���ϼӼ�
	7.���Ͽ� ���� �Ӽ���(�ַ� ���� ����� ����) Ư�� �� ��Ҹ� �����ؼ� �����Ϸ��� null�� ���ָ� �ȴ�

	*/

	file = CreateFile(fileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (file == INVALID_HANDLE_VALUE)
	{
		MessageBox(_hWnd, "�������Ͽ���", "����", MB_OK);
	}
	else
	{
		//���� : CreateFile���� �Ҵ�� �ڵ�, ���Ͽ� ������� ��Ʈ�� ��, �󸶳� �а� �� �������� ���� ũ��, �󸶳� �а� �� �������� ���� ��ȯ��(�ּ�)
		//�������̵� WriteFile(file, &BOM,2, &dwBytes, NULL);
		WriteFile(file, buf, strlen(buf) * sizeof(TCHAR), &dwRead, NULL);
		CloseHandle(file);
	}
}

string JsonSaveLoader::loadString(char* fileName)
{
	TCHAR buf[8192];
	ZeroMemory(buf, sizeof(buf));

	HANDLE file;
	DWORD dwBytes;
	//GENERIC_READ : �Ϲ����� �б� ����
	//OPEN_EXISTING : ������ ������ �� ���� ����.
	file = CreateFile(fileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (file == INVALID_HANDLE_VALUE)
	{
		MessageBox(_hWnd, "�������Ͽ���", "����", MB_OK);
		return "";
	}
	else
	{
		//���� : CreateFile���� �Ҵ�� �ڵ�, ���Ͽ� ������� ��Ʈ�� ��, �󸶳� �а� �� �������� ���� ũ��, �󸶳� �а� �� �������� ���� ��ȯ��(�ּ�)
		//�������̵� WriteFile(file, &BOM,2, &dwBytes, NULL);
		ReadFile(file, buf, 8292, &dwBytes, NULL);
		CloseHandle(file);
	}


	return string(buf);
}

void JsonSaveLoader::saveStringWithFileStream(char* fileName, string data)
{
	ofstream outFile(fileName);
	outFile << data << endl;

	outFile << data << endl;
	outFile.close();
}

string JsonSaveLoader::loadStringWithFileStream(char* fileName)
{
	ifstream fileIn;
	/*
	ios::in ������ �б⸸ ������ ���� �����ϰڴ�.
	ios::out ���⸸ ������ ���� �����ϰڴ�.
	ios::ate ������ ������ �� ������ ������ ���� �����͸� �̵���Ų��.
	ios::app �ش� ���Ͽ� �� ���������� �����͸� �߰��Ѵ�.
	ios::trunc ������ ������ �ش� ������ ��� �����͸� ���� ����.
	ios::binary ���̳ʸ� ���� ���� (�������� ���)
	*/
	fileIn.open(fileName, ios::in);

	char data;
	string jsonStr;

	while (fileIn.get(data))
	{
		jsonStr += data;
	}
	fileIn.close();

	return jsonStr;
}


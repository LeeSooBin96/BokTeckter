//DB ���� ��� Ŭ����
#pragma once

#define DB_SERVER_IP "localhost"
#define DB_USER_ID "root"
#define DB_USER_PW "610190"
#define DB_NAME "sakila" /* �����ͺ��̽� �̸� */

class CDBHandle
{
	MYSQL* connection = NULL, conn; //mysql ����, �ʱ�ȭ ��ü ������


public:
	/* DB �ʱ�ȭ �� ���� */
	void initializeDB();
	/* DB ���� ���� */
	void destroyConnect();

	/* ������ ���� */
	void excuteQuery(const char* query);
	/* ������ ���(SELECT) �������� */
	int getQueryResult(CArray<const char*>& list);
};


#include "pch.h"
#include "CDBHandle.h"

using namespace std;

void CDBHandle::initializeDB()
{
	mysql_init(&conn); //�ʱ�ȭ
	//DB ����
	connection = mysql_real_connect(&conn, DB_SERVER_IP, DB_USER_ID, DB_USER_PW, DB_NAME, 3306, (char*)NULL, 0);
	if (connection == NULL) {
		cerr << "Mysql ���� ���� : " << mysql_error(&conn) << endl;
		exit(1);
	}

	//�ѱ� ����� ���� �߰�
	mysql_query(connection, "set session character_set_connection=euckr;");
	mysql_query(connection, "set session character_set_results=euckr;");
	mysql_query(connection, "set session character_set_client=euckr;");
}

void CDBHandle::destroyConnect()
{
	mysql_close(connection);
}

/* ������ �ٷ�� �Լ��� */
void CDBHandle::excuteQuery(const char* query)
{
	if (mysql_query(connection, query) != 0) { //���� ����
		cerr << "���� ���� ���� : " << mysql_error(connection) << endl;
	}
}

int CDBHandle::getQueryResult(CArray<const char*>& list)
{ 
	MYSQL_RES* sqlRes = mysql_store_result(connection); //��� �ҷ��� ������
	int nRowNum = sqlRes->row_count; //��� ���� ����
	int nColNum = sqlRes->field_count; //��� ���� ����
	MYSQL_ROW sqlRow;
	
	list.SetSize(nRowNum * nColNum);
	for (int j = 0; j < nRowNum; j++) {
		sqlRow = mysql_fetch_row(sqlRes);
		for (int i = 0; i < nColNum; i++) {
			//CT2CA(cstr.operator LPCWSTR()) //������ Ȥ�� CString�� ����� �ְԵ� �� ���
			/*char buf[256];
			strcpy_s(buf, sqlRow[i]);*/
			list[j * nColNum + i] = sqlRow[i];
		}
	}
	
	mysql_free_result(sqlRes);
	return nColNum;
}
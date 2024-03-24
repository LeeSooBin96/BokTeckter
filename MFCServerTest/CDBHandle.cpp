#include "pch.h"
#include "CDBHandle.h"

using namespace std;

void CDBHandle::initializeDB()
{
	mysql_init(&conn); //초기화
	//DB 연결
	connection = mysql_real_connect(&conn, DB_SERVER_IP, DB_USER_ID, DB_USER_PW, DB_NAME, 3306, (char*)NULL, 0);
	if (connection == NULL) {
		cerr << "Mysql 연결 오류 : " << mysql_error(&conn) << endl;
		exit(1);
	}

	//한글 사용을 위해 추가
	mysql_query(connection, "set session character_set_connection=euckr;");
	mysql_query(connection, "set session character_set_results=euckr;");
	mysql_query(connection, "set session character_set_client=euckr;");
}

void CDBHandle::destroyConnect()
{
	mysql_close(connection);
}

/* 쿼리문 다루는 함수들 */
void CDBHandle::excuteQuery(const char* query)
{
	if (mysql_query(connection, query) != 0) { //쿼리 실행
		cerr << "쿼리 실행 오류 : " << mysql_error(connection) << endl;
	}
}

int CDBHandle::getQueryResult(CArray<const char*>& list)
{ 
	MYSQL_RES* sqlRes = mysql_store_result(connection); //결과 불러올 포인터
	int nRowNum = sqlRes->row_count; //결과 행의 개수
	int nColNum = sqlRes->field_count; //결과 열의 개수
	MYSQL_ROW sqlRow;
	
	list.SetSize(nRowNum * nColNum);
	for (int j = 0; j < nRowNum; j++) {
		sqlRow = mysql_fetch_row(sqlRes);
		for (int i = 0; i < nColNum; i++) {
			//CT2CA(cstr.operator LPCWSTR()) //쿼리문 혹시 CString에 결과값 넣게될 시 사용
			/*char buf[256];
			strcpy_s(buf, sqlRow[i]);*/
			list[j * nColNum + i] = sqlRow[i];
		}
	}
	
	mysql_free_result(sqlRes);
	return nColNum;
}
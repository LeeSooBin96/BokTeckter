//DB 관련 기능 클래스
#pragma once

#define DB_SERVER_IP "localhost"
#define DB_USER_ID "root"
#define DB_USER_PW "610190"
#define DB_NAME "sakila" /* 데이터베이스 이름 */

class CDBHandle
{
	MYSQL* connection = NULL, conn; //mysql 연결, 초기화 객체 포인터


public:
	/* DB 초기화 및 연결 */
	void initializeDB();
	/* DB 연결 종료 */
	void destroyConnect();

	/* 쿼리문 실행 */
	void excuteQuery(const char* query);
	/* 쿼리문 결과(SELECT) 가져오기 */
	int getQueryResult(CArray<const char*>& list);
};


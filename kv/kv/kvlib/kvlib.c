#include <stdio.h>
#include <strings.h>

// 각 모든 함수는 성공시 0, 실패시 각자 정의한 에러코드를 리턴한다.
 


// 주어진 key를 이용하여 value를 찾고, buf에 저장하여 리턴시켜 준다.
// 존재하지 않는 key인 경우 null을 리턴한다.
int kvget(char *key, char *buf)
{
 	return 0;
}

// 주어진 key와 data를 이용하여 kv store에 저장한다. 
// 이미 key가 존재하는 경우 덮어쓴다. 
int kvput(char *key, char *data)
{
 	return 0;
}

// 주어진 key를 이용하여 key와 value를 삭제한다. 
// 존재하지 않는 key를 삭제하려하면 그냥 0을 리턴한다.
int kvdel(char *key)
{
 	return 0;
}

// kv store를 open하여 기존의 key-value를 불러온다.
// 기존의 kv store가 없다면 생성한다. 
int kvopen()
{
 	return 0;
}

// kv store를 close한다. 
int kvclose()
{
 	return 0;
}




# 2018-2semester_System_programming-Key-Value_store_library

### 2018년 2학기 시스템프로그래밍설계 팀 프로젝트 : Key-Value store 라이브러리 제작

---

IDE : Dev C++ 5.9.2  
Language : C  
Advisor : Prof. Heeseung Jo  
Team Member : Lee Bum-won, Choi Se-jin, Lee Kang-min

### How to use

1. Download ALL file
2. Copy /kvlib.c to /kv/kv/kvlib/ (Overwrite)
3. Copy /kv/kv/kvlib to /kv.eval.dist/kv.eval/ (Overwrite)
4. Compile kvlib.c
5. Compile main.c
6. Start kv.exe

---

System Programming Project Guide

1. 프로젝트 주제  
   • Key-Value store 라이브러리 제작
   • 프로젝트 결과물은 key-value store 를 사용하는 응용프로그램과 key-value 를 처리/저장할 수 있는 라이브러리로 구성된다.  
   • 응용프로그램은 라이브러리를 링크하여 빌드되며, 정해진 인터페이스를 이용하여 key value 를 다룬다.  
   • 언어는 C 로만 한정한다. (C++ 제외)  
   • kv.eval 응용프로그램으로 라이브러리를 테스트하며 속도가 빠를 수록 좋은 점수를 부여

2. 요구사항
   • 기존의 오픈소스 라이브러리를 사용하는 것은 금지 (반드시 직접 구현할 것)  
   • key value data 는 응용프로그램의 종료 시 disk 에 저장되어야 하며, 다시 응용프로그램 시작 시 기존의 데이터를 불러올 수 있어야 한다.

3. Library interface  
   • 반드시 구현하여야 할 함수는 kvlib/main.c 에 포함된 5 가지이다.

```
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

```

• 상기 함수 이외의 필요에 따라 추가 함수 등을 구현한다.  
• key 와 value 는 길이가 다양할 수 있다.  
• key 와 value 는 특수문자(\n, \0, ..., 빈칸)등은 포함하지 않는다. (기호는 포함됨)  
• key 는 최대 4096B 까지만 사용한다.  
• value 의 크기는 제한이 없다.

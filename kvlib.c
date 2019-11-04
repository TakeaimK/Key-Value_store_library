/*
----------------------------------------------------------------------
	System programming Team Project : make key-value store library
	
							201414825 이범원
							201511033 최세진
							201615407 이강민 

----------------------------------------------------------------------
*/
//필요한 헤더 include 
#include<stdio.h>
#include<stdlib.h>
#include<strings.h>

#define SUCCESS   0			//성공시 0 return 
#define FAULT   1			//실패시 1 return 

#define TSIZE    357913      //100000 x 3에 가까운 소수(데이터 100000개보다 약 30%의 공간 추가)
#define KEY_MAX_SIZE 4097   // KEY MAX SIZE IS 4096 + '\0'
#define VALUE_MAX_SIZE 513   // VALUE MAX SIZE IS 512 + '\0'

typedef struct TreeNode            // 이진탐색트리에 사용 될 노드 구조체 
{
   char key[KEY_MAX_SIZE];       // file로부터 받아온 key 값이 저장되기 위한 변수
   char value[VALUE_MAX_SIZE];      // file로부터 받아온 data 값이 저장되기 위한 변수

   struct TreeNode* left;         // TreeNode 왼쪽 자식노드
   struct TreeNode* right;         // TreeNode 오른쪽 자식 노드
   
}NODE;

typedef struct hashTable         // 해시테이블 구조체 
{
   NODE* tableIndex[TSIZE];      // 사이즈는 10007 
   
}TABLE;

TABLE table;		//전역 테이블 선언 


int hashFunction(char *key)         // 해시 함수 
{
   unsigned int hash = 0; 		//테이블은 음수가 없으므로 unsigned 선언 
   int tmn = *key;				//첫 key를 백업 
   while(*key)                  // key의 첫째자리부터 NULL이 나올때까지 반복 
   {
      hash = hash + *key;       // 각 자리의 문자를 int형으로 더해준다. 
      *key++;                  // 다음 바이트의 문자로 넘어감 
   }
   hash*=71;					//소수 71을 곱셈 
   if((tmn - 97) < 47){			//첫 key의 값에 따라 테이블 위치 미세 조정 
   	hash+=tmn;
   }
   else{
   	hash+=((tmn - 97) - 61);
   }
   return hash % TSIZE;			//테이블 내로 들어가도록 나머지 연산 
}

int insertNode(NODE **root, char *key, char *value)
{
   NODE *parent, *child;                            //부모노드, 자식노드
   NODE *newNode; // = (NODE*)malloc(sizeof(NODE));         //새로운노드

   child = *root;                                 // 자식노드를 root에 연결( 해시 테이블)
   parent = NULL;                                  // 부모를 비워준다.
   
   //탐색을 먼저 수행
   while(child != NULL)                            // NULL이 될때까지 반복  
   {  
      if(strcmp(key, child->key)==0)
      {
         strncpy(child->value, value, strlen(value));   //key값이 같으면 value 덮어쓰기 
         return SUCCESS;                           //들어온 key값과 노드의 key 값이 같을 경우 insert 종료 
      } 
      parent=child;                              // 부모에 현재 노드값을 넣어준다. 부모와 자식을 링크해주기 위해서 부모를 알 필요가 있음 
      if(strcmp(key, child->key)<0) child = child->left;   // key값보다 현재 노드의 key값이 작을 경우 왼쪽자식트리로 이동
      else child = child->right;                      // key값보다 현재 노드의 key값이 클 경우 오른쪽으로 이동 
   }
   
   //item이 트리안에 없으므로 삽입가능
   newNode = (NODE*)malloc(sizeof(NODE));
   
   if(newNode == NULL)                              // 동적할당이 안될경우 
   {
      printf("Memory falut in insertNode\n");
      return FAULT;
   }
   //데이터 복사
   strcpy(newNode->key, key);                         // 노드에 key값 넣음 
   strcpy(newNode->value, value);                      // 노드에 value값 넣음
   newNode-> left = NULL;                          // 왼쪽 과 
   newNode-> right = NULL;                         // 오른쪽은 비워준다 
   //부모노드와 링크연결
   if(parent != NULL){                               // 부모가 NULL이 아닐 경우 
      if(strcmp(key, parent->key)<0) {                  // key값끼리 비교해서 작을경우 
         parent->left = newNode; 
      }                  // 부모의 왼쪽에 노드를 넣는다 
      else{                                     // 클경우 
         parent->right = newNode;
      }
   }                   // 오른쪽에 넣는다 
   else
      *root = newNode;                            // 부모가 없다면 root에 넣어주고 끝냄 
      
   return SUCCESS;
}

int kvget(char *key, char *buf)
{
   int index = hashFunction(key);
   
   NODE* searchKeyValue; // 매개변수로 입력받은 key가 저장된 이진탐색트리 노드를 검색하기 위한 BinSearchTreeNode 포인터 형 구조체 변수
   searchKeyValue = table.tableIndex[index]; // pBinSearchTreeNode에 찾고자 하는 key의 첫 번째 문자로 구성된 이진탐색트리의 rootNode를 저장
   
   while(searchKeyValue != NULL){ // 빌때 까지 key값 비교 반복 
      if(strcmp(key, searchKeyValue->key)<0)
      { 
         searchKeyValue = searchKeyValue->left; // 왼쪽으로
      }
      else if(strcmp(key, searchKeyValue->key)==0)
      {
         strncpy(buf, searchKeyValue->value, strlen(searchKeyValue->value)+1); // buf에 저장 
         return SUCCESS;
      }
      else if(strcmp(key, searchKeyValue->key)>0)
      { 
         searchKeyValue = searchKeyValue->right;// 오른쪽으로
      }
   }
   
   strcpy(buf, ""); // key값이 없으므로 buf값을 NULL로 초기화
   return FAULT;
}

int kvput(char *key, char *value)
{
   int index = hashFunction(key);	// index = key값 해시
   
   insertNode(&(table.tableIndex[index]), key, value);   // key값과 value값을 노드로  insert 시켜준다. 
   return SUCCESS;
}

// 주어진 key를 이용하여 key와 value를 삭제한다. 
// 존재하지 않는 key를 삭제하려하면 그냥 0을 리턴한다.
int kvdel(char *key)
{
    int index = hashFunction(key);      // index = key 값 해시
    NODE *parentNode, *childNode, *currentNode, *successorNode, *predecessorNode;
   parentNode = NULL;                                           // 부모노드는 비워주고 
   currentNode = table.tableIndex[index];                           // index의 첫부분부터 search 
   
   while(currentNode != NULL && strcmp(currentNode->key, key) != 0)       // currentNode가 비어있지 않고, 들어온key값과 노드의 key 값이 다를경우  
   {
      parentNode = currentNode;                                  // currentNode은 부모에 넣고 
      if(strcmp(key, currentNode->key)<0) {
         currentNode = currentNode->left;
      }// 키값과 현재노드값을 비교하여 이동 
      else {
         currentNode = currentNode->right;
      }
   }
   
   if(currentNode == NULL) return FAULT;                           //탐색트리에 없는 키
   
   //단말노드인경우
   if((currentNode->left == NULL)&&(currentNode->right == NULL)) 
   {
      if(parentNode != NULL)                               // 부모노드가 있으면 
      {
         if(parentNode->left == currentNode)                // 왼쪽자식이 currentNode일 경우 
            parentNode->left = NULL;                            //왼쪽을 비워준다. 
         else                                              // 오른쪽 자식일 경우 
            parentNode->right = NULL;                            // 오른쪽을 비워준다. 
      }
      else {                                              //부모노드가 없으면 루트
         table.tableIndex[index] = NULL;
      }
      return SUCCESS;
   }
   
   //두개의자식을 가지는 경우
   else if((currentNode->left != NULL)&&(currentNode->right != NULL))
   {
      predecessorNode = currentNode;      					 //오른쪽 서브트리애서
      successorNode = currentNode->right;   				 // 후속자를 찾는다 
      while(successorNode->left != NULL)					//왼쪽 자식이 NULL일 때까지 
      {
         predecessorNode = successorNode;      				//넣어 주고 
         successorNode = successorNode->left;   			 // 왼쪽자식으로 이동 
      }
      strcpy(currentNode->key, successorNode->key); 			// 노드에 key값 넣음 
      strcpy(currentNode->value, successorNode->value); 		// 노드에 value값 넣음
      
      if(predecessorNode->left == successorNode)        		 //후속자의 부모와 
         predecessorNode->left = successorNode->right;    	  //자식을 연결
      else
         predecessorNode->right = successorNode->right;  
      return SUCCESS;
   }
   
   //하나의 자식만 있는경우
   else if(((currentNode->left != NULL)&&(currentNode->right == NULL)) || ((currentNode->left == NULL)&&(currentNode->right != NULL)))
   {
      if(currentNode->left != NULL) childNode = currentNode->left;
      else childNode = currentNode->right;
      
      if(parentNode != NULL) 						// 부모가 비어있지 않을 경우 
      {    											//부모노드를 자식노드와 연결
         if(parentNode->left == currentNode)
            parentNode->left = childNode; 
         else                  
            parentNode->right = childNode;   
      }
      else
         table.tableIndex[index] = childNode; 		// 부모노드가 없으면 루트 
         
      return SUCCESS;
   }
   else{	//이도 저도 아닌 경우 에러 처리 
      return FAULT;
   }
}

int kvopen()
{
   int index;												//해시함수 결과값을 저장할 변수 
   char key[KEY_MAX_SIZE];									//key를 임시로 받을 배열 
   char value[VALUE_MAX_SIZE];								//value를 임시로 받을 배열 
   NODE* tempNode;												//구조체 read 후 넣어줄 임시 node 
   FILE *keyValueText = fopen("keyValue.bin", "ab+");             // keyValue 파일을 바이너리 모드로 오픈 
      
   if(feof(keyValueText)==FAULT)	//파일 에러시 종료 
   {
      printf("keyValue File is ERROR.\n");
      return FAULT;
   }
   
   if(keyValueText != NULL)     //keyValueText에 값이 있으면 기존의 key-value를 불러오기 위하여 
   {
      while(1)         //keyValueText안의 데이터 read
      {
         fread(&tempNode, sizeof(*tempNode), 1, keyValueText);
         if(feof(keyValueText)) break;								//파일의 끝이라면 종료 
         
         index = hashFunction(key);                    		     // key값 해시 
         insertNode(&(table.tableIndex[index]), key, value);    // key value를 노드로 insert 시켜준다.
      }   
   }
   fclose(keyValueText);			//파일 닫기 
    return SUCCESS;
}

// 트리를 순회하며 파일에 저장.
void storeTreeToFile_RECUR(NODE * root, FILE * KeyValueText)
{    
   
   if(root != NULL)		//루트로 돌아갈 때까지 순회. 중위 순회법 사용 
   {
      if(root->left != NULL)
         storeTreeToFile_RECUR(root->left, KeyValueText);		//왼쪽 자식으로 재귀 
      fwrite(&root, sizeof(*root), 1, KeyValueText);
      if(root->right != NULL)
         storeTreeToFile_RECUR(root->right, KeyValueText);		//오른쪽 자식으로 재귀 
   }
}

int kvclose()
{
   int index;
   FILE *keyValueText = fopen("keyValue.bin", "wb+");		//쓰기모드로 파일 열기 
   NODE* currentNode;      // 현재 노드에  root 넣음 

   for(index=0; index<TSIZE; index++)	// 테이블 전체 순회 
   {
      if(table.tableIndex[index]!=NULL)		//테이블의 루트노드가 있는 경우만 진입 
      {
         currentNode = table.tableIndex[index];		//최상위 노드를 삽입 
         storeTreeToFile_RECUR(currentNode, keyValueText);		//재귀함수 호출 
      
      }
   }
   fclose(keyValueText);			//파일 닫기 
   return SUCCESS;
}

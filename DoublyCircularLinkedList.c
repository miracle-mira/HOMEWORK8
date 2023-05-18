/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  School of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

/*Doubly Circular LinkedList 초기화 함수*/
int initialize(listNode** h) {

    /*헤드노더가 있을 경우 삭제*/
	if(*h != NULL)
		freeList(*h);

    /*헤드노더 생성: 전과 다르게 첫노드를 가리키는 게 아니라 일반 노드처럼 key,llink,rlink가 있는 노드가 헤더노드임*/
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;

	return 1;
}

/*Doubly Circular LinkedList 초기화 함수*/
int freeList(listNode* h){

    listNode* p = h->rlink;
    listNode* prev = (listNode *)malloc(sizeof(listNode));

    while(p != h){
        prev = p;
        p = p->rlink;
        free(prev);
    }

    free(h);


	return 0;
}


/*Doubly Circular LinkedList 출력 함수*/
void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}


/*Doubly Circular LinkedList 마지막 노드 삽입 함수*/
int insertLast(listNode* h, int key) {

    listNode* new = (listNode*)malloc(sizeof(listNode)); //새로운 노드 생성
    new->key = key; //새로운 노드의 key값을 주어진 key값으로 설정
    
    listNode* p = h->rlink; //현재 노드를 첫 노드로 설정

	//현재 노드를 마지막 노드로 설정하기위해 while문 설정
    while(p->rlink != h){
        p = p->rlink; //다음노드로 이동
    }

	//반복문을 빠져나왔을 때, p는 마지막 노드의 주소를 담고 있음
    p->rlink = new;  //기존 마지막 노드의 rlink를 헤드노드에서 새로운 마지막 노드의 주소로 바꿈
    new->llink = p;  //새로운 노드의 llink를 기존 마지막 노드의 주소로 가리킴
    new->rlink = h;  //새로운 노드의 rlink를 헤드노드로 설정해 마지막 노드임을 나타냄
    h->llink = new;  //헤드노드는 마지막 노드를 가리켜야하므로 헤드노드의 llink를 새로운 마지막 노드를 가리키도록 함.

	return 0;
}

/*Doubly Circular LinkedList 마지막 노드 삭제 함수*/
int deleteLast(listNode* h) {

	listNode* p = h->rlink; //현재 노드를 첫 노드로 설정
	listNode *prev = NULL;  //현재 노드의 바로 전 노드의 위치를 담은 변수 선언

	/*헤드노드밖에 없는데 헤드노드를 삭제하려고 하는 것을 방지*/
	if(p == h){
		printf("마지막 노드를 삭제할 수 없습니다.\n");
		return 0; //마지막 노드 삭제 함수 종료하여 다시 옵션을 선택하도록 함
	}

	/*헤드노드 제외한 노드가 한 개 이상은 있을 경우*/
	//prev가 마지막 노드를 가리키도록 설정함
	while(p->rlink != h){
		prev = p;
		p = p->rlink;
	}

	//반복문을 빠져나왔을 때 p는 마지막 노드를, prev는 마지막 전 노드의 위치를 담고 있음.
	prev->rlink = h;  //기존 마지막 전 노드의 rlink를 헤드노드의 위치로 바꾸면서 새로운 마지막 노드로 설정함
	h->llink = prev;  //헤드노드의 llink를 새로운 마지막 노드 주소로 담음.
	free(p);          //마지막 노드를 동적 할당 해제하므로써 삭제함

	return 1;
}

/*Doubly Circular LinkedList 첫 노드 삽입하는 함수*/
int insertFirst(listNode* h, int key) {

	listNode* p = h->rlink; //현재 노드를 첫 노드로 설정
	listNode* new = (listNode*)malloc(sizeof(listNode)); //새로운 노드 생성
	new->key = key; //새로운 노드의 key값을 주어진 key값으로 설정

	/*헤드노드만 있을 경우*/
	if(p == h){
		h->rlink = new;
		h->llink = new;
		new->llink = h;
		new->rlink = h;

		return 0;
	}

	/*헤드노드 제외한 노드가 한 개 이상은 있을 경우*/
	h->rlink = new;
	new->llink = h;
	new->rlink = p;
	p->llink = new;

	return 1;
}

/*Doubly Circular LinkedList 첫 노드를 삭제하는 함수*/
int deleteFirst(listNode* h) {

	listNode* p = h->rlink; //현재 노드를 첫 노드로 설정
	listNode *prev = NULL;  //현재 노드의 바로 전 노드의 위치를 담은 변수 선언

	/*헤드노드밖에 없는데 헤드노드를 삭제하려고 하는 것을 방지*/
	if(p == h){
		printf("마지막 노드를 삭제할 수 없습니다.\n");

		return 0; //마지막 노드 삭제 함수 종료하여 다시 옵션을 선택하도록 함
	}

	/*헤드노드 제외한 노드가 한 개만 있을 경우*/
	if(p->rlink == h){
		//이 경우 연결리스트에 헤드노드만 있기에 헤드노드의 rlink,llink 모두 헤드노드 위치를 갖음
		h->rlink = h;
		h->llink = h;

		free(p); //기존 첫 노드를 동적할당 해제함으로써 첫 노드를 삭제함

		return 0;
	}

	/*헤드노드 제외한 노드가 두 개 이상은 있을 경우*/
	prev = p;
	p = p->rlink;

	p->llink = h; //두 번째 노드의 llink를 헤드노드 위치로 설정하여 새로운 첫 노드로 설정함
	h->rlink = p; //헤드노드의 rlink가 새로운 첫 노드의 위치를 담음
	free(prev);   //기존 첫 노드를 동적할당 해제함으로써 첫 노드를 삭제함

	return 1;

}

/*Doubly Circular LinkedList 새로운 노드를 적절한 위치에 삽입하는 함수*/
int insertNode(listNode* h, int key) {

	listNode* p = h->rlink; //현재 노드의 위치를 담는 변수
	listNode* prev = h;  //현재 노드의 전 노드의 위치를 담는 변수
	listNode* new = (listNode*)malloc(sizeof(listNode));
	new->key = key;

	/*첫 노드 삽입: 헤드노드밖에 없어 첫 노드로 삽입해야하는 경우*/
	if(p == h){
		h->rlink = new;
		h->llink = new;
		new->llink = h;
		new->rlink = h;

		return 0;
	}

	/*중간삽입: 삽입 노드의 key값이 첫 노드의 키부터 마지막 노드의 키사이의 값들보다는 작을 경우*/
	while(p != h){
		if(key <= p->key){
			new->rlink = prev->rlink;
			new->llink = prev;
			prev->rlink = new;
			p->llink = new;

			return 0;
		}

		prev = p;
		p = p->rlink;

	}

	/*마지막 삽입: 삽입 노드가 기존 노드들의 모든 key값보다 커서 마지막 노드로 삽입해야하는 함.*/
	prev->rlink = new; //기존 마지막 노드를 새로운 마지막 노드의 전으로 바꿔줌.
	new->llink = prev; //새로운 노드의 전 노드를 기존 마지막 노드로 설정함.
	new->rlink = h;    //새로운 노드의 rlink가 헤드노드 위치를 가지도록 함.
	h->llink = new;    //헤드노드의 llink를 새로운 노드 위치로 함으로써 새로운 노드가 마지막 노드에 삽입되었음을 완성함.

	return 0;
}


/*Doubly Circular LinkedList 주어진 key값을 가진 노드를 삭제하는 함수*/
int deleteNode(listNode* h, int key) {

	listNode* p = h->rlink; //현재 노드의 위치를 담는 변수
	listNode* prev = h;  //현재 노드의 전 노드의 위치를 담는 변수
	listNode* next = p->rlink;

	/*헤드노드밖에 없는데 헤드노드를 삭제하려고 하는 것을 방지*/
	if(p == h){
		printf("주어진 노드 삭제할 수 없습니다.\n");

		return 0; //마지막 노드 삭제 함수 종료하여 다시 옵션을 선택하도록 함
	}

	
	/*헤드노드를 제외한 노드가 2개 이상일 경우 && 주어진 key값을 가진 노드가 중간에 있을 경우*/
	//주어진 key 값을 갖은 노드 위치를 찾는 과정
	while (next != h)
	{
		//주어진 key 값을 갖는 노드를 찾음
		if(key == p->key){
			prev->rlink = p->rlink;
			next->llink = p->llink;
			free(p);

			return 0;
		}

		prev = p;
		p = p->rlink;
		next = p->rlink;
	}
	
	/*주어진 key값을 가진 노드가 마지막에 있을 경우*/
	if(key == p->key){
		prev->rlink = p->rlink;
		next->llink = p->llink;
		free(p);

		return 0;
	}

	/*주어진 key값을 가진 노드가 없을 경우*/
	printf("주어진 key값을 가진 노드가 없습니다..\n");

		return 0; //다시 옵션을 선택하도록 함
}


/*Doubly Circular LinkedList를 전치하는 함수*/
int invertList(listNode* h) {


	return 0;
}
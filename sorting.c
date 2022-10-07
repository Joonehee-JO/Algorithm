#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int key;
    struct node *next;
}Node;

void arrayPrint(Node*);
void sort(Node*, int);
Node* readFile(Node*);
int count =0;

int main(){
    Node* head = (Node*)malloc(sizeof(Node*));  //헤드노드 생성
    head->next = NULL, head->key = -9999;
    head->next = readFile(head->next);          //파일 읽어서 배열 생성 후 시작주소 반환
    
    sort(head->next, count);    //정렬
    arrayPrint(head->next);     //정렬 후 출력
    
    //메모리할당해제
    Node* ptr = head->next;
    Node* previous = NULL;
    while(ptr != NULL){
        previous = ptr;
        ptr = ptr->next;
        free(previous);
    }
    free(head);
    //printf("%d", count);

    return 1;
}

//파일 읽고 배열 생성 후 시작주소 반환
Node* readFile(Node* ptr){
    char comma;         //,구분하기위함
    int data;           //읽어온 데이터
    int state = 0;      //중복데이터 구분위한 변수
    FILE* fp = fopen("Sample Data.txt", "r");   

    while(!feof(fp)){       //파일끝날 때까지 읽음
        fscanf(fp, "%d %c", &data, &comma);   //,구분과 데이터 저장

        //첫 노드 생성(루트노드)
        if(ptr == NULL){
            Node* temp = (Node*)malloc(sizeof(Node));
            temp->key = data, temp->next = NULL;
            ptr = temp; 
            count++;
            continue;
        }

        //삽입할노드 생성
        Node* temp = (Node*)malloc(sizeof(Node));
	    temp->key = data, temp->next = NULL;

        //해당 노드 리스트 마지막에 삽입
        Node* node = ptr;
        Node* previous = NULL;
        for(; node; previous = node, node=node->next){
            if(node->key == data){      //데이터가 중복되면 반복문 탈출
                state = 1;
                break;
            }
        }

        if(state != 1){     //데이터가 중복됐을 시점에 다음 노드가 없을 경우를 방지
            previous->next = temp;  //노드 삽입
            count += 1;             //노드 삽입 시 카운트증가
        }
        state = 0;          //중복데이터 구분 위한 변수 0으로 초기화
    }
    fclose(fp);             //배열 생성 후 파일 닫기

    return ptr;             //시작주소반환
}

//버블정렬알고리즘 사용하여 정렬
void sort(Node* curr, int size){
    int temp;
    Node* first = curr;         //첫노드(한번 반복 후 다시 시작주소로 돌아오기 위해 저장)
    Node* post = curr->next;    //다음노드를 가리킴
    
    for(int i=0; i<size-1; i++){
        if(post == NULL)break;          //다음노드 없으면 브레이크
        for(int j=0; j<size-1-i; j++){
            if(curr->key > post->key){  //앞뒤 비교 후 스왑
                temp = curr->key;
                curr->key = post->key;
                post->key = temp;
            }
            curr = post;            //포인팅 새로 맞춤
            post = post->next;
        }
        curr = first;               //한번 반복 후 처음부터 다시 반복
        post = curr->next;
    }
}

//배열(연결리스트) 출력
void arrayPrint(Node* ptr){         
    for(; ptr; ptr=ptr->next){      //노드 마지막까지 돌면서 출력
        printf("%d\n", ptr->key);
    }
}
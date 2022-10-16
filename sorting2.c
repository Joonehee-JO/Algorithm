#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int key;
    struct node *next;
    struct node *prev;
}Node;

void arrayPrint(Node*);
void sort(Node*, Node*);
Node* readFile(Node*);

Node* final = NULL;
int count =0;

int main(){
    Node* head = (Node*)malloc(sizeof(Node*));  //헤드노드 생성
    head->next = NULL, head->key = -9999;
    head->next = readFile(head->next);          //파일 읽어서 배열 생성 후 시작주소 반환
    
    sort(head->next, final);
    arrayPrint(head->next);

    //메모리할당해제
    Node* ptr = head->next;
    Node* previous = NULL;
    while(ptr != NULL){
        previous = ptr;
        ptr = ptr->next;
        free(previous);
    }
    free(head);
    final = NULL;

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
            temp->key = data, temp->prev = NULL, temp->next = NULL;
            ptr = temp; 
            count++;
            continue;
        }

        //삽입할노드 생성
        Node* temp = (Node*)malloc(sizeof(Node));
	    temp->key = data, temp->next = NULL, temp->prev = NULL;

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
            temp->prev = previous;
            count += 1;             //노드 삽입 시 카운트증가
            final = temp;
        }
        state = 0;          //중복데이터 구분 위한 변수 0으로 초기화
    }
    fclose(fp);             //배열 생성 후 파일 닫기

    return ptr;             //시작주소반환
}

//퀵정렬 알고리즘 사용하여 정렬
void sort(Node* left, Node* right){     //초기 left = 시작 노드, right = 마지막 노드
    if(left == NULL || right == NULL){  //전처리
        return;
    }
    int temp = 0;

    Node* part = left;              //part를 기준으로 피벗보다 큰 값과 작은 값의 영역을 구분
    Node* ptr = left;               //ptr은 피벗노드와 비교하는 용도
    Node* pivot = right;            //pivot은 마지막 노드를 가리킴
    for(; ptr != pivot; ptr=ptr->next){
        if(ptr->key < pivot->key){  //ptr의 값이 pivot의 값보다 작다면
            temp = part->key;       //스왑
            part->key = ptr->key;
            ptr->key = temp;
            part = part->next;
        }
    }
    temp = part->key;      //피벗을 part자리로 스왑, part기준 왼쪽은 피벗보다 작은 값이 정렬돼 있음
    part->key = pivot->key;
    pivot->key = temp;

    //정렬할 데이터가 하나밖에 없을 경우 방지
    if(left != part){           
        sort(left, part->prev);     //시작 노드부터 분할한 part의 이전 노드까지 다시 정렬
    }
    if(right != part){
        sort(part->next, right);    //분할한 part의 다음 노드부터 마지막 노드까지 다시 정렬
    }
}

//배열 출력
void arrayPrint(Node* ptr){         
    for(; ptr; ptr=ptr->next){      //노드 마지막까지 돌면서 출력
        printf("%d\n", ptr->key);
    }
}

# include <stdio.h>
# include <stdlib.h>
# include <string.h>


# define MAX 512
# define ROW 600 
// strdup(): 동적할당도 하면서 값의 복사도 해주는 함수
//Vehicle Name,CellDx,Sports Car,SUV,Wagon,Minivan,Pickup,AWD,RWD,Retail Price,Dealer Cost,EngineSize,Weight,Width

#define list_entry(ptr, type, member) \
	(type*)((char*)ptr - (unsigned long)&(((type*)0)->member))

# define ADD_ITEM(items,item,num,len) \
  (items)->item[num/len] |= 1 << (num%len)   

//# define HAS_ITEM  /
# define HAS_ITEM(items,item,num,len) \
  (items)->item[num/len] & 1 << (num%len)   


//# define REMOVE_ITEM /
# define REMOVE_ITEM(items,item,num,len) \
  (items)->item[num/len] &= ~(1 << (num%len))   


typedef enum car_type{
	CELL_DX,    
	SPORTS_CAR, 
	SUV,   		 
	WAGON,  		 
	MINIVAN,    
	PICKUP,    
	AWD,  			 
	BWD,
  MAX_ITEM_COUNT = 1024 
}car_type;

int len = MAX_ITEM_COUNT/(sizeof(unsigned int)*8);

typedef struct {
   unsigned int type[MAX_ITEM_COUNT/(sizeof(unsigned int)*8)];

}bitset;

// ==> car_type의 멤버의 수는 총 8개이다. 따라서 이는 unsigned char(8bit)를 사용하여 표현할 수 있다.
//     하지만 10000000 과 같이 2진수 그대로 써버리면 개발자만 이 숫자의 의미를 알게 되므로, (이를 나만 아는 마법의 숫자라 하여 
//     Magic Number 라고 한다.) 사용자 정의 자료형인 enum을 사용하여 가독성을 높인다. 

// 노드 구조체
struct node {
	struct node *prev;
	struct node *next;
};

//Car의 멤버는 총 8개.
typedef struct car{
	char *name;
	bitset types;
	int retail_price; 
	int dealer_cost;
	double engine_size;
	int weight;
	int width;

	struct node links;
}Car;



struct node head = { &head, &head };

void __add_node(struct node *prev, struct node* next, struct node* new) {
	new->next = next;
	new->prev = prev;
	prev->next = new;
	next->prev = new;
}

// s, s->next, new
void add_next(struct node *s, struct node* new) {
	__add_node(s, s->next, new);
}

// s->prev, s, new
void add_front(struct node *s, struct node* new) {
	__add_node(s->prev, s, new);
}

void check_type(Car *car,char **type1,char **type2){


	// type1
	if( HAS_ITEM(&car -> types,type,CELL_DX,len))
		*type1 = strdup("CellDx");
	else if( HAS_ITEM(&car -> types,type,SPORTS_CAR,len))
		*type1 = strdup("Sports Car");
	else if( HAS_ITEM(&car -> types,type,SUV,len))
		*type1 = strdup("SUV");
	else if( HAS_ITEM(&car -> types,type,WAGON,len))
		*type1 = strdup("Wagon");
	else if( HAS_ITEM(&car -> types,type,MINIVAN,len))
		*type1 = strdup("Minivan");
	else
		*type1 = strdup("Pickup");

	//type2
	if(HAS_ITEM(&car -> types,type,AWD,len)) 
		*type2 = strdup("AWD");
	else if(HAS_ITEM(&car -> types,type,BWD,len)) 
		*type2 = strdup("BWD");
	else 
		*type2 = strdup("None");


}

void print_list(struct node *head) {
	struct node *current = head->next;

	system("clear");

	printf("<head> ");
	while (current != head) {
		char *type1;
		char *type2;

		Car *car = list_entry(current, Car, links);
		check_type(car, &type1, &type2);

		printf(" -> [%s, %s, %s]\n", car->name, type1, type2);
		current = current->next;

		free(type1);
		free(type2);

		getchar();
	}

}

void print_car(Car *car, FILE *snapshot){

	char *type1;
	char *type2;
	check_type(car,&type1,&type2);

	if(snapshot == NULL){
		printf("%-60s %-15s %-15s %-5d %-5d %-2g %-5d %-5d \n",
				car -> name,
				type1,
				type2,
				car -> retail_price,
				car -> dealer_cost,
				car -> engine_size,
				car -> weight,
				car -> width);
	}
	else{
		fprintf(snapshot,"%-60s, %-15s, %-15s, %-5d, %-5d, %-2g, %-5d, %-5d \n",
				car -> name,
				type1,
				type2,
				car -> retail_price,
				car -> dealer_cost,
				car -> engine_size,
				car -> weight,
				car -> width);
	}

	free(type1);
	free(type2);
}

Car* make_Car(char *buf ){

	Car *car;
	car = (Car*)malloc(sizeof(Car)); //malloc 해주기
	int i;

	if(car == NULL){
		fprintf(stderr, "malloc error! \n");  
		return NULL;    
	}//malloc 안될시 오류 검사. 이러한 사소한거라도 오류 검사를 해야한다. 나중에 이러한 사소한 문제에 프로그램이 오류가 나므로!
	// malloc 오류는 더이상 할당할 메모리가 없을 때 발생한다.

	char *p;


	enum car_type car_types[8]={
		CELL_DX, 
		SPORTS_CAR, 
		SUV, 		 
		WAGON, 
		MINIVAN, 
		PICKUP, 
		AWD, 
		BWD};

	for(i=0,p=strtok(buf,",");p!=NULL; p = strtok(NULL,","),i++){

		switch(i){

			case 0: 
				car -> name = strdup(p);  // strdup()는 return 받는 포인터를 동적할당해주며 동시에 p의 문자열을 복사까지 한다.
				break; 
			case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8:
				if (atoi(p) == 1)
					ADD_ITEM(&car -> types,type,car_types[i-1],len);
				break;
			case 9:
				car -> retail_price = atoi(p);
				break;
			case 10:
				car -> dealer_cost = atoi(p);
				break;
			case 11:
				car -> engine_size = atof(p);
				break;
			case 12:
				car -> weight = atoi(p);
				break;
			case 13:
				car -> width = atoi(p);
				break;
		}

	}
	//print_car(car);

	return car;
}

int compare_idx=0;
//오름차순
int compare_ascending(const void *a , const void *b){

	Car *A = *(Car**)a;
	Car *B = *(Car**)b;

	switch(compare_idx-1){
		case 0:
			return A -> retail_price - B-> retail_price;
		case 1:
			return A -> dealer_cost - B-> dealer_cost;
		case 2:
			if(A -> engine_size > B -> engine_size) 
				return 1;
			else
				return -1;
			break;
			/* double일때
				 단순히 빼주면 -0.1을 0으로 인식하기 때문에(compare는 int로 반환하기에)
				 return 1, return -1로 명시하는 것이 좋다.
				 또 실수 자료형 자체가 오차가 있는 자료형이기에 서로 같은 경우는 return 0하지 않는다. (오차가 있으므로 애초에 같을리가 없다.)

				 그리고 abs(a-b)<0.0001 이러한 코드도 사용할 수 있지만, a,b가 같다하면 서로 0.00001만큼 차이가 나도 sort해줄수 없기때문에 이런 코드는 사용하지 말하야 한다.
			 */
		case 3:
			return A -> weight - B-> weight;
		case 4:
			return A -> width - B-> width;
	}

}

int compare_descending(const void *a , const void *b){

	Car *A = *(Car**)a;
	Car *B = *(Car**)b;

	switch(compare_idx-1){
		case 0:
			return B -> retail_price - A-> retail_price;
		case 1:
			return B -> dealer_cost - A-> dealer_cost;
		case 2:
			if(B -> engine_size > A -> engine_size)
				return 1;
			else
				return -1;
			break;
		case 3:
			return B -> weight - A-> weight;
		case 4:
			return B -> width - A-> width;
	}

}
int filter(Car **car, struct node *head,int sel_type,int sel_info ,int sel_flow){

	struct node *current = head -> next;
	car_type car_types[8] ={
		CELL_DX, 
		SPORTS_CAR, 
		SUV, 		 
		WAGON, 
		MINIVAN, 
		PICKUP, 
		AWD, 
		BWD
	}; 

	//Car *car[ROW];
	int count=0;
	while(current != head){

		//char *type1;
		//char *type2;

		Car *curcar = list_entry(current, Car, links);
		//check_type(car, &type1, &type2);

		// 1st filter
		if(HAS_ITEM(&curcar->types,type,car_types[sel_type-1],len))
			car[count++] = curcar;    

		current = current -> next;
	}

	// 2st filter
	compare_idx = sel_info;  
	if(sel_flow ==1)
		qsort(car, count, sizeof(Car*), compare_ascending);  
	else
		qsort(car, count, sizeof(Car*), compare_descending); 


	int i;
	for(i=0;i<count;i++)
		print_car(car[i],NULL);

	return count;
}
int main(){

	FILE *fp;
	char buf[MAX];
	int i;
	Car *car; //변수로 배열을 선언하면 그만큼 메모리 할당이되므로 메모리 낭비가 심하다. 따라서 포인터 배열을 선언하고 
	//이후 각 element에 동적할당(malloc)을 사용하자.

	// 1. 파일 열기 
	fp = fopen("car_data.csv", "r");
	if(fp == NULL){
		fprintf(stderr,"error!! file not exist ...\n"); //sterr을 리다이렉션으로 사용하려면 2> 으로 사용하자.
		return 1;
	}

	//한 줄씩 받기.   
	i=0; 
	while(fgets(buf,MAX,fp) != NULL){  //  == while(fgets(buf,MAX,fp))
		if(++i == 0) // 첫줄은 무시한다. if문은 모든 i가 들어가므로 i를 +1하는 기능도 있다.    	     
			continue;

		//1     
		// strlen 사용하여 \n 값 없애기.
		int len = strlen(buf);
		if(buf[len -1] == '\n')
			buf[len -1] = '\0';
		//printf("%s\n", buf); 
		car = make_Car(buf);
		if (car == NULL)
			continue;
		add_front(&head,&car->links);
	}

	i -= 1; // 첫줄 빼기
	//print_list(&head);

	int flag =0;

  printf("(총 %d의 데이터가 로드되었습니다.) \n",i);
	
	while(1){
		int option;
		int sel_type;
		int sel_info;
		int sel_flow;
		int file_opt;
		char buffer[32];
		FILE *snapshot;
		Car *car[ROW];
		int count;
		int j;

		printf("1. 검색\n");
		printf("2. 종료\n");
		printf("선택 > ");
		scanf("%d", &option);

		switch(option-1){
			case 0:
				printf("1. CellDx \n");
				printf("2. Sports Car \n");
				printf("3. SUV \n");
				printf("4. Wagon \n");
				printf("5. Minivan \n");
				printf("6. Pickup \n");
				printf("7. AWD \n");
				printf("8. RWD \n");
				printf("선택 > ");
				scanf("%d",&sel_type);

				printf("1. Retail Price \n");
				printf("2. Dealer Cost \n");
				printf("3. Engine Size \n");
				printf("4. Weight \n");
				printf("5. Width \n");
				printf("선택 > ");
				scanf("%d",&sel_info);

				printf("1. 오름차순 정렬 \n");
				printf("2. 내림차순 정렬 \n");
				printf("선택 > ");
				scanf("%d",&sel_flow);

				count=filter(car,&head,sel_type,sel_info,sel_flow);

				printf("파일로 저장하시겠습니까? \n");
				printf("1.예 \n");
				printf("2.아니오 \n");
				printf("선택 > ");
				scanf("%d",&file_opt);
				switch(file_opt-1){
					case 0:
						printf("파일이름 > ");
						scanf("%s", buffer);

						snapshot = fopen(buffer, "w");
						for(j=0; j<count; j++)
							print_car(car[j],snapshot);
						fclose(snapshot);
						printf("파일에 저장되었습니다.\n");
						break;    
				}
				break;

			case 1:
				flag = 1;
				break;

		}

		system("clear");
		if(flag ==1)
			break;
	}
	fclose(fp);
	return 0;
}

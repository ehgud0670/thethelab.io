# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "struct.h"
# include "func.h"

# define MAX 512
# define ROW 600 

int len;

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
  char *type1;
  char *type2;
	
	system("clear");

	printf("<head> ");
	while (current != head) {

		Car *car = list_entry(current, Car, links);
		check_type(car, &type1, &type2);

		printf(" -> [%s, %s, %s]\n", car->name, type1, type2);
		current = current->next;


		getchar();
	}
	free(type1);
	free(type2);

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
  }

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

	int count=0;
	while(current != head){


		Car *curcar = list_entry(current, Car, links);

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

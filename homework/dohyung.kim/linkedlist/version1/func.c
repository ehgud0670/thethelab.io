#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "struct.h"
#include "func.h"

# define ROW 400
# define COL 15
# define MAX 10000
# define WORD_SIZE 100

# define list_entry(ptr,type,member) \
    (type*)((char*)ptr - (unsigned long)(&(((type*)0)->member)))

void print_car( Car* car, int num, int flag, char *s){
  int i;
	if(s == NULL){
    printf("|No|  Name                 | kind | retail_price | dealer_cost | engine_size | weight | width |\n");
  for(int i=0; i<num; i++){
  	printf("%-3d ", i+1);
    printf("%-40s ", car[i].name);
    if(flag == 1)
      printf("%-15s ", car[i].kind2);
    else
      printf("%-15s ", car[i].kind1);
    printf("%-7d ", car[i].retail_price);
    printf("%-7d ", car[i].dealer_cost);
    printf("%-2lf ", car[i].engine_size);
    printf("%-4d ", car[i].weight);
    printf("%-2d ", car[i].width);

	  printf("\n");
	}
	printf("\n");
  }
  else{
    FILE *wp = fopen(s,"w");
    fprintf(wp,"|No|  Name                 | kind | retail_price | dealer_cost | engine_size | weight | width |\n");
    for(int i=0; i<num; i++){
  	  fprintf(wp,"%-3d ", i+1);
      fprintf(wp,"%-40s ", car[i].name);
      if(flag == 1)
        fprintf(wp,"%-15s ", car[i].kind2);
      else
        fprintf(wp,"%-15s ", car[i].kind1);
        fprintf(wp,"%-7d ", car[i].retail_price);
        fprintf(wp,"%-7d ", car[i].dealer_cost);
        fprintf(wp,"%-2lf ", car[i].engine_size);
        fprintf(wp,"%-4d ", car[i].weight);
        fprintf(wp,"%-2d ", car[i].width);

	  fprintf(wp,"\n");
	}
	  fprintf(wp,"\n");
    fclose(wp);

	}

}


void sort(Node *head, int sel_opt, int kind_idx, Kind *kind, int car_count){
  int sort_option;
  int sort_count;
  Node *current= head -> next;
  int kind_num;
  Car car[car_count];
  int i;
  int flag=0;
  int option;

  if(strcmp(kind[kind_idx].name, "AWD") ==0 || strcmp(kind[kind_idx].name,"RWD") == 0)
  	flag = 1;
  printf("1. 오름차순 정렬\n");
  printf("2. 내림차순 정렬\n");

  printf("선택> "); 
  scanf("%d", &sort_option);
  // 1번째 필터링  //kind
  sort_count = 0;
 
  while(current!=head){  
    Car *vehicle = list_entry(current, Car,links); 
    if(strcmp(vehicle->kind1, kind[kind_idx].name)==0 ||strcmp(vehicle->kind2, kind[kind_idx].name)==0){
      
      
      //car[sort_count] = (Car*)malloc(sizeof(Car));
  //    car[sort_count]->kind1 = (char*)malloc(sizeof(char)*32);
  //    car[sort_count]->kind2= (char*)malloc(sizeof(char)*32);

      strcpy(car[sort_count].name , vehicle -> name);
      strcpy(car[sort_count].kind1 , vehicle -> kind1);
      strcpy(car[sort_count].kind2 , vehicle -> kind2);
      car[sort_count].retail_price = vehicle -> retail_price;
      car[sort_count].dealer_cost = vehicle -> dealer_cost;
      car[sort_count].engine_size = vehicle -> engine_size;
      car[sort_count].weight = vehicle -> weight;
      car[sort_count].width = vehicle -> width;
  	  ++sort_count;
	  }
	  current = current->next;
	}
	/*
	for(i=0;i<sort_count;i++)
		printf("%s %lf \n", car[i]->kind1, car[i]->engine_size);
  */
  /*
  int (*fptr[10])(const void*, const void*);
  fptr[0]=compareRe1;
  fptr[1]=compareRe2;
  fptr[2]=compareDe1;
  fptr[3]=compareDe2;
  fptr[4]=compareEn1;
  fptr[5]=compareEn2;
  fptr[6]=compareWe1;
  fptr[7]=compareWe2;
  fptr[8]=compareWi1;
  fptr[9]=compareWi2;
*/
  // 2번째 필터링 swap
  printf("sort_count: %d \n", sort_count);
  printf("sort_option: %d \n", sort_option);
  printf("sel_opt: %d \n", sel_opt);

  //print_car(car,sort_count);

  if(sort_option == 1){
  	if(sel_opt == 1){
      qsort(car,sort_count, sizeof(Car),compareRe1);
      printf("hello\n");
		}
    else if(sel_opt ==2)
      qsort(car,sort_count, sizeof(Car),compareDe1);
    else if(sel_opt ==3)
      qsort(car,sort_count, sizeof(Car),compareEn1);
    else if(sel_opt ==4)
      qsort(car,sort_count, sizeof(Car),compareWe1);
    else
      qsort(car,sort_count, sizeof(Car),compareWi1);
	}
  else{
  	if(sel_opt == 1)
      qsort(car,sort_count, sizeof(Car),compareRe2);
    else if(sel_opt ==2)
      qsort(car,sort_count, sizeof(Car),compareDe2);
    else if(sel_opt ==3)
      qsort(car,sort_count, sizeof(Car),compareEn2);
    else if(sel_opt ==4)
      qsort(car,sort_count, sizeof(Car),compareWe2);
    else
      qsort(car,sort_count, sizeof(Car),compareWi2);
  }
  printf("\n\n"); 
  print_car(car,sort_count,flag,NULL);
   //for(i=0; i<sort_count;i++)
     //free(car[i]);
     
  // 다섯번째 
  printf("파일로 저장하시겠습니까?\n");
  printf("1. 예 \n");
  printf("2. 아니오 \n");
  printf("선택> "); 
  scanf("%d",&option);

  char filename[32];
  if(option==1){
    printf("파일이름> ");
    scanf("%s", filename);
    print_car(car,sort_count,flag,filename);
	}
  
}

int compareRe1(const void *a,const void *b){

  int num1 = (((Car*)a)->retail_price);
  int num2 = (((Car*)b)->retail_price);
  if (num1 >= num2)
  	return 1;
  return -1;
  //return  (int)((((Car*)a)->retail_price) - ((Car*)b)->retail_price); // 오름차순
}

int compareRe2(const void *a,const void *b){
  int num1 = (((Car*)a)->retail_price);
  int num2 = (((Car*)b)->retail_price);
  if (num2 >= num1)
  	return 1;
  return -1;
  //return  (int)((((Car*)b)->retail_price) - ((Car*)a)->retail_price); // 내림차순
}
int compareDe1(const void *a,const void *b){
  int num1 = (((Car*)a)->dealer_cost);
  int num2 = (((Car*)b)->dealer_cost);
  if (num1 >= num2)
  	return 1;
  return -1;
  //return  (int)((((Car*)a)->dealer_cost) - ((Car*)b)->dealer_cost); // 오름차순
}

int compareDe2(const void *a,const void *b){
  int num1 = (((Car*)a)->dealer_cost);
  int num2 = (((Car*)b)->dealer_cost);
  if (num2 >= num1)
  	return 1;
  return -1;
  //return  (int)((((Car*)b)->dealer_cost) - ((Car*)a)->dealer_cost); // 내림차순
}
int compareEn1(const void *a,const void *b){
  double num1 = (((Car*)a)->engine_size);
  double num2 = (((Car*)b)->engine_size);
  if (num1 >= num2)
  	return 1;
  return -1;
  //return  (int)((((Car*)a)->engine_size) - ((Car*)b)->engine_size); // 오름차순
}

int compareEn2(const void *a,const void *b){
  double num1 = (((Car*)a)->engine_size);
  double num2 = (((Car*)b)->engine_size);
  if (num2 >= num1)
  	return 1;
  return -1;
  //return  (int)((((Car*)b)->engine_size) - ((Car*)a)->engine_size); // 내림차순
}
int compareWe1(const void *a,const void *b){
  int num1 = (((Car*)a)->weight);
  int num2 = (((Car*)b)->weight);
  if (num1 >= num2)
  	return 1;
  return -1;
  //return  (int)((((Car*)a)->weight) - ((Car*)b)->weight); // 오름차순
}

int compareWe2(const void *a,const void *b){
  int num1 = (((Car*)a)->weight);
  int num2 = (((Car*)b)->weight);
  if (num2 >= num1)
  	return 1;
  return -1;
 // return  (int)((((Car*)b)->weight) - ((Car*)a)->weight); // 내림차순
}
int compareWi1(const void *a,const void *b){
  int num1 = (((Car*)a)->width);
  int num2 = (((Car*)b)->width);
  if (num1 >= num2)
  	return 1;
  return -1;
 // return  (int)((((Car*)a)->width) - ((Car*)b)->width); // 오름차순
}

int compareWi2(const void *a,const void *b){
  int num1 = (((Car*)a)->width);
  int num2 = (((Car*)b)->width);
  if (num2 >= num1)
  	return 1;
  return -1;
  //return  (int)((((Car*)b)->width) - ((Car*)a)->width); // 내림차순
}
int select_Info(){
  int sel_opt;

  printf("1. Retail Price\n");
  printf("2. Dealer Cost\n");
  printf("3. Engine Size\n");
  printf("4. Weight\n");
  printf("5. Width\n");
  
  printf("선택> "); 
  scanf("%d", &sel_opt);
  return sel_opt;
}
int select_Kind(Kind *kind, int kcount){
  int kind_idx;
  int i;
  for(i=0;i<kcount;i++){
    printf("%d.%s \n",kind[i].idx, kind[i].name);
	}
  printf("선택> "); 
  scanf("%d", &kind_idx); 
  kind_idx -=1;

  return kind_idx;
}

int set_Head(FILE *fp,int *name, Kind *kind, int *RP, int *DC ,int *ES, int *weight, int *width  ){
  int i;
  int j; 
  int head_count;
  char *head[COL];
  char *ptr;
  char *del;
  char *header=(char*)malloc(sizeof(char)*MAX);


  fgets(header,MAX,fp);

  head_count=0;
  ptr = strtok(header,",");
  while(ptr != NULL){
    head[head_count] = (char*)malloc(sizeof(char)*20);
    del =  strchr(ptr, '\r');
    if(del)
    	*del = 0;
    del = strchr(ptr, '\n');
    if(del)
    	*del =0;

    strcpy(head[head_count],ptr);
    ++head_count;
    ptr = strtok(NULL,",");// NULL이다!
	}
  free(header);

  j=0;
  for(i=0; i<head_count; i++){
    if(strcmp(head[i],"Vehicle Name")==0)
        *name = i;
    else if(strcmp(head[i],"Retail Price")==0)
    	  *RP = i;
    else if(strcmp(head[i],"Dealer Cost")==0)
    	  *DC = i;
    else if(strcmp(head[i],"EngineSize")==0)
        *ES = i;
    else if(strcmp(head[i],"Weight")==0)
        *weight = i;
    else if(strcmp(head[i],"Width")==0)
        *width = i;
    else{
       kind[j].idx = i;
       strcpy(kind[j].name, head[i]);
       j+=1;
		}	
  }
  free_arr(head,head_count);
  return j;
}

void free_arr(char **arr,int len ){

  int i;
  for(i=0; i<len; i++)
    free(arr[i]);
}

int set_Car(FILE * fp,Car **car,int name,Kind *kind,int kcount,int RP,int DC,int ES,int weight,int width){
  char *str[ROW];
  int car_count;
  int flag=0;
  int i,j;
  int word_count;
  char *ptr;
  char *del;
  char string[MAX];

  car_count = 0;
  while(fgets(string,MAX, fp) != NULL){
    str[car_count] =(char*)malloc(sizeof(char)*MAX);
    strcpy(str[car_count],string);
    car_count++;
	}

  char *word[car_count][COL];
  // str 자르기
  for(i=0; i <car_count; i++){

    ptr = strtok(str[i],",");  
    word_count=0;
    
    while(ptr != NULL){
      word[i][word_count] = (char*)malloc(sizeof(char)*WORD_SIZE);
      del =  strchr(ptr, '\r');
      if(del)
    	  *del = 0;
      del = strchr(ptr, '\n');
      if(del)
    	  *del =0;
      
      strcpy(word[i][word_count],ptr);
      ++word_count;
      ptr = strtok(NULL,",");// NULL이다!
		}
	}
	free_arr(str,car_count);
  
  // car 에 삽입하기
  for(i=0; i< car_count ; i++){
  	  car[i] = (Car*)malloc(sizeof(Car));
  	  //kind 정보 삽입하기 
      for(j=0; j<kcount; j++){
      	
      	int boolean;
        boolean=atoi(word[i][kind[j].idx]);
        if(boolean == 1 && flag == 0){
        //	car[i]->kind1 = (char*)malloc(sizeof(char)*32);
        	strcpy(car[i]->kind1, kind[j].name);
          flag = 1;
				}	
        else if(boolean == 1 && flag == 1){
        //	car[i]->kind2 = (char*)malloc(sizeof(char)*32);
        	strcpy(car[i]->kind2, kind[j].name);
        	flag=2;
			  }
			}
			if(flag!=2){
        //car[i]->kind2 = (char*)malloc(sizeof(char)*32);
				strcpy(car[i]->kind2,"None");
			}
			//flag 초기화
			flag = 0;
  	  //kind 외 정보들 삽입하기
      strcpy(car[i]->name, word[i][name]);   
      // printf("%s\n",car[i].name);
      car[i]->retail_price = atoi(word[i][RP]);
      car[i]->engine_size = atof(word[i][ES]);
      car[i]->dealer_cost = atoi(word[i][DC]);
      car[i]->weight = atoi(word[i][weight]);
      car[i]->width = atoi(word[i][width]);
      //free
      free_arr(word[i],word_count);

   }
  return car_count;
}

void insert_node(Node *prev, Node *next, Node *n){

  n -> prev = prev;
  n -> next = next;
  next -> prev = n;
  prev -> next = n;
}


void insert_rear(Node *node, Node *n ){
 
  insert_node(node, node ->next,n);
}

void insert_front(Node *node, Node *n){ 
  
  insert_node(node->prev,node , n);
}

void print_list(Node *head){
    
  Node *current = head->next;
  system("clear");
  printf("<head>");
  while(current!=head){

  	//printf("%ld" ,offsetof(User,links));
  	Car *car = list_entry(current, Car,links); 
    printf("<%s,%s,%s,%d,%d,%lf,%d,%d>\n", car->name, car->kind1, car->kind2,car->retail_price,car->dealer_cost,car->engine_size,car->weight,car->width);
    current = current -> next;
	
	}
  getchar();
}



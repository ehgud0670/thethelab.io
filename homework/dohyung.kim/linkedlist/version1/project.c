# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "struct.h"
# include "func.h"

# define ROW 400
# define COL 15
# define MAX 10000
# define WORD_SIZE 100

Node head={&head,&head};  
//Node head1={&head1,&head1};  //CellDx
//Node head2={&head2,&head2};  //Sports Car
//Node head3={&head3,&head3};  //SUV
//Node head4={&head4,&head4};  //Wagon
//Node head5={&head5,&head5};  //Minivan
//Node head6={&head6,&head6};  //Pickup
//Node head7={&head7,&head7};  //AWD
//Node head8={&head8,&head8};  //RWD

/*
Node* checkHead(int kind_idx){

  if(kind_idx == 1 )
    return &head1;
  else if(kind_idx == 2)
  	return &head2;
  else if(kind_idx == 3)
  	return &head3;
  else if(kind_idx == 4)
  	return &head4;
  else if(kind_idx == 5)
  	return &head5;
  else if(kind_idx == 6)
  	return &head6;
  else if(kind_idx == 7)
  	return &head7;
  else 
  	return &head8;
  
}
*/
int main(){
  int i;
  Car *car[ROW];
  Kind kind[10];
  int kcount;
  int car_count;
 
  int name;
  int RP;//Retail Price
  int DC;//Dealer Cost
  int ES;//EngineSize
  int weight;
  int width;
    
  int option;
  int kind_idx;
  int sel_opt;

  FILE *fp = fopen("car_data.csv","r");
  if(fp ==NULL){
    printf("error! file not exist...\n");
    return 1;
	}

  kcount = set_Head(fp, &name,kind,&RP,&DC,&ES,&weight,&width);   
  
  car_count=set_Car(fp,car,name,kind,kcount,RP,DC,ES,weight,width);

  // 연결리스트 만들기
  for(i=0;i<car_count;i++)
    insert_front(&head,&(car[i]->links));
  printf("총 %d개의 데이터가 로드되었습니다.\n", car_count);  
 
  
  // 옵션
  while(1){
    // 첫번째
    printf("1. 검색\n"); 
    printf("2. 종료\n"); 
    printf("선택> ");
    scanf("%d", &option); 
    if(option == 2)
    	break;
    // 두번째
    kind_idx = select_Kind(kind,kcount);
/*    
    for(i=0;i<car_count;i++){
      if(strcmp(car[i].kind1,kind[kind_idx].name)==0 )
        	insert_front(checkHead(kind_idx), &(car[i].links));
      if(strcmp(car[i].kind2, kind[kind_idx].name)==0) 
        	insert_front(checkHead(kind_idx), &(car[i].links));
			
			
    }
    */
    //print_list(&head);
    // 세번째
    sel_opt=select_Info(); 

    // 네번째
    sort(&head,sel_opt,kind_idx, kind, car_count);
    
  }
  fclose(fp);

  return 0;
}

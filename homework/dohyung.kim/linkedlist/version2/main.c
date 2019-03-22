
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "struct.h"
# include "func.h"

# define MAX 512
# define ROW 600 


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



int len = MAX_ITEM_COUNT/(sizeof(unsigned int)*8);

struct node head = { &head, &head };


int main(){

	FILE *fp;
	char buf[MAX];
	int i;
	Car *car;  

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

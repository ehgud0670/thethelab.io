# ifndef __STRUCT_H__
# define __STRUCT_H__

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

typedef struct {
   unsigned int type[MAX_ITEM_COUNT/(sizeof(unsigned int)*8)];

}bitset;


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


# endif

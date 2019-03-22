# include <stdio.h>


# define ADD_ITEM(items,item,num,len) \
  items.item[num/len] |= 1 << (num%len)   

//# define HAS_ITEM  /
# define HAS_ITEM(items,item,num,len) \
  items.item[num/len] & 1 << (num%len)   


//# define REMOVE_ITEM /
# define REMOVE_ITEM(items,item,num,len) \
  items.item[num/len] &= ~(1 << (num%len))   


enum item{
  TANKER,// enum의 초깃값은 0이다 .. (명심!)
  HEALER,
  NUKER,
  BUFFER,
  DEBUFFER,
  PULLER,
  PARKER,
  CASTER,
  MAX_ITEM_COUNT = 1024
};

int len = MAX_ITEM_COUNT/(sizeof(unsigned int)*8);

typedef struct {
  
  unsigned int offset[MAX_ITEM_COUNT/(sizeof(unsigned int)*8)];
}bitset;


//typedef unsigned int bitset[32];  // => 배열의 decay의 특성을 띄므로 
// bitset으로 사용하기에 부적절하다. (의미를 다르게 쓸 수 있으므로)
// 따라서 decay 특성이 없는 struct를 사용하자.



struct user{
  //bitset item;
  bitset items;
};


int main(){
	
	struct user user; 
    
  //ADD_TANKER
    ADD_ITEM(user.items,offset,TANKER,len);   



  //HAS_ITEM
  if(HAS_ITEM(user.items,offset,TANKER,len))
  	printf("탱커 있음.\n");
  else 
  	printf("탱커 없음. \n");

  //ADD_PARKER
  ADD_ITEM(user.items,offset,PARKER,len);   

  //HAS_ITEM
  if(HAS_ITEM(user.items,offset,PARKER,len))
  	printf("파커 있음.\n");
  else 
  	printf("파커 없음. \n");
  
  //REMOVE_TANKER
    REMOVE_ITEM(user.items,offset,TANKER,len);  
  
  //HAS_ITEM
  if(HAS_ITEM(user.items,offset,TANKER,len))
  	printf("탱커 있음.\n");
  else 
  	printf("탱커 없음. \n");



  return 0;
}

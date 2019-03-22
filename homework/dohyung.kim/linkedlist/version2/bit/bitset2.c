# include <stdio.h>

/*
TANKER = 00000001
~TANKER = 11111110


ADD_ITEM
변수.item |= TANKER;

REMOVE_ITEM
변수.item &= ~TANKER;

HAS_ITEM
변수.item & TANKER;


*/
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

typedef unsigned int bitset[32];  // => 배열의 decay의 특성을 띄므로 
// bitset으로 사용하기에 부적절하다. (의미를 다르게 쓸 수 있으므로)
// 따라서 decay 특성이 없는 struct를 사용하자.



struct user{
  bitset item;

};


int main(){
	
	struct user user; 
  
  printf("%d \n", len); 
//ADD_TANKER
  user.item[TANKER/len] |= 1 << (TANKER % len);

  //HAS_ITEM
  if(user.item[TANKER/len] & 1 << (TANKER % len))
  	printf("탱커 있음.\n");
  else 
  	printf("탱커 없음. \n");

  //ADD_PARKER
  user.item[PARKER/len] |= 1 << (PARKER % len);  
  //HAS_ITEM
  if(user.item[PARKER/len] & 1 << (PARKER % len))
  	printf("파커 있음.\n");
  else 
  	printf("파커 없음. \n");
  
  //REMOVE_TANKER
  user.item[TANKER/len] &= ~(1 << TANKER % len);
  //HAS_ITEM
  if(user.item[TANKER/len] & 1 << (TANKER % len))
  	printf("탱커 있음.\n");
  else 
  	printf("탱커 없음. \n");



  return 0;
}

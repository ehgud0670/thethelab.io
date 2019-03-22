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
  TANKER = 1 << 0,
  HEALER = 1 << 1,
  NUKER  = 1 << 2,
  BUFFER = 1 << 3,
  DEBUFFER = 1 << 4,
  PULLER = 1 << 5,
  PARKER = 1 << 6,
  CASTER = 1 << 7,
};

struct user{
  unsigned char item;
};


int main(){
	
	struct user user; 

  //ADD_TANKER
	user.item |= TANKER; // 00000001
  
  //HAS_ITEM
  if(user.item & TANKER)
  	printf("탱커 있음.\n");
  else 
  	printf("탱커 없음. \n");

  //ADD_PARKER
  user.item |= PARKER;  // 01000000
  
  //HAS_ITEM
  if(user.item & PARKER)
  	printf("파커 있음.\n");
  else 
  	printf("파커 없음. \n");
  
  //REMOVE_TANKER
  user.item &= ~TANKER; // 11111110
  
  //HAS_ITEM
  if(user.item & TANKER)
  	printf("탱커 있음.\n");
  else 
  	printf("탱커 없음. \n");
  
  return 0;
}

# ifndef __STRUCT_H__
# define __STRUCT_H__

typedef struct node{
   
  struct node *prev;
  struct node *next;

}Node;


typedef struct car{
  
  char name[32];
  char kind1[32];
  char kind2[32];
  int retail_price;
  int dealer_cost;
  double engine_size;
  int weight;
  int width;
  Node links;

}Car;

typedef struct kind{
 
 int idx;
 char name[32];

}Kind;

# endif

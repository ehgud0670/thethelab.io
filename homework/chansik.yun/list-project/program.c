#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node {
  struct node *prev;
  struct node *next;
};

#define list_entry(ptr, type, member) \
    (type*)((char*)ptr - (unsigned long)&(((type*)0)->member))

struct node head = { &head, &head };

void __add_node(struct node *prev, struct node* next, struct node* new) {
  new->next = next;
  new->prev = prev;
  prev->next = new;
  next->prev = new;
}

void add_next(struct node *s, struct node* new) {
  __add_node(s, s->next, new);
}

void add_front(struct node *s, struct node* new) {
  __add_node(s->prev, s, new);
}

struct car {
  char *name;
  unsigned char type;
  int retail_price;
  int dealer_cost;
  double engine_size;
  int weight;
  int width;
  
  struct node list;
};

enum car_type {
  CELL_DX = 1 << 7,
  SPORTS = 1 << 6,
  SUV = 1 << 5,
  WAGON = 1 << 4,
  MINIVAN = 1 << 3,
  PICKUP = 1 << 2,
  AWD = 1 << 1,
  RWD = 1 << 0
};


void print_car(const struct car *car) {
  printf("%s ", car->name);
  if (car->type & CELL_DX) {
    printf("CellDX ");
  } else if (car->type & SPORTS) {
    printf("Sports ");
  } else if (car->type & SUV) {
    printf("SUV ");
  } else if (car->type & WAGON) {
    printf("Wagon ");
  } else if (car->type & MINIVAN) {
    printf("Minivan ");
  } else if (car->type & PICKUP) {
    printf("Pickup ");
  }

  if (car->type & AWD) {
    printf("AWD ");
  } else if (car->type & RWD) {
    printf("RWD ");
  } else {
    printf("NONE ");
  }

  printf("%d %d %lf %d %d\n", 
      car->retail_price,
      car->dealer_cost,
      car->engine_size,
      car->weight,
      car->width);
}

struct car *alloc_car(char *buf) {
  char *p;
  int i;

  struct car *car = malloc(sizeof(struct car));
  if (car == NULL) {
    fprintf(stderr, "malloc failed..\n");
    return NULL;
  }

  car->type = 0;
  for (i = 0, p = strtok(buf, ","); p != NULL; p = strtok(NULL, ","), i++) {
    switch (i) {
      case 0: 
        car->name = strdup(p);
        break;
      case 1: case 2: case 3: case 4: case 5: case 6: case 7:
      case 8: {
                unsigned char type = atoi(p);
                car->type |= type << (8 - i);
                break;
              }
      case 9: 
              car->retail_price = atoi(p);
              break;
      case 10:
              car->dealer_cost = atoi(p);
              break;
      case 11:
              car->engine_size = atof(p);
              break;
      case 12:
              car->weight = atoi(p);
              break;
      case 13:
              car->width = atoi(p);
              break;
    }
  }

  return car;
}

void print_list(struct node *head) {
  struct node *current = head->next;
  while (current != head) {
    struct car *car = list_entry(current, struct car, list);
    print_car(car);

    current = current->next;
  }
}

int compare_pivot = 0;
int ascending_compare(const void *a, const void *b) {
  struct car *c1 = *(struct car **)a;
  struct car *c2 = *(struct car **)b;
  
  switch (compare_pivot) {
    case 0:
      return c1->retail_price - c2->retail_price;
    case 1:
      return c1->dealer_cost - c2->dealer_cost;
    case 2:
      if (c1->engine_size > c2->engine_size) {
        return 1;
      } else {
        return -1;
      } 
    case 3:
      return c1->weight - c2->weight;
    case 4:
      return c1->width - c2->width;
  }

}

int descending_compare(const void *a, const void *b) {
  struct car *c1 = *(struct car **)a;
  struct car *c2 = *(struct car **)b;

  switch (compare_pivot) {
    case 0:
      return c2->retail_price - c1->retail_price;
    case 1:
      return c2->dealer_cost - c1->dealer_cost;
    case 2:
      if (c2->engine_size > c1->engine_size) {
        return 1;
      } else {
        return -1;
      } 
    case 3:
      return c2->weight - c1->weight;
    case 4:
      return c2->width - c1->width;
  }
}

void filter_sort(struct node *head, int type, int pivot, int ascending) {
  enum car_type types[] = {
    CELL_DX,
    SPORTS,
    SUV,
    WAGON,
    MINIVAN,
    PICKUP,
    AWD,
    RWD,
  };

  enum car_type car_type = types[type - 1];
  struct node *current = head->next;
  struct car *cars[1024];
  int n = 0;
  int i = 0;

  while (current != head) {
    struct car *car = list_entry(current, struct car, list);
    if (car->type & car_type) {
      cars[n++] = car;  
    }

    current = current->next;
  }

  compare_pivot = pivot - 1;
  int (*compare)(const void*, const void*);
  if (ascending == 1) {
    compare = ascending_compare;
  } else {
    compare = descending_compare;
  }
  
  qsort(cars, n, sizeof(struct car*), compare);

  for (i = 0; i < n; ++i ){
    print_car(cars[i]);
  }
}


int main() {
  FILE* fp;
  char buf[512];
  int i;

  fp = fopen("car_data.csv", "r");
  if (fp == NULL) {
    fprintf(stderr, "file open error...\n");
    return 1;
  }

  i = 0;
  while (fgets(buf, sizeof buf, fp)) {
    int len;
    struct car *car;
    if (i++ == 0)
      continue;

    len = strlen(buf);
    if (len > 0) {
      buf[len - 1] = '\0';
    }

    car = alloc_car(buf);
    if (car == NULL) {
      continue;
    }

    add_front(&head, &car->list);
  }

  // print_list(&head);
  while (1) {
    int finish = 0;
    int choice;
    system("clear");
    printf("1. 검색\n");
    printf("2. 종료\n");
  
    scanf("%d", &choice);
    switch (choice - 1) {
      case 0:  
        {
          int type;
          int pivot;
          int ascending;
          printf("1. CellDx\n");
          printf("2. Sports Car\n");
          printf("3. SUV\n");
          printf("4. Wagon\n");
          printf("5. Minivan\n");
          printf("6. Pickup\n");
          printf("7. AWD\n");
          printf("8. RWD\n");
          scanf("%d", &type);

          printf("1. Retail Price\n");
          printf("2. Dealer Cost\n");
          printf("3. EngineSize\n");
          printf("4. Weight\n");
          printf("5. Width\n");
          scanf("%d", &pivot);

          printf("1. 오름차순\n");
          printf("2. 내림차순\n");
          scanf("%d", &ascending);

          printf("%d %d %d\n", type, pivot, ascending);
          filter_sort(&head, type, pivot, ascending);
        }
      case 1:
        finish = 1;     
        break;
    }
    
    if (finish) {
      break;
    }

  }
}









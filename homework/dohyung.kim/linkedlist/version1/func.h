# ifndef __FUNC_H__
# define __FUNC_H__

void print_car( Car* car, int num, int flag, char *s);
int compare1(const void *a,const void *b);
int compare2(const void *a,const void *b);
void print_list(Node *head);
void insert_front(Node *node, Node *n); 
void insert_rear(Node *node, Node *n );
void insert_node(Node *prev, Node *next, Node *n);
void sort(Node *head, int sel_opt, int kind_idx, Kind *kind, int car_count);
int select_Info();
int select_Kind(Kind *kind, int kcount);
int set_Car(FILE *fp,Car **car,int name,Kind *kind,int kcount,int RP,int DC,int ES,int weight,int width);

int set_Head(FILE *fp,int *name, Kind *kind, int *RP, int *DC ,int *ES, int *weight, int *width );

void free_arr(char **arr, int len);
int compareRe1(const void *a,const void *b);

int compareRe2(const void *a,const void *b);
int compareDe1(const void *a,const void *b);

int compareDe2(const void *a,const void *b);
int compareEn1(const void *a,const void *b);

int compareEn2(const void *a,const void *b);
int compareWe1(const void *a,const void *b);

int compareWe2(const void *a,const void *b);
int compareWi1(const void *a,const void *b);

int compareWi2(const void *a,const void *b);


# endif

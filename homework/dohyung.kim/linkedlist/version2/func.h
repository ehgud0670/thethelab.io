# ifndef __FUNC_H__
# define __FUNC_H__

void __add_node(struct node *prev, struct node* next, struct node* new);

void add_next(struct node *s, struct node* new);

void add_front(struct node *s, struct node* new);

void check_type(Car *car,char **type1,char **type2);

void print_list(struct node *head);

void print_car(Car *car, FILE *snapshot);

Car* make_Car(char *buf );

int compare_ascending(const void *a , const void *b);

int compare_descending(const void *a , const void *b);

int filter(Car **car, struct node *head,int sel_type,int sel_info ,int sel_flow);

# endif

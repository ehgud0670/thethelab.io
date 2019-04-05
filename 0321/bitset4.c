// bitset
#include <stdio.h>

enum {
	SWORD,
	DAGGER,
	SHIELD,
	SPEAR,
	AXE,
	GUN,
	STAFF,
	WAND,
	SWORD2,
	DAGGER2,
	SHIELD2,
	SPEAR2,
	AXE2,
	GUN2,
	STAFF2,
	WAND2,
	MAX_ITEM_COUNT = 1024
};

typedef struct {
	unsigned int data[MAX_ITEM_COUNT / (sizeof(unsigned int) * 8)];
} bitset_t;

struct user {
	bitset_t items;
};

#define ADD_ITEM(bitset, item) \
	(bitset)->data[(item) / 32] |= 1 << ((item) % 32)

#define REMOVE_ITEM(bitset, item) \
	(bitset)->data[(item) / 32] &= ~(1 << ((item) % 32))

#define HAS_ITEM(bitset, item) \
	(bitset)->data[(item) / 32] & 1 << ((item) % 32)

int main() {
	struct user user;
	printf("%ld\n", sizeof(user));

	ADD_ITEM(&user.items, SWORD);
	ADD_ITEM(&user.items, GUN);

	if (HAS_ITEM(&user.items, SWORD)) {
		printf("검이 있다.\n");
	} else {
		printf("검이 없다.\n");
	}

	REMOVE_ITEM(&user.items, SWORD);
	if (HAS_ITEM(&user.items, SWORD)) {
		printf("검이 있다.\n");
	} else {
		printf("검이 없다.\n");
	}
}

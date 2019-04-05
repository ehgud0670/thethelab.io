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
	MAX_ITEM_COUNT = 10000
};

typedef unsigned int bitset[MAX_ITEM_COUNT / (sizeof(unsigned int) * 8) + 1];

// 0 ~ 99
//  50
//     index: 50 / 32  => 1
//     offset: 50 % 32 => 18
struct user {
	bitset items;
};

#define ADD_ITEM(items, item) \
	items[item / 32] |= 1 << (item % 32)

#define REMOVE_ITEM(items, item) \
	items[item / 32] &= ~(1 << (item % 32))

#define HAS_ITEM(items, item) \
	items[item / 32] & 1 << (item % 32)

int main() {
	struct user user;
	printf("%ld\n", sizeof(user));

	ADD_ITEM(user.items, SWORD);
	ADD_ITEM(user.items, GUN);

	if (HAS_ITEM(user.items, SWORD)) {
		printf("검이 있다.\n");
	} else {
		printf("검이 없다.\n");
	}

	REMOVE_ITEM(user.items, SWORD);
	if (HAS_ITEM(user.items, SWORD)) {
		printf("검이 있다.\n");
	} else {
		printf("검이 없다.\n");
	}

	ADD_ITEM(user.items, 100);
	if (HAS_ITEM(user.items, 100)) {
		printf("OK\n");
	}

	REMOVE_ITEM(user.items, 100);
	if (HAS_ITEM(user.items, 100)) {
		printf("OK\n");
	} else {
		printf("NO\n");
	}


}

#if 0
int main() {
	struct user user;
	printf("%ld\n", sizeof(user));

	// user.items[SWORD] = 1;
	user.items |= SWORD; 
	user.items |= GUN;

	if (user.items & SWORD) {
		printf("검이 있다.\n");
	} else {
		printf("검이 없다.\n");
	}

	user.items &= ~SWORD;
	if (user.items & SWORD) {
		printf("검이 있다.\n");
	} else {
		printf("검이 없다.\n");
	}

	if (user.items & GUN) {
		printf("GUN이 있다.\n");
	} else {
		printf("GUN이 없다.\n");
	}
}
#endif

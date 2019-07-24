#include <stdio.h>

int(*foo())[4] {
	return arr;
}

void a() {}
// void (*p)()

// pointer to
// array of
// function

int(*(*goo())())[4] {
	return foo;
}

int main() {
	printf("%d\n", goo()()[0][2]);
}

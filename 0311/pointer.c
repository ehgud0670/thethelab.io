#include <stdio.h>

// '포인터'를 왜 사용해야 하는가?
//  => 함수에서 전달받은 인자의 값을 변경할 수 없기 때문에
//  => Call by reference

// DRY 원칙
//  Don't Repeat Yourself
//  => 반복하지 말아라.

// C 언어는 인자를 전달할 때, 복사를 수행한다.
//  => Call by value
//   : Call by value는 전달받은 인자의 값을 변경할 수 없다.
//    -> 값을 전달하지 말고, 주소를 전달해서, 주소값의 참조를 통해 값을 변경하면 된다.

void swap(int a, int b) {
	int temp = a;
	a = b;
	b = temp;
}

int main() {
	int a = 10;
	int b = 20;
	
	swap(a, b);

	printf("swap: %d %d\n", a, b);
	return 0;
}
#if 0
int main() {
	int a = 10;
	int b = 20;

	int temp = a;
	a = b;
	b = temp;

	temp = a;
	a = b;
	b = temp;

	printf("swap: %d %d\n", a, b);
	return 0;
}
#endif

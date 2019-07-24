#include <stdio.h>
void foo(int (*arr)[4], int n) {
	int i, j;
	for (i = 0; i < n; ++i) {
		for (j = 0; j < 4; ++j) {
			printf("%d\n", arr[i][j]);
		}
	}
}

int main() {
	int arr[3][4] = { 0, };
	// int[3][4]
	//  => arr은 3개 짜리 배열이다.
	//  => 하나의 원소가 int[4]인...
	foo(arr, 3);
	// arr: 배열의 이름은 배열의 첫번째 원소의 시작 주소로 해석된다.
	// &arr[0]
	//  arr[0]: int[4]
	// &arr[0]: int(*)[4]

}

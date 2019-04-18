
// 표준 입출력

// C
//   OS: Unix => Linux
//   - 모든 것은 파일이다.
//    OS의 자원을 파일의 인터페이스를 통해 다룰 수 있다.

//  운영체제 역활
//    => 자원을 관리한다.
//    자원
//      1. 물리적인 자원
//         CPU / RAM / HDD / SSD / Network / Device
//      2. 추상적인 자원
//         Process, Thread, Page, File

//    printf("Hello\n");
//    - 16bit OS: 비디오 메모리에 "Hello" 직접 쓴다.
//    - 32/64 OS: 보호 모드 운영체제
//     => 운영체제가 제공하는 API를 통해서, 자원에 접근할 수 있다.

//        fopen 
//         Windows - CreateFile
//         Linux   - open

//      : Unix/Linux - System call
//        Windows    - Windows API

#include <stdio.h>
// FILE*
// 1. stdin  -> keyboard(0): <
// 2. stdout -> monitor(1): >
// 3. stderr -> monitor(2): 2>

#if 0
int main() {
	fclose(stdout);

	printf("Hello, world..\n");
	fprintf(stdout, "Hello, world..\n"); 
}
#endif

// FILE
//  => 열린 파일의 정보를 가지고 있다.
//   : File Descriptor
//  => 버퍼링을 한다.
//   : printf -> fprintf(stdout, ...) -> write
//          User Process                 Kernel
//   - User mode 에서는 커널 영역에 일반적으로 접근할 수 없다.
//   - User mode 에서 커널 모드로 접근하기 위해서는, Context Switching이
//     필요하다.
//     : Trap
//   - 버퍼링을 하는 이유는 User mode와Kernel mode의 문맥 교환을 자주 
//     일어나지 않도록 하기 위해서..

// 버퍼링 정책
//   1. 풀 버퍼링 - 버퍼가 가득차면, 비운다.
//     => 일반 파일
//   2. 라인 버퍼링 - 엔터('\n')가 나오거나, 버퍼가 가득차면 비운다.또 같은 프로그램에서 출력 모드에서 입력모드로 변경될때 fflush()가 작용해 출력된다. 
//     => stdout, stdin
//   3. 노 버퍼링  - 버퍼링을 하지 않는다.
//     => stderr

//   버퍼를 비우는 표준 라이브러리 함수
//    : fflush, fclose
//    -> 프로세스가 종료하면, 프로세스가 연 파일을 스스로 정리한다.

#include <unistd.h>

int main() {
	 FILE* fp = fopen("a.txt", "w");
	 printf("hello");
	 fprintf(fp ,"hello");

	sleep(3);
}



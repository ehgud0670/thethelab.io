// 시그널
//  : 프로세스간에 주고받을 수 있는 IPC 방법 중 하나이다.


//SIGSEV
// 세그멘테이션 오류(허가되지 않은 메모리 영역)발생했다고 보내는 신호 

//SIGFPE
// 부동 소수점 에러 (Floating-Pointe Exception)발생했다고 보내는 신호

//SIGINT :터미널 인터럽트 신호 (Ctrl-C)
/*
The SIGINT signal is sent to a process by its controlling terminal when a user wishes to interrupt the process. This is typically initiated by pressing Ctrl+C, but on some systems, the "delete" character or "break" key can be used.
*/

//SIGKILL
// 
// 명령어1: kill
// 명령어2: killall

//SIGSTOP
//지정한 프로세스를 정지하게 하는 시그널 

//SIGCHID (sigchild)
// 프로그램 종료시 자식 프로세스가 자신의 부모 프로세스에게 보내는 시그널

/* SIGKILL 과 SIGSTOP */
// =>  이 시그널들은 절대로 재정의할 수 없다. 
// 이외의 다른 시그널들을 재정의 가능하다. 

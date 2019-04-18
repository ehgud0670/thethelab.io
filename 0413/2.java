// 자바가 제공하는 접근 제한자.
//  - 필드
//    private, package-private, protected, public

//  - 모듈
//    private internal protected public

package io.thethelab.hello;

class User {
    protected int age;
}

class Program {
    public static void main(String[] args) {
        User user = new User();
        user.age = 100;
    }
}


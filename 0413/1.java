// Annotation: 주석
// Comment: 주석

// Comment는 코드와 연관성이 존재하지 않는다.
// 코드가 변경되더라도, Comment가 변경되지 않아도 된다. - X
//  => Annotation
//     Compile, Run

// Annotation을 이용해서 코드를 좀 더 '선언적'으로 표현할 수 있도록 해준다.
// => AOP(관점 지향 프로그래밍)

// Spring Framework


// * 빌더 패턴
// 객체 생성의 공정은 동일하지만, 다른 표현을 가지는 객체를 생성할 때, 사용하는 패턴
// 단점
//  1. 빌더를 사용하기 위해서 반복적으로 발생하는 코드가 있다.
//  2. 객체를 생성하기 위해서 별도의 객체가 또 필요하다.

// 활용
//  1. 생성자의 인자가 많은 경우 빌더를 사용하면 좋다. - Effective Java
//  2. 객체를 불변으로 생성할 경우, 빌더가 좋다.
//    String, StringBuilder

// 불변 객체
//  장점
//  1) 동일한 내용의 객체를 공유할 수 있다.
//    => Flyweight Pattern
//  2) 동일한 내용의 경우 공유할 수 있으므로,
//     객체를 비교할 때, == 연산을 통해 비교할 수 있다.
//      == : 참조 동등성 판단
//   equals: 객체 동등성 판단

// 자바
//   1. Primitive Type
//    byte, int, short, double, char ...

//   2. Reference Type
//    class, interface, enum, array


import java.util.Arrays;

class Program {
    public static void main(String[] args) {
        // deepEquals는 배열이 배열을 가지고 있는 경우.
        Integer[][] arr1 = {{10}, {20}};
        Integer[][] arr2 = {{10}, {20}};

        System.out.println((arr1 == arr2) ? "Same" : "Diff");
        System.out.println(Arrays.equals(arr1, arr2) ? "Same" : "Diff");
        System.out.println(Arrays.deepEquals(arr1, arr2) ? "Same" : "Diff");


//        String s1 = new String("hello");
//        String s2 = new String("hello");
//        String s1 = String.valueOf("hello");
//        String s2 = String.valueOf("hello");
//
//        if (s1 == s2) {
//            System.out.println("same");
//        } else {
//            System.out.println("diff");
//        }
    }
}


/*
import org.junit.jupiter.api.Test;

class Program {
    @Test
    void foo1() {
        String s = "";
        for (int i = 0; i < 1000000; ++i) {
            s += i;
        }
    }

    @Test
    void foo2() {
        StringBuilder s = new StringBuilder("");
        for (int i = 0; i < 1000000; ++i) {
            s.append(i);
        }

        String str = s.toString();
    }


    public static void main(String[] args) {
        String s = "hello";
        String s1 = s.replace("h", "x");

        s = null;

        // System.out.println(s);
        // System.out.println(s1);
    }
}
*/

/*
class User {
    private final String name;
    private final int age;

    private String address;
    private int level;
    private int money;

    User(Builder builder) {
        this.name = builder.name;
        this.age = builder.age;
        this.address = builder.address;
        this.level = builder.level;
        this.money = builder.money;
    }

    static class Builder {
        private String name;
        private int age;

        private String address;
        private int level;
        private int money;

        Builder(String name, int age) {
            this.name = name;
            this.age = age;
        }

        Builder address(String address) {
            this.address = address;
            return this;
        }

        Builder level(int level) {
            this.level = level;
        }

        Builder money(int money) {
            this.money = money;
            return this;
        }

        User build() {
            return new User(this);
        }
    }
}

class Program {
    public static void main(String[] args) {
        User.Builder builder = new User.Builder("Tom", 42);
        builder.address("Suwon");
        builder.level(42);
        builder.money(1000);

        User user = builder.build();

        // 메소드 체인 호출 - 자기 자신의 참조를 반환하면 된다.
        User user2 = new User.Builder("Tom", 42)
                .address("Suwon")
                .level(42)
                .money(1000)
                .build();


    }
}
*/

/*
// Java beans Pattern - X
class User {
    private String name;
    private int age;

    private String address;
    private int level;
    private int money;

    public User() {}

    public void setName(String name) {
        this.name = name;
    }

    public void setAge(int age) {
        this.age = age;
		}
}
/*

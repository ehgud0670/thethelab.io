package io.thethelab.hello;

// Vector, Hashtable, StringBuffer
//  => 동기화 되어 있어서, 여러 개의 스레드가 사용해도 안전하게 사용할 수 있다.

// 결론
//  => 동기화가 필요하지 않음에도 불구하고, 동기화를 수행하므로, 불필요한 성능의 저하가 있다.
//  => 동기화의 정책을 라이브러리가 결정하는 것이 아니라, 사용자가 결정해야 한다.

import java.io.*;
import java.util.*;

// Concurrent Modification Exception
// : 컬렉션을 순회하는 도중에 다른 스레드가 해당 컬렉션을 수정하면 발생할 수 있다.


```java
class Program {
    public static void main(String[] args) {
        List<String> arr = new ArrayList<>();
        arr.add("hello");
        arr.add("world");

        // 1. 동기화
        Object mutex = new Object();

        // List<String> arr = Arrays.asList("hello", "world");
        Thread thread = new Thread(new Runnable() {
            @Override
            public void run() {
                for (int i = 0; i < 10000; ++i) {
                    synchronized (mutex) {
                        arr.add("hello");
                    }

                    try {
                        Thread.sleep(100);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        });
        thread.start();


        for (int i = 0; i < 10000; ++i) {
            for (String e : arr) {
                synchronized (mutex) {
                    System.out.println(e);
                }
            }
        }

    }
}
```

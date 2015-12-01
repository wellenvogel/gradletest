package de.wellenvogel.gtest.main;

/**
 * Created by andreas on 01.12.15.
 */
public class GTestMain {
    public static void main(String args[]){
        for (String k:System.getenv().keySet()){
            System.out.println("ENV: "+k+"="+System.getenv(k));
        }
        for (Object k: System.getProperties().keySet()){
            System.out.println("PROP: "+k+"="+System.getProperty((String)k));
        }
    }
}

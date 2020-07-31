package test.recursivetest;

import org.junit.internal.runners.statements.Fail;
import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.junit.runner.notification.Failure;

public class TestRunner {
  public static void main(String[] args){
    Result result = JUnitCore.runClasses(EditDistanceTest.class);
    for(Failure f: result.getFailures()){
      System.out.println(f.getMessage());
    }
    System.out.println("Successful: " + result.wasSuccessful() + " ran " + result.getRunCount() + " tests");
  }

}

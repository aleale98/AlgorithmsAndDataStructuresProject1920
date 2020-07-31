package test.dynamictest;

import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.junit.runner.notification.Failure;
import test.recursivetest.EditDistanceTest;

public class TestRunnerD {
  public static void main(String[] args){
    Result result = JUnitCore.runClasses(DynamicEditDistanceTest.class);
    for(Failure f: result.getFailures()){
      System.out.println(f.getMessage());
    }
    System.out.println("Successful: " + result.wasSuccessful() + " ran " + result.getRunCount() + " tests");
  }
}

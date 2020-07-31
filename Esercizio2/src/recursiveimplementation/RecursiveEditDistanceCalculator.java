package recursiveimplementation;

import interfaces.Calculator;

import javax.swing.*;

public class RecursiveEditDistanceCalculator implements Calculator {

  private String rest(String s) {
    return s.substring(1);
  }

  public int recursiveEditDistance(String s1, String s2) {
    try{
      if (s1.length() == 0) {
        return s2.length();
      } else if (s2.length() == 0) {
        return s1.length();
      } else {
        if (s1.charAt(0) == s2.charAt(0)) {
          return 0 + recursiveEditDistance(rest(s1), rest(s2));
        } else {
          return Math.min((1 + recursiveEditDistance(s1, rest(s2))),
              1 + recursiveEditDistance(rest(s1), s2));
        }
      }
    }catch (NullPointerException exception){
      JOptionPane.showMessageDialog(null, "Error, null strings cannot be checked");
      return -1;
    }
  }
}

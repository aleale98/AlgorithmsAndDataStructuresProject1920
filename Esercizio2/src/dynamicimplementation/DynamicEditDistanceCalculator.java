package dynamicimplementation;

import interfaces.Calculator;

public class DynamicEditDistanceCalculator implements Calculator {
  
  private int[][] editTable;

  public DynamicEditDistanceCalculator(int row, int col) {
    editTable = initTable(row, col);
  }

  public static int[][] initTable(int row, int col){
    int[][] editTable = new int[row][col];
    for(int i = 0; i < row; i++){
      for(int j = 0; j < col; j++){
        editTable[i][j] = -1;
      }
    }
    return editTable;
  }

  public void setEditTable(int row, int col){
    this.editTable = initTable(row, col);
  }

  public int editDistanceDyn(String s1, String s2, int i, int j){
    if(i==0){
      return j;
    }else if(j == 0){
      return i;
    }else{
      if(editTable[i-1][j-1] != -1){
        return editTable[i-1][j-1];
      }
      if(s1.charAt(i-1) == s2.charAt(j-1)){
        return editDistanceDyn(s1, s2, i-1, j-1);
      }else{
        return editTable[i-1][j-1] = 1+ Math.min(editDistanceDyn(s1, s2, i, j-1), //insert
            editDistanceDyn(s1, s2, i-1, j));
      }
    }
  }
}

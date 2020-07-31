import app.EditDistanceHandler;
import dynamicimplementation.DynamicEditDistanceCalculator;
import filereader.Reader;
import recursiveimplementation.RecursiveEditDistanceCalculator;

import java.io.File;
import java.net.URL;
import java.util.List;

public class Main {

  public static void main(String[] args) {
    //RecursiveEditDistanceCalculator r = new RecursiveEditDistanceCalculator();
    DynamicEditDistanceCalculator d = new DynamicEditDistanceCalculator(0, 0);
    EditDistanceHandler handler = null;
    List<String> dictionary = Reader.readDocument("src/files/dictionary.txt");
    List<String> correctme = Reader.readDocument("src/files/correctme.txt");
    correctme = Reader.splitStringIntoWords(correctme.get(0));
    handler = new EditDistanceHandler();
    long start = System.nanoTime();
    for(int j = 0; j < correctme.size(); j++){
      for(int i = 0; i < dictionary.size(); i++){
        d.setEditTable(correctme.get(j).length(), dictionary.get(i).length());
        handler.addItem(dictionary.get(i), d.editDistanceDyn(correctme.get(j), dictionary.get(i),
            correctme.get(j).length(), dictionary.get(i).length()));
        //handler.addItem(dictionary.get(i), r.recursiveEditDistance(dictionary.get(i), correctme.get(j)));
      }
      int min = handler.getMinDistance();
      List<String> s = handler.getKeysByValue(min);
      System.out.println("Word: "+correctme.get(j));
      System.out.print("Possible corrections: ");
      for(String str: s){
        System.out.print(str + " ");
      }
      System.out.println();
      handler = new EditDistanceHandler();
    }
    System.out.println("Elapsed time: "+ ((System.nanoTime() - start)/1000000000));
  }
}

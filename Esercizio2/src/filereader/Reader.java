package filereader;

import javax.swing.*;
import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Reader {
  public static List<String> readDocument(String path){
    List<String> dictionaryWords = null;
    try {
      dictionaryWords = new ArrayList<>();
      BufferedReader br = new BufferedReader(new FileReader(new File(path)));
      String st = "";
      while(((st = br.readLine())) != null){
        dictionaryWords.add(st);
      }
    } catch (FileNotFoundException e) {
      JOptionPane.showMessageDialog(null,"Sorry, wrong path. Cannot find the file. Ending execution :(");
      return null;
    } catch (IOException e) {
      e.printStackTrace();
    }
    return dictionaryWords;
  }
  /*
  * Qui passo tutte le stringhe. Forse potrebbe esserci un modo migliore
  * */
  public static List<String> splitStringIntoWords(String sentence){
    List<String> words = Arrays.asList(sentence.split(" "));
    for(int i = 0; i < words.size(); i++){
      words.set(i, words.get(i).replaceAll("\\p{Punct}", ""));
    }
    return words;
  }
}

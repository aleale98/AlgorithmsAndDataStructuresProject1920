import graph.*;
import substitutioncheck.SubstitutionChecker;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class Main {

  public static void main(String[] args) {
    List<Vertex> v = new ArrayList<>();
    List<Edge> e = new ArrayList<>();
    Graph g = new Graph();
    try {
      BufferedReader br = new BufferedReader(new FileReader(new File(args[0])));
      FileWriter out = new FileWriter(args[1], false);
      BufferedWriter writer = new BufferedWriter(out);
      int nodesNumber = Integer.parseInt(br.readLine());
      for (int i = 1; i <= nodesNumber; i++) {
        Vertex tmp = new Vertex(i);
        v.add(tmp);
        g.addVertex(tmp);
      }
      for (int i = 0; i < nodesNumber - 1; i++) {
        String[] tmpEdge = br.readLine().split(" ");
        Edge tmp = new Edge(v.get(Integer.parseInt(tmpEdge[0]) - 1), v.get(Integer.parseInt(tmpEdge[1]) - 1),
            Integer.parseInt(tmpEdge[2]));
        e.add(tmp);
        g.addEdge(tmp);
      }
      int query = Integer.parseInt(br.readLine());
      SubstitutionChecker checker = new SubstitutionChecker(g);
      for (int i = 0; i < query; i++) {
        String[] tmpEdge = br.readLine().split(" ");
        Edge tmp = new Edge(v.get(Integer.parseInt(tmpEdge[0]) - 1), v.get(Integer.parseInt(tmpEdge[1]) - 1),
            Integer.parseInt(tmpEdge[2]));
        writer.flush();
        writer.write(checker.checkWithBFS(tmp)+"\n");
      }

      writer.close();
      br.close();
    } catch (FileNotFoundException fileNotFoundException) {
      fileNotFoundException.printStackTrace();
    } catch (IOException ioException) {
      ioException.printStackTrace();
    }
  }
}

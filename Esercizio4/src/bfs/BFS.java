package bfs;

import graph.Colors;
import graph.Edge;
import graph.Graph;
import graph.Vertex;

import java.util.LinkedList;
import java.util.Map;
import java.util.Queue;

public class BFS {
  public static void BFS(Graph g, Vertex s) {
    Queue<Vertex> q = new LinkedList<>();
    s.setColor(Colors.GRAY);
    s.setLevel(0);
    q.add(s);
    while (!q.isEmpty()) {
      Vertex u = q.peek();
      u.setColor(Colors.BLACK);
      q.remove();
      Map<Vertex, Edge> a = u.getAdj();
      for (Map.Entry<Vertex, Edge> entry : a.entrySet()) {
        if (entry.getKey().getColor() == Colors.WHITE) {
          entry.getKey().setLevel(u.getLevel() + 1);
          entry.getKey().setColor(Colors.GRAY);
          q.add(entry.getKey());
          entry.getKey().setParent(u);
        }
      }
    }
  }
}

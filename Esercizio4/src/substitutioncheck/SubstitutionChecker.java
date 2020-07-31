package substitutioncheck;

import bfs.BFS;
import graph.Edge;
import graph.Graph;
import graph.Vertex;

import java.util.ArrayList;
import java.util.List;

public class SubstitutionChecker {
  private static Graph g;
  private List<Edge> path;


  public SubstitutionChecker(Graph g) {
    this.g = g;
    BFS.BFS(g, g.getFirst());
    path = new ArrayList<>();
  }

  private boolean isAncestor(Vertex end, Vertex start, Edge e) {
    Vertex v1 = end;
    Vertex v2 = start;
    path.clear();
    while(v2.getParent() != null && !v1.equals(v2)){
      Edge tmp = g.getEdgeGivenVertexes(v2, v2.getParent());
      if(tmp != null && tmp.getWeight() > e.getWeight()){
        path.add(tmp);
      }
      v2 = v2.getParent();
    }
    return v1.equals(v2);
  }

  public String checkWithBFS(Edge e) {
    Vertex start = null;
    Vertex end = null;
    if (e.getV1().getLevel() >= e.getV2().getLevel()) {
      start = e.getV1();
      end = e.getV2();
    } else if (e.getV1().getLevel() < e.getV2().getLevel()) {
      start = e.getV2();
      end = e.getV1();
    }
    if(isAncestor(end, start, e)) {
      return path.size() > 0 ? "YES" : "NO";
    } else {
      while (start.getLevel() > end.getLevel()) {
        if (g.getEdgeGivenVertexes(start, start.getParent()).getWeight() > e.getWeight()) {
          return "YES";
        }
        start = start.getParent();
      }
      while (!start.getParent().equals(end.getParent())) {
        if (g.getEdgeGivenVertexes(start, start.getParent()).getWeight() > e.getWeight()
            || g.getEdgeGivenVertexes(end, end.getParent()).getWeight() > e.getWeight()) {
          return "YES";
        }
        start = start.getParent();
        end = end.getParent();
      }
      if (g.getEdgeGivenVertexes(start, start.getParent()).getWeight() > e.getWeight()
          || g.getEdgeGivenVertexes(end, end.getParent()).getWeight() > e.getWeight()) {
        return "YES";
      }
      return "NO";
    }
  }
}

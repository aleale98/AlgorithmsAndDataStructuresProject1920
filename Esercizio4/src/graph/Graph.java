package graph;

import java.util.ArrayList;
import java.util.List;

public class Graph implements Cloneable {

  private List<Vertex> vertexes;
  private List<Edge> edges;

  public Graph() {
    vertexes = new ArrayList<>();
    edges = new ArrayList<>();
  }

  public void addVertex(Vertex v) {
    vertexes.add(v);
  }

  public void addEdge(Edge e) {
    edges.add(e);
    e.getV1().addAdjacent(e.getV2());
    e.getV1().addEdgeToAdj(e.getV2(), e);
    e.getV2().addAdjacent(e.getV1());
    e.getV2().addEdgeToAdj(e.getV1(), e);
  }

  public Vertex getFirst() {
    return vertexes.get(0);
  }

  public Edge getEdgeGivenVertexes(Vertex v1, Vertex v2) {
    if (v1.getAdj() != null && v1.getAdj().size() > 0)
      return v1.getAdj().get(v2);
    else
      return null;
  }
}

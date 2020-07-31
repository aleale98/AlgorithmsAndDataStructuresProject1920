package graph;

import java.util.Objects;

public class Edge implements Comparable<Edge> {
  private Vertex v1;
  private Vertex v2;
  private int weight;

  public Edge(Vertex v1, Vertex v2, int weight) {
    this.v1 = v1;
    this.v2 = v2;
    this.weight = weight;
  }

  public Vertex getV1() {
    return v1;
  }

  public Vertex getV2() {
    return v2;
  }

  public int getWeight() {
    return weight;
  }

  @Override
  public boolean equals(Object o) {
    if (this == o) return true;
    if (!(o instanceof Edge)) return false;
    Edge edge = (Edge) o;
    return getWeight() == edge.getWeight() &&
        getV1().equals(edge.getV1()) &&
        getV2().equals(edge.getV2());
  }

  @Override
  public int hashCode() {
    return Objects.hash(getV1(), getV2(), getWeight());
  }

  @Override
  public String toString() {
    return "Edge{" +
        "v1=" + v1.getName() +
        ", v2=" + v2.getName() +
        ", weight=" + weight +
        '}';
  }

  @Override
  public int compareTo(Edge o) {
    return getWeight() - o.getWeight();
  }
}

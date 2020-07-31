package graph;

import java.util.HashMap;
import java.util.Map;

public class Vertex implements Comparable<Vertex> {
  private int name;
  private Colors color;
  private Map<Vertex, Edge> adj;
  private Vertex parent;
  private int open;
  private int close;
  private int level;

  public Vertex(int name) {
    this.name = name;
    color = Colors.WHITE;
    adj = new HashMap<>();
    parent = null;

  }

  public Colors getColor() {
    return color;
  }

  public void setColor(Colors color) {
    this.color = color;
  }

  public int getName() {
    return name;
  }

  public int getClose() {
    return close;
  }

  public Map<Vertex, Edge> getAdj() {
    return adj;
  }

  public Vertex getParent() {
    return parent;
  }

  public void setParent(Vertex parent) {
    this.parent = parent;
  }

  public void addAdjacent(Vertex v) {
    if (!(adj.containsKey(v))) {
      adj.put(v, null);
    }
  }

  public int getLevel() {
    return level;
  }

  public void setLevel(int level) {
    this.level = level;
  }

  public void addEdgeToAdj(Vertex v, Edge e) {
    adj.replace(v, e);
  }

  @Override
  public String toString() {
    String s = "Vertex{" +
        " name=" + name +
        "parent= ";
    if (parent != null) {
      s += parent.getName();
    } else {
      s += "null";
    }
    s += " level " + getLevel() + " }";
    return s;
  }

  @Override
  public int compareTo(Vertex o) {
    return (getClose() - o.getClose());
  }
}

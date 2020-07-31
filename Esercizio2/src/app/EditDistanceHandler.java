package app;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class EditDistanceHandler {

    private HashMap<String, Integer> distances;

    public EditDistanceHandler() {
        distances = new HashMap<>();
    }

    public int getMinDistance() {
        return Collections.min(distances.values());
    }

    public void addItem(String s, int d) {
        distances.put(s, d);
    }

    public List<String> getKeysByValue(int d) {
        List<String> words = null;
        if (distances.containsValue(d)) {
            words = new ArrayList<>();
            for (Map.Entry<String, Integer> entry : distances.entrySet()) {
                if (entry.getValue() == d) {
                    words.add(entry.getKey());
                }
            }
        }
        return words;
    }
}

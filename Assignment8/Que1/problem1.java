import java.util.*;
import java.io.*;
import java.lang.*;
import org.jgrapht.Graph;
import org.jgrapht.graph.*;
import org.jgrapht.alg.shortestpath.*;
import org.jgrapht.alg.scoring.*;
import org.jgrapht.alg.interfaces.*;
import org.jgrapht.io.*;
import org.jgrapht.traverse.*;
import java.text.DecimalFormat;
class problem1 
{
    static final int V = 9; 
    static final int INF = Integer.MAX_VALUE;
    int minDistance(int distance[], Boolean spt[]) 
    { 
        int minimum=Integer.MAX_VALUE, smallest_index = -1; 
  
        for (int v = 0; v < V; v++) 
            if (spt[v] == false && distance[v] <= minimum) { 
                minimum = distance[v]; 
                smallest_index = v; 
            } 
  
        return smallest_index; 
    } 
   
    void printSolution(int distance[]) 
    { 
        System.out.println("Vertex \t\t Distance from Source"); 
        for (int i = 0; i < V; i++) 
            System.out.println(i + " \t\t " + distance[i]); 
    } 
    void dijkstra(int graph[][], int src) 
    { 
        int distance[] = new int[V]; 
        Boolean spt[] = new Boolean[V]; 
        for (int i = 0; i < V; i++) { 
            distance[i] = Integer.MAX_VALUE; 
            spt[i] = false; 
        } 
        distance[src] = 0; 
  
        for (int count = 0; count < V - 1; count++) { 
            int u = minDistance(distance, spt); 
 
            spt[u] = true; 
            for (int v = 0; v < V; v++) 
                if (!spt[v] && graph[u][v] != 0 && distance[u] != Integer.MAX_VALUE && distance[u] + graph[u][v] < distance[v]) 
                    distance[v] = distance[u] + graph[u][v]; 
        } 
  
        printSolution(distance); 
    }
    int shortestPath(int graph[][], int u, int v, int k) 
    { 
     	if (k == 0 && u == v)             return 0; 
        if (k == 1 && graph[u][v] != INF) return graph[u][v]; 
        if (k <= 0)                       return INF; 
  
        int res = INF; 
  
        for (int i = 0; i < V; i++) 
        { 
            if (graph[u][i] != INF && u != i && v != i) 
            { 
                int rec_res = shortestPath(graph, i, v, k-1); 
                if (rec_res != INF) 
                    res = Math.min(res, graph[u][i] + rec_res); 
            } 
        } 
        return res; 
    }
    private static DecimalFormat dcmfrmt = new DecimalFormat("#.#####");
	public static void main (String[] args) throws ImportException
	{
		Graph <String, DefaultWeightedEdge> g = new WeightedPseudograph<>(DefaultWeightedEdge.class);
		GmlImporter<String, DefaultWeightedEdge> importer = new GmlImporter<>((l, a) -> l, (f, t, l, a) -> g.getEdgeSupplier().get());
		importer.importGraph(g, new File("L8P1_T1.gml"));
		VertexScoringAlgorithm<String, Double> bc = new BetweennessCentrality<>(g);
		Map<String, Double> scores = bc.getScores();
		Set< Map.Entry<String, Double> > st = scores.entrySet();
		System.out.print("\t w:");
		System.out.println("BC(w)");
		for (Map.Entry< String, Double> me:st) 
       		{ 
           	System.out.print("BC for \tV"+me.getKey()+":"); 
           	System.out.println(dcmfrmt.format(me.getValue())); 
       		} 
	}
}

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.StringTokenizer;

public class Curse {
	public static final String inputFile = "curse.in";
	public static final String outputFile = "curse.out";

	static class MyScanner {
		BufferedReader br;
		StringTokenizer st;

		public MyScanner() {
			try {
				br = new BufferedReader(new FileReader(inputFile));
			} catch (FileNotFoundException e) {
				e.printStackTrace();
			}
		}

		String next() {
			while (st == null || !st.hasMoreElements()) {
				try {
					st = new StringTokenizer(br.readLine());
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
			return st.nextToken();
		}

		int nextInt() {
			return Integer.parseInt(next());
		}
	}

	@SuppressWarnings("unchecked")
	public static ArrayList<Integer>[] adj = new ArrayList[10001];

	private static ArrayList<Integer> solveDfs(int n) {
		// vectorul rezultat (in final contine o permutare pentru 1, 2, ... n)
		ArrayList<Integer> topsort = new ArrayList<>();

		boolean[] used = new boolean[n + 1];

		// pentru fiecare nod
		for (int node = 1; node <= n; node++) {
			// daca nodul nu a fost vizitat, pornim o parcurgere DFS
			if (!used[node]) {
				dfs(node, used, topsort);
			}
		}

		// rezultatul a fost obtinut in ordine inversa
		Collections.reverse(topsort);

		return topsort;
	}

	// porneste o parcurgere DFS din node
	// foloseste vectorul used pentru a marca nodurile vizitate
	static void dfs(int node, boolean[] used, ArrayList<Integer> topsort) {
		used[node] = true;

		for (Integer neigh : adj[node]) {
			if (!used[neigh]) {
				dfs(neigh, used, topsort);
			}
		}

		// dupa ce am terminat de vizitat nodul, adaugam nodul in sortarea topologica
		topsort.add(node);
	}

	public static void main(String[] args) {

		MyScanner sc = new MyScanner();

		int n = sc.nextInt();
		int m = sc.nextInt();
		int a = sc.nextInt();

		int[][] mat = new int[a][n];

		for (int i = 0; i < a; i++) {
			for (int j = 0; j < n; j++) {
				mat[i][j] = sc.nextInt();
			}
		}

		for (int i = 1; i <= m; i++) {
			adj[i] = new ArrayList<>();
		}

		// Creez adj
		// Un nod x are muchie catre un nod y
		// Daca masina x este cu siguranta mai
		// rapida ca masina y.
		for (int i = 1; i < a; i++) {
			for (int j = 0; j < n; j++) {
				if (mat[i - 1][j] != mat[i][j]) {
					adj[mat[i - 1][j]].add(mat[i][j]);
					break;
				}
			}
		}

		// Apelez sortare topologica dfs
		ArrayList<Integer> res = solveDfs(m);

		try {
			PrintWriter pw = new PrintWriter(outputFile);
			for (Integer i : res) {
				pw.printf("%d ", i);
			}
			pw.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}

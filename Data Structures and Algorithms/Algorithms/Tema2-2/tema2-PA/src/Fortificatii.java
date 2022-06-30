import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class Fortificatii {

	public static final String inputFile = "fortificatii.in";
	public static final String outputFile = "fortificatii.out";

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

	static class Task {

		// numarul maxim de noduri
		public static final int NMAX = 100001;

		// valoare mai mare decat orice distanta din graf
		public static final int INF = (int) 1e9;

		int n, m, k, b;
		ArrayList<Integer> barbari = new ArrayList<>();

		// Tip de date pentru algoritmul dijkstra
		// Cu array-urile pentru distante respectiv parinti.
		public static class DijkstraResult {
			public List<Integer> d;
			public List<Integer> p;

			public DijkstraResult(List<Integer> d, List<Integer> p) {
				this.d = d;
				this.p = p;
			}
		}

		// Tip de date pair, de tipul (x,y) unde x - destinatie
		// si y cost
		public static class Pair implements Comparable<Pair> {
			public int destination;
			public int cost;

			Pair(int _destination, int _cost) {
				destination = _destination;
				cost = _cost;
			}

			public int compareTo(Pair rhs) {
				return Integer.compare(cost, rhs.cost);
			}
		}

		// adj[node] = lista de adiacenta a nodului node
		// perechea (neigh, w) semnifica arc de la node la neigh de cost w
		@SuppressWarnings("unchecked")
		ArrayList<Pair>[] adj = new ArrayList[NMAX];

		private void readInput() {

			MyScanner sc = new MyScanner();
			n = sc.nextInt();
			m = sc.nextInt();
			k = sc.nextInt();
			b = sc.nextInt();
			for (int i = 0; i < b; i++) {
				barbari.add(sc.nextInt());
			}

			for (int i = 1; i <= n; i++) {
				adj[i] = new ArrayList<>();
			}

			for (int i = 1; i <= m; i++) {
				int x, y, w;
				x = sc.nextInt();
				y = sc.nextInt();
				w = sc.nextInt();
				adj[x].add(new Pair(y, w));
				adj[y].add(new Pair(x, w));
			}

		}


		private DijkstraResult dijkstra(int nodes, ArrayList<Pair>[] adj) {
			List<Integer> d = new ArrayList<>();
			List<Integer> p = new ArrayList<>();

			// Initializam distantele la infinit
			for (int node = 0; node <= nodes; node++) {
				d.add(INF);
				p.add(0);
			}

			// Folosim un priority queue de Pair, desi elementele noastre nu sunt tocmai
			// muchii.
			// Vom folosi field-ul de cost ca si distanta pana la nodul respectiv.
			// Observati ca am modificat clasa Pair ca sa implementeze interfata Comparable.
			PriorityQueue<Pair> pq = new PriorityQueue<>();

			// Inseram nodul de plecare in pq si ii setam distanta la 0.
			d.set(1, 0);
			pq.add(new Pair(1, 0));

			// Cat timp inca avem noduri de procesat
			while (!pq.isEmpty()) {
				// Scoatem head-ul cozii
				int cost = pq.peek().cost;
				int node = pq.poll().destination;

				// In cazul in care un nod e introdus in coada cu mai multe distante (pentru ca
				// distanta pana la el se imbunatateste in timp), vrem sa procesam doar
				// versiunea sa cu distanta minima. Astfel, dam discard la intrarile din coada
				// care nu au distanta optima.
				if (cost > d.get(node)) {
					continue;
				}

				// Ii parcurgem toti vecinii.
				for (var e : adj[node]) {
					int neigh = e.destination;
					int w = e.cost;

					// Se imbunatateste distanta?
					if (d.get(node) + w < d.get(neigh) && !barbari.contains(node)) {
						// Actualizam distanta si parintele.
						d.set(neigh, d.get(node) + w);
						p.set(neigh, node);
						pq.add(new Pair(neigh, d.get(neigh)));
					}
				}
			}

			// Toate nodurile ce au distanta INF nu pot fi atinse din sursa, asa ca setam
			// distantele
			// pe -1.
			for (int i = 1; i <= n; i++) {
				if (d.get(i) == INF) {
					d.set(i, -1);
				}
			}

			return new DijkstraResult(d, p);
		}

		public void solve() {

			readInput();
			DijkstraResult dij = dijkstra(n, adj);;
			ArrayList<Integer> costs = new ArrayList<>();
			// Un arrrayList cu costurile pana la un barbar, prin toti aliatii legati de barbari
			// (O sa am atatea elemenente cat noduri aliate conectate cu barbari)

			for (int i = 1; i < dij.d.size(); i++) {
				if (!barbari.contains(i) && dij.d.get(i) != -1) {
					for (Pair p : adj[i]) {
						if (barbari.contains(p.destination)) {
							costs.add(dij.d.get(i) + p.cost);
						}
					}
				}
			}

			Collections.sort(costs);

			int res = 0;
			while (k != 0) {
				int howMany = 1;
				for (int i = 0; i < costs.size(); i++) {

					// Trebuie sa incrementez atatea muchii cate fortificatii am.
					if (howMany == k) {
						if (i == costs.size() - 1 || costs.get(i + 1) > costs.get(i)) {
							res = costs.get(0) + 1;
							k = 0;
							break;
						}
						res = costs.get(0);
						k = 0;
						break;
					}

					// caz special in care am ajuns la ultimul element
					// (toate sunt egale, incep de la 0 si incrementez ultimul)
					if (i == costs.size() - 1) {
						costs.set(i, costs.get(i) + 1);
						k--;
						break;
					}

					// Trebuie sa incrementez "howMany" muchii, deoarece am ajuns
					// La un cost mai mare decat pana acum.
					if (costs.get(i + 1) > costs.get(i)) {

						// Nu am destule fortificatii cat sa incrementez toate muchiile cu
						// costul necesar, incrementez doar o parte din ele,
						// folosind toate fortificatiile.
						if (k < howMany * (costs.get(i + 1) - costs.get(i))) {
							res = costs.get(0) + (k / howMany);
							k = 0;
						} else {
							k -= howMany * (costs.get(i + 1) - costs.get(i));
							for (int j = 0; j < howMany; j++) {
								costs.set(j, costs.get(j) + (costs.get(i + 1) - costs.get(i)));
							}
						}
						break;
					}

					howMany++;
					res = costs.get(0);
				}
			}

			try {
				PrintWriter pw = new PrintWriter(outputFile);
				pw.printf("%d\n", res);
				pw.close();
			} catch (IOException e) {
				e.printStackTrace();
			}

		}
	}

	public static void main(String[] args) {
		new Task().solve();
	}
}
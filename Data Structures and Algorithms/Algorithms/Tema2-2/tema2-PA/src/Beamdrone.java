import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.StringTokenizer;

public class Beamdrone {

	public static final String inputFile = "beamdrone.in";
	public static final String outputFile = "beamdrone.out";

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

		String nextLine() {
			String str = "";
			try {
				str = br.readLine();
			} catch (IOException e) {
				e.printStackTrace();
			}
			return str;
		}
	}

	// Comparator pentru priorityQueue
	static class NodeComparator implements Comparator<Node> {

		@Override
		public int compare(Node o1, Node o2) {
			return (o1.dist - o2.dist);
		}
	}

	// Reprezinta un nod
	static class Node {
		// x,y reprezinta pozitia in matrice
		int x, y, dist;
		boolean vertically; // Cand am ajuns la acest nod, mergem pe verticala sau orizontala?

		Node(int x, int y, int dist, boolean vertically) {
			this.x = x;
			this.y = y;
			this.dist = dist;
			this.vertically = vertically;
		}

		@Override
		public boolean equals(Object obj) {
			return (this.x == ((Node)obj).x && this.y == ((Node)obj).y);
		}

	}

	// Miscarile posibile dintr-un nod (Sus, Stanga, Dreapta, Jos)
	private static final int[] row = { -1, 0, 0, 1 };
	private static final int[] col = { 0, -1, 1, 0 };


	// Functie care verifica daca am voie sa ma duc la nodul dat.
	// Verifica ca acesta sa nu fie un perete, sa fie in matrice, si sa nu mai fi fost
	// vizitat pana acum la un cost mai mare.
	private static boolean checkNode(char[][] traseu, boolean[][] visited, int row, int col,
										int dist, int[][] costs) {
		if ((row >= 0) && (row < traseu.length) && (col >= 0) && (col < traseu[0].length)
				&& traseu[row][col] != 'W' && visited[row][col] && dist < costs[row][col]) {
			visited[row][col] = false;
		}

		return (row >= 0) && (row < traseu.length) && (col >= 0) && (col < traseu[0].length)
				&& traseu[row][col] != 'W' && !visited[row][col];

	}

	// Cel mai scurt drum de la traseu[i][j] la traseu[x][y]
	// flag este prima directie a dronei (vertical sau orizontal)
	// Deci, vom apela aceasta functie de doua ori
	private static int shortestPath(char[][] traseu, int i, int j, int x, int y, boolean flag) {

		if (traseu == null || traseu.length == 0 || traseu[i][j] == 'W' || traseu[x][y] == 'W') {
			return -1;
		}

		int n = traseu.length;
		int m = traseu[0].length;

		// Construiesc doua matrici, una pentru a verifica daca am mai
		// Vizitat nodul, una cu costurile minime pana la fiecare nod.
		boolean[][] visited = new boolean[n][m];
		int[][] costs = new int[n][m];

		// Ne creem un priorityQueue in functie de costul nodurilor
		NodeComparator comparator = new NodeComparator();
		Queue<Node> q = new PriorityQueue<>(comparator);

		// Punem in queue nodul sursa
		visited[i][j] = true;
		costs[i][j] = 0;
		q.add(new Node(i, j, 0, flag));


		int min = Integer.MAX_VALUE;
		boolean switched = false;
		// True daca directia dronei se schimba (incrementam costul drumului)

		while (!q.isEmpty()) {
			Node node = q.poll();
			System.out.println("x: " + (node.x+1) + " y: " + (node.y+1) + " dist: " + node.dist);

			i = node.x;
			j = node.y;
			int dist = node.dist;


			// Am ajuns la destinatie.
			if (i == x && j == y) {
				min = dist;
				break;
			}

			// Verificam pentru doate cele 4 directii posibile
			for (int k = 0; k < 4; k++) { // Sus, Stanga, Dreapta, Jos
				// Preluam pozitia dronei cand am intrat in nodul curent
				// (mergea pe verticala sau pe orizontala)
				boolean vertically = node.vertically;

				if (checkNode(traseu, visited, i + row[k], j + col[k], dist, costs)) {
					// Putem sa mergem in urmatorul nod, il marcam ca vizitat
					visited[i + row[k]][j + col[k]] = true;

					// Vedem daca ne-am schimbat directia de mers
					// In cazul in care ne-am schimbat-o, distanta drumului pana la nod
					// va fi incrementata.
					if ((row[k] == 0) && vertically) { // Mergem vertical,
						// dar numarul randului nu se schimba, deci ne-am schimbat pe orizontala
						switched = true;
						vertically = false;
					}

					if ((row[k] != 0) && !vertically) { // Mergem orizontal,
						// dar numarul randului se schimba, deci ne-am schimbat pe verticala
						switched = true;
						vertically = true;
					}

					if (!switched) { // Daca ne-am schimbat directia de mers,
						// costul trebuie incrementat
						q.add(new Node(i + row[k], j + col[k], dist, vertically));
						costs[i + row[k]][j + col[k]] = dist;
					} else {
						q.add(new Node(i + row[k], j + col[k], dist + 1, vertically));
						costs[i + row[k]][j + col[k]] = dist + 1;
						switched = false;
					}

				}
			}
		}

		if (min != Integer.MAX_VALUE) {
			return min;
		}
		return -1;
	}

	public static void main(String[] args) {

		MyScanner sc = new MyScanner();
		int n = sc.nextInt();
		int m = sc.nextInt();
		int xi = sc.nextInt();
		int yi = sc.nextInt();
		int xf = sc.nextInt();
		int yf = sc.nextInt();

		char[][] traseu = new char[n][m];
		for (int i = 0; i < n; i++) {
			traseu[i] = sc.nextLine().toCharArray();
		}


		try {
			PrintWriter pw = new PrintWriter(outputFile);
			// Incep sa merg pe orizontala vs pe verticala.
			pw.printf("%d\n", Math.min(shortestPath(traseu, xi, yi, xf, yf, false),
					shortestPath(traseu, xi, yi, xf, yf, true)));
			pw.close();
		} catch (IOException e) {
			e.printStackTrace();
		}

	}
}

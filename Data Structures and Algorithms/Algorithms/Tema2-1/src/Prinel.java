import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;

public class Prinel {
	static class Task {
		public final String inputFile = "prinel.in";
		public final String outputFile = "prinel.out";

		int n;
		int k;
		Integer[] target;
		int[] p;


		public void solve() {
			readInput();

			target = new Integer[n];
			p = new int[n];

			PrintWriter pw;
			try {
				pw = new PrintWriter(outputFile);
			} catch (IOException e) {
				throw new RuntimeException(e);
			}

			BufferedReader br;
			try {
				FileReader f = new FileReader(inputFile);
				br = new BufferedReader(f);
			} catch (IOException e) {
				throw new RuntimeException(e);
			}

			try {
				br.readLine();
			} catch (IOException e) {
				e.printStackTrace();
			}

			for (int i = 0; i < 2; i++) {
				try {
					String[] line = br.readLine().split(" ");
					for (int j = 0; j < line.length; j++) {
						if (i == 0) {
							target[j] = Integer.parseInt(line[j]);
						} else {
							p[j] = Integer.parseInt(line[j]);
						}
					}
				} catch (IOException e) {
					e.printStackTrace();
				}
			}

			pw.printf("%d\n", getResult());

			try {
				br.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
			pw.close();
		}

		private void readInput() {
			try {
				FileReader f = new FileReader(inputFile);
				BufferedReader br = new BufferedReader(f);
				String[] line = br.readLine().split(" ");
				n = Integer.parseInt(line[0]);
				k = Integer.parseInt(line[1]);
				br.close();
			} catch (IOException e) {
				throw new RuntimeException(e);
			}
		}

		private int getResult() {

			// Incep prin a creea un vector care va
			// corespunde cu numarul de operatii necesare
			// pentru fiecare element din target
			int[] op = makeOperations();

			// De aici, problema seamana cu cea a rucsacului discret.
			// In loc de "greutate" (weight), avem un numar de operatii
			int[][] dp = new int[n + 1][k + 1];


			// cazul de bază
			for (int j = 0; j <= k; j++) {
				dp[0][j] = 0;
			}

			// cazul general
			for (int i = 1; i <= n; i++) {
				for (int j = 0; j <= k; j++) {

					// nu aleg target i deci e soluția de la pasul i - 1
					dp[i][j] = dp[i - 1][j];

					// aleg target i, deci trebuie sa scad op[target[i - 1]] operatii
					// inseamna ca inainte trebuie sa ocup maxim (j - op[target[i - 1]]) unități
					if (j - op[target[i - 1]] >= 0) {
						int aux = dp[i - 1][j - op[target[i - 1]]] + p[i - 1];

						dp[i][j] = Math.max(dp[i - 1][j], aux);
					}
				}
			}
			return dp[n][k];
		}

		// Algoritm de obtinere al vectorului de
		// operatii necesare fiecarui element
		private int[] makeOperations() {

			int max = Collections.max(Arrays.asList(target));
			int[] op = new int[max + 1];
			Arrays.fill(op, max);

			op[1] = 0;
			for (int i = 1; i <= max; i++) {
				ArrayList<Integer> divisors = getDivisors(i);

				// Sortam vectorul de divizori crescator
				Collections.sort(divisors);
				for (int j = 0; j < divisors.size(); j++) {
					int x = i + divisors.get(j);
					if (x <= max) {
						op[x] = Math.min(op[x], op[i] + 1);
					} else {
						break;
					}
				}
			}

			return op;
		}

		private ArrayList<Integer> getDivisors(int nr) {
			ArrayList<Integer> ar = new ArrayList<>();

			for (int i = 1; i <= Math.sqrt(nr); i++) {
				if (nr % i == 0) {
					ar.add(nr / i);
					if (nr / i != i) {
						ar.add(i);
					}
				}
			}

			return ar;
		}
	}


	public static void main(String[] args) {
		new Task().solve();
	}
}
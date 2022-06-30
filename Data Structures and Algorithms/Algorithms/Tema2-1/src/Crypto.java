import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;

public class Crypto {
	static class Task {
		public final String inputFile = "crypto.in";
		public final String outputFile = "crypto.out";

		int n;
		int l;
		String k;
		String s;

		public void solve() {
			readInput();

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
					String line = br.readLine();
					if (i == 0) {
						k = line;
					} else {
						s = line;
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
				l = Integer.parseInt(line[1]);
				br.close();
			} catch (IOException e) {
				throw new RuntimeException(e);
			}
		}


		private int getResult() {
			int[][] dp = new int[n + 1][l + 1];
			dp[0][0] = 1;

			int mod = 1000000007;
			for (int i = 0; i < n; ++i) {

				char c = k.charAt(i);
				for (int j = 1; j <= l; j++) {

					if (c == s.charAt(j - 1) || c == '?') {
						dp[i + 1][j] = (dp[i][j - 1] + dp[i + 1][j]) % mod;
					}
				}
				if (c == '?') {
					for (int j = 0; j <= l; j++) {
						dp[i + 1][j] = (int) (((long) dp[i][j] * (l - 1) + dp[i + 1][j]) % mod);
					}
				} else {
					for (int j = 0; j <= l; j++) {
						dp[i + 1][j] = (dp[i][j] + dp[i + 1][j]) % mod;
					}
				}

			}
			return (dp[n][l] % mod);
		}
		// in matrice - linii (n+1) numarul liniei este numarul de litere din cheie folosite
		// coloane (l+1) numarul coloanei este numarul de litere din s pentru care cautam
		// combinatii dp[x][y] cate combinatii pentru stringul format din primele y litere
		// din s gasim in primele x litere din k
	}


	public static void main(String[] args) {
		new Task().solve();
	}

}



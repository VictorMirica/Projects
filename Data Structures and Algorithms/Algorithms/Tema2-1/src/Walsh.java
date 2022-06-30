import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;

public class Walsh {
	static class Task {
		public final String inputFile = "walsh.in";
		public final String outputFile = "walsh.out";

		int n,k,x,y;

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

			for (int i = 0; i < k; i++) {
				String[] line = new String[0];
				try {
					line = br.readLine().split(" ");
				} catch (IOException e) {
					e.printStackTrace();
				}
				x = Integer.parseInt(line[0]);
				y = Integer.parseInt(line[1]);

				pw.printf("%d\n", getResult(n, x, y));
			}

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

		// Similar problemei Z Parcurgere
		// (x, y) in dreptunghiul [ (tlx, tly), (drx, dry) ]
		boolean in_rectangle(int x, int y, int tlx, int tly, int drx, int dry) {
			return (tlx <= x && x <= drx)
					&& (tly <= y && y <= dry);
		}

		int helper(int x, int y, int tlx, int tly, int n, int neg) {
			if (n == 1) {
				int ret = 0;
				if (neg % 2 == 1) {
					ret = 1;
				}
				return ret;
			}

			// down right
			int drx = tlx + n - 1;
			int dry = tly + n - 1;

			// middle
			int mx = (tlx + drx) >> 1;
			int my = (tly + dry) >> 1;

			// in care subdreptunghi se afla x, y?
			int new_n = (n >> 1);

			// 1: este in stanga-sus?

			if (in_rectangle(x, y, tlx, tly, mx, my)) {
				return helper(x, y, tlx, tly, new_n,  neg);
			}

			// 2: este in dreapta-sus?

			if (in_rectangle(x, y, tlx, my + 1, mx, dry)) {
				return helper(x, y, tlx, my + 1, new_n, neg);
			}


			// 3: este in stanga-jos?

			if (in_rectangle(x, y, mx + 1, tly, drx, my)) {
				return helper(x, y, mx + 1, tly, new_n, neg);
			}


			// 4: este in dreapta-jos?

			if (in_rectangle(x, y, mx + 1, my + 1, drx, dry)) {
				neg += 1;
				return helper(x, y, mx + 1, my + 1, new_n, neg);
			}

			return -1;
		}

		int solve_rec(int n, int x, int y) {
			int neg = 0;
			return helper(x, y, 1, 1, n, neg);
		}

		private int getResult(int n, int x, int y) {
			return solve_rec(n, x, y);
		}


	}


	public static void main(String[] args) {
		new Task().solve();
	}

}

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedHashSet;

public class Statistics {
	static class Task {
		public final String inputFile = "statistics.in";
		public final String outputFile = "statistics.out";

		int n;
		ArrayList<String> words = new ArrayList<>();
		ArrayList<Character> letters = new ArrayList<>();

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

			for (int i = 0; i < n; i++) {
				try {
					words.add(br.readLine());
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
				String line = br.readLine();
				n = Integer.parseInt(line);
				br.close();
			} catch (IOException e) {
				throw new RuntimeException(e);
			}
		}

		private int getResult() {

			StringBuilder str = new StringBuilder(words.get(0));

			// append all words
			for (String word: words) {
				str.append(word);
			}

			// O lista cu toate literele folosite
			letters = getLetters(str);

			// trec prin fiecare litera, concatenez doar cuvintele care verifica conditia
			// la final o sa intorc maxCount
			int maxCount = -1;


			// Voi crea un tabel de valori
			// fiecare cuvant va avea o valoare, litera cautata
			// va aduce +1 la valoare, celelalte -1.
			// spre exemplu daca am literele a b c si cuvantul aabc,
			// cand sunt la litera a, valoarea acestuia va fi 0.
			// alt exemplu: aaaab = 3;  bb = -2
			for (Character letter : letters) {

				// Creez tabela de valori respectiva fiecarui cuvant,
				// pentru litera la care ma aflu
				int count = 0;
				int totalValue = 0;
				ArrayList<Integer> values = makeValueTable(letter);

				// Sortez descrescator
				values.sort(Collections.reverseOrder());

				// Adaug valorile
				for (Integer val : values) {

					if (val > 0) {
						count++;
						totalValue += val;
					}

					if (val == 0 && totalValue > 0) {
						count++;
					}

					if (val < 0 && (totalValue + val) > 0) {
						count++;
						totalValue += val;
					}
				}

				if (count > maxCount) {
					maxCount = count;
				}
			}

			return maxCount;
		}

		private ArrayList<Integer> makeValueTable(Character c) {
			ArrayList<Integer> values = new ArrayList<>();

			for (String word : words) {
				int val = 2 * getNumberOfLetters(word, c)
						- word.length();
				values.add(val);
			}

			return values;
		}

		private ArrayList<Character> getLetters(StringBuilder str) {
			LinkedHashSet<Character> letters = new LinkedHashSet<>();
			for (int i = 0; i < str.length(); i++) {
				letters.add(str.charAt(i));
			}

			return new ArrayList<>(letters);
		}

		private int getNumberOfLetters(String word, Character c) {
			int count = 0;

			for (int i = 0; i < word.length(); i++) {
				if (word.charAt(i) == c) {
					count++;
				}
			}

			return count;
		}

	}


	public static void main(String[] args) {
		new Task().solve();
	}
}











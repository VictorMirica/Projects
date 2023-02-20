import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;

// Class used for reading and writing files
public class MyFileIO {
	public synchronized String getFileLine(BufferedReader br) {
		String st = null;
		// Read a line (order) from the file
		synchronized (this) {
			try {
				st = br.readLine();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}

		return st;
	}

	public synchronized void writeFileLine(BufferedWriter bw, String s) {
		try {
			bw.write(s + '\n');
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}

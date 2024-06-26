import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.*;

public class Main {
  FastScanner in;
  PrintWriter out;

  void solve() {
    int a = in.nextInt();
    int b = in.nextInt();
    out.print(a + b);
  }

  void run() {
    try {
      in = new FastScanner("input.txt");
      out = new PrintWriter("output.txt");
      solve();
      out.flush();
      out.close();
    } catch (FileNotFoundException e) {
      e.printStackTrace();
      System.exit(1);
    }
  }
  
  class FastScanner {
    BufferedReader br;
    StringTokenizer st;

    public FastScanner() {
      br = new BufferedReader(new InputStreamReader(System.in));
    }

    public FastScanner(String s) {
      try {
        br = new BufferedReader(new FileReader(s));
      } catch (FileNotFoundException e) {
        e.printStackTrace();
      }
    }

    String nextToken() {
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
      return Integer.parseInt(nextToken());
    }

    long nextLong() {
      return Long.parseLong(nextToken());
    }

    double nextDouble() {
      return Double.parseDouble(nextToken());
    }
    
    char nextChar() {
      try {
        return (char) (br.read());
      } catch (IOException e) {
        e.printStackTrace();
      }
      return 0;
    }
    
    String nextLine() {
      try {
        return br.readLine();
      } catch (IOException e) {
        e.printStackTrace();
      }
      return "";
    }
  }

  public static void main(String[] args) {
    new Main().run();
  }
}

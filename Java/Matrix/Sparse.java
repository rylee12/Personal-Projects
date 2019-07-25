/*
 * Ryan Lee
 * Title: Sparse.java
 * Description:
 */

import java.io.*;
import java.util.Scanner;

class Sparse{
        public static void main(String[] args) throws IOException{
          Scanner in = null;
          PrintWriter out = null;
          String[] token = null;
          String line = null;
          String test = null;
          int n, a, b = 0;
          int i, j, lineNumber = 0;
          int lineNumber2 = 0;
          double d = 0.0;
          Matrix A;
          Matrix B;

          if (args.length < 2){
                System.err.println("Usage: Sparse infile outfile");
                System.exit(1);
          }

          in = new Scanner(new File(args[0]));
          out = new PrintWriter(new FileWriter(args[1]));

          line = in.nextLine() + " ";
          token = line.split("\\s+");
          n = Integer.parseInt(token[0]);
          a = Integer.parseInt(token[1]);
          b = Integer.parseInt(token[2]);

          A = new Matrix(n);
          B = new Matrix(n);

          line = in.nextLine() + " ";

          while (in.hasNextLine()){
                lineNumber++;
                line = in.nextLine() + " ";
                if (line.trim().isEmpty()){
                  break;
                }
                //System.out.println(line);
                token = line.split("\\s+");
                i = Integer.parseInt(token[0]);
                j = Integer.parseInt(token[1]);
                d = Double.parseDouble(token[2]);
                A.changeEntry(i, j, d);
                //System.out.println("A " + lineNumber);
          }

          //line = in.nextLine() + " ";

          while (in.hasNextLine()){
                lineNumber2++;
                line = in.nextLine() + " ";
                token = line.split("\\s+");
                i = Integer.parseInt(token[0]);
                j = Integer.parseInt(token[1]);
                d = Double.parseDouble(token[2]);
                B.changeEntry(i, j, d);
                //System.out.println("B " + lineNumber2);
          }

          out.println("A has " + a + " non-zero entries:");
          out.println(A);
          out.println("B has " + b + " non-zero entries:");
          out.println(B);

          out.println("(1.5)*A =");
          out.println(A.scalarMult(1.5));

          out.println("A+B =");
          out.println(A.add(B));

          out.println("A+A =");
          out.println(A.add(A));

          out.println("B-A =");
          out.println(B.sub(A));

          out.println("A-A =");
          out.println(A.sub(A));

          out.println("Transpose(A) =");
          out.println(A.transpose());

          out.println("A*B =");
          out.println(A.mult(B));

          out.println("B*B =");
          out.println(B.mult(B));

          in.close();
          out.close();
        }
}

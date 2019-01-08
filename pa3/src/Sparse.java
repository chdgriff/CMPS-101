// Sparse.java - Takes in files through command line and performs operations on matrices
// Chris Griffis <chdgriff>
// pa3 05/11/18
import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;

public class Sparse {
  public static void main(String[] args) throws FileNotFoundException{
    if (args.length != 2) {
      System.err.println("Incorrect usage Sparse.java: Sparse [input_file] [output_file]");
      System.exit(-1);
    }
    
    Scanner in;
    PrintWriter out;
    Matrix A, B;
    int Anz, Bnz; // non zero values from input file
    
    in = new Scanner(new File(args[0]));
    
    A = new Matrix(in.nextInt());
    B = new Matrix(A.getSize());   
    Anz = in.nextInt();
    Bnz = in.nextInt();
    
    for (int i = 0; i < Anz; i++)
      A.changeEntry(in.nextInt(), in.nextInt(), in.nextDouble());
    for (int i = 0; i < Bnz; i++)
      B.changeEntry(in.nextInt(), in.nextInt(), in.nextDouble());
    
    in.close();
    
    out = new PrintWriter(new File(args[1]));
    
    out.print("A has " + A.getNNZ() + " non-zero entries:");
    out.print(A);
    
    out.print("\n\nB has " + B.getNNZ() + " non-zero entries:");
    out.print(B);
    
    out.print("\n\n(1.5)*A =");
    out.print(A.scalarMult(1.5));
    
    out.print("\n\nA+B =");
    out.print(A.add(B));
    
    out.print("\n\nA+A =");
    out.print(A.add(A));
    
    out.print("\n\nB-A =");
    out.print(B.sub(A));
    
    out.print("\n\nA-A =");
    out.print(A.sub(A));
    
    out.print("\n\nTranspose(A) =");
    out.print(A.transpose());
    
    out.print("\n\nA*B =");
    out.print(A.mult(B));
    
    out.print("\n\nB*B =");
    out.print(B.mult(B) + "\n");
    
    
    out.close();
    
  }
}

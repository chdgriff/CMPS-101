// Lex.java.java - Sorts an input file by unicode order
// Chris Griffis <chdgriff>

import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;

public class Lex {
  public static void main(String[] args) throws FileNotFoundException, IOException {
    if (args.length != 2) {
      System.err.println("Incorrect usage Lex.java: Lex [file_input] [file_output]");
    }
    Scanner in = new Scanner(new File(args[0]));
    String input = in.useDelimiter("\\Z").next();
    in.close();
    String[] inArr= input.split("\\n");
    
    List list = new List();
    
    boolean inserted = false;
    for (int i = 0; i < inArr.length; i++) {
      inserted = false;
      while (!inserted) {
        if (list.length() == 0) { // If empty list
          list.prepend(i);
          inserted = true;
          list.moveFront();
        }
        else if (inArr[i].compareTo(inArr[list.get()]) < 0) { // if less than cursor
          if (list.index() == 0) { // if cursor is at beginning
            list.prepend(i);
            inserted = true;
          }
          else {
            list.movePrev();
            if (inArr[i].compareTo(inArr[list.get()]) > 0) { // Greater than new cursor position
              list.insertAfter(i);
              inserted = true;
            }
          }
        }
        else if (inArr[i].compareTo(inArr[list.get()]) > 0) { // if greater than cursor
          if (list.index() == list.length()-1) { // if cursor is at the end
            list.append(i);
            inserted = true;
          }
          else {
            list.moveNext();
            if (inArr[i].compareTo(inArr[list.get()]) < 0) { // Not at end and less than cursor
              list.insertBefore(i);
              inserted = true;
            }
          }
        }
        else {
          list.insertBefore(i);
          inserted = true;
        }
      }
    }
    
    FileWriter output = new FileWriter(args[1]);
    
    list.moveFront();
    while (list.index() != -1) {
      if (list.index() != 0) output.write('\n'); 
      output.write(inArr[list.get()]);
      list.moveNext();
    }
    output.close();
  }
}
//package mypackage;
// !!!! HOCAM var kullanın demişsiniz ama versiyondan dolayı hata veriyodu emin olamadım o yüzden kullanmadım kullandığım yerlerde yorum satırında yazıyor ...
import mypackage.JavaSet;
import mypackage.JavaVector;
import mypackage.JavaContainer;

import java.io.FileWriter;
import java.io.IOException;
import java.util.Iterator;

public class Driver {
    public static void main(String[] args) {
        // Testing JavaSet
        JavaSet set1 = new JavaSet(); // Using 'var' for local variable " var set1"
        set1.add("apple");
        set1.add("orange");
        set1.add("banana");

        System.out.println("Set 1: " + set1);
        System.out.println("Set 1 Size: " + set1.size());

 
        JavaSet set2 = new JavaSet(); // Using 'var' for local variable " var set2"
        set2.add("apple");
        set2.add("grape");
        set2.add("banana");

        System.out.println("Set 2: " + set2);
        System.out.println("Set 2 Size: " + set2.size());

        System.out.println("Set 1 equals Set 2: " + set1.equals(set2));

      
        JavaVector vector1 = new JavaVector(); // Using 'var' for local variable " var vector1"
        vector1.add(1);
        vector1.add(2);
        vector1.add(3);

        System.out.println("Vector 1: " + vector1);
        System.out.println("Vector 1 Size: " + vector1.size());

     
        JavaVector vector2 = new JavaVector(); // Using 'var' for local variable "var vector2"
        vector2.add(1);
        vector2.add(4);
        vector2.add(3);

        System.out.println("Vector 2: " + vector2);
        System.out.println("Vector 2 Size: " + vector2.size());

        System.out.println("Vector 1 equals Vector 2: " + vector1.equals(vector2));

        // Writing sets to text files
        try {
            writeSetToFile(set1, "set1.txt");
            writeSetToFile(set2, "set2.txt");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void writeSetToFile(JavaContainer container, String filename) throws IOException {
        FileWriter writer = new FileWriter(filename); // Using 'var' for local variable "var writter"
        Iterator<Object> iterator = container.getIterator(); // Using 'var' for local variable "var iterator"

        while (iterator.hasNext()) {
            writer.write(iterator.next().toString() + "\n");
        }

        writer.close(); 
        System.out.println("Set written to " + filename);
    }
}

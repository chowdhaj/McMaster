import java.math.BigDecimal;
import java.util.*;

public class BigDecimalTest{
    public static void main(String[] args){
  
        // Fact: x.equals (y) == false, but x.compareTo (y) == 0 (true)
        // the equals and compareTo behave differently for TreeSet and Hashset
        // TreeSet uses BigDecimal.compareTo() which only checks the value and not the decimal portion (the scale)
        // HashSet uses equals() which checks the value and scale

        /**
        (a) Briefly describe the issue

        (b) If possible, give a test case that does not execute the fault. If not, briefly explain
        why not.

        (c) If possible, give a test case that executes the fault, but does not result in an error
        state. If not, briefly explain why not.

        (d) If possible give a test case that results in an error, but not a failure. If not, briefly
        explain why not.

        (e) In the given code, describe the first error state. Be sure to describe the complete
        state. Assume that 1.0 and 1.00 being the same is the desired behavior.
        
        (f) Can this be fixed without breaking the existing code? Why or Why not?
         */

        BigDecimal x = new BigDecimal ("1.0");
        BigDecimal y = new BigDecimal ("1.00");
       
        Set <BigDecimal> BigDecimalTree = new TreeSet <BigDecimal> ();
        BigDecimalTree.add (x);
        BigDecimalTree.add (y);
        System.out.println(BigDecimalTree.size()); //TreeSet uses BigDecimal.compareTo(), so BigDecimalTree now has 1 element as 1.0 and 1.00 are considered the same
      
        Set <BigDecimal> BigDecimalHash = new HashSet <BigDecimal> ();
        BigDecimalHash.add (x);
        BigDecimalHash.add (y);

        System.out.println(BigDecimalHash.size()); // HashSet uses BigDecimal.equals(), so BigDecimalTree now has 2 elements as 1.0 and 1.00 are considered different


    }
}

// public class BigDecimalTreeWithFixedAdd extends BigDecimals{
//     @override
//     public void add(){
//         ///... fix there
//     }
// }
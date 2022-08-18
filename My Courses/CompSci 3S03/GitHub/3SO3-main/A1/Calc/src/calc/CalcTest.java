package calc;

import org.junit.*;
import static org.junit.Assert.*;

public class CalcTest {
	
	// Simple Test Cases For Calc Functions
	@Test
	public void testAddSimple() {
		assertEquals(4, Calc.add(2, 2));
		assertEquals(90, Calc.add(50, 40));
		assertEquals(1233, Calc.add(1000, 233));
	}
	
	@Test
	public void testSubtractSimple() {
		assertEquals(2, Calc.subtract(4, 2));
		assertEquals(10, Calc.subtract(50, 40));
		assertEquals(1500, Calc.subtract(2000, 500));
	}
	
	@Test
	public void testMultiplySimple() {
		assertEquals(6, Calc.multiply(3, 2));
		assertEquals(81, Calc.multiply(9, 9));
		assertEquals(1200, Calc.multiply(120, 10));
	}
	
	@Test
	public void testDivideSimply() {
		assertEquals(2, Calc.divide(4, 2));
		assertEquals(10, Calc.divide(50, 5));
		assertEquals(1730, Calc.divide(17300, 10));
	}
	
	// Intermediate Test Case For Add
	@Test
	public void testAddIntermediate() {
		for (int i = 0; i <= 10; i++) {
			for (int j = 10; j >= 0; j--) {
				assertEquals(10, Calc.add(i++, j));
			}
		}
	}
	
	// Undo Cases
	// Addition can undo subtraction, and vice versa
	// The same applies to multiplication and division
	@Test
	public void testAddUndoSubtract() {
		// General Rule: ((A - B) + B) = A
		assertEquals(10, (Calc.add(Calc.subtract(10, 5), 5)));
		assertEquals(75, (Calc.add(Calc.subtract(75, 25), 25)));
		assertEquals(120, (Calc.add(Calc.subtract(120, 20), 20)));
	}
	
	@Test
	public void testSubtractUndoAdd() {
		// General Rule: ((A + B) - B) = A
		assertEquals(10, (Calc.subtract(Calc.add(10, 5), 5)));
		assertEquals(75, (Calc.subtract(Calc.add(75, 25), 25)));
		assertEquals(120, (Calc.subtract(Calc.add(120, 20), 20)));
	}
	
	@Test
	public void testMultiplyUndoDivide() {
		// General Rule: ((A / B) * B)  = A
		assertEquals(9, (Calc.multiply((Calc.divide(9, 3)), 3)));
		assertEquals(25, (Calc.multiply((Calc.divide(25, 5)), 5)));
		assertEquals(120, (Calc.multiply((Calc.divide(120, 6)), 6)));
	}
	
	@Test
	public void testDivideUndoMultiply() {
		// General Rule: ((A * B) / B)  = A
		assertEquals(9, (Calc.divide((Calc.multiply(9, 3)), 3)));
		assertEquals(25, (Calc.divide((Calc.multiply(25, 5)), 5)));
		assertEquals(120, (Calc.divide((Calc.multiply(120, 6)), 6)));
	}
	
    // Identity Cases
    @Test
    public void testAddIdentities() {
        // Number of times to run the case
        for (int n = -10; n < 10; n++) {
            assertEquals(n, Calc.add(n, 0));  // Zero case
            assertEquals(0, Calc.add(n, -n)); // "Do nothing" case
        }
    }

    @Test
    public void testSubtractIdentities() {
        // Number of times to run the case
        for (int n = -10; n < 10; n++) {
            assertEquals(n, Calc.subtract(n, 0)); // Zero case
            assertEquals(0, Calc.subtract(n, n)); // "Do nothing" case
        }
    }

    @Test
    public void testMultiplyIdentities() {
        // Number of times to run the case
        for (int n = -10; n < 10; n++) {
        	assertEquals(0, Calc.multiply(n, 0)); // Zero case
            assertEquals(n, Calc.multiply(n, 1)); // "Do nothing" case
        }
    }

    @Test
    public void testDivideIdentities() {
        // Number of times to run the case
        for (int n = -10; n < 10; n++) {
            if (n == 0)
                continue;
            assertEquals(n, Calc.divide(n, 1)); // Identity case
            assertEquals(1, Calc.divide(n, n)); // "Do nothing" case
        }
    }
    
    @Test
    public void testDivisionIdentities2() {
    	// Third division identity property that only applies to
    	// integer division: "For all j less than i, i / j must be 0".
    	for (int i = 0; i < 20; i++) {
    	    for (int j = i + 1; j < 21; j++) {
    	        assertEquals(0, Calc.divide(i, j));
    	    }
    	}
    }

	// Equivalency Cases
    @Test
    public void testAddSubtractEquivalency() {
        for (int n = -10; n < 10; n++) {
            for (int m = -10; m < 10; m++) {
                assertEquals(Calc.add(n, m), Calc.subtract(n, -m));
                assertEquals(Calc.subtract(n, m), Calc.add(n, -m));
            }
        }
    }

    // Boundary Tests
    @Test
    public void testAdditionBoundary() {
        // Assert that MAX_INT + any non-negative integer greater than
    	// 0 throws an error
    	// This is overflow but from MAX_INT
        try {
            int result = Calc.add(Integer.MAX_VALUE, 1);
            fail("Expected an ArithmeticException to be thrown, instead got " + result);
        } catch (ArithmeticException e) {
            // Expected
            assertTrue(true);
        }
    }

    @Test
    public void testSubtractionBoundary() {
        // Assert that MIN_INT - any non-negative integer greater than
    	// 0 throws an error
    	// This is overflow but from MIN_INT
        try {
            int result = Calc.subtract(Integer.MIN_VALUE, 1);
            fail("Expected an ArithmeticException to be thrown, instead got" + result);
        } catch (ArithmeticException e) {
            // Expected
            assertTrue(true);
        }
    }

    @Test
    public void testMultiplicationBoundary() {
        // Assert that MAX_INT * anything throws error
        try {
            int result = Calc.multiply(Integer.MAX_VALUE, 2);
            fail("Expected an ArithmeticException to be thrown, instead got " + result);
        } catch (ArithmeticException e) {
            // Expected
            assertTrue(true);
        }
    }

    @Test
    public void testDivisionBoundary() {
        // Assert that anything / 0 throws error
        try {
            int result = Calc.divide(1, 0);
            fail("Expected an ArithmeticException to be thrown, instead got " + result);
        } catch (ArithmeticException e) {
            // Expected
            assertTrue(true);
        }
    }
    // Simple Unit Tests
}

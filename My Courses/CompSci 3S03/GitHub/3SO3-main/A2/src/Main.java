/**
 * Testing the functionality of the ``PrimeNumbers`` class
 * 
 * @author hutchm6
 * @author chowdhaj
 */

public class Main {
	
	public static void main(String[] args) {
		
		PrimeNumbers p = new PrimeNumbers();
		//p.computePrimes(100);
		//System.out.println(p.toString());
		
		PrimeNumbersEratosthenes pe = new PrimeNumbersEratosthenes();
		pe.computePrimes(100);
		System.out.println(pe.toString());
		
	}
}

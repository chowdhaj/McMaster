import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;
import java.util.List;

/**
 * Reimplements the algorithm for calculating primes using the Sieve of
 * Eratosthenes, but leaves the fault from before in place.
 * 
 * @author hutchm6
 * @author chowdhaj
 */
public class PrimeNumbersEratosthenes implements Iterable<Integer> {

	private List<Integer> primes = new ArrayList<Integer>();

	public void computePrimes(int n) {

		int count = 1; // count of primes
		int number = 2; // number tested for primeness

		boolean isPrime[] = new boolean[n]; // is this number a prime
		Arrays.fill(isPrime, true);

		while (count <= n) {

			for (int divisor = 2; divisor * divisor < n; divisor++) {

				if (isPrime[divisor]) {
					for (int j = divisor; j * divisor < n; j++) {
						isPrime[j * divisor] = false;
					}

				}

				if (isPrime[divisor] && (divisor % 10 != 9)) { // FAULT
					primes.add(divisor);
					count++;
				}

			}
		}
	}

	/**
	 * Overrides the ``iterator()`` method
	 */
	@Override
	public Iterator<Integer> iterator() {
		return primes.iterator();
	}

	/**
	 * Overrides the ``toString()`` method to print all primes in the List<Integer>
	 */
	@Override
	public String toString() {
		return primes.toString();
	}
}
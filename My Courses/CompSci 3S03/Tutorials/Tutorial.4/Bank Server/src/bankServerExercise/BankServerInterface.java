package bankServerExercise;

import java.util.List;

public interface BankServerInterface {
	
	/**
	 * Returns true if the bank is active, i.e. has at least one open account, otherwise false
	 */
	public boolean getActive();
	
	/**
	 * Credits some money to a specified account
	 * 
	 * @param account 
	 * @param value the value to be credited in pence
	 * 
	 * @return true if credit succeeded, false otherwise (e.g. if credit would take account above maximum permitted balance)
	 * @throws BankException if no such account
	 */
	public boolean credit(String account, int value);
	
	/**
	 * Debits some money from a specified account
	 * 
	 * @param account 
	 * @param value the value to be debited in pence
	 * 
	 * @return true if debit succeeded, false otherwise (e.g. if debit would take account below permitted overdraft)
	 * @throws BankException if no such account
	 */
	public boolean debit(String account, int value);
	
	/** 
	 * Returns the net value of bank's holdings i.e. the sum of all account balances
	 * 
	 * @return 
	 */
	public int getNetValue();

	/**
	 * Creates a new bank account
	 * 
	 * @param string the account number for the new account (must be unique)
	 */
	public void createAccount(String accountNumber);

	/**
	 * Returns the current balance of the specified account
	 * 
	 * @param string
	 * @return
	 */
	public int getAccountBalance(String accountNumber);

	/**
	 * Returns the number of accounts in the bank
	 * 
	 * @return
	 */
	public int getNoOfAccounts();

	/**
	 * Close the specified account and (implicitly) return the balance to the customer. Overdrawn accounts (those with negative balance) cannot be closed.
	 * 
	 * @throws BankException if the account is overdrawn 
	 * 
	 * @param number
	 */
	public void closeAccount(String accountNumber);

	/**
	 * Sets a savings target for that account (this is something set by the customer; 
	 * online banking system will show their progress towards it each time they log in)
	 * 
	 * @throws BankExceptionn is target is zero or negative
	 */
	public void setSavingsTarget(String accountNumber, int target);
	
	/** 
	 * Returns an account's balance as an integer percentage of its savings target, ready for display. If no savings target has been set,
	 * returns -1.
	 * */
	public int getSavingsPercentage(String accountNumber);
	 
	/**
	 * Returns a list of all transactions that have occurred during the bank's existence, in chronological order of their occurrence.
	 * (NB the sum of the transaction values in the history will be the same as the net value of the accounts held in the bank)  
	 * 
	 */
	public List<Transaction> getTransactionHistory();
}

package bankServerExercise;

import java.util.LinkedList;
import java.util.List;
import java.util.TreeMap;

import bankServerExercise.Transaction.TransactionType;



public final class BankServer implements BankServerInterface {

	private TreeMap<String, BankAccount> accounts = new TreeMap<String, BankAccount>();
	private List<Transaction> transactionHistory = new LinkedList<Transaction>();
	private boolean active = true;
	
	@Override
	public boolean getActive() {
		return active;
	}
	
	@Override
	public boolean credit(String account, int value) {				
		if(accounts.containsKey(account))
		{
			accounts.get(account).credit(value);
			transactionHistory.add(new Transaction(account, TransactionType.CREDIT, value));
			return true;
		}
		else
		{
			throw new BankException("debit requested for nonexistent account number");
		}
	}

	@Override
	public boolean debit(String account, int value) {
		if(accounts.containsKey(account))
		{
			boolean success = accounts.get(account).debit(value); 
			if(success)
			{
				transactionHistory.add(new Transaction(account, TransactionType.DEBIT, value));
			}
			return success;			
		}
		else
		{
			throw new BankException("debit requested for nonexistent account number");
		}
	}
	
	@Override
	public int getNetValue() {
		int netBalance = 0;
		for(BankAccount b : accounts.values())
		{
			netBalance += b.getBalance();
		}
		
		return netBalance;
	}

	@Override
	public String toString()
	{		
		return "BankServer - " + accounts.size() + " accts worth £" + getNetValue();
	}

	@Override
	public void createAccount(String accountNumber) {
		accounts.put(accountNumber, new BankAccount());
		transactionHistory.add(new Transaction(accountNumber, TransactionType.CREATE_ACCOUNT, 0));
	}

	@Override
	public int getAccountBalance(String accountNumber) {		
		return accounts.get(accountNumber).getBalance();
	}

	@Override
	public int getNoOfAccounts() {		
		return accounts.size();
	}

	@Override
	public void closeAccount(String accountNumber) {	
		if(accounts.size() == 1)
		{
			active = false;
			accounts.remove(accountNumber);
			transactionHistory.add(new Transaction(accountNumber, TransactionType.CLOSE_ACCOUNT, 0));
		}
		else
		{		
			if(accounts.get(accountNumber).getBalance() >= 0)
			{
				accounts.remove(accountNumber);
				transactionHistory.add(new Transaction(accountNumber, TransactionType.CLOSE_ACCOUNT, 0));
			}
			else
			{
				throw new BankException("Attempted to close an overdrawn account");
			}
		}
	}
	
	@Override
	public void setSavingsTarget(String accountNumber, int target)
	{
		if(target < 0)
		{
			throw new BankException("Savings target of £" + target + " is not valid.");			
		}
		else
		{
			accounts.get(accountNumber).setSavingsTarget(target);
		}
	}

	@Override
	public int getSavingsPercentage(String accountNumber) {
		int target = accounts.get(accountNumber).getSavingsTarget();
		
		if(target != 0)
		{
			return (target * 100) / accounts.get(accountNumber).getBalance();
		}
		else
		{
			return 100;
		}
	}

	@Override
	public List<Transaction> getTransactionHistory() {
		return transactionHistory;
	}




}

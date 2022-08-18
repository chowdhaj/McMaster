package bankServerExercise;

//have used default visibility for this class - BankAccount is implementation detail, not something that I'm expecting you to use for testing
final class BankAccount {
	private int balance = 0;
	private int minimumBalance = 0; //default value
	private int savingsTarget = 0;

	public boolean credit(int value) {
		balance += value;
		return true;
	}

	public int getBalance() {
		return balance;
	}

	public boolean debit(int value) {
		if(balance >= minimumBalance)
		{
			balance -= value;
			return true;
		}
		else
		{
			return false;	
		}		
	}

	public void setSavingsTarget(int target)
	{
		savingsTarget = target;
	}

	public int getSavingsTarget() {
		return savingsTarget;
	}
	
}

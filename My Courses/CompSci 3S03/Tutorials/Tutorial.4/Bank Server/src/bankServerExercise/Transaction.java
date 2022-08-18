package bankServerExercise;

public final class Transaction {
	private String acctNumber;
	private TransactionType type;
	private int amount;
	
	public enum TransactionType {  
        CREATE_ACCOUNT,  
        CLOSE_ACCOUNT,  
        CREDIT,
        DEBIT,
        INTEREST
    } 
	
	public Transaction(String acctNumber, TransactionType type, int amount)
	{
		this.acctNumber = acctNumber;
		this.type = type;
		this.amount = amount;
	}

	public String getAcctNumber() {
		return acctNumber;
	}

	public TransactionType getType() {
		return type;
	}

	public int getAmount() {
		return amount;
	}
	
	
}

package SMATLibrarySystem;

import java.util.Calendar;
import java.util.List;

/**
 * 
 * NB if a method can only be sensibly performed while the Customer is registered to a library, then calling that method when not 
 * registered will cause a LibraryException
 * 
 * @author rfp1
 */
public class Customer {
	private Library lib;
	private String name;
	private Calendar dateOfBirth;
	private CustomerType type;

	/** Constructs a new Customer with the specified details */
	public Customer(String name, Calendar dob, CustomerType type)
	{
		this.name = name;
		this.dateOfBirth = dob;
		this.type = type;
	}
	
	/** Constructs a new Customer with generic but plausible details */
	public Customer()
	{
		this("A Person", Calendar.getInstance(), new CustomerType() { public Calendar getDueDate(Calendar cal) {return cal;} });
	}
	
	/** Returns a list of the books held by the customer */
	public List<LibraryBook> getBooksHeld() {
		return lib.getBooksHeld(this);
	}

	/** Sets the Library object that this customer should use */
	public void setLibrary(Library lib) {
		this.lib = lib;		
	}

	/** Returns the due date appropriate to a new loan starting immediately */
	public Calendar getDueDateForNewLoan() {
		return type.getDueDate(Calendar.getInstance());
	}


}

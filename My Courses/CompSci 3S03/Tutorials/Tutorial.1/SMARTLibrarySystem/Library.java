package SMATLibrarySystem;

import java.util.ArrayList;
import java.util.Calendar;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Library {
	private class Holding
	{
		public Holding(Customer c, LibraryBook b) {
			holder = c;
			book = b;
			dueDate = c.getDueDateForNewLoan();
		}
		
		Customer holder;
		LibraryBook book;
		Calendar dueDate;
	}
	
	private Map<String, LibraryBook> books = new HashMap<String, LibraryBook>();
	private List<Customer> customers = new ArrayList<Customer>();
	private List<Holding> heldBy = new ArrayList<Holding>(); 
	
	/**
	 * Adds the provided book to the library's holdings
	 * 
	 * If the book already exists, an additional copy will be added to the library
	 * 
	 * @param book
	 */
	public void addBook(LibraryBook book) {
		books.put(book.getDeweyCode(), book);		
	}

	/** 
	 * Returns the number of books held by the library
	 * 
	 * @return
	 */
	public int getBookCount() {
		return books.size();
	}
	
	@Override
	public String toString() {
		String s = "";
		
		if( getBookCount() > 1 )
		{
			s += "" + "Library with " + getBookCount() + " books";
		}
		else
		{
			s += "" + "Library with " + getBookCount() + " book";
		}
		
		if( heldBy.isEmpty() )
		{
			//add nothing
		}
		else 
		{
			int averageBooksPerCustomer = heldBy.size() / customers.size();
			s += ". Average of " + averageBooksPerCustomer + " books held per customer.";
		}
	
		return s;
	}

	/** Returns the LibraryBook object corresponding to the Dewey Decimal code provided. If the provided Dewey code
	 * does not correspond to any book in the library, throws a LibraryException
	 * 
	 */
	public LibraryBook getByDewey(String deweyCode) {
		return books.get(deweyCode);
	}

	/**
	 * Records that the specified customer has taken the specified book out of the library, and records an appropriate due date
	 * for the loan according to the customer's type 
	 * 
	 */
	public void takeOutBook(Customer c, LibraryBook b) {
		b.setAvailable(false);
		Holding h = new Holding(c,b);
		h.dueDate = Calendar.getInstance(); 
		h.dueDate.add(Calendar.MONTH, 1);		
		heldBy.add(h);		
	}

	/**
	 * Records that the specified customer has returned the specified book to the library
	 * 
	 */
	public void returnBook(Customer c, LibraryBook b) {
		for(int i = 0; i < heldBy.size(); i++)
		{
			Holding h = heldBy.get(i);
			if(h.book.equals(b))
			{
				heldBy.remove(i);
				break;
			}
		}		
	}
	
	/** Returns a list of LibraryBook objects corresponding to the books that the customer has on loan
	 * 
	 */
	public List<LibraryBook> getBooksHeld(Customer customer) {
		List<LibraryBook> customerBooks = new ArrayList<LibraryBook>();
		
		for(Holding h : heldBy)
		{
			if(h.holder.equals(customer))
			{
				customerBooks.add(h.book);
			}
		}
		
		return customerBooks;
	}

	/** Registers the provided Customer object with the library. Until this has been performed for a given customer, many operations 
	 * on that customer will fail with a LibraryException 
	 * 
	 */
	public void register(Customer c) {
		c.setLibrary(this);
		customers.add(c);
	}
	
	/** Deregisters the provided customer from the library */
	public void deregister(Customer c) {
		c.setLibrary(null);	
		customers.remove(c);
	}

	/** Deletes a book from the library
	 * 
	 */
	public void deleteBook(LibraryBook b) {
		books.remove(b.getDeweyCode());		
	}

	/** Returns the due date for a given book held by a given customer 
	 * 
	 */
	public Calendar getDueDate(Customer c, LibraryBook b) {
		for(Holding h : heldBy)
		{
			if(h.holder.equals(c))
			{
				if(h.book.equals(b))
				{
					return h.dueDate;
				}
			}
		}
		
		return null;		
	}

}

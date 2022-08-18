package SMATLibrarySystem;

public class LibraryBook {

	private String title;
	private int yearPublished;
	private int deweyClassDivSec;
	private int deweyBook;
	
	private boolean available = true;
	
	/** Constructs a LibraryBook instance for the book details provided
	 * 
	 * @param title
	 * @param yearPublished
	 * @param deweyCode a valid Dewey Decimal number for this book
	 * 
	 * @throws LibraryException if deweyCode is not a valid Dewey Decimal identifier
	 */
	public LibraryBook(String title, int yearPublished, String deweyCode) {
		this.title = title;
		this.yearPublished = yearPublished;
		
		String[] deweyBits = deweyCode.split("\\.");
		this.deweyClassDivSec = Integer.parseInt(deweyBits[0]);
		this.deweyBook = Integer.parseInt(deweyBits[1]);
		if(this.deweyClassDivSec < 0 || this.deweyClassDivSec > 999)
		{
			throw new LibraryException("Invalid Dewey classification, division and/or section: " + this.deweyClassDivSec);
		}
	}

	public LibraryBook() {
		this.title = "Sample Book";
		this.yearPublished = 1979;
		this.deweyClassDivSec = 0;
		this.deweyBook = 1;
	}

	/** Returns the Dewey Code for this book (that was provided at the time of creation) */
	public String getDeweyCode() {
		if(deweyClassDivSec >= 100)
		{
			return "" + deweyClassDivSec + "." + deweyBook;
		}
		else if(deweyClassDivSec >= 10)
		{
			return "" + "0" + deweyClassDivSec + "." + deweyBook;
		}
		else
		{
			return "" + deweyClassDivSec + "00" + "." + deweyBook;
		}
	}
	
	@Override
	public int hashCode()
	{
		return yearPublished;
	}

	/** Returns true if the book is not currently on loan from the library, otherwise false */
	public boolean isAvailable() { 
		return available;
	}

	/** Records the availability of the book for loan */
	public void setAvailable(boolean b) {
		available = b;		
	}

}

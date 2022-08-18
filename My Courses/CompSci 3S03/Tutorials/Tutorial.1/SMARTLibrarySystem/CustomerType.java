package SMATLibrarySystem;

import java.util.Calendar;

public interface CustomerType {

	/**
	 * Returns the appropriate due date for a new loan starting from the specified date 
	 * 
	 * @param loanStartDate the date of which the book is taken out of the library
	 * @return
	 */
	Calendar getDueDate(Calendar loanStartDate);

}

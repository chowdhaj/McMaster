package SMATLibrarySystem;

import java.util.Calendar;


public class StandardCustomerType implements CustomerType {

	@Override
	public Calendar getDueDate(Calendar loanStartDate) {
		Calendar due = (Calendar) loanStartDate.clone();
		due.add(Calendar.MONTH, 1);
		return due;
	}

}

import java.util.Scanner;
import java.util.Stack;

public class Exercise1_3_9 {

    public static void main(String[] args) {

        // Sample input: 1 + 2 ) * 3 - 4 ) * 5 - 6 ) ) )

        System.out.println("Please enter the expression:");
        Scanner in = new Scanner(System.in);
        String input = in. nextLine();

        System.out.println(getInfix(input));
    }

    private static String getInfix(String input) {

        Stack<String> operands = new Stack<>();
        Stack<String> operators = new Stack<>();

        String[] values = input.split(" ");

        for (String var : values) {
            if (var.equals("+")|| var.equals("-")||var.equals("*")||var.equals("/"))
            {
                operators.push(var);
            }
            else if (var.equals(")"))
            {
                String operator = operators.pop();
                String value2 = operands.pop();
                String value1 = operands.pop();

                String subExpression = "( " + value1 + " " + operator + " " + value2 + " )";
                operands.push(subExpression);
            }
            else
            {
                operands.push(var);
            }
        }

        return operands.pop();
    }
}

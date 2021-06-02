package solution;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class challenge18 
{
	public static long arithmetic(long lhs, long rhs, String op)
	{
		switch(op) 
		{
		case "+":
			return lhs + rhs;
		case "-":
			return lhs - rhs;
		case "/":
			return lhs / rhs;
		case "*":
			return lhs * rhs;
		}
		return rhs;
	}
	
	public static long computeLine(Scanner lineScanner)
	{
		long lhs = 0;
		long rhs = 0;
		String op = "";
		while (lineScanner.hasNext()) 
		{
			if (lineScanner.hasNextInt()) {
	        	if(lhs == 0)
	        	{
	        		lhs = lineScanner.nextInt();
	        	}
	        	else
	        	{
	        		rhs = lineScanner.nextInt();
	        	}
	        }
	        else
	        {
	        	String next_op = lineScanner.next().trim();
	        	if(next_op.equals("("))
	        	{
	        		//System.out.println("brackets open");
	        		if(lhs == 0)
	        			lhs = computeLine(lineScanner);
	        		else
	        			rhs = computeLine(lineScanner);
	        	}
	        	else if(next_op.equals(")"))
	        	{
	        		//System.out.println("brackets close");
	        		return lhs;
	        	}
	        	else if(next_op.length() > 0)
	        	{
	        		op = next_op;
	        	}     	
	        }
	        if(rhs != 0 && op != "")
	        {
	        	//System.out.println(lhs + op +  rhs);
	        	lhs = arithmetic(lhs, rhs, op);
	            //System.out.println("lhs " + lhs);
	        	op = "";
	        	rhs = 0;
	        }
            
        }
		return lhs;	
	}
	
	public static void main(String[] args)
	{
		File inputFile = new File("./src/solution/input.txt");
	    try 
	    {
	    	long sum = 0;
	    	int line_count = 1;
	        Scanner reader = new Scanner(inputFile);
	        while (reader.hasNextLine()) 
	        {	   
	        	Scanner lineScanner = new Scanner(reader.nextLine());
	        	lineScanner.useDelimiter("");
	        	long ans = computeLine(lineScanner);
		        System.out.println(line_count + "F ANS: " + ans);	
		        sum += ans;
		        line_count++;
	        }
	        System.out.println(sum);
	    } 
	    catch (FileNotFoundException e) {
	        System.out.println("scanner error");
	        e.printStackTrace();
	    }
	}
}

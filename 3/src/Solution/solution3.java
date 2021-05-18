package Solution;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class solution3 
{
	public static void main(String[] args)
	{
		int length = 0;
		boolean first_line = true;
		int trees = 0;
		int position = 0;
		File inputFile = new File("./src/Solution/input.txt");
	    try {
		        Scanner reader = new Scanner(inputFile);
		        while (reader.hasNextLine()) 
		        {
		            String data = reader.nextLine();
		        	if(first_line)
		        	{
		        		length = data.length();
		        		first_line = false;
		        	}
		        	else
		        	{
			            position = (position + 3) % length;
			            if(data.charAt(position) == '#')
			            {
			            	trees++;
			            	data = data.substring(0, position) + 'X'+ data.substring(position + 1);
			            }
			            else
			            {
			            	data = data.substring(0, position) + 'O'+ data.substring(position + 1);
			            }
		        	}
		            		     
		            System.out.println(data);
	            }
		        System.out.println("Trees: " + trees);
		        reader.close();
		    } 
	    catch (FileNotFoundException e) {
	        System.out.println("scanner error");
	        e.printStackTrace();
	    }
	}
}

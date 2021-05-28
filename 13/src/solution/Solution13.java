package solution;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class Solution13 
{
	public static void main(String[] args)
	{
		File inputFile = new File("./src/solution/input.txt");
	    try 
	    {
			int line_number = 0;
			int waiting_timestamp = 0;
			ArrayList<Integer> buses = new ArrayList<Integer>();
	        Scanner reader = new Scanner(inputFile);
	        while (reader.hasNextLine()) 
	        {
	        	if(line_number == 0)
	        	{
	        		waiting_timestamp = Integer.parseInt(reader.nextLine());
	        	}
	        	else
	        	{
	        		List<String> line = Arrays.asList(reader.nextLine().split(",", -1));
	        		for(int i = 0; i < line.size(); i++)
	        		{
	        			String bus = line.get(i);
	        			if(bus.equals("x"))
	        			{
	        				continue;
	        			}
	        			else 
	        			{
	        				buses.add(Integer.parseInt(bus));
	        			}
	        		}
	        	}
	        	line_number++;
	        }
	        int current_timestamp = waiting_timestamp;
	        int bus = -1;
	        boolean waiting = true;
	        while(waiting)
	        {
		        current_timestamp++;
		        for(int i = 0; i < buses.size(); i++)
		        {
		        	bus = buses.get(i);
		        	boolean scheduled = (current_timestamp % bus) == 0;
		        	if(scheduled)
		        	{
			        	waiting = false;
			        	break;
		        	}
		        }
	        }
	        int wait_time = current_timestamp - waiting_timestamp;
	        System.out.println("Bus " + bus + " found. Wait time: " + wait_time);
	        int answer = bus * wait_time;
	        System.out.println("Answer: " + answer);
	    } 
	    catch (FileNotFoundException e) {
	        System.out.println("scanner error");
	        e.printStackTrace();
	    }
	}
}

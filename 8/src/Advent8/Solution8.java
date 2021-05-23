package Advent8;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Solution8 
{
	public static void main(String[] args)
	{
		File inputFile = new File("./src/Advent8/input.txt");
	    try 
	    {
	        Scanner reader = new Scanner(inputFile);
	        List<String> lines = new ArrayList<String>();
	        List<Integer> instructions_executed = new ArrayList<>();
	        while (reader.hasNextLine()) 
	        {
	        	lines.add(reader.nextLine());
	        }
			int accumulator = 0;
	        for(int i = 0; i < lines.size();)
	        {
	        	//check if instruction executed
	        	if(instructions_executed.contains(i))
	        	{
	        		break;
	        	}
	        	instructions_executed.add(i);
	            String data = lines.get(i);
	            String cmd = data.substring(0, 3);
	            int value = Integer.parseInt(data.substring(4, data.length()));
	            System.out.println("Instruction " + cmd + " acc " + accumulator);
	            if(cmd.equals("jmp"))
	            {
	            	System.out.println("line " + i + " change " + value);
	            	i += value;
	            }
	            else
	            {
		            if(cmd.equals("acc"))
		            {
		            	System.out.println("acc " + accumulator + " change " + value);
		            	accumulator += value;
		            }
		            i++;
	            }
            }
	        System.out.println("Acc " + accumulator);
	        reader.close();
	    } 
	    catch (FileNotFoundException e) {
	        System.out.println("scanner error");
	        e.printStackTrace();
	    }
	}
}

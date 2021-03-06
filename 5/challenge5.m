fid = fopen("input.txt"); % open the file
best_id = 0;
while ~feof(fid) % feof(fid) is true when the file ends
      row = 0;
      col = 0;
      line = fgetl(fid) % read one line
      smallest = 0;
      largest = 127;
      size = 128;
      for index = 1:6 %find row
        c = line(index);
        if(c == 'F')
          largest = largest - (size / 2);
        else
          smallest = smallest + (size / 2);
        end
        size = size / 2;
      end
      c = line(7);
      if(c == 'F')
          row = smallest;
      else
          row = largest;
      end
      
      smallest = 0;
      largest = 7;
      size = 8;
      for index = 8:9 %find row
        c = line(index);
        if(c == 'L')
          largest = largest - (size / 2);
        else
          smallest = smallest + (size / 2);
        end
        size = size / 2;
      end
      c = line(10);
      if(c == 'L')
          col = smallest;
      else
          col = largest;
      end
      
      %calculate id and find largest
      id = row * 8 + col;
      if(id > best_id)
        best_id = id;
      end
      
end
fclose(fid); % close the file
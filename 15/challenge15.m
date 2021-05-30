fid = fopen("input.txt"); % open the file
best_id = 0;
index = 0;
list = split(fgetl(fid),','); % read line
fclose(fid); % close the file
keys = str2double(list);
turn = 1;
%map(number, last_turn used) 
m = containers.Map('KeyType','double','ValueType','double') 
for n = 1 : length(keys)
  m(keys(n)) = turn;
  turn = turn + 1;
end

turn_value = m(keys(turn-1)) - (turn-1)
% look at last turn and determine age
for n = turn : 2020-1
  if(isKey(m, turn_value))
    age = turn - m(turn_value);
  else
    age = 0;
  end
  m(turn_value) = turn; %update last played
  turn_value  = age
  turn = turn + 1
end

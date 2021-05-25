A = importdata ('input.txt', ' ', 0);
data = sort(A);
%adapter_joltage = data(end) + 3;
current_joltage = 0;
jolt_1s = 0;
jolt_3s = 1; %account for adapter
for n = 1 : length(data)
  jolt = data(n);
  if((jolt - current_joltage) == 1)
    jolt_1s = jolt_1s + 1;
  elseif((jolt - current_joltage) == 3)
    jolt_3s = jolt_3s + 1;
  else
    fprintf("something went wrong")
  end
  fprintf("Jolt: %i, prev: %i\n", jolt, current_joltage)
  current_joltage = jolt;
end
jolt_1s * jolt_3s
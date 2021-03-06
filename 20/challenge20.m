fid = fopen("input.txt"); % open the file
f = textscan(fid,'%s', 'delimiter', '\n', 'whitespace', '')
f(cellfun(@isempty,f))=[];    % eliminate any totally blank rows
input = string(f{1,1});           % display result...
tile_numbers = [];
tiles = {};
for i=1:size(input)
  if(mod(i,12) == 1)
    g = textscan(input(i), '%s %d'); %get value from header
    tile_numbers(end+1) = cell2mat(g(2));
    tile = cell2mat(input(i+1:i+10));
    tiles{end+1} = tile;
  end
  if(input(i) == '')
    continue %skip empty
  end
end
counts = []; 
for i=1:size(tiles,2)
  count = 0;
  t = cell2mat(tiles(1,i));
  e1 = convertCharsToStrings(t(:,1));
  e2 = convertCharsToStrings(t(:,end));
  e3 = convertCharsToStrings(t(1,:));
  e4 = convertCharsToStrings(t(end,:));
  edges = [e1, e2, e3, e4];
  for j=1:size(tiles,2)
    if i == j
      continue
    end
    t2 = cell2mat(tiles(1,j));
    e5 = convertCharsToStrings(t2(:,1));
    e6 = convertCharsToStrings(t2(:,end));
    e7 = convertCharsToStrings(t2(1,:));
    e8 = convertCharsToStrings(t2(end,:));
    edges2 = [e5, e6, e7, e8];
    %try matching edges
    for k=1:size(edges,2)
      for m=1:size(edges2,2)
        if edges(k) == edges2(m)
          count = count + 1;   
        end
        if reverse(edges(k)) == edges2(m)
          count = count + 1;   
        end
        if edges(k) == reverse(edges2(m))
          count = count + 1;   
        end
        if reverse(edges(k)) == reverse(edges2(m))
          count = count + 1;   
        end      
      end
    end
  end
  counts(i) = count;
end
corners = find(counts ==min(counts))
corner_vals = tile_numbers(corners)
total = 1;
for i=1:size(corner_vals,2)
  total = total * corner_vals(i);
end
num2str(total, '%d')

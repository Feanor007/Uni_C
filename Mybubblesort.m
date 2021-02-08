function y = Mybubblesort (x)
[a,b] = size(x);
y = x ; 
if isrow(x)
   length = b;
else
    length = a;
end
for i = 1:length
    for j = 1:length
        if y(j)>y(i)
            temp = y(i);
            y(i) = y(j);
            y(j) = temp;
        end
    end
end
end

function smooth_data = my_smooth(data,win_size)
n = length(data);
smooth_data = zeros(1,n);
for i = 1:n
    if (i <= win_size/2)
        start = 1;
        stop = start + win_size;
    elseif(i >= n - win_size/2)
        start = i - win_size/2;
        stop = n;
    else
        start = i - win_size/2;
        stop = start + win_size;
    end
    %The following three lines of code were used for debugging
    %disp(start)
    %check = stop - start;
    %disp(check);
    smooth_data(i) = sum(data(start:stop))/(stop-start+1);
end
end
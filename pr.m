function [Pstars,R] = pr()
    counter = 1;
    Pstars = zeros(1,10000);
    R = zeros(1,10000);
    for r = 1:0.005:3
       pstars = wt(1000,3,r,30);
       if pstars ~= -1
           Pstars(1,counter) = pstars;
           R(1,counter) = r;
           counter = counter + 1;
           disp(pstars)
           disp(r)
       end
    end
end
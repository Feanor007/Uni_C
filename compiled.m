[s,r] = pr;
s = s(s~=0);
r = r(r~=0);
plot(r,s,'o')
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
           %disp(pstars)
           %disp(r)
       end
    end
end
function Pstars = wt(t,init,r, K)
    P = zeros(1,t+1);
    P(1,1) = init;
    for i = 1:t
        P(1,i+1) = r*P(1,i)*(1-P(1,i)/K);
        if P(1,i+1) == P(1,i)
            Pstars = P(1,1+i);
        else 
            Pstars = -1;
        end
    end
    %disp(P)
end
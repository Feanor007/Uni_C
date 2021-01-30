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
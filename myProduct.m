function product = myProduct(A,B);
[r1,c1] = size(A);
[r2,c2] =size(B);
product = zeros(r1,c2);
if c1 == r2
    for i=1:r1
        for j = 1:c2
            for k = 1:r2
                product(i,j) = product(i,j)+A(i,k)*B(k,j);
            end
        end
    end
else
    error("The two matrix cannot be multiplied"); 
end

end
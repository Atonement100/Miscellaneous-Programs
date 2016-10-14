function root = sqrt_calc( sq )
    steps = 0;
    fsq = sq;
    x = sq;
    while (abs(fsq) > 10^-7 && steps < 100)
       fsq = sq - x^2;
       dfsq = -2*x;
       x = x - (fsq)/(dfsq);

       steps = steps + 1;    
       root = x;
    end
    
    if abs(fsq) > 10^-7
        disp('Warning: A root may not have been found')
    else 
        fprintf('A root has been found in %d steps\nThe square root of %d is %f\n',steps,sq,root)
    end
end


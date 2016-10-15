function x = sqrt_calc( sq )
    steps = 0;
    fsq = sq;
    
    %Find start location, could be done significantly faster
    %with the use of log() to get exponent; only allowed +-*/
    exp = 0;
    tempsq = sq;
    while (abs(tempsq) > 10^-1)
        tempsq = tempsq / 10;
        exp = exp + 1;
    end
    exp = round((exp-1)/2);
    
    x = 10^exp;
    
    while (abs(fsq) > 10^-7 && steps < 100)
       fsq = sq - x^2;
       dfsq = -2*x;
       x = x - (fsq)/(dfsq);
       steps = steps + 1;    
    end
    
    if abs(fsq) > 10^-7
        disp('Warning: A root may not have been found')
    else 
        fprintf('A root has been found in %d steps\nThe square root of %d is %f\n',steps,sq,x)
    end
end


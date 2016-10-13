function steps = midpoint_method( a, b )
    steps = 1;
    e = b-a;
    m = (b+a)/2
    fm = exp(-m/5)-sin(m);
    
    while (abs(fm) > 10^-7 && steps < 100)
       m = (b+a)/2
       fa = exp(-a/5)-sin(a);
       fm = exp(-m/5)-sin(m)
       if (fa*fm < 0) 
           b = m;
       else
           a = m;
       end
        
       e = (b-a) / 2;
       steps = steps + 1;    
    end
    
    if abs(exp(-m/5) - sin(m)) > 10^-5
        disp('Warning: exp(-m/5) != sin(m), there may not be an intersection within the interval given')
    end
end


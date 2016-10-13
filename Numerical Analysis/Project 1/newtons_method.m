function steps = newtons_method( p )
    steps = 0;
    fp = 1;
    while (abs(fp) > 10^-7 && steps < 100)
       fp = exp(-p/5)-sin(p)
       dfp = ((-1/5) * exp(-p/5)) - cos(p);
       p = p - (fp/dfp)
       steps = steps + 1;    
    end
    if abs(exp(-p/5) - sin(p)) > 10^-7
        disp('Warning: exp(-p/5) != sin(p), an intersection may not have been found')
    end
end

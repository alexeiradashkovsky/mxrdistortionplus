function Vo = clipping_stage(Vi, Ts)

    N = length(Vi);
    % Diod parameters
    eta = 1;
    Is = 1*10^-15;
    Vt = 26*10^-3;

    C2 = 1*10^-9;
    R2 = Ts/(2*C2);
    R5 = 10e3;

    Vo = zeros(N,1);
    x = 0;
    Vd = 0.1;
    thr = 0.000000001;
    b = 1.0;
    Ga = (1/R5 + 1/R2);
    for n = 1:length(Vi) 
        % Step 1: Find voltage across nonlinear componenets
        iter = 1;
        fd = -Vi(n,1)/R2 + Is * sinh(Vd/(eta*Vt)) + Ga*Vd - x;
        while (iter < 50 && abs(fd) > thr)
            fdd = (Is/(eta*Vt)) * cosh(Vd/(eta*Vt)) + Ga;
            Vnew = Vd - b * fd / fdd;
            fdNew = -Vi(n,1)/R2 + Is * sinh(Vnew/(eta*Vt)) + Ga*Vnew - x;
            if abs(fdNew) < abs(fd)
                Vd = Vnew;
                b = 1.0;
            else
                b = b * 0.5;
            end
            
            fd = -Vi(n,1)/R2 + Is * sinh(Vd/(eta*Vt)) + Ga*Vd - x;
            iter = iter + 1;
        end
        % Step 2: Calculate Output
        Vo(n,1) = Vd;
        
        % Step 3: Update State Variables
        x = 2*(Vo(n,1))/R2 - x;
    end

end % end function
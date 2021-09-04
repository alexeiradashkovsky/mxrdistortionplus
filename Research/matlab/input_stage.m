function Vo = input_stage(Vi, Ts)
  
  N = length(Vi);
  C1 = 1e-9;
  R1 = Ts / (2*C1);
  C2 = 10e-9;
  R2 = Ts / (2*C2);
  
  R3 = 10e3;
  R4 = 1e6;
 
  Ga = R4 / (R3+R4);
  Gi = Ga * (1 + R2/R1);
  Gx = Ga * R2;
  x1 = 0;
  x2 = 0;
  Vo = zeros(N, 1);
  
  for n = 1:N
    Vo(n,1) = Gi * Vi(n,1) + Gx * (x2 - x1);
    x1 = Vi(n,1) / R1 - x1;
    x2 = (Vo(n,1) / Ga - Vi(n,1)) / R2 - x2;
  end
  
end

%%

%%
clc;clear; close all;
Fs = 44100;
Ts = 1/Fs;
f = 2000;
t = [0:Ts:0.01].';

Vi = 0.1* sin(2*pi*f*t);

N = length(Vi);
C1 = 47e-9;
R1 = Ts/(2*C1);
R3 = 4700;
R4 = 1e6;
Rp = 0; % max

G = 1 / (R1+R3+Rp);
Gb = (R3+Rp) * G;
Gi = 1 + R4*G;
Gx1 = R1 * R4 * G;
x1 = 0;
x2 = 0;
Vo = zeros(N,1);
Vb = 0;
Vr1 = 0;

for n = 1:N
   Vb = Gb*Vi(n,1) - R1*Gb*x1;
   Vr1 = Vi(n,1) - Vb;
   Vo(n,1) = Gi*Vi(n,1) - Gx1*x1;
   if Vo(n,1) > 4.5;
       Vo(n,1) = 4.5;
   elseif Vo(n,1) < -4.5;
       Vo(n,1) = -4.5;  
   end
   if n < N
       x1 = (2 * Vr1 / R1) - x1;
   end
end

% Waveform
plot(t,Vi);
figure;

plot(t, Vo);

figure;
[H,F] = freqz(Vo,1,4096,Fs);
plot(F , 20*log10(abs(H)));
figure;
semilogx(F , 20*log10(abs(H)));


Vi2 = Vo;

% Diod parameters
eta = 1;
Is = 1*10^-15;
Vt = 26*10^-3;

C2 = 1*10^-9;
R2 = Ts/(2*C2);
R5 = 10e3;

Vo2 = zeros(N,1);
x = 0;
Vd = 0;
thr = 0.000000001;
for n = 1:N 
    
    % Step 1: Find voltage across nonlinear componenets
    iter = 1;
    num = -Vi(n,1)/R1 + Is * sinh(Vd/(eta*Vt)) + (1/R5 + 1/R2)*Vd - x;
    while (iter < 50 && abs(num) > thr)
        den = (Is/(eta*Vt)) * cosh(Vd/(eta*Vt)) + (1/R5 + 1/R2);
        Vd = Vd - num/den;
        num = -Vi(n,1)/R1 + Is * sinh(Vd/(eta*Vt)) + (1/R5 + 1/R2)*Vd - x;
        iter = iter + 1;
    end
    % Step 2: Calculate Output
    Vo2(n,1) = Vd;
    
    % Step 3: Update State Variables
    x = 2/R2*(Vo2(n,1)) - x;
end

figure;

plot(t, Vo2);
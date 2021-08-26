%%
clc;clear; close all;
%%
Fs = 44100;
Ts = 1/Fs;
f = 3;
t = [0:Ts:1].';

Vi = 1 * sin(2*pi*f*t);

N = length(Vi);
C1 = 47e-9;
R1 = Ts/(2*C1);
R3 = 4700;
R4 = 1e6;
Rp = 1e6; % max

G = 1 / (R1+R3+Rp);
Gb = (R3+Rp) * G;
Gi = 1 + R4*G;
Gx1 = R1 * R4 * G;
x1 = zeros(N,1);
x2 = zeros(N,1);
Vo = zeros(N,1);
Vb = zeros(N,1);
Vr1 = zeros(N,1);
Vr2 = zeros(N,1);
for n = 1:N
   Vb(n,1) = Gb*Vi(n,1) - R1*Gb*x1(n,1);
   Vr1(n,1) = Vi(n,1) - Vb(n,1);
   Vo(n,1) = Gi*Vi(n,1) - Gx1*x1(n,1);
   if Vo(n,1) > 4.5;
       Vo(n,1) = 4.5;
   elseif Vo(n,1) < -4.5;
       Vo(n,1) = -4.5;  
   end
   if n < N
       x1(n+1,1) = (2 * Vr1(n,1) / R1) - x1(n,1);
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

%%
Vi2 = Vo;


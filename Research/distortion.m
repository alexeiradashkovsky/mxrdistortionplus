clc;clear; close all;

Fs = 44100;
Ts = 1/Fs;
f = 3;
t = [0:Ts:1].';

Vi = sin(2*pi*f*t);

N = length(Vi);
C1 = 1e-3;
R1 = 1/(C1 * Ts);
C2 = 47e-6;
R2 = 1/(C2 * Ts);
R3 = 4700;
R4 = 1e6;
Rp = 1e6; % max
G = (R4 + R1) / (R3 + Rp + R2);
x1 = 0;
x2 = 0;

for n = 1:N
   Vo[n] = (G + 1) * Vi[n] + G * R2 * x2 + x1 * R1
   x1 = 2 * (
    
end

% Waveform
plot(t,x);
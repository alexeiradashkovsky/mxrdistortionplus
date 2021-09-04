clc;clear; close all;
Fs = 44100;
Ts = 1/Fs;
f = 1000;
t = [0:Ts:0.01].';

Vi = 0.1* sin(2*pi*f*t);


distVo = distortion_stage(Vi, Ts, 0);
Vo = clipping_stage(distVo, Ts);


% Waveform
subplot(3,3,2);
plot(t,Vi);
title('Effect Vi');

subplot(3,3,4);
plot(t, distVo);
title('Distortion stage');
subplot(3,3,5);
[H,F] = freqz(distVo,1,4096,Fs);
plot(F , 20*log10(abs(H)));
title('Distortion stage freq response');

subplot(3,3,6);
semilogx(F , 20*log10(abs(H)));
title('Distortion stage freq response');


subplot(3,3,7);
plot(t, Vo);
title('Clipping stage');
subplot(3,3,8);
[H2,F2] = freqz(Vo,1,4096,Fs);
plot(F2 , 20*log10(abs(H2)));
title('Clipping stage freq response');

subplot(3,3,9);
semilogx(F2 , 20*log10(abs(H2)));
title('Clipping stage freq response');
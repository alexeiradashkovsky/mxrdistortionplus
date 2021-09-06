# Distortion Pedal Using JUCE

Thanks for lassandroan for the pedal design https://github.com/lassandroan/juce-pedal-demo

![Pedal Image](./pedal_image)

## Description


Using circute analyze of https://www.electrosmash.com/mxr-distortion-plus-analysis  

## Calculations

### Calculation of the Distortion Section
![Distortion Section](./Research/final.png)
### Calculation of the Clipping Section
![Clipping Section](./Research/final_clipping.png)

## Spice Simualtion
### spice_simulation_distortion_pot_min
### spice_simulation_distortion_pot_max
![signal_max](./Research/spice_plot.PNG)
#### Distortion FFT
![fft_distortion_max](./Research/fft_distortion_max.PNG)
#### Out FFT
![fft_out_max](./Research/fft_final_max.PNG)
## Matlab Simulation
### matlab_simulation_distortion_pot_min
![Pot Min](./Research/matlab_simulation_distortion_pot_min.png)  
### matlab_simulation_distortion_pot_max
![Pot Max](./Research/matlab_simulation_distortion_pot_max.png)
## License
[MIT License](https://opensource.org/licenses/MIT)
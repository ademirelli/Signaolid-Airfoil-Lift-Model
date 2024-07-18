# Lift Model on Signaloid Platform

This repository contains a simple C program to model the lift generation of an airfoil based on the Bernoulli equation. The model includes wind speed as calculated by a Pitot tube and parameters such as ambient temperature, humidity, and elevation to determine air density.

## Assumptions

- Air density is calculated using the Magnus formula.
- Dynamic pressure is calculated using the velocity and air density.
- Adjustments are made for elevation.
- Measurement uncertainties are introduced using normal distributions.

## Parameters and Uncertainties

- **Pressure Upper Mean**: 101325 Pa (Stddev: 100 Pa)
- **Pressure Lower Mean**: 100000 Pa (Stddev: 100 Pa)
- **Temperature Mean**: 15 °C (Stddev: 2 °C)
- **Humidity Mean**: 50% (Stddev: 5%)
- **Velocity Mean**: 50 m/s (Stddev: 2 m/s)

## Instructions

1. Clone this repository.
2. Open the Signaloid Cloud Developer Platform.
3. Follow the instructions in the Signaloid documentation to upload and run the `lift_model.c` file.
4. Use the platform’s functionality to inject the distributions for uncertain parameters.

## References

- [Signaloid Documentation](https://docs.signaloid.io)
- [Example Repository: General](https://github.com/signaloid/Signaloid-Demo-General)
- [Example Repository: Metall](https://github.com/signaloid/Signaloid-Demo-Metall) 

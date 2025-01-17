#include <stdio.h>
#include <math.h>
#include <uxhw.h>

#define GRAVITY 9.81
#define R 287.05

double calculate_density(double temperature, double pressure, double humidity) {
    double e_s = 6.1094 * exp((17.625 * temperature) / (243.04 + temperature));
    double e = humidity * e_s / 100;
    double density = (pressure - e) / (R * (temperature + 273.15)) + e / (461.5 * (temperature + 273.15));
    return density;
}

double calculate_dynamic_pressure(double density, double velocity) {
    return 0.5 * density * velocity * velocity;
}

double calculate_lift(double pressure_upper, double pressure_lower, double area) {
    return (pressure_upper - pressure_lower) * area;
}

void loadInputs(double *pressure_upper, double *pressure_lower, double *temperature, double *humidity, double *velocity) {
    // Example parameters with uncertainties
    double pressure_upper_mean = 101325;
    double pressure_upper_std = 100;
    double pressure_lower_mean = 100000;
    double pressure_lower_std = 100;
    double temperature_mean = 15;
    double temperature_std = 2;
    double humidity_mean = 50;
    double humidity_std = 5;
    double velocity_mean = 50;
    double velocity_std = 2;

    // Generate random samples for each parameter using Signaloid API
    *pressure_upper = UxHwDoubleGaussDist(pressure_upper_mean, pressure_upper_std);
    *pressure_lower = UxHwDoubleGaussDist(pressure_lower_mean, pressure_lower_std);
    *temperature = UxHwDoubleGaussDist(temperature_mean, temperature_std);
    *humidity = UxHwDoubleGaussDist(humidity_mean, humidity_std);
    *velocity = UxHwDoubleGaussDist(velocity_mean, velocity_std);
}

int main() {
    double pressure_upper, pressure_lower, temperature, humidity, velocity;

    loadInputs(&pressure_upper, &pressure_lower, &temperature, &humidity, &velocity);

    // Debug prints to check values
    printf("Generated Values:\n");
    printf("Pressure Upper: %f\n", pressure_upper);
    printf("Pressure Lower: %f\n", pressure_lower);
    printf("Temperature: %f\n", temperature);
    printf("Humidity: %f\n", humidity);
    printf("Velocity: %f\n", velocity);

    // Adjust pressure for elevation
    double elevation = 0;
    pressure_upper -= 12 * elevation / 100;
    pressure_lower -= 12 * elevation / 100;

    // Calculate air density
    double pressure_mean = (pressure_upper + pressure_lower) / 2;
    double density = calculate_density(temperature, pressure_mean, humidity);
    printf("Density: %.2f kg/m^3\n", density);

    // Calculate dynamic pressure
    double dynamic_pressure = calculate_dynamic_pressure(density, velocity);
    printf("Dynamic Pressure: %.2f Pa\n", dynamic_pressure);

    // Adjust pressures with dynamic pressure
    double adjusted_pressure_upper = pressure_upper - dynamic_pressure;
    double adjusted_pressure_lower = pressure_lower + dynamic_pressure;
    printf("Adjusted Pressure Upper: %.2f Pa\n", adjusted_pressure_upper);
    printf("Adjusted Pressure Lower: %.2f Pa\n", adjusted_pressure_lower);

    // Calculate lift using the correct pressure difference
    double area = 10.0;
    double lift = calculate_lift(adjusted_pressure_lower, adjusted_pressure_upper, area);
    printf("Calculated Lift: %.2f N\n", lift);

    return 0;
} 

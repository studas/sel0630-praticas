import matplotlib.pyplot as plt
from gpiozero import LightSensor
import time

# Initialize the LightSensor
ldr = LightSensor(4)

# Lists to store time and LDR values
times = []
values = []

# Create a figure and axis for plotting
plt.ion()  # Enable interactive mode
fig, ax = plt.subplots()
line, = ax.plot(times, values, 'b-')
ax.set_title('Real-time LDR Sensor Reading')
ax.set_xlabel('Time (s)')
ax.set_ylabel('LDR Value')
ax.set_ylim(0, 1)

# Record the start time
start_time = time.time()

while True:
    try:
        current_time = time.time() - start_time
        ldr_value = ldr.value

        times.append(current_time)
        values.append(ldr_value)

        line.set_xdata(times)
        line.set_ydata(values)

        ax.set_xlim(0, current_time + 1)
        ax.relim()
        ax.autoscale_view()

        plt.draw()
        plt.pause(0.01)  # Pause to allow the plot to update

    except KeyboardInterrupt:
        print("Interrupted by user")
        break

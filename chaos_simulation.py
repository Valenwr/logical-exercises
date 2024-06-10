import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import solve_ivp
from matplotlib.animation import FuncAnimation

# Parameters for the double pendulum
m1 = 1.0  # mass of the first pendulum
m2 = 1.0  # mass of the second pendulum
L1 = 1.0  # length of the first pendulum
L2 = 1.0  # length of the second pendulum
g = 9.81  # acceleration due to gravity

# External force parameters
F0 = 0.5  # amplitude of the external force
omega = 1.0  # frequency of the external force

def equations(t, y):
    theta1, z1, theta2, z2 = y
    delta = theta2 - theta1
    
    M = m1 + m2
    m21 = m2 / M
    L1L2 = L1 / L2
    
    den1 = (m1 + m2) * L1 - m2 * L1 * np.cos(delta) * np.cos(delta)
    den2 = (L2 / L1) * den1
    
    dydt = np.zeros_like(y)
    
    dydt[0] = z1
    dydt[1] = (m2 * L1 * z1 * z1 * np.sin(delta) * np.cos(delta) +
               m2 * g * np.sin(theta2) * np.cos(delta) +
               m2 * L2 * z2 * z2 * np.sin(delta) -
               M * g * np.sin(theta1) + F0 * np.cos(omega * t)) / den1
    
    dydt[2] = z2
    dydt[3] = (- m2 * L2 * z2 * z2 * np.sin(delta) * np.cos(delta) +
               M * (g * np.sin(theta1) * np.cos(delta) - L1 * z1 * z1 * np.sin(delta) - g * np.sin(theta2)) + 
               F0 * np.cos(omega * t) * np.cos(delta)) / den2
    
    return dydt

# Initial conditions: [theta1, z1, theta2, z2]
y0 = [np.pi / 2, 0, np.pi / 2, 0]

# Time span for the simulation
t_span = (0, 20)
t_eval = np.linspace(t_span[0], t_span[1], 1000)

# Solve the differential equations
sol = solve_ivp(equations, t_span, y0, t_eval=t_eval)

# Extract the solutions
theta1, theta2 = sol.y[0], sol.y[2]

# Convert to Cartesian coordinates for plotting
x1 = L1 * np.sin(theta1)
y1 = -L1 * np.cos(theta1)
x2 = x1 + L2 * np.sin(theta2)
y2 = y1 - L2 * np.cos(theta2)

# Set up the figure and axis
fig, ax = plt.subplots()
ax.set_xlim(-2, 2)
ax.set_ylim(-2, 2)

# Initialize the lines for the pendulums
line1, = ax.plot([], [], 'o-', lw=2)
line2, = ax.plot([], [], 'o-', lw=2)

# Function to initialize the animation
def init():
    line1.set_data([], [])
    line2.set_data([], [])
    return line1, line2

# Function to update the animation at each frame
def update(frame):
    line1.set_data([0, x1[frame]], [0, y1[frame]])
    line2.set_data([x1[frame], x2[frame]], [y1[frame], y2[frame]])
    return line1, line2

# Create the animation
ani = FuncAnimation(fig, update, frames=range(len(t_eval)),
                    init_func=init, blit=True, interval=20)

# Show the animation
plt.show()

import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_excel(r"C:\Users\vikto\OneDrive - Aalborg Universitet\Comtek1-Little-Boy\P1\Figures\ultrasound_sensor\ultrasound_data.xlsx")

plt.plot(df["Elapsed Time"], df["Distance"], color = "blue", label = "Ultrasonic sensor") 
plt.axline((2.329, 0), (2.329, 60), color = "red", linestyle = "dashed", label = "Person")
plt.axline((5.964, 0), (5.964, 60), linestyle = "dashed", color = "red")
plt.axline((9.272, 0), (9.272, 60), linestyle = "dashed", color = "red",)
plt.axline((12.46, 0), (12.46, 60), linestyle = "dashed", color = "red")
plt.axline((15.574, 0), (15.574, 60), linestyle = "dashed", color = "red")
plt.axline((18.823, 0), (18.823, 60), linestyle = "dashed", color = "red")
plt.axline((21.946, 0), (21.946, 60), linestyle = "dashed", color = "red")
plt.axline((25.144, 0), (25.144, 60), linestyle = "dashed", color = "red")
plt.axline((0, 90), (30, 90), linestyle = "dashed", color = "black", label = "Lower limit, 90 cm")
plt.title('Distance as a function of time for Ultrasonic Sensor HC-SR04')
plt.xlabel('Time (sec)')
plt.ylabel('Distance (cm)')
plt.legend(loc="lower right")
plt.show()         

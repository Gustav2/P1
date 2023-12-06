import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_excel(r"C:\Users\vikto\OneDrive - Aalborg Universitet\Comtek1-Little-Boy\P1\Figures\IR_sensor\IR_data.xlsx")

plt.plot(df["Elapsed Time"], df["Distance"], color = "blue", label = "IR sensor") 
plt.axline((6.274, 0), (6.274, 60), color = "red", linestyle = "dashed", label = "Person")
plt.axline((9.656, 0), (9.656, 60), linestyle = "dashed", color = "red")
plt.axline((13.182, 0), (13.182, 60), linestyle = "dashed", color = "red",)
plt.axline((16.786, 0), (16.786, 60), linestyle = "dashed", color = "red")
plt.axline((20.246, 0), (20.246, 60), linestyle = "dashed", color = "red")
plt.axline((23.573, 0), (23.573, 60), linestyle = "dashed", color = "red")
plt.axline((27.621, 0), (27.621, 60), linestyle = "dashed", color = "red")
plt.axline((30.085, 0), (30.085, 60), linestyle = "dashed", color = "red")
plt.axline((0, 20), (30, 20), linestyle = "dashed", color = "black", label = "Lower limit, 20 cm")
plt.title('Distance as a function of time for IR Sensor SHARP 0A41SK')
plt.xlabel('Time (sec)')
plt.ylabel('Distance (cm)')
plt.legend(loc="lower right")
plt.show()         

import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_excel(r"C:\Users\vikto\OneDrive - Aalborg Universitet\Comtek1-Little-Boy\P1\Figures\force_sensor\force_data.xlsx")

plt.plot(df["Elapsed Time"], df["Pressure"], color = "blue", label = "Force sensor") 
plt.axline((3.61, 0), (3.61, 60), color = "red", linestyle = "dashed", label = "Door open")
plt.axline((11.04, 0), (11.04, 60), linestyle = "dashed", color = "red")
plt.axline((18.06, 0), (18.06, 60), linestyle = "dashed", color = "red",)
plt.axline((24.28, 0), (24.28, 60), linestyle = "dashed", color = "red")
plt.axline((30.68, 0), (30.68, 60), linestyle = "dashed", color = "red")
plt.axline((38.02, 0), (38.02, 60), linestyle = "dashed", color = "red")
plt.axline((45.61, 0), (45.61, 60), linestyle = "dashed", color = "red")
plt.axline((0, 18), (30, 18), linestyle = "dashed", color = "black", label = "Lower limit, 18 cm")
plt.title('Pressure as a function of time for Force Sensor FSR-402')
plt.xlabel('Time (sec)')
plt.ylabel('Pressure (analogue value)')
plt.legend(loc="lower right")
plt.show()

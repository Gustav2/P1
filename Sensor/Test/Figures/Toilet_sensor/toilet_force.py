import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_excel(r"toilet_force.xlsx")

plt.plot(df["Elapsed Time"], df["Pressure"], color = "blue", label = "Force sensor") 
plt.axline((0.08, 0), (0.08, 60), color = "red", linestyle = "dashed", label = "Door open")
plt.axline((5.33, 0), (5.33, 60), linestyle = "dashed", color = "red")
plt.axline((9.61, 0), (9.61, 60), linestyle = "dashed", color = "red",)
plt.axline((13.34, 0), (13.34, 60), linestyle = "dashed", color = "red")
plt.axline((16.17, 0), (16.17, 60), linestyle = "dashed", color = "red")
plt.axline((19.73, 0), (19.73, 60), linestyle = "dashed", color = "red")
plt.axline((22.89, 0), (22.89, 60), linestyle = "dashed", color = "red")
plt.axline((26.43, 0), (26.43, 60), linestyle = "dashed", color = "red")
plt.axline((29.85, 0), (29.85, 60), linestyle = "dashed", color = "red")
plt.title('Pressure by toiletseat as a function of time for Force Sensor FSR-402')
plt.ylim(200,1400)
plt.xlabel('Time (sec)')
plt.ylabel('Pressure (analogue value)')
plt.legend(loc="lower right")
plt.show()
import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_excel(r"C:\Users\magnu\Documents\COMTEK\Programmering\P1\Sensor\Test\Figures\PIR_sensor\PIR_data.xlsx")

plt.gca().set_aspect('equal', adjustable='box')
plt.plot(df["Elapsed Time"], df["Detection"], color = "blue", label = "IR sensor") 
plt.axline((2.199, 0), (2.199, 1), color = "red", linestyle = "dashed", label = "Person")
plt.axline((5.375, 0), (5.375, 1), linestyle = "dashed", color = "red")
plt.axline((8.619, 0), (8.619, 1), linestyle = "dashed", color = "red")
plt.axline((19.405, 0), (19.405, 1), linestyle = "dashed", color = "red")
plt.axline((22.558, 0), (22.558, 1), linestyle = "dashed", color = "red")
plt.axline((25.967, 0), (25.967, 1), linestyle = "dashed", color = "red")
plt.axline((30.123, 0), (30.123, 1), linestyle = "dashed", color = "red")
plt.axline((33.374, 0), (33.374, 1), linestyle = "dashed", color = "red")

plt.margins(y=0.5)

plt.title('Detection of person by PIR Sensor HC-SR501')
plt.xlabel('Time (sec)')
plt.ylabel('Person')
plt.legend(loc="lower right")
plt.show()         

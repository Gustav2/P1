import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_excel(r".\Test_laser_data.xlsx")

plt.plot(df["Elapsed Time"], df["Detection"], color = "blue", label = "Laser Door Dectection") 
plt.axline((2.32, 3000), (2.32, 0), color = "red", linestyle = "dashed", label = "Person")
plt.axline((5.78, 3000), (5.78, 0), linestyle = "dashed", color = "red")
plt.axline((9.01, 3000), (9.01, 0), linestyle = "dashed", color = "red")
plt.axline((11.96, 3000), (11.96, 0), linestyle = "dashed", color = "red")
plt.axline((18.26, 3000), (18.26, 0), linestyle = "dashed", color = "red")
plt.axline((22.07, 3000), (22.07, 0), linestyle = "dashed", color = "red")
plt.axline((25.24, 3000), (25.24, 0), linestyle = "dashed", color = "red")
plt.axline((29.21, 3000), (29.21, 0), linestyle = "dashed", color = "red")
plt.ylim(0,3000)

plt.margins(y=0.5)

plt.title('Detection of person by Laser')
plt.xlabel('Time (sec)')
plt.ylabel('Analog Value')
plt.legend(loc="lower right")
plt.show()
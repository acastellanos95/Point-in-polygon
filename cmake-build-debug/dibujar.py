import matplotlib.pyplot as plt
from matplotlib.patches import Polygon
import numpy as np
import ast

poligonos = []

fPoligono = open("polygon_tot.dat", "r")
for x in fPoligono:
    line = x.split()
    id = ast.literal_eval(line[0])
    numberPoints = ast.literal_eval(line[1])
    points = []
    for i in range(0, numberPoints):
        x = ast.literal_eval(line[(i*2)+2])
        y = ast.literal_eval(line[(i*2)+2 + 1])
        points.append([x,y])
    poligonos.append(points)
fPoligono.close()

# print(poligonos)

puntos = []

# fPuntos = open("puntos.data", "r")
# for x in fPuntos:
#     line = x.split()
#     x = ast.literal_eval(line[0])
#     y = ast.literal_eval(line[1])
#     point = [x,y]
#     puntos.append(point)
# fPuntos.close()

# print(puntos)
ax = plt.axes()

# puntos = np.array(puntos)
# x, y = puntos.T
# plt.scatter(x, y, marker='.', lw=0.05, alpha=0.5)

for poligono in poligonos:
    ax.add_patch(Polygon(poligono, facecolor = np.random.rand(3,),zorder=0))

plt.axis('scaled')
plt.show()
plt.savefig("poligono_prueba_doctor.png")
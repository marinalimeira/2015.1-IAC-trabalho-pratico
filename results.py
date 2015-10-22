import numpy as np
import matplotlib.pyplot as plt

text_file = open("result.txt")

new_contents = []

for line in text_file:
    if not line.strip():
        continue
    else:
        if not line.startswith("%CPU"):
            new_contents.append(line.strip().replace("     ", " ").split(" "))

cpu = []
mem = []

for data in new_contents:
    cpu.append(data[0])
    mem.append(data[1])

mem[0] =  "0.0"
plt.ylabel('Memoria (kB)')
plt.xlabel('Tempo')
# para gerar gráficos de CPU
#plt.ylabel('CPU')
#plt.plot(cpu)
plt.plot(mem)
plt.show()


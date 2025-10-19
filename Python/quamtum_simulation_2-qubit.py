from qiskit import QuantumCircuit, transpile
from qiskit_aer import Aer, AerSimulator
from qiskit_aer.primitives import Sampler as AerSampler
from qiskit.visualization import plot_histogram
import matplotlib.pyplot as plt

# 2 qubits => search space of size N=4
n = 2


# Initialize Superposition (Hadamards on all qubits)
qc = QuantumCircuit(n)
qc.h([0, 1])
qc.cz(0, 1)



# Diffusion Operator (Inversion About Mean)
qc.h([0, 1])
qc.x([0, 1])
qc.h(1)
qc.cx(0, 1)
qc.h(1)
qc.x([0, 1])
qc.h([0, 1])
qc.measure_all()



#Execution
# Use the qasm simulator
sim = AerSimulator()
compiled_circuit = transpile(qc, sim)
result = sim.run(compiled_circuit, shots=1024).result()
counts = result.get_counts()

# Run the circuit 1000 times
print("Results:", counts)
plot_histogram(counts)
plt.show()



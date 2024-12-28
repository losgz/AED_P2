import matplotlib.pyplot as plt
import pandas as pd

# Read from the CSV file
df_csv = pd.read_csv("results.csv")


# Group by cases for connecting lines
best_case_csv = df_csv[df_csv["Case"] == "Best"].sort_values("Vertices")
worst_case_csv = df_csv[df_csv["Case"] == "Worst"].sort_values("Vertices")
random_case_csv = df_csv[df_csv["Case"] == "Random"].sort_values("Vertices")

# Create the plot
plt.figure(figsize=(12, 8))

# Plot the scatter points for each case
plt.scatter(
    best_case_csv["Vertices"],
    best_case_csv["Ops"],
    color="green",
    label="Melhor caso",
    alpha=0.7,
)
plt.scatter(
    worst_case_csv["Vertices"],
    worst_case_csv["Ops"],
    color="red",
    label="Pior Caso",
    alpha=0.7,
)
plt.scatter(
    random_case_csv["Vertices"],
    random_case_csv["Ops"],
    color="blue",
    label="Caso Médio",
    alpha=0.7,
)

# Connect the points with lines for each case
plt.plot(
    best_case_csv["Vertices"],
    best_case_csv["Ops"],
    color="green",
    linestyle="--",
    alpha=0.7,
)
plt.plot(
    worst_case_csv["Vertices"],
    worst_case_csv["Ops"],
    color="red",
    linestyle="--",
    alpha=0.7,
)
plt.plot(
    random_case_csv["Vertices"],
    random_case_csv["Ops"],
    color="blue",
    linestyle="--",
    alpha=0.7,
)

# Labels and title
plt.title("Número de operações vs Número de vertices", fontsize=14)
plt.xlabel("Número de vertices", fontsize=14)
plt.ylabel("Número de operações", fontsize=14)
plt.grid(alpha=0.3)
plt.legend()
plt.show()

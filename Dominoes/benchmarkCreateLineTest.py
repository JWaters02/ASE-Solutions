import matplotlib.pyplot as plt
import pandas as pd

csv_file_path = "benchmarkCreateLineTest.csv"
try:
    data = pd.read_csv(csv_file_path)
    print(data)
    expected_columns = ["testSize", "worstCaseTime", "averageCaseTime"]
    missing_columns = [col for col in expected_columns if col not in data.columns]

    if missing_columns:
        raise ValueError(f"Missing columns: {', '.join(missing_columns)}")

    testSize = data['testSize']
    worstCaseTime = data['worstCaseTime']
    averageCaseTime = data['averageCaseTime']

    worstCaseTime = worstCaseTime / 1000000000
    averageCaseTime = averageCaseTime / 1000000000

    plt.figure(figsize=(10, 6))

    plt.plot(testSize, worstCaseTime, label='Dominoes Worst Case')
    plt.plot(testSize, averageCaseTime, label='Dominoes Average Case')

    plt.xlabel('Test Size')
    plt.ylabel('Time (s)')
    plt.legend()

    plt.title('Dominoes Time Comparison (Only for Creating the line)')
    plt.grid(True)
    plt.show()

except FileNotFoundError:
    print(f"CSV file not found at path: {csv_file_path}")
except Exception as e:
    print(f"An error occurred: {e}")

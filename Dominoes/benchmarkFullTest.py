import matplotlib.pyplot as plt
import pandas as pd

csv_file_path = "benchmarkFullTest.csv"
try:
    data = pd.read_csv(csv_file_path)
    print(data)
    expected_columns = ["testSize", "worstCaseTime", "averageCaseTime", "convolutedTime"]
    missing_columns = [col for col in expected_columns if col not in data.columns]

    if missing_columns:
        raise ValueError(f"Missing columns: {', '.join(missing_columns)}")

    testSize = data['testSize']
    worstCaseTime = data['worstCaseTime']
    averageCaseTime = data['averageCaseTime']
    convolutedTime = data['convolutedTime']

    worstCaseTime = worstCaseTime / 1000000000
    averageCaseTime = averageCaseTime / 1000000000
    convolutedTime = convolutedTime / 1000000000

    plt.figure(figsize=(10, 6))

    plt.plot(testSize, worstCaseTime, label='Dominoes Worst Case')
    plt.plot(testSize, averageCaseTime, label='Dominoes Average Case')
    plt.plot(testSize, convolutedTime, label='Dominoes Convoluted')

    plt.xlabel('Test Size')
    plt.ylabel('Time (s)')
    plt.legend()

    plt.title('Dominoes Time Comparison (Full test)')
    plt.grid(True)
    plt.show()

except FileNotFoundError:
    print(f"CSV file not found at path: {csv_file_path}")
except Exception as e:
    print(f"An error occurred: {e}")

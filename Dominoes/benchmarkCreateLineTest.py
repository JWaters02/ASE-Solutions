import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import matplotlib.ticker as ticker

csv_file_path = "benchmarkCreateLineTest.csv"
try:
    data = pd.read_csv(csv_file_path)
    print(data)
    expected_columns = ["testSize", "worstCaseTime", "averageCaseTime"]
    missing_columns = [col for col in expected_columns if col not in data.columns]

    if missing_columns:
        raise ValueError(f"Missing columns: {', '.join(missing_columns)}")

    data['testSize'] = data['testSize'].replace('K', 'e3', regex=True).replace('M', 'e6', regex=True).astype(float)

    testSize = data['testSize']
    worstCaseTime = data['worstCaseTime'] / 1e9
    averageCaseTime = data['averageCaseTime'] / 1e9

    plt.figure(figsize=(10, 6))

    # plt.yscale('log')
    # plt.xscale('log')

    plt.plot(testSize, worstCaseTime, label='Dominoes Worst Case')
    plt.plot(testSize, averageCaseTime, label='Dominoes Average Case')

    max_test_size = max(testSize)
    theoretical_test_sizes = np.linspace(1, max_test_size, num=1000)
    plt.plot(theoretical_test_sizes, np.log2(theoretical_test_sizes) / 1e1, label='Theoretical O(log n)', linestyle='--')
    plt.plot(theoretical_test_sizes, theoretical_test_sizes / 1e5, label='Theoretical O(n)', linestyle='--')
    # plt.plot(theoretical_test_sizes, (theoretical_test_sizes * np.log2(theoretical_test_sizes)) / 1e5, label='Theoretical O(n log n)', linestyle='--')
    # plt.plot(theoretical_test_sizes, (theoretical_test_sizes * (np.log2(theoretical_test_sizes) ** 2)) / 1e6, label='Theoretical O(n log^2 n)', linestyle='--')

    plt.xlabel('Number of input dominoes')
    plt.ylabel('Time (s)')

    # Set axis scales and limits
    plt.xlim(left=1e1, right=max_test_size)

    # Format the y-axis to show time in full integer seconds
    plt.gca().yaxis.set_major_formatter(ticker.FuncFormatter(lambda y, _: '{:g}'.format(y)))

    plt.legend()
    plt.title('Dominoes Time Comparison (Only for Creating the line)')
    plt.grid(True)
    plt.show()

except FileNotFoundError:
    print(f"CSV file not found at path: {csv_file_path}")
except Exception as e:
    print(f"An error occurred: {e}")

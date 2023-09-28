import matplotlib.pyplot as plt
import pandas as pd

csv_file_path = "mapTimes.csv"
try:
    data = pd.read_csv(csv_file_path)
    print(data)
    expected_columns = ["size", "mapTime", "unorderedMapTime", "bstTime"]
    missing_columns = [col for col in expected_columns if col not in data.columns]

    if missing_columns:
        raise ValueError(f"Missing columns: {', '.join(missing_columns)}")

    mapSize = data['size']
    mapTime = data['mapTime']
    unordered_mapTime = data['unorderedMapTime']
    bstTime = data['bstTime']

    plt.figure(figsize=(10, 6))

    plt.plot(mapSize, mapTime, label='std::map')
    plt.plot(mapSize, unordered_mapTime, label='std::unordered_map')
    plt.plot(mapSize, bstTime, label='binary search tree')

    plt.xlabel('Map Size')
    plt.ylabel('Time (ms)')
    plt.legend()

    plt.title('Map Time Comparison')
    plt.grid(True)
    plt.show()

except FileNotFoundError:
    print(f"CSV file not found at path: {csv_file_path}")
except Exception as e:
    print(f"An error occurred: {e}")

import random
import sys

def compute_disorder(arr):
    mistakes = 0
    total_pairs = 0
    n = len(arr)
    
    for i in range(n):
        for j in range(i + 1, n):
            total_pairs += 1
            if arr[i] > arr[j]:
                mistakes += 1
                
    if total_pairs == 0:
        return 0.0
    return (mistakes / total_pairs) * 100.0

def main():
    # 1. Initialize a perfectly sorted stack of 500 numbers
    arr = list(range(1, 501))
    current_disorder = 0.0
    
    # 2. Target window: roughly 20% disorder (19.5% to 20.5%)
    while not (19.5 <= current_disorder <= 20.5):
        # Pick two random indexes and swap them
        i, j = random.sample(range(500), 2)
        arr[i], arr[j] = arr[j], arr[i]
        
        current_disorder = compute_disorder(arr)
        
        # If we accidentally pushed the disorder way past our target, undo the swap
        if current_disorder > 20.5:
            arr[i], arr[j] = arr[j], arr[i]
            current_disorder = compute_disorder(arr)
            
    # 3. Print verification stats to stderr so it won't break bash pipelines
    print(f"[Generator Logs] Exact Dataset Disorder Score: {current_disorder:.2f}%", file=sys.stderr)
    
    # 4. Print the clean numbers space-separated to stdout
    print(" ".join(map(str, arr)))

if __name__ == "__main__":
    main()
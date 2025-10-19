def parserS(S):
    if S == 'S':
        return ["Ab"]  # Return as list
    return []

def parserA1(A):
    if A == 'A':
        return ["aAb"]
    return []

def parserA2(A):
    if A == 'A':
        return ['E']
    return []

def grammar(terminal, start, depth=3):
    if depth > 3:  # Add stopping condition
        return start
        
    print(f"Depth {depth}: {start}")
    
    new_results = []
    for item in start:
        if 'A' in item:  # Only process if contains non-terminal 'A'
            for alphabet in terminal:
                new_results.extend(parserA1(alphabet))
                new_results.extend(parserA2(alphabet))
    
    if new_results:
        start.extend(new_results)
        return grammar(terminal, start, depth + 1)
    
    return start

def main():
    parsed_result = parserS('S')
    result = grammar(['a', 'b'], parsed_result)
    print(f"Final result: {result}")

if __name__ == "__main__":
    main()
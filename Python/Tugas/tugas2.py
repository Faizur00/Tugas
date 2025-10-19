def noparam_noreturn():
    print("hello world")

def param_noreturn(x: int):
    squared = x*x
    print (squared)

def noparam_return():
    print ("returning -1")
    return -1

def param_return(x: int):
    print(f"returning {x*x}")
    return x*x

def main():
    noparam_noreturn()
    param_noreturn(2)
    noparam_return()
    param_return(4)

if __name__ == "__main__":
    main()
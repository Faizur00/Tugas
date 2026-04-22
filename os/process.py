import os
import time
from multiprocessing import Process


def worker():
    time.sleep(2)


if __name__ == "__main__":
    print(f"parent process is running, PID = {os.getpid()}")

    p = Process(target=worker)
    p.start()
    p.join()

    print("Parent process finished")
    
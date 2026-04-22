import os
import time
from multiprocessing import Process

from util import fetch_url


def normal_process(num):
    print(f"\nStart running child proces number{num} for type: CPU,PPID: {os.getppid()} PID: {os.getpid()}")
    time.sleep(30)
    print(f"Finished running child process for type: CPU,PPID: {os.getppid()} PID: {os.getpid()}")


def io_process(num):
    print(f"\nStart running child proces number{num} for type: I/O,PPID: {os.getppid()} PID: {os.getpid()}")
    ctime = time.time()
    fetch_url("quantum")
    ttime = time.time() - ctime
    print(f"Finished running child process for type: I/O,PPID: {os.getppid()} PID: {os.getpid()}. time: {ttime}")
    time.sleep(30)


if __name__ == "__main__":
    print(f"parent process is running,PPID: {os.getppid()} PID = {os.getpid()}")
    print('\n\n')

    num_of_process = 2
    processes = []

    for i in range(num_of_process):
        p_cpu = Process(target=normal_process, args=(i,))
        p_io = Process(target=io_process, args=(i,))
        processes.append(p_cpu)
        processes.append(p_io)
        p_cpu.start()
        p_io.start()

    for p in processes:
        p.join()

    print("Finished Running")

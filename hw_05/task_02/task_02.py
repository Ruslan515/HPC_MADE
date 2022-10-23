from mpi4py import MPI
import numpy as np
import matplotlib.pyplot as plt
import argparse
import os

PLOT_DIR = "./result_plot"

np.random.seed(42)

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
proc_cnt = comm.Get_size()

parser = argparse.ArgumentParser()
parser.add_argument("law", type=int)
parser.add_argument("size", type=int)
parser.add_argument("steps", type=int)
parser.add_argument("plot_dir", type=str)
parser.add_argument("--period", action="store_true")
parser.add_argument("--plot", action="store_true")
args = parser.parse_args()

LAW = args.law
SIZE_ORDER = args.size
STEPS = args.steps
if args.period:
    PERIOD = True
else:
    PERIOD = False

law_array = np.array(
    [int(_) for _ in np.binary_repr(LAW, 8)],
    dtype=np.int8
)

u = np.array([[4], [2], [1]])


def step(x, law_array):
    y = np.vstack((np.roll(x, 1), x, np.roll(x, -1))).astype(np.int8)
    z = np.sum(y * u, axis=0).astype(np.int8)
    res = law_array[7 - z]
    if not PERIOD:
        if rank == 0:
            res[0] = x[0]
        elif rank == proc_cnt - 1:
            res[-1] = x[-1]
    return res


def send(arr):
    if rank == 0:
        comm.send(arr[-1], dest=rank + 1)
        if PERIOD:
            comm.send(arr[0], dest=proc_cnt - 1)
            arr = np.insert(arr, 0, comm.recv(source=proc_cnt - 1))
        arr = np.append(arr, comm.recv(source=rank + 1))
    elif rank == proc_cnt - 1:
        if PERIOD:
            comm.send(arr[-1], dest=0)
            arr = np.append(arr, comm.recv(source=0))
        comm.send(arr[0], dest=rank - 1)
        arr = np.insert(arr, 0, comm.recv(source=rank - 1))
    else:
        comm.send(arr[0], dest=rank - 1)
        comm.send(arr[-1], dest=rank + 1)
        arr = np.append(arr, comm.recv(source=rank + 1))
        arr = np.insert(arr, 0, comm.recv(source=rank - 1))
    return arr


def slice(arr):
    if PERIOD:
        arr = arr[1:-1]
    else:
        if rank == 0:
            arr = arr[:-1]
        elif rank == proc_cnt - 1:
            arr = arr[1:]
        else:
            arr = arr[1:-1]        
    return arr


def main():
    k, m = divmod(SIZE_ORDER, proc_cnt)
    start = rank * k + min(rank, m)
    end = (rank + 1) * k + min(rank + 1, m)
    proc_size = end - start
    arr = np.random.randint(2, size=proc_size)

    start = MPI.Wtime()
    hist = np.zeros((STEPS, proc_size), dtype=np.int8)
    hist[0, :] = arr

    for i in range(STEPS - 1):
        arr = send(arr)
        arr = step(arr, law_array)
        arr = slice(arr)
        hist[i + 1, :] = arr

    gathered = comm.gather(hist, root=0)

    if rank == 0:
        res = np.concatenate([a for a in gathered], axis=1)
        if args.plot:
            PLOT_DIR = args.plot_dir
            if not os.path.exists(PLOT_DIR):
                os.makedirs(PLOT_DIR)
            plt.figure(figsize=(10, 10))
            plt.axis("off")
            plt.title(f"{LAW}__{SIZE_ORDER}__{STEPS}")
            plt.imshow(res, cmap=plt.cm.binary)
            file_name = f"{LAW}__{SIZE_ORDER}__{STEPS}.png"
            file_name = os.path.join(PLOT_DIR, file_name)
            plt.savefig(file_name)
        print(f"rank == {rank}. время == {MPI.Wtime() - start}")

    MPI.Finalize()


if __name__ == "__main__":
    main()
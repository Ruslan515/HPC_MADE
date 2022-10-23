from mpi4py import MPI
import random

def main():
    comm = MPI.COMM_WORLD
    rank = comm.Get_rank()
    size = comm.Get_size()
    list_to_visit_process = list(list(range(1, size)))
    name_process = "process_" + str(rank)

    if rank == 0:
        list_process = [rank]
        destination = random.choice(list_to_visit_process)
        message = name_process
        comm.ssend((message, list_process), dest=destination)
    else:
        message, list_process = comm.recv()
        message += ' ' + name_process
        list_process.append(rank)
        list_to_visit_process = [r for r in list_to_visit_process if r not in list_process]
        if list_to_visit_process:
            destination = random.choice(list_to_visit_process)
            comm.ssend((message, list_process), dest=destination)
        else:
            print(message)

    MPI.Finalize()

if __name__ == "__main__":
    main()
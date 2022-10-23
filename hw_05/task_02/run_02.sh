mpirun -n 2 python3 task_02.py 110 100 100 $1 --period --plot
mpirun -n 6 python3 task_02.py 10 1000 1000 $1 --period --plot
mpirun -n 8 python3 task_02.py 110 1000 1000 $1 --period --plot
mpirun -n 10 python3 task_02.py 120 1000 1000 $1 --plot
mpirun -n 12 python3 task_02.py 110 2000 2000 $1 --period --plot
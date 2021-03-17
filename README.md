# ft_philosophers


<img width="967" alt="Screenshot 2021-03-17 at 17 16 03" src="https://user-images.githubusercontent.com/73602657/111481924-7a0b0300-8744-11eb-8c80-c6879078ec68.png">

## About

Philosophers is a project of the mandatory part of the cursus.
It's only made in C and the main goal was to understand how threads works in language C and use them to solve a logical problem.
The simulation will stop if all philosophers have eaten enough or if one philosopher die.

- There are three different version of the algorithm :
    - Philo_one is about using threads and mutexs
    - Philo_two is about using threads and semaphores
    - Philo_three is about using processes and semaphores

- Click here for a full [subject][1]

`This project was code for MACOS`

### Building and running the project

1. Download/Clone this repo

        git clone https://github.com/bMicheal42/ft_philosophers.git
2. `cd` into the root directory, then `cd` into philo_x (one, two or three) and run `make`

        cd 42_philosophers/philo_one
        make

3.  run `./philo_x arg1 arg2 arg3 arg4 (arg5)` from the directory philo_x.
    - arg1 is the number of philosopher
    - arg2 is the time to die in ms
    - arg3 is the time to eat in ms
    - arg4 is the time to sleep in ms
    - arg5 (optional) is the number of time each philosopher needs to eat to end the simulation

## Ressources

* [Parallel Computing](https://computing.llnl.gov/tutorials/parallel_comp/)
* [POSIX Threads](https://computing.llnl.gov/tutorials/pthreads/) ([pthread routines](https://computing.llnl.gov/tutorials/pthreads/#AppendixA))
* [Working example](https://timmurphy.org/2010/05/04/pthreads-in-c-a-minimal-working-example/)
* [French tutorial](https://franckh.developpez.com/tutoriels/posix/pthreads/)
* [Semaphores in C](http://greenteapress.com/thinkos/html/thinkos012.html)
* [Semaphores example in French](http://jean-luc.massat.perso.luminy.univ-amu.fr/ens/docs/thread-sem.html)
* [fork() example](https://timmurphy.org/2014/04/26/using-fork-in-cc-a-minimum-working-example/)
* [fork() multiple childs](https://stackoverflow.com/questions/876605/multiple-child-process)
* [Semaphore when programs end](https://stackoverflow.com/questions/9537068/sem-close-vs-sem-unlink-when-process-terminates)

[1]: https://github.com/bMicheal42/ft_philosophers/blob/master/philos.pdf

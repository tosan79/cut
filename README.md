# cpu usage tracker

- i've tested the program on linux vm (on **google cloud compute engine**) and used there `stress -c 1 -t 10` command before `make test`

- the number of cores is hardcoded in the file **cut.h** and adjusted to the vm i runned the code on
also it is always one bigger than the actual number of cores, so in my case it is 3 = 2 + 1
in most cases it will be 5 = 4 + 1, so please change the value using e.g. `vim cut.h` and replace the value of `NUM_OF_CORES` constant there

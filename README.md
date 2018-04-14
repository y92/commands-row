# Commands Rows
Program which implements commands redirections rows

This program implements redirections such as : command_1 | command_2 | ... | command_n

## Compile

cd src
make

## Execute

If you want to execute a row of k commands, run :

* ./commandRows command_1 arg1_1 arg1_2 ... arg1_n \; command_2 arg2_1 arg2_2 ... arg2_m \; ... \; command_k argk_1 argk_2 ... argk_p

For example, if you want to execute who | sort | wc -l, run :

* ./commandRows who \; sort \; wc -l


## Clean
To remove binary object files, run :

* make clean

To remove binary object files and the executables, run :

* make cleanall
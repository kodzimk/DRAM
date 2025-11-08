<div align="center">
<pre>
RAIDR
---------------------------------------------------
a way to solve refresh problem (energy,power,time) related to dram refreshes
</pre>
</div>

# Short Explanation

This program implemented a whole dram system at level of chips and my dram prototype and architecture(There is whole dimm)<br>
You can add our idea or implementation just refactoring the code<br>
Good luck!<br>

# My Solution

Using bloom filter i am detecting allocated row index and storing<br>
because i dont have electric charge i dont know retention or interval when cell have to be refreshed<br>
So my way is to not refresh the row that all equal '0',not allocated or not used address of memory<br>
"Difference is insane.16 bank and in each bank we have 128 row and column and difference 12 times or even more<br>"
More row size or chip count or even bank count more difference<br>
I am tradeoffing some physical memory like 2-3kb over energy and performance<br>
I would like to implement RAIDR<br>

# Build and Running
Requirement gcc.<br>
In two platforms

```sh
cd src/components
make
cd ../..
```

Then<br>

## Linux

```sh
make
./dram
```

## Windows

```sh
./build.sh
./dram.exe
MUST HAVE: GCC 
```

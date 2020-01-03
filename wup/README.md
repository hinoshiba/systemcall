warming up
===

* Setup the environment C Lang.
* [sources](./src)

---

1. install gcc.
	```
	sudo -E apt install gcc make gdb
	```
2. compile source.
	```
	user@host src $make
	```
3. execute helloworld file.
	```
	user@host src $./helloworld
	Hello, world!
	```
4. execute gdb.
	```
	user@host src $gdb ./helloworld
	(gdb) break main
	(gdb) run
	(gdb) continue #next
	```

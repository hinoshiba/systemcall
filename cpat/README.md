cpat
===

* Target the file I/O. Create a command "cpat" that combines cat and cp.

---

1. exercise 01
	* Do only open and close.
	* [source](./src/01/open.c)
2. exercise 02
	* Add function of stop in the case signal HUP from exercise 01.
	* [source](./src/02/open.c)
	* reference
		* [wikipedia C signal handling](https://en.wikipedia.org/wiki/C_signal_handling)
3. cat.
	* Create cat using read(2) and write(2)
	* [source](./src/03/cat.c)
4. cpat.
	* Add function of write to file.
	* [source](./src/04/cpat.c)
5. use readv(2) and writev(2) at cpat.
6. `...` to be continued.

### index idea memo

* sendfile
* select
	* libev
	* libuv
	* libevent
* sigfd
* mq_overview

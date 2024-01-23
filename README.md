# rl
Going through *Reinforcement Learning - An Introduction* by Sutton and Barto.

Completion is doubtful.

## Quick Start
Move into each folder and run the following to build each script and run it:

```
cd <subfolder>
chmod +x build.sh
./build.sh
./main
```

README's in subfolder may describe other available scripts.

## Reference
Read the excellent book: *Reinforcement Learning - An Introduction* at Sutton's website <http://incompleteideas.net/book/the-book-2nd.html>

Sutton provides all code examples written in LISP.
Here is a convenient curl command to download all of his code:

```shell
wget --recursive --level=1 --no-parent --no-directories  --accept '*.lisp' --directory-prefix=. http://www.incompleteideas.net/book/code/ 
```
# Images author:
* Sheya (go check their artwork out and give it some love, is's amazing! [Twitter](https://twitter.com/Sukuroneko), [weibo](https://weibo.com/kisinSheya), [pixiv](https://www.pixiv.net/en/users/11764388))
# What is it?
This is a simple demonstration of how you can embed any kind of file into a C executable
# How to use it?
1. include [`embed.h`](embed.h) header into your build file (which must be C for now, I will consider adding cli to this. `make_embed.c` is the build file here.), then call `embed_resources` on an array of strings (they must be relative paths to included files)
2. include generated header and acces file data as byte arrays (symbols that can not be C identifiers are replaced with `_`, so `resources/file.png` will become `resources_file_png`).
3. acces file size with `<c_file_name>_size` variables
4. when compiling the final executable, add generared assembly file to a list of sources
5. profit
# How this works?
1. It generates assembly file with a macro that uses `.incbin` directive and exports a symbol and size of included binary file
2. it generates C identifiers from file names
3. It adds assembly macro invocation for each file
4. It imports each file in header using "extern" specifier
5. profit 
# How to build the example?
1. compile the builder (`cc -o make make_embed.c`)
2. run the builder (`./make build`)
3. then you can run the executable with `./make run` or `./embed_test`. you can also run it from different directory using `./make test`.
4. delete build files with `./make clean`
# Support
* platform: Linux 64bit works. did not test on 32bit, but should work. It may work on windows, but i did not test it.
* compiler: gcc works. clang should work, I tested it somewhere in the middle of writing this. other compilers - as long as they support GNU assembler
* language: I added c++ protection (`#ifdef __cplusplus: extern "C" { ...`) but did not test it.
# Should I use headers from this repo in my project?
If you work in production, absolutely no, just steal the idea and re-write it. <br>
If you are coding to have fun, sure, go ahead.
# License
Public Domain

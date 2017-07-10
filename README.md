# tcbot

Directory watching transcode scheduler.

tcbot [input dir] [output dir]

tcbot watches [input dir] for .mkv files. When it sees a .mkv file it calls a batch file called tc.bat with 2 arguments. The path
to the input file and the path to the output file. The output file name is created by appending the incoming file name to the path
to the output directory. If the transcode is successful the file is removed from [input dir]. If the transcode fails, the input file
is moved to [input dir]/Broken.

WARNING IMPORTANT

When dropping files into [input dir] you should use a Move operator instead of a Copy. Move's are atomic within the same file system
on Windows.

Building

I used Microsoft Visual Studio Community 2017 to build.

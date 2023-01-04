# 42_pipex

# Usage
```
$ git clone https://github.com/ak0327/42_pipex
$ cd 42_pipex
```

# Mandatory
## Compile
```
$ make
```

## Operate
```
$ ./pipex infile cmd1 cmd2 outfile
```
It's operate same as
```
$ < infile cmd1 | cmd2 > outfile
```

# Bonus
## Compile
```
$ make bonus
```
##Operate
### Multiple pileline
```
$ ./pipex infile cmd1 cmd2 ... cmdn outfile
```
It's operate same as
```
$ < infile cmd1 | cmd2 |..| cmdn > outfile
```

### Here_doc
```
$ ./pipex here_doc LIMITER cmd1 cmd2 outfile
```
It's operate same as
```
$ cmd1 << LIMITER | cmd2 >> outfile
```


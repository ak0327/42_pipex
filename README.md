# 42_pipex

# Usage
```
$ git clone https://github.com/ak0327/42_pipex
$ cd 42_pipex
```
<br><br>

# Mandatory
## Compile
```shell
$ make
```
<br>

## Operate
```shell
$ ./pipex infile cmd1 cmd2 outfile
```
It's operate same as
```shell
$ < infile cmd1 | cmd2 > outfile
```
<br>
for example ...

```shell
% cat -e infile 
this is test file$
hoge$
huga piyo$
END$
% 
% ./pipex infile "cat -e" "awk '{print \$1}'" /dev/stdout 
this
hoge$
huga
END$
%
```

<br><br>

# Bonus
## Compile
```shell
$ make bonus
```
## Operate
### Multiple pileline
```shell
$ ./pipex infile cmd1 cmd2 ... cmdn outfile
```
It's operate same as
```shell
$ < infile cmd1 | cmd2 |..| cmdn > outfile
```
<br><br>

### Here_doc
```shell
$ ./pipex here_doc LIMITER cmd1 cmd2 outfile
```
It's operate same as
```shell
$ cmd1 << LIMITER | cmd2 >> outfile
```
<br>

for example ...
```shell
% export ARG=42Tokyo
% ./pipex here_doc EOF "cat" "cat -e" /dev/stdout
heredoc> hello $ARG
heredoc> this is heredoc
heredoc> EOF
hello 42Tokyo$
this is heredoc$
%
```

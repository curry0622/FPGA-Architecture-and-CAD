# Source Code

## How to Compile

In this directory, enter the following command. It will generate the executable file in the current directory.

```shell
make
```

If you want to remove it, please enter the following command:

```shell
make clean
```

## How to Run

In this directory, enter the following command:

```shell
./topart [INPUT_FILE] [OUTPUT_FILE]
```

e.g.

The following command will run your code and read [B1.txt](../benchmarks/B1.txt) as input and output the result to **tmp.out**.

```shell
./topart ../benchmarks/B1.txt tmp.out
```

## How to Verify

In this directory, enter the following command, where **[BENCHMARK]** specifies which benchmark to verify.

```shell
make verify b=[BENCHMARK]
```

e.g.

The following command will run your code and verify your output on [B1.txt](../benchmarks/B1.txt).

```shell
make verify b=1
```

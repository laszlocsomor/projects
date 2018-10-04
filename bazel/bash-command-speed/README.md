# Measure Bash command execution speed

## Usage

```
bazel build -c opt //:benchmark
```

## Windows

```
Bash commands (sample size is 1000):
  95th %: 38049 us
  99th %: 67842 us
  99.5th %: 73850 us
  99.9th %: 86580 us
  max: 88058 us
```

## Linux

```
Bash commands (sample size is 1000):
  95th %: 1331 us
  99th %: 1418 us
  99.5th %: 1507 us
  99.9th %: 1648 us
  max: 1725 us
```

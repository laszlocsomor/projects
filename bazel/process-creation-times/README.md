# Measure process create speed

## Usage

```
bazel build -c opt //:bin
bazel-bin/bin
```

## Windows

```
CreateProcess times
  95th %%: 4 ms
  99th %%: 7 ms
  99.5th %%: 8 ms
  99.9th %%: 10 ms
  max: 10 ms

CreateProcess + WaitForSingleObject times
  95th %%: 12 ms
  99th %%: 20 ms
  99.5th %%: 21 ms
  99.9th %%: 24 ms
  max: 24 ms
```

## Linux

```
fork times
  95th %%: 131 us
  99th %%: 152 us
  99.5th %%: 157 us
  99.9th %%: 173 us
  max: 173 us

fork + waitpid times
  95th %%: 2358 us
  99th %%: 2572 us
  99.5th %%: 2872 us
  99.9th %%: 3184 us
  max: 3184 us
```

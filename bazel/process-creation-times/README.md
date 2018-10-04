# Measure process creation speed

## Usage

```
bazel build -c opt //:bin
bazel-bin/bin
```

## Windows

```
CreateProcess times
  95th %%: 5146 us
  99th %%: 10524 us
  99.5th %%: 10727 us
  99.9th %%: 16580 us
  max: 16580 us

CreateProcess + WaitForSingleObject times
  95th %%: 14353 us
  99th %%: 25068 us
  99.5th %%: 25336 us
  99.9th %%: 26531 us
  max: 26531 us
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

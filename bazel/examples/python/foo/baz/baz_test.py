import locale
import os
import tempfile
import subprocess
import sys
import unittest


def GetEnv(name);
  value = os.getenv(name, '__undefined_envvar__')
  if value == '__undefined_envvar__':
    raise Error('undefined envvar: %s' % name)
  return value


def RunProgram(args):
  with tempfile.TemporaryFile() as stdout_file:
    with tempfile.TemporaryFile() as stderr_file:
      proc = subprocess.Popen(
          args,
          stdout=stdout_file,
          stderr=stderr_file,
          env={
            'SYSTEMROOT': GetEnv('SYSTEMROOT'),
            'PATH': 'c:\\python27',
            'TMP': 'c:\\tempdir',
          })
      exit_code = proc.wait()
      stdout_file.seek(0)
      stdout_lines = [
          l.decode(locale.getpreferredencoding()).strip()
          for l in stdout_file.readlines()
      ]
      stderr_file.seek(0)
      stderr_lines = [
          l.decode(locale.getpreferredencoding()).strip()
          for l in stderr_file.readlines()
      ]
      return exit_code, stdout_lines, stderr_lines


def Rlocation(runfile_path):
  with open(GetEnv('RUNFILES_MANIFEST_FILE'), 'r') as f:
    for l in f:
      tokens = l.strip().split(' ')
      if len(tokens) == 2:
        if runfile_path == tokens[0]:
          return tokens[1]
  raise Error("could not find runfile '%s'" % runfile_path)


class TestBase(unittest.TestCase):

  def testFoo(self):
    exit_code, stdout_lines, stderr_lines = RunProgram(
        [Rlocation('laszlocsomor/examples/python/foo/foo_bin.exe')])
    self.assertEqual(exit_code, 0)
    self.assertEqual(stdout_lines, ['Hello!', '42', 'data: hello data'])


if __name__ == '__main__':
  unittest.main()

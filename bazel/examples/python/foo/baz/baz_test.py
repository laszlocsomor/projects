import locale
import os
import tempfile
import subprocess
import sys
import unittest


def GetEnv(name, default=None):
  value = os.getenv(name, '__undefined_envvar__')
  if value == '__undefined_envvar__':
    if default:
      return default
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
  """Returns the actual location (absolute path) of a runfile."""
  test_srcdir = GetEnv('TEST_SRCDIR')
  result = {}
  with open(os.path.join(test_srcdir, 'MANIFEST'), 'r') as f:
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
    if exit_code:
      self.fail("exit_code=%d, stdout=(\n%s)\n, stderr=(\n%s\n)" % (
        exit_code,
        '\n'.join(stdout_lines),
        '\n'.join(stderr_lines)))

if __name__ == '__main__':
  unittest.main()

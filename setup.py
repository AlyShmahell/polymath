import platform
import re
import shutil
import sys, os

from setuptools import Extension, setup
from setuptools.command.install import install
from subprocess import call

if sys.version_info < (3, 5):
    raise Exception('Only Python 3.5 and above are supported.')
    
with open('LICENSE', 'r') as legal:
    license = " ".join(line.strip() for line in legal)
    
class customInstallClass(install):
    def run(self):
        install.run(self)
        os.system("cmake ./")
        os.system("sudo cmake --build . --target install")
        os.system("rm -rf CMakeCache.txt install_manifest.txt Makefile CMakeFiles cmake_install.cmake")
    

setup(
    name='intf',
    author='Aly Shmahell',
    author_email='aly.shmahell@gmail.com',
    license=license,
    description="a multiple precision integer arithmetic C++ library.",
    url='https://github.com/AlyShmahell/intf',
    cmdclass={'install': customInstallClass}
)
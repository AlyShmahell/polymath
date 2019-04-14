import os

if __name__ == '__main__':
    os.system("cmake ./")
    os.system("sudo cmake --build . --target install")
    os.system("rm -rf CMakeCache.txt install_manifest.txt Makefile CMakeFiles cmake_install.cmake")
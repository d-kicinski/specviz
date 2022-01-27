import setuptools
from setuptools import Extension

extensions = []
libtensor = Extension(name="pyfft", sources=[])
extensions.append(libtensor)

setuptools.setup(
    ext_modules=extensions
)

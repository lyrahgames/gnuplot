./: lib{lyrahgames-gnuplot}: \
  lyrahgames/gnuplot/hxx{** -version} \
  lyrahgames/gnuplot/hxx{version}
{
  cxx.export.poptions = "-I$out_root" "-I$src_root"
}
cxx.poptions =+ "-I$out_root" "-I$src_root"

lyrahgames/gnuplot/
{
  hxx{version}: in{version} $src_root/manifest
  {
    dist = true
    clean = ($src_root != $out_root)
  }
}

hxx{**}: install.subdirs = true

./: tests/ manifest doc{README.md AUTHORS.md} legal{COPYING.md}
tests/: install = false